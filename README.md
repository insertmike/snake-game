# Snake Game
A command-line version of the snake game written in C++ .
## Features
- Snake moves in all directions 
- If snake eat a fruit its tail grows
- Snake go through walls
## Build: 
_Game is tested and written on Windows OS with the Microsoft Visual Studio Compiler_
1. Open VS Developer Prompt 
2. Go to game folder 
2. Run nmake file:

   nmake main 
   
## How to play:
Move snake with the following keyboard keys:

**W** - UP

**A** - LEFT 

**S** - DOWN

**D** - RIGHT 

**X** - to exit 

###### To clear *.obj and *.exe files do:

nmake clean 

## ToDo
- [ ] Rewrite logic function to not allow fruits to spawn on the snake
- [ ] Add functionality for the user to choose the desired map ( matrix ) size
- [ ] Add functionality for the user to change the speed of the snake 
- [ ] Think about obstacles
