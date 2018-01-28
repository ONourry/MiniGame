#include "Fruit.h"



Fruit::Fruit()
{
}

void Fruit::setXPosition(int position) {
	x_position = position;
}

void Fruit::setYPosition(int position) {
	y_position = position;
}

int Fruit::getXPosition() {
	return x_position;
}

int Fruit::getYPosition() {
	return y_position;
}

Fruit::~Fruit()
{
}
