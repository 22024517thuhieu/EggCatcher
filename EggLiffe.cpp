#include "stdafx.h"
#include "EggLife.h"


EggLife::EggLife()
{
	rect_->x = SCREEN_WIDTH / 3;
	rect_->y = 110;
	rect_->w = EGGLIFE_WIDTH;
	rect_->h = EGGLIFE_HEIGHT;
	x_val_ = 0;
	y_val_ = 0;
	is_move_ = true;
}

EggLife::~EggLife()
{

}


void EggLife::HandleMove() {
	rect_->y += y_val_;
}