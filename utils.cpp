#include "utils.h"

GLdouble *setIdentity()
{
    GLdouble *m = new GLdouble[16];

    m[0] = 1;  m[4] = 0; m[8] = 0;   m[12] = 0;
    m[1] = 0;  m[5] = 1; m[9] = 0;  m[13] = 0;
    m[2] = 0;  m[6] = 0; m[10] = 1;  m[14] = 0;
    m[3] = 0;  m[7] = 0; m[11] = 0;  m[15] = 1;

    return m;
}

GLfloat *lookAt(Vector3 eye, Vector3 look, Vector3 up)
{
    GLfloat *view = new GLfloat[16];
    Vector3 n, u, v, d;

    n.set(eye.x - look.x, eye.y - look.y, eye.z - look.z);
    u = up.cross(n);
    v = n.cross(u);

    n.normalized();
    u.normalized();
    v.normalized();

    d.set(-eye.dot(u), -eye.dot(v), -eye.dot(n));

    view[0] = u.x; view[1] = v.x; view[2] = n.x; view[3] = 0;
    view[4] = u.y; view[5] = v.y; view[6] = n.y; view[7] = 0;
    view[8] = u.z; view[9] = v.z; view[10] = n.z; view[11] = 0;
    view[12] = d.x; view[13] = d.y; view[14] = d.z; view[15] = 1;

    return view;
}

void lookAt(Vector3 eye, Vector3 look, Vector3 up, GLfloat res[16])
{
    Vector3 n, u, v, d;

    n.set(eye.x - look.x, eye.y - look.y, eye.z - look.z);
    u = up.cross(n);
    v = n.cross(u);

    n.normalized();
    u.normalized();
    v.normalized();

    d.set(-eye.dot(u), -eye.dot(v), -eye.dot(n));

    res[0] = u.x; res[1] = v.x; res[2] = n.x; res[3] = 0;
    res[4] = u.y; res[5] = v.y; res[6] = n.y; res[7] = 0;
    res[8] = u.z; res[9] = v.z; res[10] = n.z; res[11] = 0;
    res[12] = d.x; res[13] = d.y; res[14] = d.z; res[15] = 1;
}

GLfloat* rotateX(GLfloat angle)
{
    GLfloat c = cos(angle * DEG2RAD);
    GLfloat s = sin(angle * DEG2RAD);

    GLfloat *m = new GLfloat[16];

    m[0] = 1;  m[4] = 0; m[8] = 0;   m[12] = 0;
    m[1] = 0;  m[5] = c; m[9] = -s;  m[13] = 0;
    m[2] = 0;  m[6] = s; m[10] = c;  m[14] = 0;
    m[3] = 0;  m[7] = 0; m[11] = 0;  m[15] = 1;

    return m;
}

void rotateX(GLfloat angle, GLfloat res[16])
{
    GLfloat c = cos(angle * DEG2RAD);
    GLfloat s = sin(angle * DEG2RAD);

    res[0] = 1;  res[4] = 0; res[8] = 0;   res[12] = 0;
    res[1] = 0;  res[5] = c; res[9] = -s;  res[13] = 0;
    res[2] = 0;  res[6] = s; res[10] = c;  res[14] = 0;
    res[3] = 0;  res[7] = 0; res[11] = 0;  res[15] = 1;
}

GLfloat *rotateY(GLfloat angle)
{
    GLfloat c = cos(angle * DEG2RAD);
    GLfloat s = sin(angle * DEG2RAD);

    GLfloat* m = new GLfloat[16];

    m[0] = c;  m[4] = 0; m[8] = s;  m[12] = 0;
    m[1] = 0;  m[5] = 1; m[9] = 0;  m[13] = 0;
    m[2] = -s; m[6] = 0; m[10] = c; m[14] = 0;
    m[3] = 0;  m[7] = 0; m[11] = 0; m[15] = 1;

    return m;
}

void rotateY(GLfloat angle, GLfloat res[16])
{
    GLfloat c = cos(angle * DEG2RAD);
    GLfloat s = sin(angle * DEG2RAD);

    res[0] = c;  res[4] = 0; res[8] = s;  res[12] = 0;
    res[1] = 0;  res[5] = 1; res[9] = 0;  res[13] = 0;
    res[2] = -s; res[6] = 0; res[10] = c; res[14] = 0;
    res[3] = 0;  res[7] = 0; res[11] = 0; res[15] = 1;
}

GLfloat* rotateZ(float angle)
{
    GLfloat c = cos(angle * DEG2RAD);
    GLfloat s = sin(angle * DEG2RAD);

    GLfloat *m = new GLfloat[16];

    m[0] = c; m[4] = -s; m[8] = 0;  m[12] = 0;
    m[1] = s; m[5] = c;  m[9] = 0;  m[13] = 0;
    m[2] = 0; m[6] = 0;  m[10] = 1; m[14] = 0;
    m[3] = 0; m[7] = 0;  m[11] = 0; m[15] = 1;

    return m;
}

void rotateZ(float angle, GLfloat res[16])
{
    GLfloat c = cos(angle * DEG2RAD);
    GLfloat s = sin(angle * DEG2RAD);

    res[0] = c; res[4] = -s; res[8] = 0;  res[12] = 0;
    res[1] = s; res[5] = c;  res[9] = 0;  res[13] = 0;
    res[2] = 0; res[6] = 0;  res[10] = 1; res[14] = 0;
    res[3] = 0; res[7] = 0;  res[11] = 0; res[15] = 1;
}

GLfloat* rotate(float angle, Vector3 Axis)
{
    GLfloat c = cos(angle * DEG2RAD);
    GLfloat s = sin(angle * DEG2RAD);

    GLfloat *m = new GLfloat[16];

    GLfloat x = Axis.x;
    GLfloat y = Axis.y;
    GLfloat z = Axis.z;

    m[0] = (1 - c)*x*x + c;   m[4] = (1 - c)*x*y - s*z; m[8] = (1 - c)*x*z + s*y; m[12] = 0;
    m[1] = (1 - c)*x*y + s*z; m[5] = (1 - c)*y*y + c;   m[9] = (1 - c)*y*z - s*x; m[13] = 0;
    m[2] = (1 - c)*x*z - s*y; m[6] = (1 - c)*y*z + s*x; m[10] = (1 - c)*z*z + c;  m[14] = 0;
    m[3] = 0;                 m[7] = 0;                 m[11] = 0;                m[15] = 1;

    return m;
}

void rotate(float angle, Vector3 Axis, GLfloat res[16])
{
    GLfloat c = cos(angle * DEG2RAD);
    GLfloat s = sin(angle * DEG2RAD);

    GLfloat x = Axis.x;
    GLfloat y = Axis.y;
    GLfloat z = Axis.z;

    res[0] = (1 - c)*x*x + c;   res[4] = (1 - c)*x*y - s*z; res[8] = (1 - c)*x*z + s*y; res[12] = 0;
    res[1] = (1 - c)*x*y + s*z; res[5] = (1 - c)*y*y + c;   res[9] = (1 - c)*y*z - s*x; res[13] = 0;
    res[2] = (1 - c)*x*z - s*y; res[6] = (1 - c)*y*z + s*x; res[10] = (1 - c)*z*z + c;  res[14] = 0;
    res[3] = 0;                 res[7] = 0;                 res[11] = 0;                res[15] = 1;
}

GLfloat* perspective(float fovy, float aspect, float zNear, float zFar)
{
    GLfloat *m = new GLfloat[16];

    m[0] = 1.0/(aspect * tan(fovy / 2)); m[4] = 0; m[8] = 0;  m[12] = 0;
    m[1] = 0; m[5] = 1.0/tan(fovy / 2);  m[9] = 0;  m[13] = 0;
    m[2] = 0; m[6] = 0;  m[10] = -(zFar + zNear)/(zFar - zNear); m[14] = -2*zFar*zNear/(zFar - zNear);
    m[3] = 0; m[7] = 0;  m[11] = -1; m[15] = 0;

    return m;
}

GLfloat* ortho(float left, float right, float bottom, float top, float zNear, float zFar)
{
    GLfloat *m = new GLfloat[16];

    m[0] = 2.0/(right - left); m[4] = 0; m[8] = 0; m[12] = -(right + left)/(right - left);
    m[1] = 0; m[5] = 2.0/(top - bottom); m[9] = 0; m[13] = -(top + bottom)/(top - bottom);
    m[2] = 0; m[6] = 0; m[10] = 2.0/(zNear - zFar); m[14] = -(zFar + zNear)/(zFar - zNear);
    m[3] = 0; m[7] = 0; m[11] = 0; m[15] = 1;

    return m;
}

void matrixMul(float a[4][4], float b[4][4], float c[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            c[i][j] = 0;
            for (int k = 0; k<4; k++)
                c[i][j] += a[i][k] * b[k][j];
        }
    }
}
void matrixMul(float a[4][4], float b[4], float c[4])
{
    for (int i = 0; i < 4; i++)
    {
        c[i] = 0;
        for (int j = 0; j<4; j++)
        {
            c[i] += a[i][j] * b[j];
        }
    }
}

void transposeMatrix(float m[], float b[4][4])
{
    for (int i = 0; i< 4; i++)
    {
        for (int j = 0; j< 4; j++)
        {
            b[i][j] = m[j * 4 + i];
        }
    }
}

GLfloat* multiply(GLfloat* left, GLfloat* right, bool res2left)
{
    GLfloat* res = new GLfloat[16];

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            float sum = 0.0;
            for (int k = 0; k < 4; k++)
            {
                sum += left[k + 4 * i] * right[j + 4 * k];
            }
            res[4 * i + j] = sum;
        }
    }

    if (res2left)
    {
        delete[] left;
        left = nullptr;
    }

    return res;
}

GLfloat* multiply(GLfloat* left, GLfloat* right)
{
    GLfloat* res = new GLfloat[16];

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            float sum = 0.0;
            for (int k = 0; k < 4; k++)
            {
                sum += left[k + 4 * i] * right[j + 4 * k];
            }
            res[4 * i + j] = sum;
        }
    }

    delete[] left;
    left = nullptr;

    delete[] right;
    right = nullptr;

    return res;
}

void pickMatrix(float x, float y, float deltax, float deltay, GLint viewport[4])
{
    if (deltax <= 0 || deltay <= 0)
    {
        return;
    }

    glTranslated((viewport[2] - 2 * (x - viewport[0])) / deltax, (viewport[3] - 2 * (y - viewport[1])) / deltay, 0);

    glScaled(viewport[2] / deltax, viewport[3] / deltay, 1.0);
}

float angle2Vecs(Vector3 v0, Vector3 v1)
{
    v0.normalized();
    v1.normalized();
    return std::acos(std::min(1.0f, v0.dot(v1))) * RAD2DEG;
}

Vector3 windowToSphere(Vector3 point, int width, int height)
{
    float d, a;
    Vector3 v;

    v.x = (point.x - ((width - 1.0) / 2.0)) * 2.0 / width;
    v.y = (point.y - ((height - 1.0) / 2.0)) * 2.0 / height;

    d = sqrt(v.x * v.x + v.y * v.y);

    if (d < 1.0)
        v.z = cos((PI/2.0) * d);
    else
        v.z = 0.0;

    a = sqrt(v.dot(v));
    v /= a;

    return v;
}

Vector3 mapToSphere(Vector3 v)
{
    float d, a;

    d = sqrt(v.x * v.x + v.y * v.y);

    if (d < 1.0)
        v.z = cos((PI/2.0) * d);
    else
        v.z = 0.0;

    a = 1.0 / sqrt(v.dot(v));
    v *= a;

    return v;
}

void windowToWorldCoords(int x, int y, GLdouble model[], GLdouble proj[], GLint viewport[], GLfloat *v)
{
    GLdouble winX, winY, winZ;
    GLdouble posX, posY, posZ;

    winX = (float)x;
    winY = (float)y;

    glReadPixels(x, int(winY), 0, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

    gluUnProject(winX, winY, winZ, model, proj, viewport, &posX, &posY, &posZ);

    v[0] = (float)posX;
    v[1] = (float)posY;
    v[2] = (float)posZ;
}

std::string findKey(std::map<std::string, int>& map, int value)
{
    for (auto& it : map)
    {
        if (it.second == value)
        {
            return it.first;
        }
    }

    return "";
}
