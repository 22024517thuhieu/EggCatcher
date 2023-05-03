ï»¿// ChickenObject.cpp

#include "stdafx.h"
#include "Chicken.h"

Chicken::Chicken()
{
}

Chicken::~Chicken()
{
}

void Chicken::AddPos(const int& xPos)
{
	pos_list_.push_back(xPos);
}

void Chicken::Init(SDL_Renderer* screen)
{
	LoadImg("img//chicken.png", screen);
	number_ = 3;
	if (pos_list_.size() > 0)
	{
		pos_list_.clear();
	}

	AddPos(200);
	AddPos(400);
	AddPos(600);
}

void Chicken::Show(SDL_Renderer* screen)
{
	for (int i = 0; i < (int)pos_list_.size(); i++)
	{
		rect_->x = pos_list_.at(i);
		rect_->y = 25;
		Render(screen);
	}
}