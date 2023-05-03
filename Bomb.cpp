#include "stdafx.h"
#include "Bomb.h"

Bomb::Bomb()
{
	rect_->x = SCREEN_WIDTH / 3;
	rect_->y = 110;
	rect_->w = BOMB_WIDTH;
	rect_->h = BOMB_HEIGHT;

	x_val_ = 0;
	y_val_ = 0;
}

Bomb::~Bomb()
{

}

void Bomb::HandleMove() {
	rect_->y += y_val_;
	if (rect_->y > SCREEN_HEIGHT ) {
		rect_->y = 110;
		int x_positions[] = {x1, x2, x3};
		int random_x_index = rand() % 3;
		rect_->x = x_positions[random_x_index]; }
}