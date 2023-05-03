#include "stdafx.h"
#include "CommonFunction.h"

bool SDLCommonFunc::CheckCollision(const SDL_Rect *object1, const SDL_Rect *object2)
{
	int left_a = object1->x;
	int right_a = object1->x + object1->w;
	int top_a = object1->y;
	int bottom_a = object1->y + object1->h;

	int left_b = object2->x;
	int right_b = object2->x + object2->w;
	int top_b = object2->y;
	int bottom_b = object2->y + object2->h;

	if (left_b > left_a && left_b < right_a)
	{
		if (top_a < bottom_b && bottom_b < top_a + object1->h/2)
		{
			return true;
		}
	}

	if (right_b > left_a && right_b < right_a)
	{
		if (top_a == bottom_b && bottom_b < top_a + object1->h/2)
		{
			return true;
		}
	}

	return false;
}

int SDLCommonFunc::getRandomNumber(int a, int b)
{
	static bool first = true;
	if (first)
	{
		srand( time(NULL) );
		first = false;
	}
	int result=a + rand() % (( b + 1 ) - a);
	result=(result/10)*10;
	return result;
}

bool SDLCommonFunc::CheckFocusWithRect(int x1, int y1, int x, int y, int w, int h)
{
	if (x1 >= x && x1 <= x + w && y1 >= y && y1 <= y+h)
	{
		return true;
	}
	return false;
}