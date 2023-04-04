#ifndef AMO_OBJECT_H_
#define AMO_OBJECT_H_
#include "BaseObject.h"

#define WIDTH_LASER 35
#define HEIGHT_LASER 5

#define WIDTH_SPHERE 9
#define HEIGHT_SPHERE 9 

#define WIDTH_DB 70
#define HEIGHT_DB 15

#define WIDTH_BULLET 39
#define HEIGHT_BULLET 40

class AmoObject : public BaseObject
{
public:
    enum AmoType 
     {
     NONE = 0,
     LASER = 1,
     SPHERE = 2,
	 DB = 3
     };
    AmoObject();
    ~AmoObject();
    void HandleInputAction(SDL_Event events);    // chưa dùng đến

    void HandleMove(const int& x_border, const int& y_border,const int &k);      // Đạn cho nhân vật
	                                                                             //k là kiểu
	void HandleMoveRightToLeft1();
	void HandleMoveRightToLeft2();                             // Đạn cho boss
	void HandleMoveRightToLeft3(const int &k);

    int get_type() const {return amo_type_;}                   //Lấy số liệu từ enum Amotype
    void set_type(const int& type) {amo_type_ = type;}

    bool get_is_move() const {return is_move_;}                     // kiểm tra đúng sai        
    void set_is_move(bool is_move) {is_move_= is_move;}

    void SetWidthHeight(const int& width, const int& height) {rect_.w = width; rect_.h = height;};            //Lấy số liệu của rộng và dài của đạn

	void set_x_val(const int& val) {x_val_ = val;}     //Lấy tốc độ của đạn bắn theo trục nằm ngang 
    int get_x_val() const {return x_val_;}

	void set_y_val(const int& val) {y_val_ = val;}      //đạn trục oy
    int get_y_val() const {return y_val_;}

private:
	int k;
    int x_val_;
    int y_val_;
    bool is_move_;
    int amo_type_;
};



#endif
