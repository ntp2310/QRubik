#ifndef POINT3_H
#define POINT3_H

#include "vectors.h"


class Point3
{
public:
    float x, y, z;
    Vector3 vertexNorm;

    void set(float dx, float dy, float dz)
    {
        x = dx; y = dy; z = dz;
    }
    void set(Point3& p)
    {
        x = p.x; y = p.y; z = p.z;
    }
    Point3() { x = y = z = 0; }
    Point3(float dx, float dy, float dz)
    {
        x = dx; y = dy; z = dz;
    }
};

#endif // POINT3_H

