#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "library/Circle.h"

using namespace std;
using namespace glm;

void windowSizeChangeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0,0,width,height);
}


void drawCircle(Circle circle,float scale,mat4 modelMatrix,int program,vec4 color)
{
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glutils::setUniform4f(program,"color",color.r,color.g,color.b,color.a);
    for(int i=0;i<36;i++)
    {
        modelMatrix=mat4(1.0f);
        modelMatrix=glm::scale(modelMatrix,vec3(scale,scale,scale));
        modelMatrix=rotate(modelMatrix,radians(10.0f*i),vec3(0.0,1.0,0.0));
        glutils::setMatrix4fv(program,"model",&modelMatrix[0][0]);
        circle.draw(program);
        modelMatrix=mat4(1.0f);
        modelMatrix=glm::scale(modelMatrix,vec3(scale,scale,scale));
        modelMatrix=rotate(modelMatrix,radians(10.0f*i),vec3(1.0,0.0,0.0));
        glutils::setMatrix4fv(program,"model",&modelMatrix[0][0]);
        circle.draw(program);
    }
}


int main() {

    if (!glfwInit()) {
        cout << "glfw init failed" << endl;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(800, 800, "earthdemo", nullptr, nullptr);
    if (!window) {
        cout << "create window failed" << endl;
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);
    glewInit();
    glfwSetFramebufferSizeCallback(window, windowSizeChangeCallback);
    Circle circle(0.0f, 0.0f, 0.0f, 1.0f,10.0f);
    glm::mat4 modelMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 projectionsMatrix;
    int program = glutils::loadProgram("circle_ver.slgl", "circle_fragment.slgl");

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        modelMatrix = glm::mat4(1.0f);
        viewMatrix = glm::mat4(1.0f);
        projectionsMatrix = glm::mat4(1.0f);
        viewMatrix = glm::lookAt(vec3(0.0f, 0.0f, 3.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
        projectionsMatrix = perspective(radians(45.0f), (float) 800 / (float) 800, 0.1f, 100.0f);
        glutils::setMatrix4fv(program,"view",&viewMatrix[0][0]);
        glutils::setMatrix4fv(program,"projection",&projectionsMatrix[0][0]);
        drawCircle(circle,0.5f,modelMatrix,program,vec4(1.0f,1.0f,1.0f,1.0f));
        drawCircle(circle,1.0f,modelMatrix,program,vec4(0.0f,0.0f,1.0f,0.5f));
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}