#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include"BaseObject.h"
#include"Common_Function.h"

const int EXP_WIDTH_MAIN = 230;
const int EXP_HEIGHT_MAIN = 230;

class ExplosionObject :public BaseObject
{
public:
    ExplosionObject();
    ~ExplosionObject();
    void set_clip2();
    void set_frame(const int& fr) {frame_ = fr;}
    void ShowEx(SDL_Surface* des);

private:
    int frame_;
    SDL_Rect clip_ [3];
};
#endif
