ma#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include"Common_Function.h"
#include"BaseObject.h"
#include "AmoObject.h"
#include <vector>

#define WIDTH_MAIN_OBJECT 86
#define HEIGHT_MAIN_OBJECT 91

class MainObject : public BaseObject
{
public:
	MainObject();
	~MainObject();

	int move_speed;

	void HandleInputAction(SDL_Event event);                //Bắt sự kiện từ bàn phím

	void HandleMove();               //Di chuyển của nhân vật đi được khoảng bao nhiêu so với chiều dài của ảnh 

	int RemoveAmo(const int &idx, int hp);           //Kiểm tra khi bắn trúng Boss được bao nhiêu viên


	void SetAmoList(std::vector<AmoObject*> amo_list) {p_amo_list_ = amo_list;}               // hàm vecto xác định ví trí của đạn theo nhân vật
	std::vector<AmoObject*> GetAmoList() const {return p_amo_list_;} 
private:
	int x_val_;
	int y_val_;
	int hp;
	std::vector<AmoObject*> p_amo_list_;
};


#endif
