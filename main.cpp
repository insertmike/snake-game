#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include <string>

#include "main.h"
using namespace std;

bool gameOver;
// Game mode -> 0 - easy, 1 - hard 
bool gameMode;
// Map dimensions
 int width = 5;
 int height = 5;
// Head position coordinates
int x,y;
// Fruit position coordinates
int fruitX, fruitY;
// Tail
int tailX[100], tailY[100];
// Length of the tail
int lentail;
// Score variable
int score;
// Highest score variable
int highestScore = 0;
// Enum to track direction
enum eDirection{ 
	STOP = 0,
	LEFT,
	RIGHT,
	UP,
	DOWN
};
int modeX, modeY;
// Holds the direction of the snake 
eDirection dir;
int main(int argc, char **argv)
{
   DecideMapDimensions();

   gameMode = DecideGameMode();

   srand(time(0));
   //system("cls");
   Setup();
   while (!gameOver)
   {
      //Draw();
      //Input();
      //Logic();
      //Sleep(100);
   }
   cout<<"Exiting ..."<<endl;
   return 0;
}

void DecideMapDimensions()
{
   bool widthDecided(false);
   bool heightDecided(false);
   while (!widthDecided || !heightDecided)
   {
      if (!widthDecided)
      {
         cout << "Enter desired map width: ";
         cin >> width;
         cout << endl;
         if (!cin.good())
         {
            cout << "Value entered for width is invalid. Please enter a number." << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
         }
         else
         {
            widthDecided = true;
         }
      }

      if (!heightDecided)
      {
         cout << "Enter desired map height: ";
         cin >> height;
         cout << endl;
         if (!cin.good())
         {
            cout << "Value entered for height is invalid. Please enter a number." << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
         }
         else
         {
            heightDecided = true;
         }
      }

   }
}

eGameMode DecideGameMode()
{
   // Default to easy
   eGameMode gameMode = eGameMode::eGM_Easy;
   bool gameModeDecided(false);
   while (!gameModeDecided)
   {
      cout << "Game modes:" << endl;
      cout << "0 - EASY" << endl;
      cout << "1 - HARD" << endl;
      cout << "Enter game mode: ";
      int buffer;
      cin >> buffer;
      if (!cin.good())
      {
         cout << "Value entered for game mode is invalid." << endl;
         cin.clear();
         cin.ignore(INT_MAX, '\n');
         continue;
      }
      else
      {
         // Use the switch and the enum for readability.
         // It also makes adding new game modes a little
         // easier to do
         switch (buffer)
         {
            case eGM_Easy:
               gameModeDecided = true;
               gameMode = eGM_Easy;
               break;
            case eGM_Hard:
               gameModeDecided = true;
               gameMode = eGM_Hard;
               break;
            default:
               cout << "Invalid input: " << buffer << endl;
               cout << "Please try again" << endl;
               break;
         }
      }
   }
   return gameMode;
}

int readHighestScore()
{
	int buffer = 0;
	// Open the file
	ifstream file("highestScore.o");
	if(!file)
	{
		return 0;
	}
	file>>buffer;
	file.close();
	return buffer;
	
	// 
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
	//system("cls");
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position;
	
	Position.X = 0;
	Position.Y = 0;
	
	SetConsoleCursorPosition(hOut, Position);
	// Print top wall 
	for(int i = 0; i < width + 2; i++)
		cout<<"#";
	cout<<endl;
	// Print side walls
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			if(j == 0)
				cout<<"#";
			// Printing the head 
			if( i == y && j == x)
				cout<<"O";
			else if(i == fruitY && j == fruitX)
				cout<<"F";
			else 
			{
				bool print = false;
				 for(int k = 0; k < lentail; k++)
				 {
					if(tailX[k] == j && tailY[k] == i)
					{
						 cout<<"o";
						 print = true;
					}
				 }
				if(!print)
					cout<<" "; 
			}
			if(j == width - 1)
				cout<<"#";	
			// Display game mode of the right hand side of center the map
			if(j == width - 1 && i == height / 2)
			{
				// Display game mode 
				if(gameMode)
					cout<<"        GAME MODE: HARD";
				else
					cout<<"        GAME MODE: EASY";
				
			}
		}
		cout<<endl;
	}

	// Print bottom wall
	for(int i = 0; i < width + 2; i++)
		cout<<"#";
	cout<<endl;
	cout<<"HEAD X = "<<x<<" Y = "<<y<<endl;
	cout<<"FRUIT X = "<<fruitX<<"Y = "<<fruitY<<endl;
	cout<<"Score: "<<score<<endl;
	highestScore = readHighestScore();
	cout<<"Highest Score: "<<highestScore<<endl;
	
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
				if(lentail > 0)
				{
				if(dir == RIGHT)
					break;
				}
				dir = LEFT;
				break;
			case 'd':
				if(lentail > 0)
				{
				if(dir == LEFT)
					break;
				}
				dir = RIGHT;
				break;
			case 'w': 
				if(lentail > 0)
				{
				if(dir == DOWN)
					break;
				}
				dir = UP;
				break;
			case 's':
				if(lentail > 0)
				{
				if(dir == UP)
					break;
				}
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

	// Previous x coordinate of the tail
	int ptailX = tailX[0];
	// Previous y coordinate of the tail
	int ptailY = tailY[0];
	int ptail2X, ptail2Y;
	tailX[0] = x;
	tailY[0] = y;
	for(int i = 1; i < lentail; i++)
	{
		ptail2X = tailX[i];
		ptail2Y = tailY[i];
		tailX[i] = ptailX;
		tailY[i] = ptailY;
		ptailX = ptail2X;
		ptailY = ptail2Y;
	}
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
	if(gameMode)
	{
		if(x >= width || x < 0 || y >= height || y < 0)
		{
		gameOver = true;
		
		}
	}
	if(x >= width)
		x = 0;
	else if(x < 0) 
		x = width - 1;
	if(y >= height)
		y = 0;
	else if(y < 0) 
		y = height - 1;
	
	// Check if there is collision between head and tail 
	// Loop through all tail segments 
	for(int i = 0; i < lentail; i++)
	{
		if(tailX[i] == x && tailY[i] == y)
		{
			gameOver = true;
		}
	}
	if(x == fruitX && y == fruitY)
	{
		score++;
		if(score > highestScore)
			highestScore = score;
			// Update highest score in the file
			ofstream scoreFile("highestScore.o");
			scoreFile << to_string(highestScore);
			scoreFile.close();
		lentail++;
		fruitX = rand() % width;
		fruitY = rand() % height;
	}
}
