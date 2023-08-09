// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

Transform::Transform() : m(mat4(1)), mInv(mat4(1)) {}

Transform::Transform(const float mat[4][4]) :
    m(mat4(mat[0][0], mat[1][0], mat[2][0], mat[3][0],
        mat[0][1], mat[1][1], mat[2][1], mat[3][1],
        mat[0][2], mat[1][2], mat[2][2], mat[3][2],
        mat[0][3], mat[1][3], mat[2][3], mat[3][3])),
    mInv(Invert(m)) {}

Transform::Transform(const mat4& mat) : m(mat), mInv(Invert(mat)) {}

Transform::Transform(const mat4 &mat, const mat4 &matInv) : m(mat), mInv(matInv) {};

bool Transform::isIdentity(mat4 M) {
    mat4 I = mat4(1);
	bool isIdentity = glm::all(glm::equal(M[0], I[0])) && glm::all(glm::equal(M[1], I[1])) &&
		glm::all(glm::equal(M[2], I[2])) && glm::all(glm::equal(M[3], I[3]));
    return isIdentity;
}

bool Transform::isIdentity() {
    bool identity = m[0][0] && !m[0][1] && !m[0][2] && !m[0][3]
        && !m[1][0] && m[1][1] && !m[1][2] && !m[1][3]
        && !m[2][0] && !m[2][1] && m[2][2] && !m[2][3]
        && !m[3][0] && !m[3][1] && !m[3][2] && m[3][3];
    return identity;
}
mat4 Transform::Invert(const mat4 mat) {
    if (isIdentity(mat)) return mat;
    float determinant = glm::determinant(mat);
    mat4 adjMatrix;
    int indices[3] = { 1,2,3};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::valarray<int> iSub(indices, 3);
            iSub = (iSub.cshift(-i) + i) % 4;
            std::valarray<int> jSub(indices, 3);
            jSub = (jSub.cshift(-j) + j) % 4;
            mat3 subMatrix = mat3(mat[iSub[0]][jSub[0]], mat[iSub[1]][jSub[0]], mat[iSub[2]][jSub[0]],
                mat[iSub[0]][jSub[1]], mat[iSub[1]][jSub[1]], mat[iSub[2]][jSub[1]],
                mat[iSub[0]][jSub[2]], mat[iSub[1]][jSub[2]], mat[iSub[2]][jSub[2]]);
            adjMatrix[j][i] = pow(-1, (i + j)) * glm::determinant(subMatrix);
        }
    }
    return (1.0f / determinant) * adjMatrix;
}

mat3 Transform::InvertMat3(const mat3 mat) {
    float determinant = glm::determinant(mat);
    mat3 adjMatrix;
    int indices[2] = { 1,2 };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::valarray<int> iSub(indices, 2);
            iSub = (iSub.cshift(-i) + i) % 3;
            std::valarray<int> jSub(indices, 2);
            jSub = (jSub.cshift(-j) + j) % 3;
            glm::mat2 subMatrix = glm::mat2(mat[iSub[0]][jSub[0]], mat[iSub[1]][jSub[0]],
                mat[iSub[0]][jSub[1]], mat[iSub[1]][jSub[1]]);
            adjMatrix[j][i] = pow(-1, (i + j)) * glm::determinant(subMatrix);
        }
    }
    return (1.0f / determinant) * adjMatrix;
}

Transform Transform::Translate(const vec3 &T) 
{
    mat4 ret;
    ret = mat4(1.0f);
    ret[3] = vec4(T, 1);
    return Transform(ret);
}

Transform Transform::Scale(const vec3 &T) 
{
    mat4 ret;
    ret = mat4(1.0f);
    ret[0] *= T.x;
    ret[1] *= T.y;
    ret[2] *= T.z;
    return Transform(ret);
}

Transform Transform::Rotate(const float degrees, const vec3& axis) 
{
    float radians = glm::radians(degrees);
    vec3 axisnorm = glm::normalize(axis);
    mat3 aDotA = mat3(axisnorm.x * axisnorm, axisnorm.y * axisnorm, axisnorm.z * axisnorm);
    mat3 aStar = mat3(vec3(0, axisnorm.z, -axisnorm.y), vec3(-axisnorm.z, 0, axisnorm.x), vec3(axisnorm.y, -axisnorm.x, 0));
    mat3 result = mat3(1) * glm::cos(radians) + aDotA * (1 - glm::cos(radians)) + aStar * glm::sin(radians);
    return Transform(mat4(result));
}

Transform Transform::LookAt(const vec3 &eye, const vec3 &center, const vec3 &up) 
{
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
    return Transform(result);
}

Bounds Transform::operator()(const Bounds& b) const {
    vec3 pMin = vec3(maxNum);
	vec3 pMax = vec3(-maxNum);
	for (int i = 0; i < 8; i++) {
		vec4 transformedVertex = m * vec4(b.Vertex(i),1);
		pMin.x = (transformedVertex.x < pMin.x) ? transformedVertex.x : pMin.x;
		pMin.y = (transformedVertex.y < pMin.y) ? transformedVertex.y : pMin.y;
		pMin.z = (transformedVertex.z < pMin.z) ? transformedVertex.z : pMin.z;
		pMax.x = (transformedVertex.x > pMax.x) ? transformedVertex.x : pMax.x;
		pMax.y = (transformedVertex.y > pMax.y) ? transformedVertex.y : pMax.y;
		pMax.z = (transformedVertex.z > pMax.z) ? transformedVertex.z : pMax.z;
	}
    return Bounds(pMin, pMax);
}

Bounds Transform::operator()(Bounds b) {
    vec3 pMin = vec3(maxNum);
	vec3 pMax = vec3(-maxNum);
	for (int i = 0; i < 8; i++) {
		vec4 transformedVertex = m * vec4(b.Vertex(i),1);
		pMin.x = (transformedVertex.x < pMin.x) ? transformedVertex.x : pMin.x;
		pMin.y = (transformedVertex.y < pMin.y) ? transformedVertex.y : pMin.y;
		pMin.z = (transformedVertex.z < pMin.z) ? transformedVertex.z : pMin.z;
		pMax.x = (transformedVertex.x > pMax.x) ? transformedVertex.x : pMax.x;
		pMax.y = (transformedVertex.y > pMax.y) ? transformedVertex.y : pMax.y;
		pMax.z = (transformedVertex.z > pMax.z) ? transformedVertex.z : pMax.z;
	}
    return Bounds(pMin, pMax);
}

Ray Transform::operator()(const Ray& ray) {
    vec4 o = vec4(ray.point, 1), d = vec4(ray.dir, 0);
    o = m * o;
    d = glm::normalize(m * d);
    return Ray(vec3(o), vec3(d));

}

vec3 Transform::operator()(const vec3& v) {
    vec4 x = vec4(v, 1);
    vec4 y = m * x;
    return vec3(y[0], y[1], y[2]);
}
