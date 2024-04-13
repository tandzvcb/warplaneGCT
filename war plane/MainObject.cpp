
#include "MainObject.h"


MainObject::MainObject()		//construtor
{
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = WIDTH_MAIN_OBJECT;
	rect_.h = HEIGHT_MAIN_OBJECT;
	x_val_ = 0;
	y_val_ = 0;
	
}

MainObject::~MainObject()
{
	if(p_object_ != NULL)SDL_FreeSurface(p_object_);
}

void MainObject::HandleInputAction(SDL_Event events)		
{
	if(events.type == SDL_KEYDOWN)
	{
		switch(events.key.keysym.sym)
		{
		case SDLK_UP:
			y_val_ -= HEIGHT_MAIN_OBJECT / 8;

			break;
		case SDLK_DOWN:
			y_val_ += HEIGHT_MAIN_OBJECT / 8;
			break;
		case SDLK_RIGHT:
			x_val_ += WIDTH_MAIN_OBJECT  / 8;

			break;
		case SDLK_LEFT:
			x_val_ -= WIDTH_MAIN_OBJECT / 8;
			break;
		
		}
	}
	else if(events.type == SDL_KEYUP)
	{
		switch(events.key.keysym.sym)
		{
		case SDLK_UP: y_val_ += HEIGHT_MAIN_OBJECT / 8; break;
		case SDLK_DOWN: y_val_ -= HEIGHT_MAIN_OBJECT / 8; break;
		case SDLK_LEFT: x_val_ += WIDTH_MAIN_OBJECT/8;break;
		case SDLK_RIGHT: x_val_ -= WIDTH_MAIN_OBJECT / 8; break;
		}
	}
	if(events.type == SDL_MOUSEBUTTONDOWN){
		if(events.button.button == SDL_BUTTON_LEFT){
			CreateBullet();
		}
	}
}
void MainObject::CreateBullet()
{
	BulletObject* p_bullet = new BulletObject();
	p_bullet->SetWidthHeight(WIDTH_BULLET, WIDTH_BULLET);
	p_bullet->LoadImg("img/bullet_main.png");
	p_bullet->set_type(BulletObject::BULLET_MAIN);

	p_bullet->SetRect(this->rect_.x + this->rect_.w - 30 , this->rect_.y + this->rect_.h * 0.8);
	p_bullet->set_is_move(true);
	p_bullet->set_x_val(8);

	p_bullet_list.push_back(p_bullet);
	
}

void MainObject::MakeBullet(SDL_Surface* des)
{
	for(int i = 0; i < p_bullet_list.size(); i++)
		{
			
			BulletObject* p_bullet = p_bullet_list.at(i);
			if(p_bullet != NULL)
			{
				if(p_bullet->get_is_move())
				{
					p_bullet->HandleMove(SCREEN_WIDTH , SCREEN_HEIGHT);
					p_bullet->Show(des);
				}
				else 
				{
					if(p_bullet != NULL)
					{
						p_bullet_list.erase(p_bullet_list.begin() + i);
						delete p_bullet;
						p_bullet = NULL;
					}
				}
			}
		}
}

void MainObject::HandleMove() 
{
	
	rect_.x += x_val_;
	if(rect_.x < 0 || rect_.x + WIDTH_MAIN_OBJECT > SCREEN_WIDTH){
		rect_.x -= x_val_;
	}
	rect_.y += y_val_;
	if(rect_.y < 0 || rect_.y + HEIGHT_MAIN_OBJECT > SCREEN_HEIGHT - 200)
	{
		rect_.y -= y_val_;

	}
}
