#include "cprocessing.h"

typedef struct Player {
	CP_Vector position;
	CP_Vector direction;
	int speed;
	int diameter;
};

typedef struct Health {
	CP_Vector position;
	CP_Vector scale;
	int max_health;
	int current_health;
};

typedef struct Zone {
	CP_Vector position;
	int diameter;
};

void Game_Init(void)
{


}


void Game_Update(void)
{
}

void Game_Exit(void)
{

}