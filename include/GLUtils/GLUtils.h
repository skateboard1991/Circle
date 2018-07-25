//
// Created by wujiaxin1 on 2018/6/22.
//
#include <GL/glew.h>
#include <cstring>
#include <iostream>
#ifndef CLIONPROJECTS_GLUTILS_H
#define CLIONPROJECTS_GLUTILS_H
using namespace std;
namespace glutils{
    int loadShader(string filePath,int type);
    int linkProgram(int vertexShader,int fragShader);
    int loadProgram(string vertexPath,string fragPath);
    void setMatrix4fv(int program, string name, float *value);
    void setUniform4f(int program,string name,float v0,float v1,float v2,float v3);
}
#endif //CLIONPROJECTS_GLUTILS_H
