#ifndef MESH_H
#define MESH_H

#include "face.h"
#include "point3.h"
#include "vectors.h"
#include "utils.h"


class Mesh
{
public:
    int		numVerts;
    Point3*		pt;

    int		numFaces;
    Face*		face;

public:
    Mesh() : numVerts(0), pt(nullptr), numFaces(0), face(nullptr) {}

    ~Mesh()
    {
        if (pt)
            delete[] pt;

        if (face)
            delete[] face;

        numVerts = 0;
        numFaces = 0;
    }

    void drawWireframe();
    void drawColor();

    void drawSmooth(bool smooth);
    void setupMaterial(float ambient[], float diffuse[], float specular[], float shininess);
    void calculateFaceNorms();
    void calculateVertexNorm();
    void createBox(int nStacks, int nSlices, float fRadius, float size);
    void createRoundSquare(int nSegment, float fRadius, float thin, float radius, float centerx, float centery, float centerz);
};


#endif // MESH_H

