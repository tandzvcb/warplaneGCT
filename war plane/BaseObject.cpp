#include "BaseObject.h"

BaseObject::BaseObject()
{
	rect_.x = 0;
	rect_.y = 0;
	p_object_ = NULL; //sử dụng để kiểm tra xem ảnh đã được tải vào bộ nhớ hay chưa.

}

BaseObject::~BaseObject()
{
	
}
bool BaseObject::LoadImg(const char* file_name)
{
	p_object_ = SDLCommonFunc::LoadImage(file_name); //tải hình ảnh từ tệp file_name vào bộ nhớ và gán cho đối tượng p_object_.
	if(p_object_ == NULL)return false;

	return true;
}

void BaseObject::Show(SDL_Surface* des)
{
	if(p_object_ != NULL){
	rect_ = SDLCommonFunc::ApplySurface(p_object_, des, rect_.x, rect_.y); 
	}
}


