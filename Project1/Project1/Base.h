#pragma once
#include "Snake.h"
#include "Fruit.h"
class Base
{
public:
	Base();
	~Base();
	Snake snake;
	Fruit fruit;
};

void init(Snake * snake[], Fruit & fruit);
