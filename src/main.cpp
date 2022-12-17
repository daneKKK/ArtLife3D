#include "io/screen.h"
#include "io/settings_camera.h"
#include "io/keyboard.h"

#include "graphics/rendering/shader.h"
#include "graphics/models/cube.hpp"

#include "simulation/Simulation.h"

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
	
	//задай колличество кубов===========================
	/*cube MultyCube[1000];
	for (int i = 0; i < 1000; i++) {
		MultyCube[i].init();
	}*/
	Simulation sim(40.0f, 40.0f, 0.0f);
	//==================================================

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

		// process input
		user.input_keyboard();
		user.input_mouse();

		// render
		Screen.update();

		// draw shapes
		Shader.activate();

		Shader.setFloat("mixVal", mixVal);

		// create transformation

		view = user.getVeiwMatrix();
		//http://www.songho.ca/opengl/gl_projectionmatrix.html
		projection = glm::perspective(glm::radians(user.zoom), (float)screen::SCR_WIDTH / (float)screen::SCR_HEIGHT, 0.1f, 100.0f);

		Shader.setMat4("view", view);
		Shader.setMat4("projection", projection);

		//подставь параметры сюда!===============================
		sim.step(currentTime, Shader);
		/*for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				for (int k = 0; k < 10; k++) {
					MultyCube[100 * i + 10 * j + k].render(Shader,
						{ 10 * i, 10 * j, 10 * k }, //позиция куба x, y, z
						{ 0.1f * i, 0.1f * j, 0.1f * k, 0.0f }); //цвет куба меняется от 0 до 1, первые 3 параметра r,g,b, последний всунь по умолчанию 0
				}
			} 
		}*/
		//=======================================================

		// send new frame to window
		Screen.newFrame();
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
