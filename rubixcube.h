#ifndef RUBIXCUBE_H
#define RUBIXCUBE_H

#include "utils.h"
#include "matrices.h"
#include "vectors.h"
#include "cubie.h"
#include "facecubie.h"
#include "rotation.h"

class RubixCube
{
private:
    int     sizeRubix;  
    bool    isAnimate;
    float   size;
    float   blockSpace;
    float   delta;

    std::vector<Cubie*> *listCubies;

    Rotation* current;

public:
    int     _data[6][3][3];

    RubixCube();

    RubixCube(int rubikData[6][3][3], int num);

    ~RubixCube();

    bool checkIdle();

    FaceCubie* generateCubieColor(float x, float y, float z);

    Cubie* findCubieById(int id);

    bool checkFinalState();

    char* generateConfig();

    void setDelta(float delta);

    void manipulate(Moviment *moviment);

    void render(bool isPress);

    void update();

    void stop();

    void matchCube2Data();

    void matchData2Cube(int data[6][3][3]);
};

#endif // RUBIXCUBE_H

