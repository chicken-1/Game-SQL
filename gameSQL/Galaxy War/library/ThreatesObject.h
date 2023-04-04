#ifndef THREATES_OBJECT_H_
#define THREATES_OBJECT_H_

#include "Common_Function.h"
#include "BaseObject.h"
#include "AmoObject.h"
#include<vector>

#define WIDTH_THREAT 80
#define HEIGHT_THREAT 88
class ThreatObject : public BaseObject
{
public:
	ThreatObject();
	~ThreatObject();
	
	void HandleMove (const int & x_bordr , const int &y_bordr, int hangso);            //Di chuyển boss radom theo chiều thẳng đứng

	void HandleMove_0 (const int & x_bordr , const int &y_bordr, int hangso);           //Di chuyển boss radom theo chiều ngang

	void HandleInputAction(SDL_Event events);             //Chưa dùng đến
	
	void set_x_val(const int &val ) {x_val_ = val;}                // Tốc độ bắn của boss theo chiều ngang
	int get_x_val() const {return x_val_ ;}


	int get_y_val() const {return y_val_ ;}                       //Tốc độ bắn của boss theo chiều thẳng đứng
	void set_y_val(const int &val ) {y_val_ = val;}

	void SetAmoList1(std::vector<AmoObject*> amo1_list) {p_amo1_list_ = amo1_list;}
	std::vector<AmoObject*> GetAmoList1() const {return p_amo1_list_;} 
	
	void SetAmoList2(std::vector<AmoObject*> amo2_list) {p_amo2_list_ = amo2_list;}               
	std::vector<AmoObject*> GetAmoList2() const {return p_amo2_list_;}

	void SetAmoList3(std::vector<AmoObject*> amo3_list) {p_amo3_list_ = amo3_list;}
	std::vector<AmoObject*> GetAmoList3() const {return p_amo3_list_;}

	void InitAmo(AmoObject * p_amo1, AmoObject *p_amo2,AmoObject *p_amo3);               //Khởi tạo 3 viên đạn cho Boss


	void MakeAmo(SDL_Surface *des , const int &x_limit ,const int & y_limit,const int& k );             //Show ra viên đạn được bắn như thế nào
																//Biến k là boss sẽ nhận được tốc độ bắn + k vào một khoảng thời gian sau khi ăn viên fast


	void Reset(const int &xboder);                    // Kiểm tra xem khi đạn của boss trúng nhân vật


	void ResetAmo();                       // Sau khi boss ăn viên slow 
private:
	int x_val_;
	int y_val_;
	int hangso;
	std::vector<AmoObject*> p_amo1_list_;
	std::vector<AmoObject*> p_amo2_list_;
	std::vector<AmoObject*> p_amo3_list_;
};



#endif 
