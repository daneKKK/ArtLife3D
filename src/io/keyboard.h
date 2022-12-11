#ifndef KEYBOARD_H
#define KEYBOARD_H

#define GLFW_INCLUDE_NONE
#include <glad/glad.h> //БEьBБEзычный загрузчиБE
#include <GLFW/glfw3.h>

class keyboard
{
private:
	static bool keys[];
	static bool keysChanged[];

public:
	//key start callback
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	/*
		accessors
	*/

	static bool key(int key);
	static bool keyChanged(int key);
	static bool keyWentUp(int key);
	static bool keyWentDown(int key);
};

#endif //KEYBOARD_H

