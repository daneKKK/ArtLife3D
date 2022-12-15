#include "io/screen.h"
#include "io/settings_camera.h"
#include "io/keyboard.h"

#include "graphics/rendering/shader.h"
#include "graphics/models/cube.hpp"


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
	shader Shader("assets/object.vs", "assets/object.fs");
	
	// MODELS==============================
	cube Cube0(glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.75f));
	Cube0.init();

	cube Cube1(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.75f));
	Cube1.init();

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	while (!Screen.shouldClose()) {
		// calculate dt
		double currentTime = glfwGetTime();
		user.dt = currentTime - user.lastTime;
		user.lastTime = currentTime;

		if (keyboard::key(GLFW_KEY_ESCAPE)) {
			Screen.setShouldClose(true);
		}
		// change mix value
		if (keyboard::key(GLFW_KEY_Q)) {
			mixVal += 0.5f * user.dt;
			if (mixVal > 1) {
				mixVal = 1.0f;
			}
		}
		if (keyboard::key(GLFW_KEY_E)) {
			mixVal -= 0.5f * user.dt;
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
		Shader.activate();

		Shader.setFloat("mixVal", mixVal);

		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 36);

		// create transformation
		
		view = user.getVeiwMatrix();
		//http://www.songho.ca/opengl/gl_projectionmatrix.html
		projection = glm::perspective(glm::radians(user.zoom), (float)screen::SCR_WIDTH / (float)screen::SCR_HEIGHT, 0.1f, 100.0f);

		Shader.setMat4("view", view);
		Shader.setMat4("projection", projection);

		Cube0.render(Shader, {1.0f, 1.0f, 1.0f});
		Cube1.render(Shader, {-1.0f, 1.0f, 0.0f});

		// send new frame to window
		Screen.newFrame();
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}