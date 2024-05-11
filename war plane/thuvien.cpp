
#include"thuvien.h"
#include"TextObject.h"

bool SDLCommonFunc::CheckForcusWithRect(const int& x, const int& y, const SDL_Rect& rect)
{
	if(x >= rect.x && x < rect.x + rect.w && 
		y >= rect.y && y <= rect.y + rect.h)
	{
		return true;
	}
	return false;

}
int SDLCommonFunc::ShowMenu(SDL_Surface* des, TTF_Font* font)
{

	std::ifstream file("best_score.txt");

	gMenu  = LoadImage("img/menu.png");
	if(gMenu == NULL){
		return 1;
	}


	const int kMenuItemNum = 2;
	SDL_Rect pos_arr[kMenuItemNum];
	pos_arr[0].x = 535;
	pos_arr[0].y = 380;

	pos_arr[1].x = 535;
	pos_arr[1].y = 430;

	

	TextObject best_score;
	best_score.SetColor(TextObject::BLACK_TEXT);
	best_score.SetRect(535,480);

	TextObject text_menu[kMenuItemNum];

	std::string strMenu1("Play game");
	text_menu[0].SetText(strMenu1);
	text_menu[0].SetColor(TextObject::BLACK_TEXT);
	text_menu[0].SetRect(pos_arr[0].x, pos_arr[0].y);

	std::string strMenu2("Exit game");
	text_menu[1].SetText(strMenu2);
	text_menu[1].SetColor(TextObject::BLACK_TEXT);
	text_menu[1].SetRect(pos_arr[1].x, pos_arr[1].y);


	bool selected[kMenuItemNum] = {0, 0};
	int xm = 0;
	int ym = 0;

	SDL_Event m_event;
	while(true)
	{
		
		SDLCommonFunc::ApplySurface(gMenu, des, 0, 0);
		
		int high_score;
		file >> high_score;

		std::string strbest("Best socre: ");
		std::string strbest1 = std::to_string(high_score);
		strbest += strbest1;

		best_score.SetText(strbest);
		best_score.CreateText(font, des);

		for(int i = 0; i < kMenuItemNum; i++)
		{
			text_menu[i].CreateText(font, des);
		}

		while(SDL_PollEvent(&m_event))
		{
			//Mix_PlayChannel(-1, sound, 0);
			switch (m_event.type)
			{
			case SDL_QUIT:
				return 1;
			case SDL_MOUSEMOTION:
				{
					xm = m_event.motion.x;
					ym = m_event.motion.y;

					for(int i = 0; i < kMenuItemNum; i++)
					{
						if(CheckForcusWithRect(xm, ym, text_menu[i].GetRect()))
						{
							if(selected[i] == false)
							{
								selected[i] = true;
								text_menu[i].SetColor(TextObject::RED_TEXT);
							}
						}
						else
						{
							if(selected[i] == true)
							{
								selected[i] = false;
								text_menu[i].SetColor(TextObject::BLACK_TEXT);
							}
						}
					}
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				{
					xm = m_event.button.x;
					ym = m_event.button.y;
					for(int i = 0; i < kMenuItemNum; i++)
					{
						if(CheckForcusWithRect(xm, ym, text_menu[i].GetRect()))
						{
							
							return i;
						}
					}

				}
			default:
				break;
			case SDL_KEYDOWN:
				if(m_event.key.keysym.sym == SDLK_ESCAPE)
				{
					return 1;
				}
			}
		}

		SDL_Flip(des);
	}


	return 1;
}


SDL_Surface* SDLCommonFunc::LoadImage(std::string file_path)
{
	SDL_Surface* loadImage = NULL;				// lưu trữ hình ảnh từ file
	SDL_Surface* optimizeImage = NULL;			// lưu trữ hình ảnh được tối ưu hóa

	loadImage = IMG_Load(file_path.c_str());

	if(loadImage != NULL)
	{
		optimizeImage = SDL_DisplayFormat(loadImage);			// tối ưu hóa hình ảnh
		SDL_FreeSurface(loadImage);

		if(optimizeImage != NULL)
		{
				// loại bỏ background của cái đối tượng con
				UINT32 color_key = SDL_MapRGB(optimizeImage->format, 255, 255, 255);		
				SDL_SetColorKey(optimizeImage, SDL_SRCCOLORKEY, color_key);

		}
	}
	return optimizeImage;
}

SDL_Rect SDLCommonFunc::ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y)				// vẽ lên tọa độ cụ thể
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(src, NULL, des, &offset);

	return offset;
}


void SDLCommonFunc::ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x ,int y)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(src, clip, des, &offset);
}


bool SDLCommonFunc::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
	int left_a = object1.x;
	int right_a = object1.x + object1.w;
	int top_a = object1.y;
	int bottom_a = object1.y + object1.h;

	int left_b = object2.x;
	int right_b = object2.x + object2.w;
	int top_b = object2.y;
	int bottom_b = object2.y + object2.h;

	// Case 1: size object 1 > size object 2
	if (left_a > left_b && left_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b)
		{
			return true;
		}
	}

	if (left_a > left_b && left_a < right_b)
	{
		if (bottom_a > top_b && bottom_a < bottom_b)
		{
			return true;
		}
	}

	if (right_a > left_b && right_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b)
		{
			return true;
		}
	}

	if (right_a > left_b && right_a < right_b)
	{
		if (bottom_a > top_b && bottom_a < bottom_b)
		{
			return true;
		}
	}

	// Case 2: size object 1 < size object 2
	if (left_b > left_a && left_b < right_a)
	{
		if (top_b > top_a && top_b < bottom_a)
		{
			return true;
		}
	}

	if (left_b > left_a && left_b < right_a)
	{
		if (bottom_b > top_a && bottom_b < bottom_a)
		{
			return true;
		}
	}

	if (right_b > left_a && right_b < right_a)
	{
		if (top_b > top_a && top_b < bottom_a)
		{
			return true;
		}
	}

	if (right_b > left_a && right_b < right_a)
	{
		if (bottom_b > top_a && bottom_b < bottom_a)
		{
			return true;
		}
	}

	// Case 3: size object 1 = size object 2
	if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
	{
		return true;
	}

	return false;

}

void SDLCommonFunc::CleanUp()
{
	SDL_FreeSurface(gScreen);
	SDL_FreeSurface(gBkground);
}