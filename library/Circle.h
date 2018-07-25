//
// Created by wujiaxin1 on 2018/7/25.
//

#ifndef EARTHDEMO_CIRCLE_H
#define EARTHDEMO_CIRCLE_H

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLUtils/GLUtils.h>
using namespace glm;
using namespace std;
class Circle {
public:
    float x;
    float y;
    float z;
    float radius;
    float degreeStep;
    Circle(float x, float y, float z, float radius,float degreeStep);

    void draw(int program);

private:
    unsigned VAO,VBO;
    int pointNum;
    void setup();

};

Circle::Circle(float x, float y, float z, float radius,float degreeStep) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->radius = radius;
    this->degreeStep=degreeStep;
    setup();
}

void Circle::draw(int program) {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
    glUseProgram(program);
    glBindVertexArray(VAO);
//    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glDrawArrays(GL_TRIANGLE_FAN,0, pointNum);
}

void Circle::setup() {
    pointNum = static_cast<const int>(360 / degreeStep + 2);
    float data[pointNum * 3];
    data[0]=this->x;
    data[1]=this->y;
    data[2]=this->z;
    for (int i = 1; i < pointNum; i++) {
       float degree=degreeStep*(i-1);
       data[i*3]=radius*cos(radians(degree));
       data[i*3+1]=radius*sin(radians(degree));
       data[i*3+2]=this->z;
    }
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data),data,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3* sizeof(float),0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}


#endif //EARTHDEMO_CIRCLE_H
