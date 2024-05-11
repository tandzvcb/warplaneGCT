#ifndef TEXT_OBJECT_H_
#define TEXT_OBJECT_H_

#include "BaseObject.h"
#include "thuvien.h"


class TextObject : public BaseObject
{
public:
	enum TextColor
	{
		BLACK_TEXT = 0,
		RED_TEXT = 1,
		BLUE_TEXT = 2
	};

	TextObject();
	~TextObject();

	void SetText(std::string& text) {str_val_ = text;}
	void SetColor(const int& type);
	void CreateText (TTF_Font* font, SDL_Surface* des);
private:
	std::string str_val_;
	SDL_Color text_color_;
};

#endif