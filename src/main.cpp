#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <chrono>

#include "Renderer/ShaderProgram.h"
#include "Resources/ResourceManager.h"
#include "Renderer/Texture2D.h"
#include "Renderer/Sprite.h"
#include "Renderer/AnimatedSprite.h"


glm::ivec2 g_windowSize(640, 480);


GLfloat point[] = {
    0.0f, 0.5f, 0.0f,
    50.f, -50.f, 0.0f, 
    -50.f, -50.f, 0.0f
};

GLfloat colors[] = {
    1.0f, 0.0f, 0.0f, 
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

GLfloat texCoord[] = {
    0.5f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f
};

/*
const char* vertex_shader =
"#version 460\n"
"layout(location = 0) in vec3 vertex_position;"
"layout(location = 1) in vec3 vertex_color;"
"out vec3 color;"
"void main() {"
"   color = vertex_color;"
"   gl_Position = vec4(vertex_position,1.0);"
"}";
 

const char* fragment_shader =
"#version 460\n"
"in vec3 color;"
"out vec4 frag_color;"
"void main() {"
"   frag_color = vec4(color, 1.0);"
"};";*/

bool isEagle = false;

void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height) {
    g_windowSize.x = width;
    g_windowSize.y = height;
    glViewport(0, 0, g_windowSize.x, g_windowSize.y);
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    } 
    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
        isEagle = !isEagle;
    }
}

int main(int argc, char** argv)
{ 
    
   // ResourceManager(argv[0]);

    /* Initialize the library */
    if (!glfwInit()) {
        std::cout << "glfwInit failed" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pWindow = glfwCreateWindow(g_windowSize.x, g_windowSize.y, "Battle City", nullptr, nullptr);
    if (!pWindow)
    {
        std::cout << "glfwCreateWindow failed!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);

    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);


    if (!gladLoadGL()) {
        std::cout << "Can't load GLAD!" << std::endl;
        return -1;
    }

    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "OpenGL " << GLVersion.major << "." << GLVersion.minor << std::endl;

    glClearColor(1, 1, 0, 1);
    {
        ResourceManager resourceManager(argv[0]);
        auto pDefaultShaderProgram = resourceManager.loadShaders("DefaultShader", "res\\shaders\\vertex.txt", "res\\shaders\\fragment.txt");
        if (!pDefaultShaderProgram) {
            std::cerr << "Can't create shader program: " << "DefaultShader" << std::endl;
            return -1;
        }

        auto pSpriteShaderProgram = resourceManager.loadShaders("SpriteShader", "res\\shaders\\vSprite.txt", "res\\shaders\\fSprite.txt");
        if (!pSpriteShaderProgram) {
            std::cerr << "Can't create shader program: " << "SpriteShader" << std::endl;
            return -1;
        }

        auto tex = resourceManager.loadTexture("DefaultTexture", "res\\textures\\map_16x16.png");

        std::vector<std::string> subTexturesNames = { "eagle",
                                                     "deadeagle",
                                                     "spark1",
                                                     "spark2",
                                                     "spark3",
                                                     "veryBigSpark" };

        auto pTextureAtlas = resourceManager.loadTextureAtlas("DefaultTextureAtlas", "res\\textures\\map_16x16.png", std::move(subTexturesNames), 16, 16);


        auto pSprite = resourceManager.loadSprite("NewSprite", "DefaultTextureAtlas", "SpriteShader", 100, 100, "eagle");
        pSprite->setPosition(glm::vec2(300, 100));


        auto pAnimatedSprite = resourceManager.loadAnimatedSprite("NewAnimatedSprite", "DefaultTextureAtlas", "SpriteShader", 100, 100, "eagle");
        pAnimatedSprite->setPosition(glm::vec2(300, 300));
        std::vector<std::pair<std::string, uint64_t>> eagleState;
        eagleState.emplace_back(std::make_pair<std::string, uint64_t>("eagle", 1000000000));
        eagleState.emplace_back(std::make_pair<std::string, uint64_t>("deadeagle", 1000000000));

        std::vector<std::pair<std::string, uint64_t>> sparkState;
        sparkState.emplace_back(std::make_pair<std::string, uint64_t>("spark1", 1000000000));
        sparkState.emplace_back(std::make_pair<std::string, uint64_t>("spark2", 1000000000));
        sparkState.emplace_back(std::make_pair<std::string, uint64_t>("spark3", 1000000000));


        pAnimatedSprite->insertState("eagleState", std::move(eagleState));
        pAnimatedSprite->insertState("sparkState", std::move(sparkState));

        pAnimatedSprite->setState("sparkState");
        //VBO

        GLuint points_vbo = 0;
        glGenBuffers(1, &points_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

        GLuint colors_vbo = 0;
        glGenBuffers(1, &colors_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

        GLuint texCoord_vbo = 0;
        glGenBuffers(1, &texCoord_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, texCoord_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord), texCoord, GL_STATIC_DRAW);

        //vertex array object
        GLuint vao = 0;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, texCoord_vbo);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        pDefaultShaderProgram->use();
        pDefaultShaderProgram->setInt("tex", 0);

        glm::mat4 modelMatrix_1 = glm::mat4(1.f);
        modelMatrix_1 = glm::translate(modelMatrix_1, glm::vec3(100.f, 200.f, 0.f));

        glm::mat4 modelMatrix_2 = glm::mat4(1.f);
        modelMatrix_2 = glm::translate(modelMatrix_2, glm::vec3(590.f, 200.f, 0.f));

        
        glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(g_windowSize.x), 0.f, static_cast<float>(g_windowSize.y), -100.f, 100.f);

        pDefaultShaderProgram->setMatrix4("projectionMat", projectionMatrix);


        pSpriteShaderProgram->use();
        pSpriteShaderProgram->setInt("tex", 0);
        pSpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);

        auto lastTime = std::chrono::high_resolution_clock::now();

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(pWindow))
        {
            if (isEagle) {
                pAnimatedSprite->setState("eagleState");
            }
            else {
                pAnimatedSprite->setState("sparkState");
            }
            auto currentTime = std::chrono::high_resolution_clock::now();
            uint64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();
            lastTime = currentTime;

            pAnimatedSprite->update(duration);
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            pDefaultShaderProgram->use();

            glBindVertexArray(vao);
            tex->bind();

            pDefaultShaderProgram->setMatrix4("modelMat", modelMatrix_1);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            pDefaultShaderProgram->setMatrix4("modelMat", modelMatrix_2);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            pSprite->render();
            pAnimatedSprite->render();
            /* Swap front and back buffers */
            glfwSwapBuffers(pWindow);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}
