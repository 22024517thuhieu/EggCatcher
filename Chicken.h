#ifndef CHICKEN_H
#define CHICKEN_H

#include "CommonFunction.h"
#include "BaseObject.h"
#include <vector>

class Chicken : public BaseObject
{
public:
    static const int CHICKEN_WIDTH = 80;
    static const int CHICKEN_HEIGHT = 80;

    Chicken();
    ~Chicken();
	void SetNumber(const int& num) {number_ = num;}
    void AddPos(const int& xPos);
    void Show(SDL_Renderer* screen);
    void Init(SDL_Renderer* screen);
    void Decrease();
private:
    int number_;
    std::vector<int> pos_list_;
};

#endif // CHICKEN_H