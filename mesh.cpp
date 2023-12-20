#include "mesh.h"


void Mesh::createBox(int nStacks, int nSlices, float fRadius, float size)
{
    numVerts = 8 * (nSlices / 4 + 1) * (nStacks / 2 + 1);
    pt = new Point3[numVerts];

    float theta = 0.0, phi = 0.0, x, y, z;

    int k = 0;
    for (int j = 0; j <= nStacks / 2; j++)
    {
        phi = PI / 2 - j * (PI / nStacks);
        for (int i = 0; i <= nSlices / 4; i++)
        {
            theta = i * (2 * PI / nSlices);
            x = size + fRadius * sin(theta) * cos(phi);
            y = size + fRadius * sin(phi);
            z = size + fRadius * cos(theta) * cos(phi);
            pt[k].set(x, y, z);
            k++;
        }
    }

    for (int j = 0; j <= nStacks / 2; j++)
    {
        phi = PI / 2 - j * (PI / nStacks);
        for (int i = nSlices / 4; i <= nSlices / 2; i++)
        {
            theta = i * (2 * PI / nSlices);
            x = size + fRadius * sin(theta) * cos(phi);
            y = size + fRadius * sin(phi);
            z = -size + fRadius * cos(theta) * cos(phi);
            pt[k].set(x, y, z);
            k++;
        }
    }

    for (int j = 0; j <= nStacks / 2; j++)
    {
        phi = PI / 2 - j * (PI / nStacks);
        for (int i = nSlices / 2; i <= 3 * nSlices / 4; i++)
        {
            theta = i * (2 * PI / nSlices);
            x = -size + fRadius * sin(theta) * cos(phi);
            y = size + fRadius * sin(phi);
            z = -size + fRadius * cos(theta) * cos(phi);
            pt[k].set(x, y, z);
            k++;
        }
    }

    for (int j = 0; j <= nStacks / 2; j++)
    {
        phi = PI / 2 - j * (PI / nStacks);
        for (int i = 3 * nSlices / 4; i <= nSlices; i++)
        {
            theta = i * (2 * PI / nSlices);
            x = -size + fRadius * sin(theta) * cos(phi);
            y = size + fRadius * sin(phi);
            z = size + fRadius * cos(theta) * cos(phi);
            pt[k].set(x, y, z);
            k++;
        }
    }

    for (int j = 0; j <= nStacks / 2; j++)
    {
        phi = -PI / 2 + j * (PI / nStacks);
        for (int i = 0; i <= nSlices / 4; i++)
        {
            theta = i * (2 * PI / nSlices);
            x = size + fRadius * sin(theta) * cos(phi);
            y = -size + fRadius * sin(phi);
            z = size + fRadius * cos(theta) * cos(phi);
            pt[k].set(x, y, z);
            k++;
        }
    }

    for (int j = 0; j <= nStacks / 2; j++)
    {
        phi = -PI / 2 + j * (PI / nStacks);
        for (int i = nSlices / 4; i <= nSlices / 2; i++)
        {
            theta = i * (2 * PI / nSlices);
            x = size + fRadius * sin(theta) * cos(phi);
            y = -size + fRadius * sin(phi);
            z = -size + fRadius * cos(theta) * cos(phi);
            pt[k].set(x, y, z);
            k++;
        }
    }

    for (int j = 0; j <= nStacks / 2; j++)
    {
        phi = -PI / 2 + j * (PI / nStacks);
        for (int i = nSlices / 2; i <= 3 * nSlices / 4; i++)
        {
            theta = i * (2 * PI / nSlices);
            x = -size + fRadius * sin(theta) * cos(phi);
            y = -size + fRadius * sin(phi);
            z = -size + fRadius * cos(theta) * cos(phi);
            pt[k].set(x, y, z);
            k++;
        }
    }

    for (int j = 0; j <= nStacks / 2; j++)
    {
        phi = -PI / 2 + j * (PI / nStacks);
        for (int i = 3 * nSlices / 4; i <= nSlices; i++)
        {
            theta = i * (2 * PI / nSlices);
            x = -size + fRadius * sin(theta) * cos(phi);
            y = -size + fRadius * sin(phi);
            z = size + fRadius * cos(theta) * cos(phi);
            pt[k].set(x, y, z);
            k++;
        }
    }

    numFaces = 8 * (nStacks / 2) * (nSlices / 4) + 8 * nStacks / 2 + 4 * nSlices / 4 + 6;
    face = new Face[numFaces];
    int idx = 0;

    for (int i = 0; i < nSlices / 4; i++)
    {
        for (int j = 0; j < nStacks / 2; j++)
        {
            face[idx].nVerts = 4;
            face[idx].vert = new VertexID[face[idx].nVerts];

            face[idx].vert[0].vertIndex = i + j * (nSlices / 4 + 1);
            face[idx].vert[1].vertIndex = face[idx].vert[0].vertIndex + nSlices / 4 + 1;
            face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + 1;
            face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + 1;
            idx++;
        }
    }

    for (int i = 0; i < nSlices / 4; i++)
    {
        for (int j = 0; j < nStacks / 2; j++)
        {
            face[idx].nVerts = 4;
            face[idx].vert = new VertexID[face[idx].nVerts];

            face[idx].vert[0].vertIndex = i + j * (nSlices / 4 + 1) + numVerts / 8;
            face[idx].vert[1].vertIndex = face[idx].vert[0].vertIndex + nSlices / 4 + 1;
            face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + 1;
            face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + 1;
            idx++;
        }
    }

    for (int i = 0; i < nSlices / 4; i++)
    {
        for (int j = 0; j < nStacks / 2; j++)
        {
            face[idx].nVerts = 4;
            face[idx].vert = new VertexID[face[idx].nVerts];

            face[idx].vert[0].vertIndex = i + j * (nSlices / 4 + 1) + 2 * (numVerts / 8);
            face[idx].vert[1].vertIndex = face[idx].vert[0].vertIndex + nSlices / 4 + 1;
            face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + 1;
            face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + 1;
            idx++;
        }
    }

    for (int i = 0; i < nSlices / 4; i++)
    {
        for (int j = 0; j < nStacks / 2; j++)
        {
            face[idx].nVerts = 4;
            face[idx].vert = new VertexID[face[idx].nVerts];

            face[idx].vert[0].vertIndex = i + j * (nSlices / 4 + 1) + 3 * (numVerts / 8);
            face[idx].vert[1].vertIndex = face[idx].vert[0].vertIndex + nSlices / 4 + 1;
            face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + 1;
            face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + 1;
            idx++;
        }
    }

    //ngang
    for (int i = 0; i < nStacks / 2; i++)
    {
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];

        face[idx].vert[0].vertIndex = nSlices / 4 + i * (nSlices / 4 + 1);
        face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + (nSlices / 4 + 1) * (nStacks / 2 + 1) - nSlices / 4;
        face[idx].vert[2].vertIndex = face[idx].vert[3].vertIndex + nSlices / 4 + 1;
        face[idx].vert[1].vertIndex = face[idx].vert[0].vertIndex + nSlices / 4 + 1;
        idx++;
    }

    for (int i = 0; i < nStacks / 2; i++)
    {
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];

        face[idx].vert[0].vertIndex = nSlices / 4 + i * (nSlices / 4 + 1) + (nSlices / 4 + 1) * (nStacks / 2 + 1);
        face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + (nSlices / 4 + 1) * (nStacks / 2 + 1) - nSlices / 4;
        face[idx].vert[2].vertIndex = face[idx].vert[3].vertIndex + nSlices / 4 + 1;
        face[idx].vert[1].vertIndex = face[idx].vert[0].vertIndex + nSlices / 4 + 1;
        idx++;
    }

    for (int i = 0; i < nStacks / 2; i++)
    {
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];

        face[idx].vert[0].vertIndex = nSlices / 4 + i * (nSlices / 4 + 1) + 2 * (nSlices / 4 + 1) * (nStacks / 2 + 1);
        face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + (nSlices / 4 + 1) * (nStacks / 2 + 1) - nSlices / 4;
        face[idx].vert[2].vertIndex = face[idx].vert[3].vertIndex + nSlices / 4 + 1;
        face[idx].vert[1].vertIndex = face[idx].vert[0].vertIndex + nSlices / 4 + 1;
        idx++;
    }

    for (int i = 0; i < nStacks / 2; i++)
    {
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];

        face[idx].vert[0].vertIndex = nSlices / 4 + i * (nSlices / 4 + 1) + 3 * (nSlices / 4 + 1) * (nStacks / 2 + 1);
        face[idx].vert[3].vertIndex = (nSlices / 4 + 1) * i;
        face[idx].vert[2].vertIndex = face[idx].vert[3].vertIndex + nSlices / 4 + 1;
        face[idx].vert[1].vertIndex = face[idx].vert[0].vertIndex + nSlices / 4 + 1;
        idx++;
    }

    for (int i = 0; i < nSlices / 4; i++)
    {
        for (int j = 0; j < nStacks / 2; j++)
        {
            face[idx].nVerts = 4;
            face[idx].vert = new VertexID[face[idx].nVerts];

            face[idx].vert[0].vertIndex = i + j * (nSlices / 4 + 1) + 4 * (numVerts / 8);
            face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSlices / 4 + 1;
            face[idx].vert[2].vertIndex = face[idx].vert[3].vertIndex + 1;
            face[idx].vert[1].vertIndex = face[idx].vert[0].vertIndex + 1;
            idx++;
        }
    }

    for (int i = 0; i < nSlices / 4; i++)
    {
        for (int j = 0; j < nStacks / 2; j++)
        {
            face[idx].nVerts = 4;
            face[idx].vert = new VertexID[face[idx].nVerts];

            face[idx].vert[0].vertIndex = i + j * (nSlices / 4 + 1) + 5 * (numVerts / 8);
            face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSlices / 4 + 1;
            face[idx].vert[2].vertIndex = face[idx].vert[3].vertIndex + 1;
            face[idx].vert[1].vertIndex = face[idx].vert[0].vertIndex + 1;
            idx++;
        }
    }

    for (int i = 0; i < nSlices / 4; i++)
    {
        for (int j = 0; j < nStacks / 2; j++)
        {
            face[idx].nVerts = 4;
            face[idx].vert = new VertexID[face[idx].nVerts];

            face[idx].vert[0].vertIndex = i + j * (nSlices / 4 + 1) + 6 * (numVerts / 8);
            face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSlices / 4 + 1;
            face[idx].vert[2].vertIndex = face[idx].vert[3].vertIndex + 1;
            face[idx].vert[1].vertIndex = face[idx].vert[0].vertIndex + 1;
            idx++;
        }
    }

    for (int i = 0; i < nSlices / 4; i++)
    {
        for (int j = 0; j < nStacks / 2; j++)
        {
            face[idx].nVerts = 4;
            face[idx].vert = new VertexID[face[idx].nVerts];

            face[idx].vert[0].vertIndex = i + j * (nSlices / 4 + 1) + 7 * (numVerts / 8);
            face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSlices / 4 + 1;
            face[idx].vert[2].vertIndex = face[idx].vert[3].vertIndex + 1;
            face[idx].vert[1].vertIndex = face[idx].vert[0].vertIndex + 1;
            idx++;
        }
    }

    //ngang nguoc
    for (int i = 0; i < nStacks / 2; i++)
    {
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];

        face[idx].vert[0].vertIndex = nSlices / 4 + i * (nSlices / 4 + 1) + 4 * (nSlices / 4 + 1) * (nStacks / 2 + 1);
        face[idx].vert[1].vertIndex = face[idx].vert[0].vertIndex + (nSlices / 4 + 1) * (nStacks / 2 + 1) - nSlices / 4;
        face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSlices / 4 + 1;
        face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSlices / 4 + 1;
        idx++;
    }

    for (int i = 0; i < nStacks / 2; i++)
    {
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];

        face[idx].vert[0].vertIndex = nSlices / 4 + i * (nSlices / 4 + 1) + 5 * (nSlices / 4 + 1) * (nStacks / 2 + 1);
        face[idx].vert[1].vertIndex = face[idx].vert[0].vertIndex + (nSlices / 4 + 1) * (nStacks / 2 + 1) - nSlices / 4;
        face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSlices / 4 + 1;
        face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSlices / 4 + 1;
        idx++;
    }

    for (int i = 0; i < nStacks / 2; i++)
    {
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];

        face[idx].vert[0].vertIndex = nSlices / 4 + i * (nSlices / 4 + 1) + 6 * (nSlices / 4 + 1) * (nStacks / 2 + 1);
        face[idx].vert[1].vertIndex = face[idx].vert[0].vertIndex + (nSlices / 4 + 1) * (nStacks / 2 + 1) - nSlices / 4;
        face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSlices / 4 + 1;
        face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSlices / 4 + 1;
        idx++;
    }

    for (int i = 0; i < nStacks / 2; i++)
    {
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];

        face[idx].vert[0].vertIndex = nSlices / 4 + i * (nSlices / 4 + 1) + 7 * (nSlices / 4 + 1) * (nStacks / 2 + 1);
        face[idx].vert[1].vertIndex = (nSlices / 4 + 1) * i + 4 * (nSlices / 4 + 1) * (nStacks / 2 + 1);
        face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSlices / 4 + 1;
        face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSlices / 4 + 1;
        idx++;
    }

    //doc
    for (int i = 0; i < nSlices / 4; i++)
    {
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];

        face[idx].vert[0].vertIndex = (nStacks / 2) * (nSlices / 4 + 1) + i;
        face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + 1;
        face[idx].vert[2].vertIndex = face[idx].vert[3].vertIndex + 4 * (nSlices / 4 + 1) * (nStacks / 2 + 1);
        face[idx].vert[1].vertIndex = face[idx].vert[2].vertIndex - 1;
        idx++;
    }

    for (int i = 0; i < nSlices / 4; i++)
    {
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];

        face[idx].vert[0].vertIndex = (nStacks / 2) * (nSlices / 4 + 1) + i + (nSlices / 4 + 1) * (nStacks / 2 + 1);
        face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + 1;
        face[idx].vert[2].vertIndex = face[idx].vert[3].vertIndex + 4 * (nSlices / 4 + 1) * (nStacks / 2 + 1);
        face[idx].vert[1].vertIndex = face[idx].vert[2].vertIndex - 1;
        idx++;
    }

    for (int i = 0; i < nSlices / 4; i++)
    {
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];

        face[idx].vert[0].vertIndex = (nStacks / 2) * (nSlices / 4 + 1) + i + 2 * (nSlices / 4 + 1) * (nStacks / 2 + 1);
        face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + 1;
        face[idx].vert[2].vertIndex = face[idx].vert[3].vertIndex + 4 * (nSlices / 4 + 1) * (nStacks / 2 + 1);
        face[idx].vert[1].vertIndex = face[idx].vert[2].vertIndex - 1;
        idx++;
    }

    for (int i = 0; i < nSlices / 4; i++)
    {
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];

        face[idx].vert[0].vertIndex = (nStacks / 2) * (nSlices / 4 + 1) + i + 3 * (nSlices / 4 + 1) * (nStacks / 2 + 1);
        face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + 1;
        face[idx].vert[2].vertIndex = face[idx].vert[3].vertIndex + 4 * (nSlices / 4 + 1) * (nStacks / 2 + 1);
        face[idx].vert[1].vertIndex = face[idx].vert[2].vertIndex - 1;
        idx++;
    }

    face[idx].nVerts = 4;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[0].vertIndex = 0;
    face[idx].vert[3].vertIndex = (nSlices / 4 + 1) * (nStacks / 2 + 1);
    face[idx].vert[2].vertIndex = 2 * (nSlices / 4 + 1) * (nStacks / 2 + 1);
    face[idx].vert[1].vertIndex = 3 * (nSlices / 4 + 1) * (nStacks / 2 + 1);
    idx++;


    //
    face[idx].nVerts = 4;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[0].vertIndex = 4 * (nSlices / 4 + 1) * (nStacks / 2 + 1);
    face[idx].vert[1].vertIndex = 5 * (nSlices / 4 + 1) * (nStacks / 2 + 1);
    face[idx].vert[2].vertIndex = 6 * (nSlices / 4 + 1) * (nStacks / 2 + 1);
    face[idx].vert[3].vertIndex = 7 * (nSlices / 4 + 1) * (nStacks / 2 + 1);
    idx++;

    face[idx].nVerts = 4;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[0].vertIndex = nSlices / 4 + (nStacks / 2) * (nSlices / 4 + 1);
    face[idx].vert[1].vertIndex = face[idx].vert[0].vertIndex + (nSlices / 4 + 1) * (nStacks / 2 + 1) - nSlices / 4;
    face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + 4 * (nStacks / 2 + 1) * (nSlices / 4 + 1);
    face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + 4 * (nStacks / 2 + 1) * (nSlices / 4 + 1);
    idx++;

    face[idx].nVerts = 4;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[0].vertIndex = nSlices / 4 + (nStacks / 2) * (nSlices / 4 + 1) + (nStacks / 2 + 1) * (nSlices / 4 + 1);
    face[idx].vert[1].vertIndex = face[idx].vert[0].vertIndex + (nSlices / 4 + 1) * (nStacks / 2 + 1) - nSlices / 4;
    face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + 4 * (nStacks / 2 + 1) * (nSlices / 4 + 1);
    face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + 4 * (nStacks / 2 + 1) * (nSlices / 4 + 1);
    idx++;

    face[idx].nVerts = 4;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[0].vertIndex = nSlices / 4 + (nStacks / 2) * (nSlices / 4 + 1) + 2 * (nStacks / 2 + 1) * (nSlices / 4 + 1);
    face[idx].vert[1].vertIndex = face[idx].vert[0].vertIndex + (nSlices / 4 + 1) * (nStacks / 2 + 1) - nSlices / 4;
    face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + 4 * (nStacks / 2 + 1) * (nSlices / 4 + 1);
    face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + 4 * (nStacks / 2 + 1) * (nSlices / 4 + 1);
    idx++;

    face[idx].nVerts = 4;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[0].vertIndex = nSlices / 4 + (nStacks / 2) * (nSlices / 4 + 1) + 3 * (nStacks / 2 + 1) * (nSlices / 4 + 1);
    face[idx].vert[1].vertIndex = (nSlices / 4 + 1) * (nStacks / 2);// - nSlices / 4;
    face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + 4 * (nStacks / 2 + 1) * (nSlices / 4 + 1);
    face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + 4 * (nStacks / 2 + 1) * (nSlices / 4 + 1);
    idx++;
}

void Mesh::createRoundSquare(int nSegment, float fRadius, float thin, float radius, float centerx, float centery, float centerz)
{
    numVerts = ((nSegment + 1) * 4 + 1) * 2;
    pt = new Point3[numVerts];

    int idx = 0;
    float fAngle = 2 * PI / (4 * nSegment), angle = 0;
    float x, y, z;
    pt[0].set(centerx, centery, centerz);

    for (int i = 0; i <= nSegment; i++)
    {
        x = centerx + radius + fRadius * cos(angle);
        y = centery + radius + fRadius * sin(angle);
        z = centerz;

        pt[i + 1].set(x, y, z);
        if (i < nSegment) angle += fAngle;
    }

    for (int i = nSegment + 1; i <= 2 * nSegment + 1; i++)
    {
        x = centerx - radius + fRadius * cos(angle);
        y = centery + radius + fRadius * sin(angle);
        z = centerz;

        pt[i + 1].set(x, y, z);
        if (i < 2 * nSegment + 1) angle += fAngle;
    }

    for (int i = 2 * nSegment + 2; i <= 3 * nSegment + 2; i++)
    {
        x = centerx - radius + fRadius * cos(angle);
        y = centery - radius + fRadius * sin(angle);
        z = centerz;

        pt[i + 1].set(x, y, z);
        if (i < 3 * nSegment + 2) angle += fAngle;
    }

    for (int i = 3 * nSegment + 3; i <= 4 * nSegment + 3; i++)
    {
        x = centerx + radius + fRadius * cos(angle);
        y = centery - radius + fRadius * sin(angle);
        z = centerz;

        pt[i + 1].set(x, y, z);
        if (i < 4 * nSegment + 3) angle += fAngle;
    }

    pt[4 * nSegment + 5].set(centerx, centery, centerz + thin);

    for (int i = 4 * nSegment + 5; i <= 5 * nSegment + 5; i++)
    {
        x = centerx + radius + fRadius * cos(angle);
        y = centery + radius + fRadius * sin(angle);
        z = centerz + thin;

        pt[i + 1].set(x, y, z);
        if (i < 5 * nSegment + 5) angle += fAngle;
    }

    for (int i = 5 * nSegment + 6; i <= 6 * nSegment + 6; i++)
    {
        x = centerx - radius + fRadius * cos(angle);
        y = centery + radius + fRadius * sin(angle);
        z = centerz + thin;

        pt[i + 1].set(x, y, z);
        if (i < 6 * nSegment + 6) angle += fAngle;
    }

    for (int i = 6 * nSegment + 7; i <= 7 * nSegment + 7; i++)
    {
        x = centerx - radius + fRadius * cos(angle);
        y = centery - radius + fRadius * sin(angle);
        z = centerz + thin;

        pt[i + 1].set(x, y, z);
        if (i < 7 * nSegment + 7) angle += fAngle;
    }

    for (int i = 7 * nSegment + 8; i <= 8 * nSegment + 8; i++)
    {
        x = centerx + radius + fRadius * cos(angle);
        y = centery - radius + fRadius * sin(angle);
        z = centerz + thin;

        pt[i + 1].set(x, y, z);
        if (i < 8 * nSegment + 8) angle += fAngle;
    }

    numFaces = (4 * nSegment + 4) * 2 + (4 * nSegment + 4) + 0;
    face = new Face[numFaces];

    for(int i = 0; i < nSegment; i++)
    {
        face[idx].nVerts = 3;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = 0;
        face[idx].vert[2].vertIndex = i + 1;
        face[idx].vert[1].vertIndex = i + 2;
        idx++;
    }

    for(int i = 0; i < nSegment; i++)
    {
        face[idx].nVerts = 3;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = 0;
        face[idx].vert[2].vertIndex = i + 1 + nSegment + 1;
        face[idx].vert[1].vertIndex = i + 2 + nSegment + 1;
        idx++;
    }

    for(int i = 0; i < nSegment; i++)
    {
        face[idx].nVerts = 3;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = 0;
        face[idx].vert[2].vertIndex = i + 1 + 2 * (nSegment + 1);
        face[idx].vert[1].vertIndex = i + 2 + 2 * (nSegment + 1);
        idx++;
    }

    for(int i = 0; i < nSegment; i++)
    {
        face[idx].nVerts = 3;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = 0;
        face[idx].vert[2].vertIndex = i + 1 + 3 * (nSegment + 1);
        face[idx].vert[1].vertIndex = i + 2 + 3 * (nSegment + 1);
        idx++;
    }

    face[idx].nVerts = 3;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[0].vertIndex = 0;
    face[idx].vert[2].vertIndex = 4 * (nSegment + 1);
    face[idx].vert[1].vertIndex = 1;
    idx++;

    face[idx].nVerts = 3;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[0].vertIndex = 0;
    face[idx].vert[2].vertIndex = (nSegment + 1);
    face[idx].vert[1].vertIndex = (nSegment + 1) + 1;
    idx++;

    face[idx].nVerts = 3;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[0].vertIndex = 0;
    face[idx].vert[2].vertIndex = 2 * (nSegment + 1);
    face[idx].vert[1].vertIndex = 2 * (nSegment + 1) + 1;
    idx++;

    face[idx].nVerts = 3;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[0].vertIndex = 0;
    face[idx].vert[2].vertIndex = 3 * (nSegment + 1);
    face[idx].vert[1].vertIndex = 3 * (nSegment + 1) + 1;
    idx++;

    ///////////////////////////////////////////////////////

    for(int i = 0; i < nSegment; i++)
    {
        face[idx].nVerts = 3;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = 4 * nSegment + 5;
        face[idx].vert[1].vertIndex = i + 1 + 4 * nSegment + 5;
        face[idx].vert[2].vertIndex = i + 2 + 4 * nSegment + 5;
        idx++;
    }

    for(int i = 0; i < nSegment; i++)
    {
        face[idx].nVerts = 3;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = 4 * nSegment + 5;
        face[idx].vert[1].vertIndex = i + 1 + nSegment + 1 + 4 * nSegment + 5;
        face[idx].vert[2].vertIndex = i + 2 + nSegment + 1 + 4 * nSegment + 5;
        idx++;
    }

    for(int i = 0; i < nSegment; i++)
    {
        face[idx].nVerts = 3;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = 4 * nSegment + 5;
        face[idx].vert[1].vertIndex = i + 1 + 2 * (nSegment + 1) + 4 * nSegment + 5;
        face[idx].vert[2].vertIndex = i + 2 + 2 * (nSegment + 1) + 4 * nSegment + 5;
        idx++;
    }

    for(int i = 0; i < nSegment; i++)
    {
        face[idx].nVerts = 3;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = 4 * nSegment + 5;
        face[idx].vert[1].vertIndex = i + 1 + 3 * (nSegment + 1) + 4 * nSegment + 5;
        face[idx].vert[2].vertIndex = i + 2 + 3 * (nSegment + 1) + 4 * nSegment + 5;
        idx++;
    }

    face[idx].nVerts = 3;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[0].vertIndex = 4 * nSegment + 5;
    face[idx].vert[1].vertIndex = 4 * (nSegment + 1) + 4 * nSegment + 5;
    face[idx].vert[2].vertIndex = 1 + 4 * nSegment + 5;
    idx++;

    face[idx].nVerts = 3;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[0].vertIndex = 4 * nSegment + 5;
    face[idx].vert[1].vertIndex = (nSegment + 1) + 4 * nSegment + 5;
    face[idx].vert[2].vertIndex = (nSegment + 1) + 1 + 4 * nSegment + 5;
    idx++;

    face[idx].nVerts = 3;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[0].vertIndex = 4 * nSegment + 5;
    face[idx].vert[1].vertIndex = 2 * (nSegment + 1) + 4 * nSegment + 5;
    face[idx].vert[2].vertIndex = 2 * (nSegment + 1) + 1 + 4 * nSegment + 5;
    idx++;

    face[idx].nVerts = 3;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[0].vertIndex = 4 * nSegment + 5;
    face[idx].vert[1].vertIndex = 3 * (nSegment + 1) + 4 * nSegment + 5;
    face[idx].vert[2].vertIndex = 3 * (nSegment + 1) + 1 + 4 * nSegment + 5;
    idx++;

    /*
    face[idx].nVerts = 4 * nSegment + 4;
    face[idx].vert = new VertexID[face[idx].nVerts];
    for (int i = 8 * nSegment + 9 , k = 0; i >= 4 * nSegment + 6; i--, k++)
    {
        face[idx].vert[k].vertIndex = i;
    }

    idx++;
    */
    for (int i = 0; i < 4 * nSegment + 4; i++)
    {
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = i + 1;
        face[idx].vert[3].vertIndex = i + 1 + 4 * nSegment + 5;
        face[idx].vert[2].vertIndex = i + 1 + 4 * nSegment + 5 + 1;
        face[idx].vert[1].vertIndex = i + 1 + 1;
        if (i == 4 * nSegment + 3)
        {
            face[idx].vert[0].vertIndex = 4 * nSegment + 4;
            face[idx].vert[3].vertIndex = 4 * nSegment + 4 + 4 * nSegment + 5;
            face[idx].vert[2].vertIndex = 4 * nSegment + 6;
            face[idx].vert[1].vertIndex = 1;
        }
        idx++;
    }
}

void Mesh::setupMaterial(float ambient[], float diffuse[], float specular[], float shininess)
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}

void Mesh::drawColor()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    for (int f = 0; f < numFaces; f++)
    {
        glBegin(GL_POLYGON);
        for (int v = 0; v < face[f].nVerts; v++)
        {
            int iv = face[f].vert[v].vertIndex;
            glVertex3d(pt[iv].x, pt[iv].y, pt[iv].z);
        }
        glEnd();
    }
}

void Mesh::drawSmooth(bool smooth)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    for (int f = 0; f < numFaces; f++)
    {
        glBegin(GL_POLYGON);
        for (int v = 0; v < face[f].nVerts; v++)
        {
            int iv = face[f].vert[v].vertIndex;

            if (smooth)
                glNormal3d(pt[iv].vertexNorm.x, pt[iv].vertexNorm.y, pt[iv].vertexNorm.z);
            else
                glNormal3d(face[f].facenorm.x, face[f].facenorm.y, face[f].facenorm.z);

            glVertex3d(pt[iv].x, pt[iv].y, pt[iv].z);
        }
        glEnd();
    }
}

void Mesh::calculateFaceNorms()
{
    float	mx, my, mz;
    int		idx, next;

    for (int f = 0; f < numFaces; f++)
    {
        mx = 0;
        my = 0;
        mz = 0;
        for (int v = 0; v < face[f].nVerts; v++)
        {
            idx = v;
            next = (idx + 1) % face[f].nVerts;

            int		p1 = face[f].vert[idx].vertIndex;
            int		p2 = face[f].vert[next].vertIndex;

            mx += (pt[p1].y - pt[p2].y) * (pt[p1].z + pt[p2].z);
            my += (pt[p1].z - pt[p2].z) * (pt[p1].x + pt[p2].x);
            mz += (pt[p1].x - pt[p2].x) * (pt[p1].y + pt[p2].y);
        }
        face[f].facenorm.set(mx, my, mz);
        face[f].facenorm.normalized();
    }
}

void Mesh::calculateVertexNorm()
{
    float mx, my, mz;

    for (int v = 0; v < numVerts; v++)
    {
        mx = 0;
        my = 0;
        mz = 0;
        for (int f = 0; f < numFaces; f++)
        {
            for (int vf = 0; vf < face[f].nVerts; vf++)
            {
                if (face[f].vert[vf].vertIndex == v)
                {
                    mx += face[f].facenorm.x;
                    my += face[f].facenorm.y;
                    mz += face[f].facenorm.z;
                }
            }
        }
        pt[v].vertexNorm.set(mx, my, mz);
        pt[v].vertexNorm.normalized();
    }
}

