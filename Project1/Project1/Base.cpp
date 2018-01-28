#include <iostream>
#include <SFML/Graphics.hpp>
#include "Base.h"
#include "Snake.h"
using namespace sf;

int horizontalBoardSize = 30, verticalBoardSize = 20, size = 16;
int snakeLength = 4;
const int MAXLENGTH = 100;


void init(Snake (&snake) [MAXLENGTH], Fruit &fruit) {
	//Initial coordinates
	snake[0].setXPosition(0);
	snake[0].setYPosition(verticalBoardSize - snakeLength);

	snake[1].setXPosition(0);
	snake[1].setYPosition(snake[0].getYPosition() + 1);

	snake[2].setXPosition(0);
	snake[2].setYPosition(snake[0].getYPosition() + 2);

	snake[3].setXPosition(0);
	snake[3].setYPosition(snake[0].getYPosition() + 3);

	fruit.setXPosition(10);
	fruit.setYPosition(10);
}

void update(int direction, Snake snake [], Fruit &fruit) {

	//Update snake body to make it move
	for (int i = snakeLength - 1; i > 0; i--){
		snake[i].setXPosition(snake[i - 1].getXPosition());
		snake[i].setYPosition(snake[i - 1].getYPosition());
	}

	//Update head based on input
	if (direction == 0) {
		snake[0].setXPosition(snake[0].getXPosition() - 1);
	}
	else if (direction == 1) {
		snake[0].setYPosition(snake[0].getYPosition() - 1);
	}
	else if (direction == 2) {
		snake[0].setXPosition(snake[0].getXPosition() + 1);
	}
	else if (direction == 3) {
		snake[0].setYPosition(snake[0].getYPosition() + 1);
	}

	//if the snake eats a fruit, increase snake length and generate new coordinate for fruit
	if (snake[0].getXPosition() == fruit.getXPosition() && snake[0].getYPosition() == fruit.getYPosition()) {
		snakeLength++;
		fruit.setXPosition(rand() % horizontalBoardSize);
		fruit.setYPosition(rand() % verticalBoardSize);
	}

	//if the snake goes further than the screen, bring it to the other side
	if (snake[0].getXPosition() > horizontalBoardSize) {
		snake[0].setXPosition(0);
	}
	if (snake[0].getYPosition() > verticalBoardSize) {
		snake[0].setYPosition(0);
	}
	if (snake[0].getXPosition() < 0) {
		snake[0].setXPosition(horizontalBoardSize);
	}
	if (snake[0].getYPosition() < 0) {
		snake[0].setYPosition(verticalBoardSize);
	}

	//If the head touches the body, reset the snake at the point of contact
	for (int i = 1; i < snakeLength; i++){
		if (snake[0].getXPosition() == snake[i].getXPosition() &&
			snake[0].getYPosition() == snake[i].getYPosition()) {
			snakeLength = i;
		}
	}
}

int main() {

	Snake snake [MAXLENGTH];
	Fruit fruit;

	init(snake, fruit);

	int windowWidth = size*horizontalBoardSize;
	int windowHeight = size*verticalBoardSize;
	int direction = 1;

	srand(time(0));

	RenderWindow window(VideoMode(windowWidth, windowHeight), "Snake");

	Clock clock;
	float timer = 0;
	float delay = 0.1;

	//Sprites and textures
	Texture t1, t2, t3;
	t1.loadFromFile("images/white.png");
	t2.loadFromFile("images/red.png");
	t3.loadFromFile("images/green.png");

	Sprite sprite1, sprite2, sprite3;
	sprite1.setTexture(t1);
	sprite2.setTexture(t2);
	sprite3.setTexture(t3);

	while (window.isOpen()) {

		float currentTime = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += currentTime;

		//Check if user tries to close window
		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed) {
				window.close();
			}
		}

		//Setup directions of the snake
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			direction = 0;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Up)) {
			direction = 1;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right)) {
			direction = 2;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down)) {
			direction = 3;
		}

		//Update the board
		if (timer > delay) {
			timer = 0;
			update(direction, snake, fruit);
		}

		window.clear();

		//Multiply the positions by size so that the fruit and snake stay within the board squares

		//Draw white background
		for (int i = 0; i < horizontalBoardSize; i++) {
			for (int j = 0; j < verticalBoardSize; j++) {
				sprite1.setPosition(i*size, j*size);
				window.draw(sprite1);
			}
		}

		//Draw the snake
		for (int i = 0; i < snakeLength; i++) {
			sprite2.setPosition(snake[i].getXPosition() * size, snake[i].getYPosition() * size);
			window.draw(sprite2);
		}

		//Draw the fruit
		sprite3.setPosition(fruit.getXPosition() * size, fruit.getYPosition() * size);
		window.draw(sprite3);

		window.display();
	}
	return 0;
}