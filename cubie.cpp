#include "cubie.h"


Cubie::Cubie(float size, Vector3 pos, int id, FaceCubie* initFaceColors, int num)
{
    this->size = size;

    initX = pos.x;
    initY = pos.y;
    initZ = pos.z;

    angle.set(0.0f, 0.0f, 0.0f);

    this->position = pos;

    this->id = id;

    n = 16;

    this->initFaceColors = initFaceColors;
    faceColors = new FaceCubie(initFaceColors);

    number = num;

    idle = false;

    cornerRadius = size / 4.4;
    blockSpace = (2 * size) + (2.0 * size / 4.4);

    colorDirection = { {"initleft", 0}, {"initright", 1}, {"inittop", 2}, {"initbottom", 3}, {"initfront", 4}, {"initback", 5} };

    initFRU.set(pos.x + size, pos.y + size, pos.z + size);
    initFLU.set(pos.x - size, pos.y + size, pos.z + size);
    initFLD.set(pos.x - size, pos.y - size, pos.z + size);
    initFRD.set(pos.x + size, pos.y - size, pos.z + size);

    initBRU.set(pos.x + size, pos.y + size, pos.z - size);
    initBLU.set(pos.x - size, pos.y + size, pos.z - size);
    initBLD.set(pos.x - size, pos.y - size, pos.z - size);
    initBRD.set(pos.x + size, pos.y - size, pos.z - size);

    int nSegment = 24;

    cubie.createBox(nSegment, 2 * nSegment, cornerRadius, size);
    cubie.calculateFaceNorms();
    cubie.calculateVertexNorm();

    roundSq.createRoundSquare(nSegment, 7.0 * size / 46.0, size / 23.0, size / 1.25, pos.x, pos.y, pos.z + size + cornerRadius);
    roundSq.calculateFaceNorms();
    roundSq.calculateVertexNorm();
}

Cubie::~Cubie()
{
    delete faceColors;
    faceColors = nullptr;

    delete initFaceColors;
    initFaceColors = nullptr;

    colorDirection.clear();
}

void Cubie::rotate(float delta, int axis, bool special)
{
    count = n;

    angle[axis] += delta;

    for (int i = 0; i < 3; i++)
    {
        if (angle[i] > 360.0f) angle[i] -= 360.0f;
        if (angle[i] < -360.0f) angle[i] += 360.0f;
    }

    this->axis = axis;
    this->special = special;

    idle = true;

    stopAngle = angle[axis];

    if (axis == 0)
        local.rotateX(delta);

    else if (axis == 1)
        local.rotateY(delta);

    else if (axis == 2)
        local.rotateZ(delta);

}

void Cubie::updateID()
{
    int idx = 1;

    for (float x = -0.5 * (number - 1) * blockSpace; x <= 0.51 * (number - 1) * blockSpace; x += blockSpace)
    {
        for (float y = -0.5 * (number - 1) * blockSpace; y <= 0.51 * (number - 1) * blockSpace; y += blockSpace)
        {
            for (float z = -0.5 * (number - 1) * blockSpace; z <= 0.51 * (number - 1) * blockSpace; z += blockSpace)
            {
                if (round(position.x - x) == 0 && round(position.y - y) == 0 && round(position.z - z) == 0)
                {
                    id = idx;
                    return;
                }
                idx++;
            }
        }
    }
}

void Cubie::updatePoints()
{
    if (axis == 0)
        rotation.setRotateX(angle[axis]);

    else if (axis == 1)
        rotation.setRotateY(angle[axis]);

    else if (axis == 2)
        rotation.setRotateZ(angle[axis]);

    position = rotation * position;

    initFRU = rotation * initFRU;
    initFLU = rotation * initFLU;
    initFLD = rotation * initFLD;
    initFRD = rotation * initFRD;

    initBRU = rotation * initBRU;
    initBLU = rotation * initBLU;
    initBLD = rotation * initBLD;
    initBRD = rotation * initBRD;

    updateID();
    resetTransforms();
    idle = false;
}

void Cubie::update(bool isPressed)
{
    float delta;

    if (!isPressed && !special)
    {
        if (angle[axis] > -45 && angle[axis] < 45)
        {
            if (count <= 0.0)
            {
                angle[axis] = 0.0;
                updatePoints();
            }
            else
            {
                delta = (0.0 - stopAngle) / n;
                angle[axis] += delta;

                if (axis == 0)
                    local.rotateX(delta);

                else if (axis == 1)
                    local.rotateY(delta);

                else
                    local.rotateZ(delta);

                count--;
            }
        }
        else if (angle[axis] >= 45 && angle[axis] < 135)
        {
            if (count <= 0.0)
            {
                angle[axis] = 90.0;
                updatePoints();
            }
            else
            {
                delta = (90.0 - stopAngle) / n;
                angle[axis] += delta;

                if (axis == 0)
                    local.rotateX(delta);

                else if (axis == 1)
                    local.rotateY(delta);

                else
                    local.rotateZ(delta);

                count--;
            }
        }
        else if (angle[axis] >= 135 && angle[axis] < 225)
        {
            if (count <= 0.0)
            {
                angle[axis] = 180.0;
                updatePoints();
            }
            else
            {
                delta = (180.0 - stopAngle) / n;
                angle[axis] += delta;

                if (axis == 0)
                    local.rotateX(delta);

                else if (axis == 1)
                    local.rotateY(delta);

                else
                    local.rotateZ(delta);

                count--;
            }
        }
        else if (angle[axis] >= 225 && angle[axis] < 315)
        {
            if (count <= 0.0)
            {
                angle[axis] = 270.0;
                updatePoints();
            }
            else
            {
                delta = (270.0 - stopAngle) / n;
                angle[axis] += delta;

                if (axis == 0)
                    local.rotateX(delta);

                else if (axis == 1)
                    local.rotateY(delta);

                else
                    local.rotateZ(delta);

                count--;
            }
        }
        else if (angle[axis] >= 315.0)
        {
            if (count <= 0.0)
            {
                angle[axis] = 360.0;
                updatePoints();
            }
            else
            {
                delta = (360.0 - stopAngle) / n;
                angle[axis] += delta;

                if (axis == 0)
                    local.rotateX(delta);

                else if (axis == 1)
                    local.rotateY(delta);

                else
                    local.rotateZ(delta);

                count--;
            }
        }
        else if (angle[axis] <= -45 && angle[axis] > -135)
        {
            if (count <= 0.0)
            {
                angle[axis] = -90.0;
                updatePoints();
            }
            else
            {
                delta = (-90.0 - stopAngle) / n;
                angle[axis] += delta;

                if (axis == 0)
                    local.rotateX(delta);

                else if (axis == 1)
                    local.rotateY(delta);

                else
                    local.rotateZ(delta);

                count--;
            }
        }
        else if (angle[axis] <= -135 && angle[axis] > -225)
        {
            if (count <= 0.0)
            {
                angle[axis] = -180.0;
                updatePoints();
            }
            else
            {
                delta = (-180.0 - stopAngle) / n;
                angle[axis] += delta;

                if (axis == 0)
                    local.rotateX(delta);

                else if (axis == 1)
                    local.rotateY(delta);

                else
                    local.rotateZ(delta);

                count--;
            }
        }
        else if (angle[axis] <= -225 && angle[axis] > -315)
        {
            if (count <= 0.0)
            {
                angle[axis] = -270.0;
                updatePoints();
            }
            else
            {
                delta = (-270.0 - stopAngle) / n;
                angle[axis] += delta;

                if (axis == 0)
                    local.rotateX(delta);

                else if (axis == 1)
                    local.rotateY(delta);

                else
                    local.rotateZ(delta);

                count--;
            }
        }
        else if (angle[axis] <= -315)
        {
            if (count <= 0.0)
            {
                angle[axis] = -360.0;
                updatePoints();
            }
            else
            {
                delta = (-360.0 - stopAngle) / n;
                angle[axis] += delta;

                if (axis == 0)
                    local.rotateX(delta);

                else if (axis == 1)
                    local.rotateY(delta);

                else
                    local.rotateZ(delta);

                count--;
            }
        }
    }
}

int Cubie::setName(Vector3 v0, Vector3 v1, Vector3 v2, Vector3 v3)
{
    if (v0.z > position.z && v1.z > position.z && v2.z > position.z && v3.z > position.z)
    {
        return (id * 100) + FRONT;
    }
    else if (v0.z < position.z && v1.z < position.z && v2.z < position.z && v3.z < position.z)
    {
        return (id * 100) + BACK;
    }
    else if (v0.x < position.x && v1.x < position.x && v2.x < position.x && v3.x < position.x)
    {
        return (id * 100) + LEFT;
    }
    else if (v0.x > position.x && v1.x > position.x && v2.x > position.x && v3.x > position.x)
    {
        return (id * 100) + RIGHT;
    }
    else if (v0.y > position.y && v1.y > position.y && v2.y > position.y && v3.y > position.y)
    {
        return (id * 100) + TOP;
    }
    else if (v0.y < position.y && v1.y < position.y && v2.y < position.y && v3.y < position.y)
    {
        return (id * 100) + BOTTOM;
    }

    return -1;
}

void Cubie::setColor(int id, int colorIdx)
{
    int name = id % 10;

    switch (name)
    {
        case 0:
            faceColors->left = colorIdx;
            break;

        case 1:
            faceColors->right = colorIdx;
            break;

        case 2:
            faceColors->top = colorIdx;
            break;

        case 3:
            faceColors->bottom = colorIdx;
            break;

        case 4:
            faceColors->front = colorIdx;
            break;

        case 5:
            faceColors->back = colorIdx;
            break;

        default:
            break;
    }
}

void Cubie::setMaterial(int colorIdx, float specular[], float ambient[])
{
    GLfloat ColorArr[][4] = {{ 0.0f / 255.0f, 30.0f / 255.0f, 255.0f / 255.0f, 1.0f },
                             { 11.0f / 255.0f, 146.0f / 255.0f, 38.0f / 255.0f, 1.0f },
                             { 250.0f / 255.0f, 210.0f / 255.0f, 0.0f / 255.0f, 1.0f },
                             { 240.0f / 255.0f, 240.0f / 255.0f, 240.0f / 255.0f, 1.0f },
                             { 211.0f / 255.0f, 4.0f / 255.0f, 4.0f / 255.0f, 1.0f },
                             { 255.0f / 255.0f, 80.0f / 255.0f, 0.0f / 255.0f, 1.0f },
                             { 5.0f / 255.0f, 5.0f / 255.0f, 5.0f / 255.0f, 1.0f }};

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ColorArr[colorIdx]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 15.0f);
}

void Cubie::shadowMode(int type_of_plane)
{
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_EQUAL, type_of_plane, ~0);
    glStencilOp(GL_KEEP,GL_KEEP,GL_ZERO);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_LIGHTING);
    glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
}

void Cubie::restoreBasic()
{
    glDisable(GL_BLEND);
    glDisable(GL_STENCIL_TEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

void Cubie::drawShadow()
{
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(-0.01f, -0.01f);

    /*
    glBegin(GL_QUADS);
    // back
    glVertex3d(B1.x, B1.y, B1.z);
    glVertex3d(B2.x, B2.y, B2.z);
    glVertex3d(B3.x, B3.y, B3.z);
    glVertex3d(B4.x, B4.y, B4.z);

    //bottom
    glVertex3d(D4.x, D4.y, D4.z);
    glVertex3d(D3.x, D3.y, D3.z);
    glVertex3d(D2.x, D2.y, D2.z);
    glVertex3d(D1.x, D1.y, D1.z);

    //left
    glVertex3d(L1.x, L1.y, L1.z);
    glVertex3d(L2.x, L2.y, L2.z);
    glVertex3d(L3.x, L3.y, L3.z);
    glVertex3d(L4.x, L4.y, L4.z);

    //right
    glVertex3d(R1.x, R1.y, R1.z);
    glVertex3d(R2.x, R2.y, R2.z);
    glVertex3d(R3.x, R3.y, R3.z);
    glVertex3d(R4.x, R4.y, R4.z);

    /// Up
    glVertex3d(T1.x, T1.y, T1.z);
    glVertex3d(T2.x, T2.y, T2.z);
    glVertex3d(T3.x, T3.y, T3.z);
    glVertex3d(T4.x, T4.y, T4.z);

    //Front
    glVertex3d(F1.x, F1.y, F1.z);
    glVertex3d(F2.x, F2.y, F2.z);
    glVertex3d(F3.x, F3.y, F3.z);
    glVertex3d(F4.x, F4.y, F4.z);
    glEnd();
    */
    cubie.drawColor();

    glDisable(GL_POLYGON_OFFSET_FILL);
}

void Cubie::render(bool isPressed)
{
    if (idle)
    {
        update(isPressed);
    }

    glEnable(GL_POINT_SMOOTH);

    glHint(GL_POLYGON_SMOOTH_HINT, GL_DONT_CARE);

    glPushMatrix();

    glMultMatrixf(local.get());

    glShadeModel(GL_SMOOTH);

    int name;

    glInitNames();

    glPushMatrix();
    name = setName(initFLU, initFLD, initFRD, initFRU);
    setColor(name, initFaceColors->front);
    colorDirection["initfront"] = name % 10;
    glPushName(name);
    setMaterial(initFaceColors->front, spec1, amb1);
    if (initFaceColors->front != 6) roundSq.drawSmooth(false);
    glPopName();
    glPopMatrix();


    glPushMatrix();
    name = setName(initFRU, initFRD, initBRD, initBRU);
    setColor(name, initFaceColors->right);
    colorDirection["initright"] = name % 10;
    glPushName(name);
    setMaterial(initFaceColors->right, spec1, amb1);
    glTranslated(initX, initY, initZ);
    glRotated(90.0, 0.0, 1.0, 0.0);
    glTranslated(-initX, -initY, -initZ);
    if (initFaceColors->right != 6) roundSq.drawSmooth(false);
    glPopName();
    glPopMatrix();


    glPushMatrix();
    name = setName(initBRU, initBRD, initBLD, initBLU);
    setColor(name, initFaceColors->back);
    colorDirection["initback"] = name % 10;
    glPushName(name);
    setMaterial(initFaceColors->back, spec1, amb1);
    glTranslated(initX, initY, initZ);
    glRotated(180.0, 0.0, 1.0, 0.0);
    glTranslated(-initX, -initY, -initZ);
    if (initFaceColors->back != 6) roundSq.drawSmooth(false);
    glPopName();
    glPopMatrix();


    glPushMatrix();
    name = setName(initBLU, initBLD, initFLD, initFLU);
    setColor(name, initFaceColors->left);
    colorDirection["initleft"] = name % 10;
    glPushName(name);
    setMaterial(initFaceColors->left, spec1, amb1);
    glTranslated(initX, initY, initZ);
    glRotated(-90.0, 0.0, 1.0, 0.0);
    glTranslated(-initX, -initY, -initZ);
    if (initFaceColors->left != 6) roundSq.drawSmooth(false);
    glPopName();
    glPopMatrix();


    glPushMatrix();
    name = setName(initBLU, initFLU, initFRU, initBRU);
    setColor(name, initFaceColors->top);
    colorDirection["inittop"] = name % 10;
    glPushName(name);
    setMaterial(initFaceColors->top, spec1, amb1);
    glTranslated(initX, initY, initZ);
    glRotated(-90.0, 1.0, 0.0, 0.0);
    glTranslated(-initX, -initY, -initZ);
    if (initFaceColors->top != 6) roundSq.drawSmooth(false);
    glPopName();
    glPopMatrix();


    glPushMatrix();
    name = setName(initBLD, initBRD, initFRD, initFLD);
    setColor(name, initFaceColors->bottom);
    colorDirection["initbottom"] = name % 10;
    glPushName(name);
    setMaterial(initFaceColors->bottom, spec1, amb1);
    glTranslated(initX, initY, initZ);
    glRotated(90.0, 1.0, 0.0, 0.0);
    glTranslated(-initX, -initY, -initZ);
    if (initFaceColors->bottom != 6) roundSq.drawSmooth(false);
    glPopName();
    glPopMatrix();


    glPushMatrix();
    setMaterial(6, spec0, amb0);
    glTranslated(initX, initY, initZ);
    cubie.drawSmooth(true);
    glPopMatrix();

    glPopMatrix();
}

void Cubie::changeColor(int face, int colorIdx)
{
    std::string Face = findKey(colorDirection, face);

    if (Face == "initleft")
        initFaceColors->left = colorIdx;

    else if (Face == "initright")
        initFaceColors->right = colorIdx;

    else if (Face == "inittop")
        initFaceColors->top = colorIdx;

    else if (Face == "initbottom")
        initFaceColors->bottom = colorIdx;

    else if (Face == "initfront")
        initFaceColors->front = colorIdx;

    else if (Face == "initback")
        initFaceColors->back = colorIdx;
}

void Cubie::place()
{
    updatePoints();
}

void Cubie::resetTransforms()
{
    angle.set(0.0f, 0.0f, 0.0f);
}

std::string Cubie::getColorInfo()
{
    std::string color = "";

    if (faceColors->front != 6)
    {
        color += std::to_string(faceColors->front);
    }
    if (faceColors->back != 6)
    {
        color += std::to_string(faceColors->back);
    }
    if (faceColors->top != 6)
    {
        color += std::to_string(faceColors->top);
    }
    if (faceColors->bottom != 6)
    {
        color += std::to_string(faceColors->bottom);
    }
    if (faceColors->left != 6)
    {
        color += std::to_string(faceColors->left);
    }
    if (faceColors->right != 6)
    {
        color += std::to_string(faceColors->right);
    }

    return color;
}


