#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H


#include "utils.h"
#include "rubixcube.h"
#include "matrices.h"
#include "vectors.h"
#include "camera.h"

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <QLibrary>
#include <QDebug>
#include <string>
#include <cstring>
#include <QMatrix4x4>


#define BUFSIZE 1024

class OpenGLWindow : public QOpenGLWindow ,protected QOpenGLFunctions
{
public:
    explicit OpenGLWindow(QWindow *parent = nullptr);
    ~OpenGLWindow();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    RubixCube *rubix;
    Cubie *choosenCubie;
    Cubie *cubie;

    Matrix4 m_projection;
    Matrix4 m_view;
    Matrix4 m_model;
    Matrix4 randRotation;

    Vector3 lastPos, curPos;
    Vector3 startPos, endPos;

private:
    void setupLight();
    void render(bool select);
    void mouseDrag(int cubieIdx);
    void updateGL();
    int pick(int x, int y);

public:
    void solve();
    void inputByCamera();

    GLuint selectBuf[BUFSIZE];

    Vector3 norm, normX, normY, normZ;
    Vector3 eye, target, up;
    Vector3 text;


    bool    isPressed, cameraOn, execute, pause;
    bool    track;
    bool    configMode, facedir;
    float   aspect, angle, speedup = 1.5;
    int     coord;
    int     selectedCubie;
    int     currentColor;
    int     _data[6][3][3];
    int     idx;

    QString solution;
    char    *sol;
    std::vector<QString> path;
};

#endif // OpenGLWindow_H


