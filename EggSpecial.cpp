#include "stdafx.h"
#include "EggSpecial.h"


EggSpecial::EggSpecial()
{
	rect_->x = SCREEN_WIDTH / 3;
	rect_->y = 110;
	rect_->w = EGGSPECIAL_WIDTH;
	rect_->h = EGGSPECIAL_HEIGHT;
	x_val_ = 0;
	y_val_ = 0;
	is_move_ = true;
}

EggSpecial::~EggSpecial()
{

}


void EggSpecial::HandleMove() {
	rect_->y += y_val_;
}