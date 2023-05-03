#ifndef PLAYER_H
#define PLAYER_H

#include "CommonFunction.h"
#include "BaseObject.h"

#define BASKET_WIDTH 100
#define BASKET_HEIGHT 100

class Player : public BaseObject
{
public:
	Player();
	~Player();

	void HandleInputAction(SDL_Event event);
	void HandleMove();

private:
	int x_val_;
	int y_val_;
};
#endif // PLAYER_H