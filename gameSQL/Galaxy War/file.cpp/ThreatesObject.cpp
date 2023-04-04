#include "ThreatesObject.h"
#include "Common_Function.h"
#include "AmoObject.h"
#include "BaseObject.h"
#include <cstdlib>
#include <ctime>

ThreatObject::ThreatObject()
{
	rect_.x = SCREEN_WIDTH;
	rect_.y = SCREEN_HEIGHT*0.5;
	rect_.w = WIDTH_THREAT;
	rect_.h = HEIGHT_THREAT;

	x_val_ = 0;
	y_val_ = 0;
}

ThreatObject::~ThreatObject()
{

}

void ThreatObject::InitAmo(AmoObject * p_amo1, AmoObject *p_amo2,AmoObject *p_amo3)
{
	if(p_amo1 != NULL)
	{
		bool ret1 = p_amo1->LoadImg("dan4.png");
		if(ret1 != NULL)
		{
			p_amo1->set_is_move(true);
			p_amo1->SetWidthHeight(WIDTH_SPHERE,HEIGHT_SPHERE);
			p_amo1->set_type(AmoObject::SPHERE);
			p_amo1->SetRect(rect_.x , rect_.y + rect_.h * 0.5);             // ví trị xuất hiện của đạn
			p_amo1_list_.push_back(p_amo1);
		}
	}
	if(p_amo2 != NULL)
	{
		bool ret2 = p_amo2->LoadImg("dan4.png");
		if(ret2 != NULL)
		{
			p_amo2->set_is_move(true);
			p_amo2->SetWidthHeight(WIDTH_SPHERE,HEIGHT_SPHERE);
			p_amo2->set_type(AmoObject::SPHERE);
			p_amo2->SetRect(rect_.x , rect_.y + rect_.h * 0.5);
			p_amo2_list_.push_back(p_amo2);
		}
	}

	if(p_amo3 != NULL)
	{
		bool ret3 = p_amo3->LoadImg("tenlua10.png");
		if(ret3 != NULL)
		{
			p_amo3->set_is_move(true);
			p_amo3->SetWidthHeight(WIDTH_SPHERE,HEIGHT_SPHERE);
			p_amo3->set_type(AmoObject::DB);
			p_amo3->SetRect(rect_.x , rect_.y + rect_.h * 0.5);
			p_amo3_list_.push_back(p_amo3);
		}
	}
}



void ThreatObject::MakeAmo(SDL_Surface *des , const int &x_limit ,const int & y_limit,const int &k)
{
	for(int i = 0; i < p_amo1_list_.size(); i++)
	{
		AmoObject* p_amo1 = p_amo1_list_.at(i);
		if(p_amo1)
		{
			if(p_amo1->get_is_move())
			{
				p_amo1->Show(des);
				p_amo1->HandleMoveRightToLeft1();             //đạn boss đi theo hướng của hàm
			}
			else 
			{
				p_amo1->set_is_move(true);
				p_amo1->SetRect(rect_.x , rect_.y + rect_.h * 0.5);
			}
		}
	}

	for(int j = 0; j < p_amo2_list_.size(); j++)
	{
		AmoObject* p_amo2 = p_amo2_list_.at(j);
		if(p_amo2)
		{
			if(p_amo2->get_is_move())
			{
				p_amo2->Show(des);
				p_amo2->HandleMoveRightToLeft2();
			}

			else 
			{
				p_amo2->set_is_move(true);
				p_amo2->SetRect(rect_.x , rect_.y + rect_.h * 0.5 );
			}
		}
	}

	for(int j = 0; j < p_amo3_list_.size(); j++)
	{
		AmoObject* p_amo3 = p_amo3_list_.at(j);
		if(p_amo3)
		{
			if(p_amo3->get_is_move())
			{
				p_amo3->Show(des);
				p_amo3->HandleMoveRightToLeft3(k);
			}

			else 
			{
				p_amo3->set_is_move(true);
				p_amo3->SetRect(rect_.x , rect_.y + rect_.h * 0.5 );
			}
		}
	}
}





void ThreatObject::HandleMove(const int & x_bordr , const int &y_bordr,int hangso)             //di chuyển thắng đứng của boss
{
	int k = 0 ;
	if(rect_.y < 10 ) { rect_.y += y_val_; k = 1;}
	if(hangso == 0 || k==1) {rect_.y += y_val_;}
	
	k = 0;
	if(rect_.y + HEIGHT_THREAT > SCREEN_HEIGHT) 
	{
		rect_.y -= y_val_; k = 1 ;
	}
	if(hangso == 1 || k==1 ) {rect_.y -= y_val_;}
}

void ThreatObject::HandleMove_0(const int & x_bordr , const int &y_bordr,int hangso)          // di chuyển ngang của boss
{
	int k = 0 ;
	if(rect_.x < 500 ) { rect_.x += x_val_; k = 1;}
	if(hangso == 0 || k==1) {rect_.x += x_val_;}
	
	k = 0;
	if(rect_.x + WIDTH_THREAT > SCREEN_WIDTH) 
	{
		rect_.x -= x_val_; k = 1 ;
	}
	if(hangso == 1 || k==1 ) {rect_.x -= x_val_;}
}

void ThreatObject::Reset(const int &xboder)                                          //xử lí đạn boss trúng nhân vật
{
	rect_.x  =  xboder + 700;
	if(p_amo3_list_.size() > 0 && xboder < p_amo3_list_.size())
	{
		for(int i = 0; i < p_amo3_list_.size();i++)
		{
			if(xboder < p_amo3_list_.size())
			{
				AmoObject* p_amo = p_amo3_list_.at(xboder);
				

				if(p_amo != NULL)
				 {
					 delete p_amo;
					 p_amo = NULL;
				
				}
			}
		}
	}

	if(p_amo2_list_.size() > 0 && xboder < p_amo2_list_.size())
	{
		for(int i = 0; i < p_amo2_list_.size();i++)
		{
			if(xboder < p_amo2_list_.size())
			{
				AmoObject* p_amo = p_amo2_list_.at(xboder);
				

				if(p_amo != NULL)
				 {
					 delete p_amo;
					 p_amo = NULL;
				
				}
			}
		}
	}

	if(p_amo1_list_.size() > 0 && xboder < p_amo1_list_.size())
	{
		for(int i = 0; i < p_amo1_list_.size();i++)
		{
			if(xboder < p_amo1_list_.size())
			{
				AmoObject* p_amo = p_amo1_list_.at(xboder);
				

				if(p_amo != NULL)
				 {
					 delete p_amo;
					 p_amo = NULL;
				
				 }
			}
		}
	}

}

void ThreatObject::ResetAmo()                   //khi boss ăn viên slow 
{
	srand(time(NULL));
	int k = rand()%(10 - 5 + 1) + 5;
	int i = rand()%5;  
	rect_.x = k*100;
	rect_.y = i*100;
}
