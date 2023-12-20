#ifndef UTILS_H
#define UTILS_H

#define PI 3.141592653589
#define DEG2RAD PI/180.0
#define RAD2DEG 180.0/PI
#define FRONT 4
#define BACK 5
#define LEFT 0
#define RIGHT 1
#define TOP 2
#define BOTTOM 3

#include "GLee.h"
#include "vectors.h"

#include <QOpenGLFunctions>

#include <cmath>
#include <algorithm>
#include <map>
#include <queue>
#include <cstring>
#include <vector>

#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <GL/freeglut.h>


GLdouble *setIdentity();
/*
GLfloat *lookAt(Vector3 eye, Vector3 look, Vector3 up);

void lookAt(Vector3 eye, Vector3 look, Vector3 up, GLfloat res[16]);

GLfloat* rotateX(float angle);

void rotateX(float angle, GLfloat res[16]);

GLfloat* rotateY(float angle);

void rotateY(float angle, GLfloat res[16]);

GLfloat* rotateZ(float angle);

void rotateZ(float angle, GLfloat res[16]);

GLfloat* rotate(float angle, Vector3 Axis);

void rotate(float angle, Vector3 Axis, GLfloat res[16]);
*/
GLfloat* perspective(float fovy, float aspect, float zNear, float zFar);

GLfloat* ortho(float left, float right, float bottom, float top, float zNear, float zFar);

void setupMaterial(float ambient[], float diffuse[], float specular[], float shininess);

void matrixMul(GLfloat a[4][4], GLfloat b[4][4], GLfloat c[4][4]);

void matrixMul(GLfloat a[4][4], GLfloat b[4], GLfloat c[4]);

void transposeMatrix(GLfloat m[], GLfloat b[4][4]);

GLfloat* multiply(GLfloat* left, GLfloat* right, bool res2left);

GLfloat* multiply(GLfloat* left, GLfloat* right);

void pickMatrix(float x, float y, float deltax, float deltay, GLint viewport[4]);

float angle2Vecs(Vector3 v0, Vector3 v1);

Vector3 windowToSphere(Vector3 point, int width, int height);

Vector3 mapToSphere(Vector3 pNDC);

void windowToWorldCoords(int x, int y, GLdouble model[], GLdouble proj[], GLint viewport[], GLfloat *v);

std::string findKey(std::map<std::string, int>& map, int value);

#endif // UTILS_H

