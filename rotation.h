#ifndef ROTATION_H
#define ROTATION_H

#include "vectors.h"
#include "utils.h"
#include "cubie.h"


class Rotation
{
private:
    int     axis;
    int     n;
    int     size;
    int     special;
    float   angle;
    float   leftDegree;
    bool    clockwise;
    bool    animationEnded;

    std::vector<Cubie*> *listCubies;
    std::vector<Cubie*> *choosenCubies;

    Vector3 position;

public:
    Rotation(std::vector<Cubie*>* animationCubes, Vector3 pos, bool clockwise, int axis, int spec);
    Rotation(std::vector<Cubie*>* animationCubes, Moviment* moviment);
    ~Rotation();

    int getSpecial();

    bool getAnimateEnded();

    std::vector<Cubie*>* filter();

    void animate(float delta);
};

#endif // ROTATION_H
