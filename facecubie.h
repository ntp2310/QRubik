#ifndef FACECUBIE_H
#define FACECUBIE_H


class FaceCubie
{
public:
    int left;
    int right;
    int top;
    int bottom;
    int front;
    int back;

public:
    FaceCubie(int front, int back, int top, int bottom, int left, int right)
    {
        this->left = left;
        this->right = right;
        this->top = top;
        this->bottom = bottom;
        this->front = front;
        this->back = back;       
    }

    FaceCubie(FaceCubie *a)
    {
        this->left = a->left;
        this->right = a->right;
        this->top = a->top;
        this->bottom = a->bottom;
        this->front = a->front;
        this->back = a->back;
    }
};

#endif // FACECUBIE_H

