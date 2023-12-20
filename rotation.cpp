#include "rotation.h"

Rotation::Rotation(std::vector<Cubie*>* animationCubes, Vector3 pos, bool clockwise, int axis, int special)
{
    listCubies = animationCubes;
    choosenCubies = new std::vector<Cubie*>;

    this->clockwise = clockwise;
    this->axis = axis;
    this->special = special;

    animationEnded = false;

    size = 3;

    for (unsigned int i = 0; i < listCubies->size(); i++)
    {
        if (round(listCubies->at(i)->position[axis] - pos[axis]) == 0)
            choosenCubies->push_back(listCubies->at(i));

        if (choosenCubies->size() == size * size) break;
    }

    if (special)
        leftDegree = (clockwise) ? -90.0f : 90.0f;

    angle = 90.0f;
}

Rotation::Rotation(std::vector<Cubie*>* animationCubes, Moviment* moviment)
{
    listCubies = animationCubes;
    choosenCubies = new std::vector<Cubie*>;

    this->clockwise = moviment->clockwise;
    this->axis = moviment->axis;
    this->special = moviment->special;
    this->angle = moviment->angle;

    animationEnded = false;

    size = 3;

    for (unsigned int i = 0; i < listCubies->size(); i++)
    {
        if (round(listCubies->at(i)->position[this->axis] - moviment->position[this->axis]) == 0)
        {
            if (listCubies->at(i)->idle)
            {
                choosenCubies->clear();
                break;
            }

            choosenCubies->push_back(listCubies->at(i));
        }

        if (choosenCubies->size() == size * size) break;
    }

    if (special)
        leftDegree = (clockwise) ? -moviment->angle : moviment->angle;
}

Rotation::~Rotation()
{
    choosenCubies = nullptr;
    listCubies = nullptr;
}

int Rotation::getSpecial()
{
    return special;
}

bool Rotation::getAnimateEnded()
{
    return animationEnded;
}

void Rotation::animate(float delta)
{
    if (special) delta = 2.0 * angle / fabs(angle);

    if (clockwise) delta = -delta;

    if (!choosenCubies->empty())
    {
        for (unsigned int i = 0; i < choosenCubies->size(); i++)
            choosenCubies->at(i)->rotate(delta, axis, special);
    }

    if (special == 1)
    {
        leftDegree -= delta;
        if (leftDegree == 0)
        {
            for (unsigned int i = 0; i < choosenCubies->size(); i++)
                choosenCubies->at(i)->place();

            animationEnded = true;
        }
    }
}
