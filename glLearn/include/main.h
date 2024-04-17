#ifndef _MAIN_H_
#define _MAIN_H_
#include "game.h"

void press_close_window(GLFWwindow *window);
void frame_size_callback(GLFWwindow *window, int width, int height);
void keyboardInput(GLFWwindow *window);
void mouse_button_input(GLFWwindow *window);
void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);

#endif