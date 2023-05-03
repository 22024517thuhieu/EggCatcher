#include "stdafx.h"
#include "HealthObject.h"

HealthObject::HealthObject()
{
	number_ = 0;
}

HealthObject::~HealthObject()
{

}

void HealthObject::AddPos(const int& xPos)
{
	pos_list_.push_back(xPos);
}

void HealthObject::Init(SDL_Renderer* screen)
{
	LoadImg("img//Heart.png", screen);
	number_ = 3;
	if (pos_list_.size() > 0)
	{
		pos_list_.clear();
	}

	AddPos(20);
	AddPos(70);
	AddPos(120);
}

void HealthObject::Show(SDL_Renderer* screen)
{
	for (int i = 0; i < pos_list_.size(); i++)
	{
		rect_->x = pos_list_.at(i);
		rect_->y = 5;
		Render(screen);
	}
}

void HealthObject::Decrease()
{
	number_ --;
	pos_list_.pop_back();
}

void HealthObject::Increase()
{
	if (number_<3) {
	number_ ++;
	AddPos(pos_list_.back() + 50);
	}
}