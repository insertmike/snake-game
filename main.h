enum eGameMode
{
   eGM_Easy = 0,
   eGM_Hard
};

void DecideMapDimensions();
eGameMode DecideGameMode();
void Setup();
void Draw();
void Input();
void Logic();