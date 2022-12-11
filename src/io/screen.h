#ifndef SCREEN_H
#define SCREEN_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class screen {
private:
	GLFWwindow* window;

public:
	static unsigned int SCR_WIDTH;
	static unsigned int SCR_HEIGHT;

	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

	screen();

	bool init();

	static void OpenGL_version();

	void setParameters();

	// main loop
	void update();
	void newFrame();

	// window closing
	bool shouldClose();
	void setShouldClose(bool shouldClose);

};

#endif //SCREEN_H