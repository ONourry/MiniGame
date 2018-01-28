#include "Snake.h"



Snake::Snake()
{
}

void Snake::setXPosition(int position) {
	x_position = position;
}

void Snake::setYPosition(int position) {
	y_position = position;
}

int Snake::getXPosition() {
	return x_position;
}

int Snake::getYPosition() {
	return y_position;
}


Snake::~Snake()
{
}
