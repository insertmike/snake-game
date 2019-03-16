# Snake Game
A command-line version of the snake game written in C++ .
## Features
- User can choose desired map (x, y) size 
- Snake moves in all directions 
- If the snake eats a fruit its tail grows
- Player has score
- Player has highest score which is stored in a .o file 
- The game has two modes -
  - Easy: Wall collisions allowed
  - Hard: If wall collision - Game Over
- Try again function 
## Build: 
_Game is tested and written on Windows OS with the Microsoft Visual Studio Compiler_
1. Open VS Developer Prompt 
2. Go to game folder 
2. Run nmake file:

   nmake main 
   
###### To clear *.obj and *.exe files do:

   nmake clean 

## How to play:
Move snake with the following keyboard keys:

**W** - UP

**A** - LEFT 

**S** - DOWN

**D** - RIGHT 

**X** - to exit 

## ToDo
- [ ] Rewrite logic function to not allow fruits to spawn on the snake
- [ ] Add replay gameplay function
- [x] Add functionality for the user to choose the desired map ( matrix ) size
- [ ] Add functionality for the user to change the speed of the snake 
- [ ] Think about obstacles
- [x] Add highest score function who stores score in a .o file 
- [x] Make 2 Game Modes 
     - Easy: Wall collisions allowed. 
	 - Hard: If wall collision - Game Over.
- [x] Add try again function	
- [ ] Think of logic to have two different high scores for the two different modes 
- [ ] Check if tail is too long for the matrix the user to win the game
