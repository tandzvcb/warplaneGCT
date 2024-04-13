#ifndef AMO_OBJECT_H_
#define AMO_OBJECT_H_

#include "BaseObject.h"


#define WIDTH_BULLET 5
#define HEIGHT_BULLET 5

class BulletObject : public BaseObject
{
public:
	enum BulletType
	{
		NONE = 0,
		BULLET_MAIN = 1,
		BULLET_THREAT = 2
	};

	BulletObject();
	~BulletObject();
	void HandleInputAction(SDL_Event events);          // xử lý hành đông vào
	void HandleMove(const int& x_border, const int& y_border);
	void HandleMoveRightToLeft();

	int get_type() const {return bullet_type_;}
	void set_type(const int& type) {bullet_type_ = type;}

	bool get_is_move() const {return is_move_;}
	void set_is_move(bool is_move) {is_move_ = is_move;}
	void SetWidthHeight(const int& width, const int& height) {rect_.w = width; rect_.h = height;}

	void set_x_val(const int& val) {x_val_ = val;}
	void set_y_val(const int& val) {y_val_ = val;}

	int get_x_val() const {return x_val_;}
	int get_y_val() const {return y_val_;}
private:
	int x_val_;
	int y_val_;
	bool is_move_;
	int bullet_type_;
};
#endif
