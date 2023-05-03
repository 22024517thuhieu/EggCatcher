#ifndef EGGSPECIAL_H
#define EGGSPECIAL_H

#include "CommonFunction.h"
#include "BaseObject.h"

#define EGGSPECIAL_WIDTH 70
#define EGGSPECIAL_HEIGHT 80

class EggSpecial : public BaseObject {
public:
	EggSpecial();
	~EggSpecial();
	void HandleMove();
	void set_x_val(const int& xVal) {x_val_ = xVal;}
	void set_y_val(const int& yVal) {y_val_ = yVal;}
	int get_x_val() const {return x_val_;}
	int get_y_val() const {return y_val_;}
	void RemoveEgg(EggSpecial* egg);
private:
	int x_val_;
	int y_val_;
	bool is_move_;
};

#endif // EGGSPECIAL_H