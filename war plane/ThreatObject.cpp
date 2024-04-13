
#include "thuvien.h"
#include "ThreatObject.h"

ThreatObject::ThreatObject()
{
	rect_.x = SCREEN_WIDTH;
	rect_.y = SCREEN_HEIGHT;
	rect_.w = WIDTH_THREAT;
	rect_.h = HEIGHT_THREAT;
	
	x_val_ = 0;
	y_val_ = 0;
}
ThreatObject::~ThreatObject()
{
	
}

void ThreatObject::HandleMove(const int & x_border, const int& y_border)
{
	rect_.x -= x_val_;
	int rand_y = 0;
	if(rect_.x < 0)
	{
		rect_.x = SCREEN_WIDTH;
		rand_y = rand()% 600 + 1;
		if(rand_y > SCREEN_HEIGHT - UNDER_LIMIT_THREAT)
		{
			rand_y = SCREEN_HEIGHT * 0.3;
		}
		rect_.y = rand_y;
	}

}

void ThreatObject::InitBullet(BulletObject* p_bullet)
{
	if(p_bullet != NULL)
	{
		bool ret = p_bullet->LoadImg("img/bullet_threat.png");

		if(ret)
		{
			p_bullet->set_is_move(true);
			p_bullet->SetWidthHeight(WIDTH_BULLET, WIDTH_BULLET);
			p_bullet->set_type(BulletObject::BULLET_THREAT);
			p_bullet->SetRect(rect_.x, rect_.y + rect_.h * 0.5 );
			p_bullet->set_x_val(8);
			p_bullet_list.push_back(p_bullet);
		}

	}

}

void ThreatObject::MakeBullet(SDL_Surface* des, const int& x_limit, const int& y_limit)
{
	for(int i = 0; i < p_bullet_list.size(); i++)
	{
		BulletObject* p_bullet = p_bullet_list.at(i);
		if(p_bullet)
		{
			if(p_bullet->get_is_move())
			{
				p_bullet->HandleMoveRightToLeft();
				p_bullet->Show(des);
			}
			else{
				// xet lai vi tri ban dau cho dan
				p_bullet->set_is_move(true);
				p_bullet->SetRect(rect_.x, rect_.y + rect_.h * 0.5);
			}
		}
	}

}


void ThreatObject::Reset(const int& x_border)
{
	rect_.x = x_border;
	int rand_y = rand()% 600 + 10;
	if(rand_y > SCREEN_HEIGHT - UNDER_LIMIT_THREAT)
	{
		rand_y = SCREEN_HEIGHT * 0.3;
	}
	rect_.y = rand_y;

}