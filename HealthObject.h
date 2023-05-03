#ifndef HEALTH_OBJECT_H
#define HEALTH_OBJECT_H

#include "CommonFunction.h"
#include "BaseObject.h"
#include <vector>

class HealthObject : public BaseObject
{
public:
	HealthObject();
	~HealthObject();
	void SetNumber(const int& num) {number_ = num;}
	void AddPos(const int& xPos);
	void Show(SDL_Renderer* screen);
	void Init(SDL_Renderer* screen);
	void Decrease();
		void Increase();

private:
	int number_;
	std::vector<int> pos_list_;
};

#endif // HEALTH_OBJECT_