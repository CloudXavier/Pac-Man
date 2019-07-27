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

int Strong_Time, life, beans, level;

bool Check_Turning(int x, int y, int a, int b) {
	return Map[x][y] ^ '#' && Map[a][b] ^ '#';
} //Check whether it's a turning

void Load_Data(void) {
	srand((unsigned)(time(NULL))); //Reset the Random seed

	Save_Ghost[1].X = 13, Save_Ghost[2].X = 14, Save_Ghost[3].X = 14, Save_Ghost[4].X = 14;
	Save_Ghost[1].Y = 11, Save_Ghost[2].Y = 10, Save_Ghost[3].Y = 11, Save_Ghost[4].Y = 12;
	Save_Ghost[1].Direction = 1, Save_Ghost[2].Direction = 4, Save_Ghost[3].Direction = 1, Save_Ghost[4].Direction = 3;
	Save_Ghost[1].Color = 4, Save_Ghost[2].Color = 14, Save_Ghost[3].Color = 11, Save_Ghost[4].Color = 13;
	Save_Ghost[1].locked = 10, Save_Ghost[2].locked = 10, Save_Ghost[3].locked = 10, Save_Ghost[4].locked = 10;
	// Process the Ghost

	Score = 0, life = 3, level = 1; //Reset the Score, life and the level

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
}

void Data_Processing(int temp) {

	PacMan.X = 21, PacMan.Y = 11, PacMan.Direction = 1, PacMan.Color = 14;
	
	for(int i = 1; i < 5; i++) {
		Ghost[i].X = Save_Ghost[i].X;
		Ghost[i].Y = Save_Ghost[i].Y;
		Ghost[i].Direction = Save_Ghost[i].Direction;
		Ghost[i].Color = Save_Ghost[i].Color;
		Ghost[i].locked = Save_Ghost[i].locked;
	}

	if(!temp) {
		PacMan.locked = 5;
		return;
	}

	beans = 188; // Reset the number of the bean

	for(int i = 0; i <= Height + 1; i++)
		for(int j = 0; j <= Width + 1; j++)
			Map[i][j] = Save_Map[i][j];
	//Give "Save" to "Map" (Restore data)
} //Process the base data