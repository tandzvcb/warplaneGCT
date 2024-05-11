#include "TextObject.h"

TextObject::TextObject()
{
	rect_.x = 0;
	rect_.y = 0;
	text_color_.r = 255;
	text_color_.g = 215;
	text_color_.b = 0;
}

TextObject::~TextObject()
{

}

void TextObject::SetColor(const int& type)
{
	if(type == BLACK_TEXT)
	{
		SDL_Color color = {0, 0, 0};
		text_color_ = color;
	}
	if(type == RED_TEXT)
	{
		SDL_Color color = {255, 0, 0};
		text_color_ = color;
	}
	if(type == BLUE_TEXT){
		SDL_Color color = {0, 0, 255};
		text_color_ = color;
	}
}

void TextObject::CreateText(TTF_Font* font, SDL_Surface* des)
{
	p_object_ = TTF_RenderText_Solid(font, str_val_.c_str(), text_color_);		// tao ra doi tuong co mau sac, font chu
	Show(des);
}