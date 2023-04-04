#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_
#include "Common_Function.h"

class BaseObject
{
public:
	BaseObject();
	~BaseObject();
	void Show(SDL_Surface* des);

	bool LoadImg(const char* file_name);           //Kiểm tra xem có load được ảnh ko


	void SetRect(const int &x,const int &y){ rect_.x = x , rect_.y = y;}        //Toạ độ mà ảnh hiện ra   
	SDL_Rect GetRect() const {return rect_;}

	SDL_Surface* GetObject(){return p_object_;}         //
protected:
	SDL_Rect rect_;
	SDL_Surface* p_object_;
};
#endif
