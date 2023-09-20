#pragma once
#include "GameObject.h"
#include <vector>
#include "Vector2.h"

class Polygon :
    public GameObject
{
private:
    std::vector<Vector2> _points; //Exprim�e relativement au centre de gravit� du polygon


    // H�rit� via GameObject
    virtual void Draw(Console& r_cons) override;

};

