#include"Common_Function.h"
#include"MainObject.h"
#include"ThreatesObject.h"
#include <cstdlib>
#include <ctime>
#include"TextObject.h"
#include"ExplosionObject.h"
#include <math.h>

  

TTF_Font * g_font_text = NULL;

	bool Init()
	{
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return false;
	}
	g_screen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_SWSURFACE);

	if(g_screen == NULL)
		return false;

	if(TTF_Init() == -1)
	{
		return false;
	}

	g_font_text = TTF_OpenFont("Aller_Rg.ttf",35);      // Chen phong chu menu 
	return true;
}

int main(int arc, char*agrv[])
{
	Quaylai:

	bool is_quit = false;

	if(Init() == false)
		return 0;

	g_bkground = SDLCommonFunc::LoadImage("aa.png");              //Chen Backgound

	if(g_bkground == NULL)
	{
		return 0;
	}

	
    //Make MainObject
	MainObject human_object;
	human_object.SetRect(20,0);
	bool ret = human_object.LoadImg("boss.png");                  //Chen Anh nhan vat
	if(!ret)
	{
		return 0;
	}

	ExplosionObject exp_main;
    bool rett = exp_main.LoadImg("vunolon_update.png");
    exp_main.set_clip2();
    if (rett == false) return 0;
   


    //Make ThreatObject                 //gọi boss
    ThreatObject* p_threat = new ThreatObject();
    ret = p_threat->LoadImg("boss2.png");                                 //Chen anh boss
    if(ret == false)
        {return 0;}
	p_threat->SetRect(SCREEN_WIDTH - 100 , SCREEN_HEIGHT* 0.5);
    p_threat->set_y_val(4);                    // tốc độ di chuyển theo ox
	p_threat->set_x_val(15);                                // oy 

	//gọi 3 đạn cho boss
	AmoObject* p_amo1 = new AmoObject();
	AmoObject* p_amo2 = new AmoObject();
	AmoObject* p_amo3 = new AmoObject();

	p_threat->InitAmo(p_amo1 ,p_amo2, p_amo3);

	int k = 0;
	int d = 0;
	int kt1 = 0;
	int kt2 =0 ;
	int kt3 = 0;

	
	int ret_menu = SDLCommonFunc::ShowMenu(g_screen, g_font_text);
	if(ret_menu == 1)
	{
		return true;
	}

	//Make ItemsObject                   //items
	MainObject slow_bullet, fast_bullet;
    int x1=200, y1=20, a1=0, b1=0, x2=300, y2=500, a2=0, b2=0;           //gọi toạ độ
    srand(time(NULL));
    x1 = rand() % (200-100+1)+100;
    x2 = rand() % (300-100+1)+100;
    y1 = rand() % (500-100+1)+100;
    y2 = rand() %(500-100+1)+100;


	while(!is_quit)
	{
		srand(time(NULL));
		while(SDL_PollEvent(&g_even))
		{
			if(g_even.type == SDL_QUIT)
			{
				is_quit = true;
				break;
			}
			human_object.HandleInputAction(g_even);
		}


		SDLCommonFunc:: ApplySurface(g_bkground,g_screen,0,0);

		human_object.HandleMove();
        human_object.Show(g_screen);


        for(int i=0; i < human_object.GetAmoList().size(); i++)
        {
         std::vector<AmoObject*> amo_list = human_object.GetAmoList();
         AmoObject* p_amo = amo_list.at(i);
         if(p_amo != NULL)
         {
           if(p_amo->get_is_move())
           {
             p_amo->Show(g_screen);
			 p_amo->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT,kt2);


			 if(kt2 != 0 && k < 1500)    //khi nhân vật ăn items
			 {
				p_amo->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT,kt2);
				k++; 
				if(k > 160 && kt2 == 21){kt2 = 0;}
				if(k > 800 && kt2 == 15){kt2 = 0;}
			 }
           }
           else
           {
             if(p_amo != NULL)
             {
               amo_list.erase(amo_list.begin() + i);
               human_object.SetAmoList(amo_list);

               delete p_amo;
               p_amo = NULL;
             }
           }
         }

        }
		if(kt1!=0)
		{
		kt3++;
			if(kt3 > 300){kt1 = 0;kt3=0;}
		}
        //Run ThreatObject
		
		p_threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT,rand()%2);
        p_threat->Show(g_screen);
		p_threat->MakeAmo(g_screen,SCREEN_WIDTH,SCREEN_HEIGHT,kt1);
		

		//Run ItemObject


		if(d>=3)
		{
			bool is_col1 = SDLCommonFunc::CheckCollision(human_object.GetRect(), slow_bullet.GetRect());  //check va chạm giữa nhân vật và viên slow_bullet
			if(is_col1)
			{
			  srand(time(NULL));
			  x1 = rand() % 450;
			  a1 = rand() % (250-100+1)+100;
			  b1 = rand() % (250-100+1) + 100;
			  y1 = rand() % (550-50+1)+50;
			  k = 0;
			  kt2 = 15;
			}

			bool ret1 = slow_bullet.LoadImg("slow1.png");               //
			if(!ret1)
			{
	    		return 0;
    		}
			slow_bullet.SetRect(x1+a1+b1,y1);
			slow_bullet.Show(g_screen);
		   
			

			//check va chạm giữa nhân vật và viên fast_bullet
			 bool is_col2 = SDLCommonFunc::CheckCollision(human_object.GetRect(), fast_bullet.GetRect()); 
			if(is_col2)
			{
			  srand(time(NULL));
			  x2 = rand() % 370;
			  a2 = rand() % (300-100+1)+100;
			  b2 = rand() % (100-100+1) + 100;
			  y2 = rand() % (500-50+1)+50;
			  k = 0;
			  kt2 = 21;
			  
			}
			
			
			fast_bullet.SetRect(x2+a2+b2,y2);
        
		   bool ret2 = fast_bullet.LoadImg("fs.png");
			if(!ret2)
			{
	    		return 0;
    		}
			fast_bullet.Show(g_screen);
	     }

		bool vc1 = SDLCommonFunc::CheckCollision(p_threat->GetRect(),fast_bullet.GetRect());          //khi boss ăn viên fast
		if(vc1)
		{
			  kt1 = 10;
			  srand(time(NULL));
			  x2 = rand() % 400;
			  a2 = rand() % (350-100+1)+150;
			  b2 = rand() % (300-100+1) + 150;
			  y2 = rand() % (500-50+1)+50;
			  fast_bullet.SetRect(x2+a2+b2,y2);
			  fast_bullet.Show(g_screen);
		}
		/*p_threat->MakeAmo(g_screen,SCREEN_WIDTH,SCREEN_HEIGHT,kt1);*/
		bool vc2 = SDLCommonFunc::CheckCollision(p_threat->GetRect(),slow_bullet.GetRect());          //khi boss ăn viên slow
		if(vc2)
		{
			  srand(time(NULL));
			  x1 = rand() % 450;
			  a1 = rand() % (350-100+1)+150;
			  b1 = rand() % (300-100+1) + 150;
			  y1 = rand() % (500-50+1)+50;
			  slow_bullet.SetRect(x1+a1+b1,y1);
			  slow_bullet.Show(g_screen);
			  p_threat->ResetAmo();
		}


		//Khi người chơi va chạm vs boss
		bool is_col = SDLCommonFunc::CheckCollision(human_object.GetRect(),p_threat->GetRect());
		if (is_col)
		{

			//vụ nổ 
			for(int ex1 = 0; ex1 < 3; ex1++)
             {
                        int x_pos1 = (human_object.GetRect().x + human_object.GetRect().w*0.5) - EXP_WIDTH_MAIN*0.5;
                        int y_pos1 = (human_object.GetRect().y + human_object.GetRect().h*0.5) - EXP_HEIGHT_MAIN*0.5;

                        exp_main.set_frame(ex1);
                        exp_main.SetRect(x_pos1, y_pos1);
                        exp_main.ShowEx(g_screen);
                        //Update Screen
		                if(SDL_Flip(g_screen) == -1 )
                            return 0;
             }

			//game over 
			if(MessageBox(NULL,L"GAME OVER", L"Info" , MB_OK) == IDOK)
			{
				delete p_threat;
				goto Quaylai;
				/*SDLCommonFunc::CleanUp();
				SDL_Quit();
				return 1;*/
			}
		}
		

		//đạn của người chơi trúng boss
		std::vector<AmoObject*> amo_list = human_object.GetAmoList();
		for (int t = 0 ; t< amo_list.size(); t++)
		{
			AmoObject* p_amo = amo_list.at(t);

			if(p_amo != NULL)
			{
				bool ret_col = SDLCommonFunc::CheckCollision(p_amo->GetRect(),p_threat->GetRect());
				if(ret_col == true)
				{
					d = human_object.RemoveAmo(t,d);
					//d là số lần va chạm


					if(d==30) 
					{
						for(int ex1 = 0; ex1 < 3; ex1++)
						 {
							int x_pos1 = (p_threat->GetRect().x + p_threat->GetRect().w*0.5) - EXP_WIDTH_MAIN*0.5;
							int y_pos1 = (p_threat->GetRect().y + p_threat->GetRect().h*0.5) - EXP_HEIGHT_MAIN*0.5;

							exp_main.set_frame(ex1);
							exp_main.SetRect(x_pos1, y_pos1);
							exp_main.ShowEx(g_screen);
							//Update Screen
							if(SDL_Flip(g_screen) == -1 )
								return 0;
						 }

						if(MessageBox(NULL,L"YOU WIN", L"Info" , MB_OK) == IDOK)
						{
							delete p_threat;
							goto Quaylai;
							/*SDLCommonFunc::CleanUp();
							SDL_Quit();
							return 1;*/
						}
					}
					break;
				}
			}
		}
		if(d>=5)
			{
				p_threat->HandleMove_0(SCREEN_WIDTH, SCREEN_HEIGHT,rand()%2);
				p_threat->HandleMove_0(SCREEN_WIDTH, SCREEN_HEIGHT,rand()%2);	
			}

		if(d >= 17) 
			{
				 ;
			}



		// đạn của boss trúng người chơi
		std::vector<AmoObject*> amo_list3 = p_threat->GetAmoList3();
		for (int t = 0 ; t< amo_list3.size(); t++)
		{
			AmoObject* p_amo = amo_list3.at(t);

			if(p_amo != NULL)
			{
					bool ret_col3 = SDLCommonFunc::CheckCollision(p_amo->GetRect(),human_object.GetRect());
					if(ret_col3 == true)
					{
					p_threat->Reset(t);


					for(int ex1 = 0; ex1 < 3; ex1++)
                    {
                        int x_pos1 = (human_object.GetRect().x + human_object.GetRect().w*0.5) - EXP_WIDTH_MAIN*0.5;
                        int y_pos1 = (human_object.GetRect().y + human_object.GetRect().h*0.5) - EXP_HEIGHT_MAIN*0.5;

                        exp_main.set_frame(ex1);
                        exp_main.SetRect(x_pos1, y_pos1);
                        exp_main.ShowEx(g_screen);
                        //Update Screen
		                if(SDL_Flip(g_screen) == -1 )
                            return 0;
                    }


					if(MessageBox(NULL,L"GAME OVER" , L"Info", MB_OK) == IDOK)
					{
						delete p_threat;
						goto Quaylai;
					}
					

					break;
					
				}
			}
		}

		std::vector<AmoObject*> amo_list1 = p_threat->GetAmoList1();
		for (int t = 0 ; t< amo_list1.size(); t++)
		{
			AmoObject* p_amo = amo_list1.at(t);

			if(p_amo != NULL)
			{
					bool ret_col1 = SDLCommonFunc::CheckCollision(p_amo->GetRect(),human_object.GetRect());
					if(ret_col1 == true)
					{
					p_threat->Reset(t);

					for(int ex1 = 0; ex1 < 3; ex1++)
                    {
                        int x_pos1 = (human_object.GetRect().x + human_object.GetRect().w*0.5) - EXP_WIDTH_MAIN*0.5;
                        int y_pos1 = (human_object.GetRect().y + human_object.GetRect().h*0.5) - EXP_HEIGHT_MAIN*0.5;

                        exp_main.set_frame(ex1);
                        exp_main.SetRect(x_pos1, y_pos1);
                        exp_main.ShowEx(g_screen);
                        //Update Screen
		                if(SDL_Flip(g_screen) == -1 )
                            return 0;
                    }


					if(MessageBox(NULL,L"GAME OVER", L"Info" , MB_OK) == IDOK)
					{
						delete p_threat;
						goto Quaylai;
						/*SDLCommonFunc::CleanUp();
						SDL_Quit();
						return 1;*/
					}
					

					break;
					
				}
			}
		}

		std::vector<AmoObject*> amo_list2 = p_threat->GetAmoList2();
		for (int t = 0 ; t< amo_list2.size(); t++)
		{
			AmoObject* p_amo = amo_list2.at(t);

			if(p_amo != NULL)
			{
					bool ret_col2 = SDLCommonFunc::CheckCollision(p_amo->GetRect(),human_object.GetRect());
					if(ret_col2 == true)
					{
					p_threat->Reset(t);

					for(int ex1 = 0; ex1 < 3; ex1++)
                    {
                        int x_pos1 = (human_object.GetRect().x + human_object.GetRect().w*0.5) - EXP_WIDTH_MAIN*0.5;
                        int y_pos1 = (human_object.GetRect().y + human_object.GetRect().h*0.5) - EXP_HEIGHT_MAIN*0.5;

                        exp_main.set_frame(ex1);
                        exp_main.SetRect(x_pos1, y_pos1);
                        exp_main.ShowEx(g_screen);
                        //Update Screen
		                if(SDL_Flip(g_screen) == -1 )
                            return 0;
                    }


					if(MessageBox(NULL,L"GAME OVER", L"Info" , MB_OK) == IDOK)
					{
						delete p_threat;
						goto Quaylai;
						/*SDLCommonFunc::CleanUp();
						SDL_Quit();
						return 1;*/
					}
					

					break;
					
				}
			}
		}
		

		if(SDL_Flip(g_screen) == -1 )
			return 0;
	} 

	SDLCommonFunc::CleanUp();
	SDL_QUIT;
	return 1;
}
