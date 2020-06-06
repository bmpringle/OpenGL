#pragma once

#include "Scene.h"
#include <random>
#include<GLFW/glfw3.h>

class Logic {
    public:
        virtual void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;

        virtual Scene setup(Scene scene) = 0;

        virtual Scene doLogicTick(Scene scene, GLFWwindow* window) = 0;
};