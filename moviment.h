#ifndef MOVIMENT_H
#define MOVIMENT_H

#include "vectors.h"


class Moviment
{
public:
    int     axis;
    int     n;
    float   angle;
    bool    clockwise;
    int     special;

    Vector3 position;

    Moviment()
    {
        axis = 0;
        n = 3;
        angle = 0;
        clockwise = true;
        special = false;
    }

    ~Moviment(){}

    Moviment(Vector3 pos, bool clockwise, int axis, float angle, int n)
    {
        this->axis = axis;
        this->position = pos;
        this->clockwise = clockwise;
        this->angle = angle;
        this->n = n;
        special = 0;
    }

    Moviment(Vector3 pos, bool clockwise, int axis, float angle, int n, int spec)
    {
        this->axis = axis;
        this->position = pos;
        this->clockwise = clockwise;
        this->angle = angle;
        this->n = n;
        special = spec;
    }
};


#endif // MOVIMENT_H

