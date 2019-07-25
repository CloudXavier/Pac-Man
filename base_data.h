#include <time.h>

const int Height = 27, Width = 21; //The default Height and the Width of the map

const char Save_Map[Height + 2][Width + 2] = {
	{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
	{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
	{'#', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '#'},
	{'#', '#', '.', '#', '#', '#', '.', '#', '#', '#', '.', '#', '.', '#', '#', '#', '.', '#', '#', '#', '.', '#', '#'},
	{'#', '#', '@', '#', ' ', '#', '.', '#', ' ', '#', '.', '#', '.', '#', ' ', '#', '.', '#', ' ', '#', '@', '#', '#'},
	{'#', '#', '.', '#', '#', '#', '.', '#', '#', '#', '.', '#', '.', '#', '#', '#', '.', '#', '#', '#', '.', '#', '#'},
	{'#', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '#'},
	{'#', '#', '.', '#', '#', '#', '.', '#', '.', '#', '#', '#', '#', '#', '.', '#', '.', '#', '#', '#', '.', '#', '#'},
	{'#', '#', '.', '#', '#', '#', '.', '#', '.', '#', '#', '#', '#', '#', '.', '#', '.', '#', '#', '#', '.', '#', '#'},
	{'#', '#', '.', '.', '.', '.', '.', '#', '.', '.', '.', '#', '.', '.', '.', '#', '.', '.', '.', '.', '.', '#', '#'},
	{'#', '#', '#', '#', '#', '#', '.', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', '.', '#', '#', '#', '#', '#', '#'},
	{'#', ' ', ' ', ' ', ' ', '#', '.', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '.', '#', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', '#', '.', '#', ' ', '#', '#', ' ', '#', '#', ' ', '#', '.', '#', ' ', ' ', ' ', ' ', '#'},
	{'#', '#', '#', '#', '#', '#', '.', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', '.', '#', '#', '#', '#', '#', '#'},
	{' ', ' ', ' ', ' ', ' ', ' ', '.', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', '.', ' ', ' ', ' ', ' ', ' ', ' '},
	{'#', '#', '#', '#', '#', '#', '.', '#', ' ', '#', '#', '#', '#', '#', ' ', '#', '.', '#', '#', '#', '#', '#', '#'},
	{'#', ' ', ' ', ' ', ' ', '#', '.', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '.', '#', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', '#', '.', '#', ' ', '#', '#', '#', '#', '#', ' ', '#', '.', '#', ' ', ' ', ' ', ' ', '#'},
	{'#', '#', '#', '#', '#', '#', '.', '#', ' ', '#', '#', '#', '#', '#', ' ', '#', '.', '#', '#', '#', '#', '#', '#'},
	{'#', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '#'},
	{'#', '#', '.', '#', '#', '#', '.', '#', '#', '#', '.', '#', '.', '#', '#', '#', '.', '#', '#', '#', '.', '#', '#'},
	{'#', '#', '@', '.', '.', '#', '.', '.', '.', '.', '.', ' ', '.', '.', '.', '.', '.', '#', '.', '.', '@', '#', '#'},
	{'#', '#', '#', '#', '.', '#', '.', '#', '.', '#', '#', '#', '#', '#', '.', '#', '.', '#', '.', '#', '#', '#', '#'},
	{'#', '#', '#', '#', '.', '#', '.', '#', '.', '#', '#', '#', '#', '#', '.', '#', '.', '#', '.', '#', '#', '#', '#'},
	{'#', '#', '.', '.', '.', '.', '.', '#', '.', '.', '.', '#', '.', '.', '.', '#', '.', '.', '.', '.', '.', '#', '#'},
	{'#', '#', '.', '#', '#', '#', '#', '#', '#', '#', '.', '#', '.', '#', '#', '#', '#', '#', '#', '#', '.', '#', '#'},
	{'#', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '#'},
	{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
	{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
};
//The main map of the Pac-man

const int Pic[5] = {' ', '^', 'v', '<', '>'}; //The icon of the cursor

const int Move[5][2] = {{0, 0}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}}; //Direction of the movements

int Score;

int Map[Height + 2][Width + 2]; //Use it when the game restart

struct Coordinate {
	int X, Y, Direction, locked, Color;
} PacMan, Ghost[5], Save_Ghost[5]; //See the name

bool Turnings[Height + 1][Width + 1]; //Save Turnings

int Strong_Time;

bool Check_Turning(int x, int y, int a, int b) {
	return Map[x][y] ^ '#' && Map[a][b] ^ '#';
} //Check whether it's a turning

void Data_Processing() {
	srand((unsigned)(time(NULL))); //Reset the Random seed

	Score = 0; // Reset the Scofre

	for(int i = 0; i <= Height + 1; i++)
		for(int j = 0; j <= Width + 1; j++)
			Map[i][j] = Save_Map[i][j];
	//Give "Save" to "Map" (Restore data)

	PacMan.X = 21, PacMan.Y = 11, PacMan.Direction = 1, PacMan.Color = 14;
	// Load the PacMan

	Ghost[1].X = 13, Ghost[2].X = 14, Ghost[3].X = 14, Ghost[4].X = 14;
	Ghost[1].Y = 11, Ghost[2].Y = 10, Ghost[3].Y = 11, Ghost[4].Y = 12;
	Ghost[1].Direction = 1, Ghost[2].Direction = 4, Ghost[3].Direction = 1, Ghost[4].Direction = 3;
	Ghost[1].Color = 4, Ghost[2].Color = 14, Ghost[3].Color = 11, Ghost[4].Color = 13;
	// Process the Ghost

	for(int i = 1; i < 5; i++) {
		Save_Ghost[i].X = Ghost[i].X;
		Save_Ghost[i].Y = Ghost[i].Y;
		Save_Ghost[i].Direction = Ghost[i].Direction;
	}

	for(int i = 1; i <= Height; i++)
		for(int j = 1; j <= Width; j++) {
			bool sum = false; //Check it's or not turning

			if(Check_Turning(i - 1, j, i, j - 1)) sum = true;
			if(Check_Turning(i - 1, j, i, j + 1)) sum = true;
			if(Check_Turning(i + 1, j, i, j - 1)) sum = true;
			if(Check_Turning(i + 1, j, i, j + 1)) sum = true;
			//Rules to check turning

			Turnings[i][j] = sum;
		}
	//Search the Turnings
} //Process the base data