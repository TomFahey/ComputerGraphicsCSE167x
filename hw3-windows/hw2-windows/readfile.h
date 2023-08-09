#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#include <GL/glew.h>
#include <GL/glut.h>

#include "primitive.h"
#include "light.h"

vec3 eye;
vec3 center;
vec3 up;

int res_x, res_y;
float fovy, fovx;

std::vector<vec3> vertices;
std::vector<Light> lights;
std::stack<mat4> transfstack;

extern AggregatePrimitive scenePrimitive;

// Material properties
vec3 ambient;
vec3 diffuse;
vec3 emission;
vec3 shininess;
vec3 specular;

// Image properties
int imgWidth;
int imgHeight;

// Camera properties
vec3 eye;
vec3 center;
vec3 up;
//float fovy;



void matransform (stack<mat4> &transfstack, GLfloat* values);
void rightmultiply (const mat4 & M, stack<mat4> &transfstack);
bool readvals (stringstream &s, const int numvals, GLfloat * values);
void readfile (const char * filename);
