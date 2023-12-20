#include "rubixcube.h"

RubixCube::RubixCube()
{
    sizeRubix = 0;
    isAnimate = false;
    current = nullptr;
    listCubies = nullptr;
}

RubixCube::RubixCube(int data[6][3][3], int num)
{
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            for(int k = 0; k < 3; k++)
            {
                _data[i][j][k] = data[i][j][k];
            }
        }
    }

    sizeRubix = num;
    current = nullptr;

    listCubies = new std::vector<Cubie*>;

    isAnimate = false;

    size = 2.25 / 5.0;

    int id = 1;

    blockSpace = (2 * size) + (2.0 * size / 4.4);

    for (float x = -0.5 * (num - 1) * blockSpace; x <= 0.5 * (num - 1) * blockSpace; x += blockSpace)
    {
        for (float y = -0.5 * (num - 1) * blockSpace; y <= 0.5 * (num - 1) * blockSpace; y += blockSpace)
        {
            for (float z = -0.5 * (num - 1) * blockSpace; z <= 0.5 * (num - 1) * blockSpace; z += blockSpace)
            {
                FaceCubie* cubieColor = generateCubieColor(x, y, z);
                listCubies->push_back(new Cubie(size, Vector3(x, y, z), id, cubieColor, num));
                id++;
            }
        }
    }
}

RubixCube::~RubixCube()
{
    if (listCubies)
    {
        for (unsigned int i = 0; i < listCubies->size(); i++)
        {
            delete listCubies->at(i);
        }

        listCubies->clear();

        delete listCubies;
        listCubies = nullptr;
    }

    if (current)
    {
        delete current;
        current = nullptr;
    }
}

bool RubixCube::checkIdle()
{
    if (current)
        return true;

    for (unsigned int i = 0; i < listCubies->size(); i++)
    {
        if (listCubies->at(i)->idle) return true;
    }

    return false;
}

FaceCubie* RubixCube::generateCubieColor(float x, float y, float z)
{
    FaceCubie* cubieColor = new FaceCubie(4, 5, 2, 3, 0, 1);

    if (x < 0.5 * (sizeRubix - 1) * blockSpace)
        cubieColor->right = 6;

    if (x > -0.5 * (sizeRubix - 1) * blockSpace)
        cubieColor->left = 6;

    if (y < 0.5 * (sizeRubix - 1) * blockSpace)
        cubieColor->top = 6;

    if (y > -0.5 * (sizeRubix - 1) * blockSpace)
        cubieColor->bottom = 6;

    if (z < 0.5 * (sizeRubix - 1) * blockSpace)
        cubieColor->front = 6;

    if (z > -0.5 * (sizeRubix - 1) * blockSpace)
        cubieColor->back = 6;

    return cubieColor;
}

Cubie* RubixCube::findCubieById(int id)
{
    for (unsigned int i = 0; i < listCubies->size(); i++)
    {
        if (listCubies->at(i)->id == id)
            return listCubies->at(i);
    }

    return nullptr;
}

bool RubixCube::checkFinalState()
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                if (_data[i][j][k] != _data[i][1][1])
                    return false;
            }
        }
    }

    return true;
}

char* RubixCube::generateConfig()
{
    char *str = new char[54];

    int stt[] = { 2, 1, 4, 3, 0, 5 };

    int idx = 0;

    for (int k = 0; k < 6; k++)
    {
        int t = stt[k];
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (_data[t][i][j] == _data[0][1][1])
                    str[idx] = 'L';

                else if (_data[t][i][j] == _data[1][1][1])
                    str[idx] = 'R';

                else if (_data[t][i][j] == _data[2][1][1])
                    str[idx] = 'U';

                else if (_data[t][i][j] == _data[3][1][1])
                    str[idx] = 'D';

                else if (_data[t][i][j] == _data[4][1][1])
                    str[idx] = 'F';

                else if (_data[t][i][j] == _data[5][1][1])
                    str[idx] = 'B';

                idx++;
            }
        }
    }

    return str;
}

void RubixCube::setDelta(float delta)
{
    this->delta = delta;
}

void RubixCube::manipulate(Moviment *moviment)
{
    current = new Rotation(listCubies, moviment);
    delete moviment;
}

void RubixCube::render(bool isPress)
{
    update();

    for(unsigned int i = 0; i < listCubies->size(); i++)
        listCubies->at(i)->render(isPress);
}

void RubixCube::update()
{
    if (current)
    {
        if (current->getSpecial() == 1)
        {
            if (!current->getAnimateEnded())
                current->animate(delta);
            else
                stop();
        }
        else
            current->animate(delta);
    }

    delta = 0;
}

void RubixCube::stop()
{
    if (current)
    {
        delete current;
        current = nullptr;
    }
}

void RubixCube::matchCube2Data()
{
    int count = 1;
    int COL = sizeRubix - 1, ROW = sizeRubix - 1;

    for (int col = 0; col <= COL; col++)
    {
        for (int row = ROW; row >= 0; row--)
        {
            _data[FRONT][row][col] = findCubieById((ROW + 1) * count)->faceColors->front;

            count++;
        }
    }

    count = 1;
    for (int col = COL; col >= 0; col--)
    {
        for (int row = ROW; row >= 0; row--)
        {
            _data[BACK][row][col] = findCubieById(count)->faceColors->back;

            count += COL + 1;
        }
    }

    count = 1;
    for (int row = ROW; row >= 0; row--)
    {
        for (int col = 0; col <= COL; col++)
        {
            _data[LEFT][row][col] = findCubieById(count)->faceColors->left;

            count++;
        }
    }

    count = (ROW + 1) * (ROW + 1) * (ROW + 1);
    for (int row = 0; row <= ROW; row++)
    {
        for (int col = 0; col <= COL; col++)
        {
            _data[RIGHT][row][col] = findCubieById(count)->faceColors->right;

            count--;
        }
    }

    count = 0;
    for (int col = 0; col <= COL; col++)
    {
        count += (COL + 1) * (ROW + 1) + 1 - (COL + 1);
        for (int row = 0; row <= ROW; row++)
        {
            _data[TOP][row][col] = findCubieById(count)->faceColors->top;

            if (row < ROW)
                count++;
        }
    }

    count = 1;
    for (int col = 0; col <= COL; col++)
    {
        for (int row = ROW; row >= 0; row--)
        {
            _data[BOTTOM][row][col] = findCubieById(count + ((COL + 1) * (ROW + 1) + 1 - (COL + 1)) * col)->faceColors->bottom;

            if (row > 0)
                count++;
        }
    }
}

void RubixCube::matchData2Cube(int data[6][3][3])
{
    int count = 1;
    int COL = sizeRubix - 1, ROW = sizeRubix - 1;

    Cubie *cube;

    for (int col = 0; col <= COL; col++)
    {
        for (int row = ROW; row >= 0; row--)
        {
            _data[FRONT][row][col] = data[FRONT][row][col];
            cube = findCubieById((ROW + 1) * count);
            cube->changeColor(FRONT, data[FRONT][row][col]);
            count++;
        }
    }

    count = 1;
    for (int col = COL; col >= 0; col--)
    {
        for (int row = ROW; row >= 0; row--)
        {
            _data[BACK][row][col] = data[BACK][row][col];
            cube = findCubieById(count);
            cube->changeColor(BACK, data[BACK][row][col]);
            count += COL + 1;
        }
    }

    count = 1;
    for (int row = ROW; row >= 0; row--)
    {
        for (int col = 0; col <= COL; col++)
        {
            _data[LEFT][row][col] = data[LEFT][row][col];
            cube = findCubieById(count);
            cube->changeColor(LEFT, data[LEFT][row][col]);
            count++;
        }
    }

    count = (ROW + 1) * (ROW + 1) * (ROW + 1);
    for (int row = 0; row <= ROW; row++)
    {
        for (int col = 0; col <= COL; col++)
        {
            _data[RIGHT][row][col] = data[RIGHT][row][col];
            cube = findCubieById(count);
            cube->changeColor(RIGHT, data[RIGHT][row][col]);
            count--;
        }
    }

    count = 0;
    for (int col = 0; col <= COL; col++)
    {
        count += (COL + 1) * (ROW + 1) + 1 - (COL + 1);
        for (int row = 0; row <= ROW; row++)
        {
            _data[TOP][row][col] = data[TOP][row][col];
            cube = findCubieById(count);
            cube->changeColor(TOP, data[TOP][row][col]);

            if (row < ROW)
                count++;
        }
    }

    count = 1;
    for (int col = 0; col <= COL; col++)
    {
        for (int row = ROW; row >= 0; row--)
        {
            _data[BOTTOM][row][col] = data[BOTTOM][row][col];
            cube = findCubieById(count + ((COL + 1) * (ROW + 1) + 1 - (COL + 1)) * col);
            cube->changeColor(BOTTOM, data[BOTTOM][row][col]);

            if (row > 0)
                count++;
        }
    }
}



