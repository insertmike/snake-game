#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
using namespace std;
void Setup();
void Draw();
void Input();
void Logic();
bool gameOver;
// Map dimensions
const int width = 20;
const int height = 20;
// Head position coordinates
int x,y;
// Fruit position coordinates
int fruitX, fruitY;
// Score variable
int score;
// Enum to track direction
enum eDirection{
	STOP = 0,
	LEFT,
	RIGHT,
	UP,
	DOWN
};
// Holds the direction of the snake 
eDirection dir;
int main(int argc, char **argv)
{
	Setup();
	while(!gameOver)
	{
		Draw();
		Input();
		Logic();
	    Sleep(50);
	}
	return 0;
}

void Setup()
{
	gameOver = false;
	score = 0;
	// Snake won't move until user change initial direction 
	dir = STOP;
	// Center position of the head 
	x = width / 2;
	y = height / 2;
	// Seed the fruit random 
	fruitX = rand() % width;
	fruitY = rand() % height;
	
}
void Draw()
{
	// Clear the screen
	system("cls");
	// HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	// COORD Position;
	
	// Position.X = 0;
	// Position.Y = 0;
	
	// SetConsoleCursorPosition(hOut, Position);
	// Print top wall 
	for(int i = 0; i <= width; i++)
		cout<<"#";
	cout<<endl;
	// Print side walls
	for(int i = 0; i <= height; i++)
	{
		for(int j = 0; j <= width; j++)
		{
			if(j == 0 || j == width)
				cout<<"#";
			// Printing the head 
			if( i == y && j == x)
			{
				cout<<"O";
			}
			else if( i == fruitY && j == fruitX)
			{
				cout<<"F";
			}
			else 
				cout<<" ";
		}
		cout<<endl;
	}

	// Print bottom wall
	for(int i = 0; i <= width; i++)
		cout<<"#";
	cout<<endl;
	cout<<"HEAD X = "<<x<<" Y = "<<y<<endl;
	cout<<"FRUIT X = "<<fruitX<<"Y = "<<fruitY<<endl;
	cout<<"Score: "<<score;
}
void Input()
{
	// If keyboard key is pressed 
	// Returns boolean otherwise 0
	if(_kbhit())
	{
		// Returns ASCII value of character pressed 
		char key = _getch();
		switch(key)
		{
			case 'a':
				dir = LEFT;
				break;
			case 'd':
				dir = RIGHT;
				break;
			case 'w': 
				dir = UP;
				break;
			case 's':
				dir = DOWN;
				break;
			case 'x':
				gameOver = true;
				break;
		}
	
	}
}
void Logic()
{
	switch(dir)
	{
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
		default:
			break;
	}
	if(x >= width || x < 0 || y >= height || y < 0)
	{
		gameOver = true;
	}
	if(x == fruitX && y == fruitY)
	{
		score++;
		fruitX = rand() % width;
		fruitY = rand() % height;
	}
}