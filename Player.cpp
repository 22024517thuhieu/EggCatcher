#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	rect_->x = 410;
	rect_->y = 450;
	rect_->w = BASKET_WIDTH;
	rect_->h = BASKET_HEIGHT;
	x_val_ = rect_->x;
	y_val_ = rect_->y;

}

Player::~Player()
{

}

void Player::HandleInputAction(SDL_Event events)
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_LEFT:
			if (x_val_  > 10 ) x_val_ -= BASKET_WIDTH*2;
			break;
		case SDLK_RIGHT:
			if (x_val_ + 200 < SCREEN_WIDTH ) x_val_ += BASKET_WIDTH*2;
			break;

		default:
			break;
		}
	}
}


void Player::HandleMove()
{
	rect_->x = x_val_;
	rect_->y = y_val_;

}