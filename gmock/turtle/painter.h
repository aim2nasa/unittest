#ifndef __PAINTER_H__
#define __PAINTER_H__

#include "turtle.h"

class Painter
{
        Turtle *turtle_;
public:
        Painter( Turtle *turtle): turtle_(turtle){}

        bool DrawCircle(int, int, int)
        {
                turtle_->PenDown();
                return true;
        }
};

#endif
