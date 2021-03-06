#include "Engine.h"

Engine::Engine(Logic& _logic) : logic(_logic) {
    initEngine();
}

int Engine::runEngine() {
    logic.setup(scene);
    glClearColor(1, 0, 0, 1);
    //run app
    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        _logic(VAO, VBO, VBO_C, window);

        render(window, width, height, VAO, shaderProgram);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return stopEngine();
}

int Engine::initEngine() {
    //load GLFW
    window = loadGLFW();

    glfwSetKeyCallback(window, key_callback);

    //check if GLFW was loaded
    if(window == nullptr) {
        return 1;
    }

    //load GLAD
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return 1;
    }

    //set framebuffer settings for glfw
    glfwGetFramebufferSize(window, &width, &height);
    glfwSwapInterval(1);

    //set viewport
    glViewport(0, 0, width, height);

    //get shaders, VBO, and VAO
    shaderProgram = loadShaders();

    glGenBuffers(1, &VBO);

    glGenBuffers(1, &VBO_C);

    VAO = makeVAO(VBO, VBO_C); 

    glfwSetWindowUserPointer(window, (void *)&logic);

    return 0;
}

int Engine::stopEngine() {
    //cleanup
    cleanup(window);
    return 0;
}

void Engine::cleanup(GLFWwindow* window) {
    glfwDestroyWindow(window);
    glfwTerminate();
}

unsigned int Engine::loadShaders() {
    std::string vertexSrc = "";
    std::string fragmentSrc = "";

    std::ifstream infile;
    infile.open("assets/vertexshader.txt");
    while(!infile.eof()) {
        std::string tsrc = "";
        std::getline(infile, tsrc);
        vertexSrc = vertexSrc + tsrc + "\n";
    }
    infile.close();

    infile.open("assets/fragmentshader.txt");
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

unsigned int Engine::makeVAO(unsigned int VBO, unsigned int VBO_C) {
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);  

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    return VAO;
}

GLFWwindow* Engine::loadGLFW() {
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

void Engine::render(GLFWwindow* window, int width, int height, unsigned int VAO, unsigned int shaderProgram) {
    glUseProgram(shaderProgram);  
    glDrawArrays(GL_TRIANGLES, 0, scene.getRenderVertices().size());
}

void Engine::_logic(unsigned int VAO, unsigned int VBO, unsigned int VBO_C, GLFWwindow* window) {

    logic.doLogicTick(scene, window);
    glBindVertexArray(VAO);
    float array [scene.getRenderVertices().size()];
    for(int i=0; i<scene.getRenderVertices().size(); ++i) {
        array[i] = scene.getRenderVertices()[i];
    }

    glBindBuffer(GL_VERTEX_ARRAY, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);  

    glBufferData(GL_ARRAY_BUFFER, sizeof(array), array, GL_STATIC_DRAW);
    
}