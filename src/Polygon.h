#pragma once
#include <vector>

#include "GameObject.h"
#include "Vector2.h"

class Polygon :
    public GameObject
{
private:
    std::vector<Vector2> _points; //Exprimée relativement au centre de gravité du polygon


    // Hérité via GameObject
    virtual void Draw(Console& r_cons) override;

};

