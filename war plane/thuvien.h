﻿#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include<windows.h>
#include<fstream>
#include<SDL.h>
#include<string>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<vector>


const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;
const int SCREEN_SPEED = 2;

static SDL_Surface* gScreen = NULL;
static SDL_Surface* gBkground = NULL;
static SDL_Event g_event;
static SDL_Surface* gMenu		= NULL;

namespace SDLCommonFunc
{
	SDL_Surface* LoadImage(std::string file_path);				// tải ảnh 
	SDL_Rect ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);    // vẽ ảnh src lên des(màn hinh) tại tọa độ(x,y)
	void ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x ,int y);
	bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);		// xử lý va chạm
	int	 ShowMenu(SDL_Surface* des, TTF_Font* font);
	bool CheckForcusWithRect(const int& x, const int& y, const SDL_Rect& rect);

	void CleanUp();					// Giải phóng tài nguyên
}

#endif