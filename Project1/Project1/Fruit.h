#pragma once
class Fruit
{
private:
	int x_position;
	int y_position;
public:
	void setXPosition(int position);
	void setYPosition(int position);
	int getXPosition();
	int getYPosition();
	Fruit();
	~Fruit();
};

