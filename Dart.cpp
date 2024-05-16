#include "Dart.h"
Dart ::Dart()
{
    rect.x = 0;
    rect.y = 0;
    rect.h =0;
    rect.w = 0;

}

Dart :: ~Dart()
{

}
void Dart::setRect(const int &x,const int &y)
    {
        rect.x = x;
        rect.y = y;
        rect.h = Height_Dart;
        rect.w = Width_Dart;

    }
void Dart::MoveDart(const int& x_border, const int &y_border)
{
    if(bullet_status == Right_) // Walk Right
     {
         rect.x += DART_SPEED;
        if (rect.x >= x_border)
        {
            ismove = false;
        }
     }
     else{
        rect.x -= DART_SPEED;
        if (rect.x <= 0)
        {
            ismove = false;
        }
     }

}

