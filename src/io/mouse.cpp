#include "mouse.h"

double mouse::x = 0;
double mouse::y = 0;

double mouse::lastX = 0;
double mouse::lastY = 0;

double mouse::dx = 0;
double mouse::dy = 0;

double mouse::scrollDX = 0;
double mouse::scrollDY = 0;

//��. cursorPosCallback
bool mouse::firstMouse = true;

//��� ������� ����� ��������
bool mouse::buttons[GLFW_MOUSE_BUTTON_LAST] = { 0 };
//��������� ���
bool mouse::buttonsChanged[GLFW_MOUSE_BUTTON_LAST] = { 0 };

//��������� ������� ����� ������ 1 ����
void mouse::cursorPosCallback(GLFWwindow* window, double _x, double _y) { 
	x = _x;
	y = _y;

	if (firstMouse) {
		lastX = x;
		lastY = y;
		firstMouse = false;
	}

	dx = x - lastX;
	dy = lastY - y;
	lastX = x;
	lastY = y;
}
//���������� ����������
void mouse::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) { 
	if (action != GLFW_RELEASE) {
		if (!buttons[button]) {
			buttons[button] = true;
		}
	}
	else {
		buttons[button] = false;
	}
	buttonsChanged[button] = action != GLFW_REPEAT;
}
//���������� �������� �����, 1 - �� ������� ����������, 2 - ����������� ��������� (1 �����, -1 �����)
void mouse::mouseWheelCallback(GLFWwindow* window, double dx, double dy) {
	scrollDX = dx;
	scrollDY = dy;
}

double mouse::getMouseX() {
	return x;
}
double mouse::getMouseY() { 
	return y;
}

double mouse::getDX() {
	double _dx = dx;
	dx = 0;
	return _dx;
}
double mouse::getDY() {
	double _dy = dy;
	dy = 0;
	return _dy;
}

double mouse::getScrollDX() {
	double dx = scrollDX;
	scrollDX = 0;
	return dx;
}
double mouse::getScrollDY() { 
	double dy = scrollDY;
	scrollDY = 0;
	return dy;
}

bool mouse::button(int button) {
	return buttons[button];
}
bool mouse::buttonChanged(int button) { 
	bool ret = buttonsChanged[button];
	buttonsChanged[button] = false;
	return ret;
}
bool mouse::buttonWentUp(int button) { 
	return !buttons[button] && buttonChanged(button);
}
bool mouse::buttonWentDown(int button) {
	return buttons[button] && buttonChanged(button);
}