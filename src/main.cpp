#include "io/screen.h"
#include "io/settings_camera.h"
#include "io/keyboard.h"

#include "graphics/rendering/shader.h"
#include "graphics/models/cube.hpp"

#ifndef VECTOR
#include <vector>
#endif

#ifndef CREATURE_H
#include "simulation/Creature.h"
#endif


int main() 
{

	float mixVal = 0.5f;
	screen Screen;
	settings_camera user(camera({ 0.0f, 0.0f, 0.0f }));
	glfwInit();
	screen::OpenGL_version();
	if (!Screen.init()) {
		std::cout << "Could not open window" << std::endl;
		glfwTerminate();
		return -1;
	}
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}
	Screen.setParameters();

	// SHADERS===============================
	Shader shader("assets/object.vs", "assets/object.fs");

	// MODELS==============================
	cube Cube(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.75f));
	Cube.init();

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// CREATURES
	int simulationX = 100;
	int simulationY = 100;

	std::vector<Creature> herbivore;
	std::vector<Creature> carnivore;

	herbivore.push_back(Creature(10, 50, 0, 0, 0, 3, 0, 24, 1, 1.0f));
	carnivore.push_back(Creature(40, 50, 0, 0, 0, 0.5f, 0, 24, 1, 0.8f));

	while (!Screen.shouldClose()) {
		// simulation
		

		// calculate dt
		double currentTime = glfwGetTime();
		user.dt = currentTime - user.lastTime;
		user.lastTime = currentTime;
		if (keyboard::key(GLFW_KEY_ESCAPE)) {
			Screen.setShouldClose(true);
		}
		// change mix value
		if (keyboard::key(GLFW_KEY_Q)) {
			mixVal += .05f;
			if (mixVal > 1) {
				mixVal = 1.0f;
			}
		}
		if (keyboard::key(GLFW_KEY_E)) {
			mixVal -= .05f;
			if (mixVal < 0) {
				mixVal = 0.0f;
			}
		}

		// process input
		user.input_keyboard();
		user.input_mouse();

		// render
		Screen.update();

		// draw shapes
		shader.activate();

		shader.setFloat("mixVal", mixVal);

		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// create transformation
		
		view = user.getVeiwMatrix();
		projection = glm::perspective(glm::radians(user.zoom), (float)screen::SCR_WIDTH / (float)screen::SCR_HEIGHT, 0.1f, 100.0f);

		shader.setMat4("view", view);
		shader.setMat4("projection", projection);

		Cube.render(shader);

		// send new frame to window
		Screen.newFrame();
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}