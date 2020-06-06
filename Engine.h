#pragma once

#include<cstdlib>
extern "C" {
    #include<glad/glad.h>
}
#include<stdio.h> 
#include<iostream>
#include<fstream>
#include "Logic.h"

class Engine {
    public:

    Scene scene = Scene();
    Logic& logic;

    Engine(Logic& _logic);

    int runEngine();

    //dont call this

    private: 

    GLFWwindow* window;
    int width, height;
    unsigned int shaderProgram;
    unsigned int VBO;
    unsigned int VBO_C;
    unsigned int VAO;

    int initEngine();

    int stopEngine();

    static void error_callback(int error, const char* description)
    {
        fprintf(stderr, "Error: %s\n", description);
    }

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }  

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        Logic *logic = (Logic *)glfwGetWindowUserPointer(window);
        logic->keyCallback(window, key, scancode, action, mods);
    }

    void cleanup(GLFWwindow* window);

    unsigned int loadShaders();

    unsigned int makeVAO(unsigned int VBO, unsigned int VBO_C);

    GLFWwindow* loadGLFW();

    void render(GLFWwindow* window, int width, int height, unsigned int VAO, unsigned int shaderProgram);

    void _logic(unsigned int VAO, unsigned int VBO, unsigned int VBO_C, GLFWwindow* window);
};