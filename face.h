#ifndef FACE_H
#define FACE_H
#include "vectors.h"
#include "vertexid.h"

class Face
{
public:
    int         nVerts;
    VertexID*	vert;
    Vector3     facenorm;

    Face() : nVerts(0), vert(nullptr) {}

    ~Face()
    {
        if (vert)
        {
            delete[] vert;
            vert = nullptr;
        }
        nVerts = 0;
    }
};

#endif // FACE_H

