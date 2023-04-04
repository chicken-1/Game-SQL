#include"ExplosionObject.h"

ExplosionObject::ExplosionObject()
{

}

ExplosionObject::~ExplosionObject()
{

}
void ExplosionObject::set_clip2()
{
  clip_[0].x = 0;
  clip_[0].y = 0;
  clip_[0].w = EXP_WIDTH_MAIN;
  clip_[0].h = EXP_HEIGHT_MAIN;

  clip_[1].x = EXP_WIDTH_MAIN;
  clip_[1].y = 0;
  clip_[1].w = EXP_WIDTH_MAIN;
  clip_[1].h = EXP_HEIGHT_MAIN;

  clip_[2].x = 2*EXP_WIDTH_MAIN;
  clip_[2].y = 0;
  clip_[2].w = EXP_WIDTH_MAIN;
  clip_[2].h = EXP_HEIGHT_MAIN;
}

void ExplosionObject::ShowEx(SDL_Surface* des)
{
    if(frame_ >= 3)
    {
        frame_ = 0;
    }

	SDLCommonFunc::ApplySurfaceVideo(this->p_object_, des, &clip_[frame_], rect_.x, rect_.y);
}
