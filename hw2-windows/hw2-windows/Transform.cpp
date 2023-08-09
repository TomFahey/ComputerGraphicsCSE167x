// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"
#include <glm/gtx/string_cast.hpp>
#include <iostream>

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis) 
{
    // YOUR CODE FOR HW2 HERE
    // Please implement this.  Likely the same as in HW 1.  
    float radians = glm::radians(degrees);
    vec3 axisnorm = glm::normalize(axis);
    mat3 aDotA = mat3(axisnorm.x * axisnorm, axisnorm.y * axisnorm, axisnorm.z * axisnorm);
    mat3 aStar = mat3(vec3(0, axisnorm.z, -axisnorm.y), vec3(-axisnorm.z, 0, axisnorm.x), vec3(axisnorm.y, -axisnorm.x, 0));
    mat3 result = mat3(1) * glm::cos(radians) + aDotA * (1 - glm::cos(radians)) + aStar * glm::sin(radians);
    return result;
}

void Transform::left(float degrees, vec3& eye, vec3& up) 
{
    // YOUR CODE FOR HW2 HERE
    // Likely the same as in HW 1.  
    //std::cout << "Initial: \tEye: " << glm::to_string(eye) << ", Up: " << glm::to_string(up) << std::endl;
    mat3 R = rotate(degrees, up);
    vec3 result = R * eye;
    eye = result;
    //std::cout << "Modified: \tEye: " << glm::to_string(eye) << ", Up: " << glm::to_string(up) << std::endl;
}

void Transform::up(float degrees, vec3& eye, vec3& up) 
{
    // YOUR CODE FOR HW2 HERE 
    // Likely the same as in HW 1.  
    //std::cout << "Initial: \tEye: " << glm::to_string(eye) << ", Up: " << glm::to_string(up) << std::endl;
    vec3 rotAxis = glm::normalize(glm::cross(up, eye));
    mat3 R = rotate(-degrees, rotAxis);
    vec3 result = R * eye;
    eye = result;
    up = glm::normalize(glm::cross(eye, rotAxis));
    //std::cout << "Modified: \tEye: " << glm::to_string(eye) << ", Up: " << glm::to_string(up) << std::endl;
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) 
{
    // YOUR CODE FOR HW2 HERE
    // Likely the same as in HW 1.  
    vec3 w = glm::normalize(eye);
    vec3 u = glm::normalize(glm::cross(up, eye));
    vec3 v = glm::normalize(glm::cross(w, u));
    mat4 result, rotate, translate;
    rotate[0] = vec4(u, 0);
    rotate[1] = vec4(v, 0);
    rotate[2] = vec4(w, 0);
    rotate[3] = vec4(0, 0, 0, 1);
    rotate = glm::transpose(rotate);
    translate[0] = vec4(1, 0, 0, -eye.x);
    translate[1] = vec4(0, 1, 0, -eye.y);
    translate[2] = vec4(0, 0, 1, -eye.z);
    translate[3] = vec4(0, 0, 0, 1);
    translate = glm::transpose(translate);
    result = rotate * translate;
    return result;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
    mat4 ret;
    // YOUR CODE FOR HW2 HERE
    // New, to implement the perspective transform as well.  
    float halfTheta = glm::radians(fovy/2);
    float right, top, near, far;
    top = glm::tan(halfTheta);
    right = aspect * top;
    near = zNear;
    far = zFar;
    mat4 projMatrix;
    projMatrix[0] = vec4(1 / right, 0, 0, 0);
    projMatrix[1] = vec4(0, 1 / top, 0, 0);
    projMatrix[2] = vec4(0, 0, -(far + near)/(far - near), -1);
    projMatrix[3] = vec4(0, 0, -(2*far*near)/(far - near), 0);
    std::cout << glm::to_string(projMatrix) << std::endl;
    ret = projMatrix;
    return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
    mat4 ret;
    // YOUR CODE FOR HW2 HERE
    // Implement scaling 
    ret = mat4(1.0f);
    ret[0] *= sx;
    ret[1] *= sy;
    ret[2] *= sz;
    return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
    mat4 ret;
    // YOUR CODE FOR HW2 HERE
    // Implement translation 
    ret = mat4(1.0f);
    ret[3] = vec4(tx, ty, tz, 1);
    return ret;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
    vec3 x = glm::cross(up,zvec); 
    vec3 y = glm::cross(zvec,x); 
    vec3 ret = glm::normalize(y); 
    return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
