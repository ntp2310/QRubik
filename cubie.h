#ifndef CUBIE_H
#define CUBIE_H

#include "vectors.h"
#include "facecubie.h"
#include "mesh.h"
#include "moviment.h"
#include "utils.h"
#include "matrices.h"


class Cubie
{
public:

    GLfloat amb0[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat amb1[4] = { 0.25f, 0.25f, 0.25f, 1.0f };

    GLfloat spec0[4] = { 0.45f, 0.45f, 0.45f, 1.0f };
    GLfloat spec1[4] = { 0.35f, 0.35f, 0.35f, 1.0f };

    Vector3 position;
    Vector3 angle;

    FaceCubie* initFaceColors;
    FaceCubie* faceColors;

    float  initX;
    float  initY;
    float  initZ;

    float   size;
    float   n;
    float   count;

    float  stopAngle;
    float  blockSpace;
    float  cornerRadius;

    bool    idle;
    bool    special;
    int     id;
    int     number;
    int     axis;

    Vector3 initFRU, initFLU, initFLD, initFRD, initBRU, initBLU, initBLD, initBRD;

    Matrix4 rotation;
    Matrix4 local;

    Mesh cubie;
    Mesh polygon;
    Mesh roundSq;

    std::map<std::string, int> colorDirection;

    Cubie(float size, Vector3 pos, int id, FaceCubie* initFaceColors, int num);

    ~Cubie();

    int setName(Vector3 v0, Vector3 v1, Vector3 v2, Vector3 v3);

    void rotate(float delta, int axis, bool special);

    void updateID();

    void updatePoints();

    void update(bool isPressed);

    void setColor(int id, int colorIdx);

    void setMaterial(int colorIdx, float specular[], float ambient[]);

    void shadowMode(int type_of_plane);

    void restoreBasic();

    void drawShadow();

    void render(bool isPressed);

    void changeColor(int face, int colorIdx);

    void place();

    void resetTransforms();

    std::string getColorInfo();
};



#endif // CUBIE_H

