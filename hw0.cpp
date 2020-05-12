#include<cstdlib>
extern "C" {
    #include<glad/glad.h>
}
#include<GLFW/glfw3.h>
#include<stdio.h> 
#include<iostream>
#include<fstream>
#include "Scene.cpp"

static Scene scene = Scene();

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

void cleanup(GLFWwindow* window) {
    glfwDestroyWindow(window);
    glfwTerminate();
}

unsigned int loadShaders() {
    std::string vertexSrc = "";
    std::string fragmentSrc = "";

    std::ifstream infile;
    infile.open("vertexshader.txt");
    while(!infile.eof()) {
        std::string tsrc = "";
        std::getline(infile, tsrc);
        vertexSrc = vertexSrc + tsrc + "\n";
    }
    infile.close();

    infile.open("fragmentshader.txt");
    while(!infile.eof()) {
        std::string tsrc = "";
        std::getline(infile, tsrc);
        fragmentSrc = fragmentSrc + tsrc  + "\n";
    }
    infile.close();

    const char *vertexSource = vertexSrc.c_str();
    const char *fragmentSource = fragmentSrc.c_str();

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader); 
    return shaderProgram;
}

unsigned int makeVAO(unsigned int VBO) {
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);  

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  

    return VAO;
}

GLFWwindow* loadGLFW() {
    if (!glfwInit()) {
        return nullptr;
    }
    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL Engine", NULL, NULL);
    if (!window) {
        return nullptr;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

    glfwMakeContextCurrent(window);
    return window;
}

void render(GLFWwindow* window, int width, int height, unsigned int VAO, unsigned int shaderProgram) {
    glUseProgram(shaderProgram);  
    glDrawArrays(GL_TRIANGLES, 0, scene.root_node.getVertices().size());
}

void logic(unsigned int VAO) {
    glBindVertexArray(VAO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(scene.root_node.getVertices()), scene.root_node.getVertices().data(), GL_STATIC_DRAW);
}

int main() {

    //load GLFW
    GLFWwindow* window = loadGLFW();

    //check if GLFW was loaded
    if(window == nullptr) {
        return 1;
    }

    //load GLAD
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return 1;
    }

    //set framebuffer settings for glfw
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glfwSwapInterval(1);

    //set viewport
    glViewport(0, 0, width, height);

    //get shaders, VBO, and VAO
    unsigned int shaderProgram = loadShaders();

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int VAO = makeVAO(VBO); 

    //set scene
    std::vector<float> vertices_vector = std::vector<float>();
    vertices_vector.push_back(-0.5f), vertices_vector.push_back(-0.5f), vertices_vector.push_back(0.0f),
    vertices_vector.push_back(0.5f), vertices_vector.push_back(-0.5f), vertices_vector.push_back(0.0f),
    vertices_vector.push_back(0.0f),  vertices_vector.push_back(0.5f), vertices_vector.push_back(0.0f);
    scene.root_node.children.push_back(Node("triangle1", vertices_vector, std::vector<Node>()));

    //run app
    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        logic(VAO);
        render(window, width, height, VAO, shaderProgram);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    //cleanup
    cleanup(window);
    return 0;
}

