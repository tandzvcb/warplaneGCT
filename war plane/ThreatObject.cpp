
#include "thuvien.h"
#include "ThreatObject.h"

ThreatObject::ThreatObject()
{
	rect_.x = SCREEN_WIDTH;            // v? trí ban ??u c?a ??i t??ng m?i ?e d?a ???c ??t ? c?nh ph?i c?a màn hình 
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
	rect_.x -= x_val_;   //M?i ?e d?a di chuy?n t? ph?i sang trái 
	int rand_y = 0;
	if(rect_.x < 0)
	{
		rect_.x = SCREEN_WIDTH;//  N?u m?i ?e d?a di chuy?n ra kh?i phía trái c?a màn hình nó s? ???c ??t l?i ? phía bên ph?i c?a màn hình m?t v? trí ng?u nhiên theo chi?u d?c.
		rand_y = rand()% 600 + 1;
		if(rand_y > SCREEN_HEIGHT - UNDER_LIMIT_THREAT)
		{
			rand_y = SCREEN_HEIGHT * 0.3;
		}
		rect_.y = rand_y;
	}
	c
}

void ThreatObject::InitBullet(BulletObject* p_bullet) //kh?i t?o ??n cho m?i ?e d?a.
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
			p_bullet->set_x_val(1);
			p_bullet_list.push_back(p_bullet);
		}

	}

}

void ThreatObject::MakeBullet(SDL_Surface* des, const int& x_limit, const int& y_limit)   // t?o và di chuy?n các viên ??n c?a m?i ?e d?a.
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


void ThreatObject::Reset(const int& x_border)      // ??t l?i v? trí c?a m?i ?e d?a khi nó ?ã ?i ra kh?i màn hình.
{
	rect_.x = x_border;
	int rand_y = rand()% 600 + 10;
	if(rand_y > SCREEN_HEIGHT - UNDER_LIMIT_THREAT)
	{
		rand_y = SCREEN_HEIGHT * 0.3;
	}
	rect_.y = rand_y;

}