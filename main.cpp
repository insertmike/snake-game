#include<iostream>
using namespace std;
void Setup();
void Draw();
void Input();
void Logic();
bool gameOver;
// Map dimensions
const int width = 20;
const int height = 10;
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
		// Sleep(10);
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
	// System command to clear the screen
	system("cls");
	
	// Print top wall 
	for(int i = 0; i < width; i++)
		cout<<"#";
	cout<<endl;
	// Print side walls
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			if(j == 0 || j == width - 1)
				cout<<"#";
			else 
				cout<<" ";
		}
		cout<<endl;
	}



	// Print bottom wall
	for(int i = 0; i < width; i++)
		cout<<"#";
	cout<<endl;
}
void Input()
{
	
}
void Logic()
{

}