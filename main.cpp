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

// Game mode | 0 == EASY, 1 == HARD
bool gameMode;

// Map dimensions
 int width = 5;
 int height = 5;

// Head position coordinates
int x,y;

// Fruit position coordinates
int fruitX, fruitY;

// Array of memory for tail positions
int tailX[100], tailY[100];

// Length of the tail
int lentail;

// Current score 
int score;

// Highest score 
int highestScore = 0;

// Enum holding the current direction of the snake head
// By default it is 0
enum eDirection{ 
	STOP = 0,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

// Current direction of snake head | Left, Right, Up, Down or Stop
eDirection dir;
int main(int argc, char **argv)
{

	// Prompt user for map dimensions X -> Width , Y -> Height
   DecideMapDimensions();
   // Prompt user to decide a game mode, Easy or Hard
   gameMode = DecideGameMode();

   
   srand(time(0));
   // Clear console to Draw on clear screen
   system("cls");
   // Setting up initial settings of the game
   Setup();
   // Running game until game over
   while (!gameOver)
   {
      Draw();
      Input();
      Logic();
      Sleep(100);
   }
   cout<<"Exiting ..."<<endl;
   // Closing the window slightly after the game has finisheed
   Sleep(800);
   return 0;
}
/**
 * Method: DecideMapDimensions()
 * ------------------------
 * Method which prompts the user to enter width and height values
 * for the matrix of the snake. 
 *
 * @type: void
 *
*/
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
/**
 * Enumerator : DecideGameMode
 * ------------------------
 * Used initially in the start of the game for the user to enter
 * which game mode he would like to play
 *
 * @type: enum
 *
*/
eGameMode DecideGameMode()
{
   // Default to easy
   eGameMode gameMode = eGameMode::eGM_Easy;
   bool gameModeDecided(false);
   // Prompt for game mode until decided
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

/**
 * Method: readHighestScore()
 * ------------------------
 * Method which tries to open the 'highestScore.o', 
 * read the value stored inside into a variable of 
 * type int and return it
 *
 * @type: int
 *
 * @return buffer, the value read from the highest score file
 *
*/
int readHighestScore()
{
	// Buffer to read highest score in
	int buffer = 0;
	// Open highest score file
	ifstream file("highestScore.o");
	// Check if opened successfully 
	if (!file)
	{
		return 0;
	}
	// Read highest score into the buffer
	file >> buffer;
	// Close the file
	file.close();
	// Return highest score
	return buffer;
}
/**
 * Method: Setup()
 * ------------------------
 * Setting up the initial settings for the game.
 *
 * @type: void
 *
*/
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
/**
 * Method: Draw()
 * ------------------------
 * Drawing the matrix for the game with:
 * - the snake head, tail && fruit 
 * - the Game Mode | Aside the Matrix
 * - the current X && Y position of the snake head
 * - the current highest score
 *
 * @type: void
 *
*/
void Draw()
{
	// The next 5 lines of code handle the way the matrix displays on the loop by 
	// handling the position of the cursor. Prevents output from blinking.
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
			// If reached fruit indexes, print fruit
			else if(i == fruitY && j == fruitX)
				cout<<"F";
			else 
			{
				bool print = false;
				// Printing snake tail
				 for(int k = 0; k < lentail; k++)
				 {
					if(tailX[k] == j && tailY[k] == i)
					{
						 cout<<"o";
						 print = true;
					}
				 }
				 // If not printing snake or fruit, print whitespace 
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
	// Print snake current coordinates
	cout<<"HEAD X = "<<x<<" Y = "<<y<<endl;
	cout<<"FRUIT X = "<<fruitX<<"Y = "<<fruitY<<endl;
	// Print current score
	cout<<"Score: "<<score<<endl;
	// Read and print highest score
	highestScore = readHighestScore();
	cout<<"Highest Score: "<<highestScore<<endl;
	
}
/**
 * Method: Input()
 * ------------------------
 * Check if one of the game keyboard keys is pressed 
 * and updates the direction of the snake
 *
 * @type: void
 *
*/
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
/**
 * Method: Logic()
 * ------------------------
 * Implements the logic of :
 * - how the tail coordinates are being updated ( pointers )
 * - determinate the head of the snake direction based on the output
 *   from the Input() function
 * - checks if the game is over based on the game mode
 * - updates if there is a new high score and writes it to the 'highestScore.o'
 *
 * @type: void
 *
*/
void Logic()
{

	// Previous x coordinate of the tail
	int ptailX = tailX[0];
	// Previous y coordinate of the tail
	int ptailY = tailY[0];
	int ptail2X, ptail2Y;
	tailX[0] = x;
	tailY[0] = y;
	// Update tail indexes
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
		// Check if snake coordinates are greater than matrix coordinates
		if(x >= width || x < 0 || y >= height || y < 0)
		{
		// Snake coordinates are greater, set game over to true
		gameOver = true;
		
		}
	}
	// The possibility for the snake to go through walls
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
	// If head of the snake equals fruit coordinates:
	// - Update score
	// - Update length of the tail
	// - Seed new fruit
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
