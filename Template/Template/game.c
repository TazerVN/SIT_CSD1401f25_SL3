#include "cprocessing.h"
#include "utils.h"
#include "mainmenu.h"

typedef struct Player {
	CP_Vector position;
	CP_Vector direction;
	int speed;
	float acc;
	int diameter;
};

typedef struct Health {
	CP_Vector position;
	CP_Vector scale;
	float max_health;
	float current_health;
};

typedef struct Zone {
	CP_Vector position;
	int diameter;
	CP_Color color;
};

struct Player p1;
struct Health healthbar;
struct Zone healing_zone;
struct Zone damage_zone;
float dt;


void lose_health() {
	int value = 10;
	if (healthbar.current_health > 0) {
		healthbar.current_health -= dt * value;
	}
}

void gain_health() {
	int value = 10;
	if (healthbar.current_health < healthbar.max_health) {
		healthbar.current_health += dt * value;
	}
}

void zone_draw(struct Zone* z, void *f(void)) {
	CP_Settings_Fill(z->color);
	CP_Graphics_DrawCircle(z->position.x, z->position.y, z->diameter);
	if (AreCirclesIntersecting(z->position.x, z->position.y, z->diameter / 2, p1.position.x, p1.position.y, p1.diameter / 2)) {
		f();
	}

}

void healthbar_draw(struct Health* h) {
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Settings_Fill(CP_Color_Create(100, 0, 0, 255));
	CP_Graphics_DrawRect(h->position.x, h->position.y, h->scale.x, h->scale.y);//healthbar background
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Graphics_DrawRect(h->position.x, h->position.y, h->scale.x * h->current_health/h->max_health, h->scale.y);//healthbar current
}

void health_brick(struct Health* h) {
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	if (h->current_health > 0) {
		int num = 10 * (h->current_health / h->max_health);
		for (int i = 1; i <= num; i++) {
			CP_Graphics_DrawRect((h->position.x - h->scale.x / 10 + (i * h->scale.x / 10)), h->position.y + h->scale.y + 50, h->scale.x / 12, h->scale.y / 8);
		}
	}
}

void player_draw(struct Player* p) {
	
	float dt = CP_System_GetDt();
	float x = p->position.x;
	float y = p->position.y;
	float s = p->speed;
	float a = p->acc;
	CP_Vector d = CP_Vector_Set(p->direction.x, p->direction.y);

	if (CP_Input_KeyDown(KEY_S)) {
		d.y += dt * a;
	}
	if (CP_Input_KeyDown(KEY_W)) {
		d.y -= dt * a;
	}
	if (CP_Input_KeyDown(KEY_D)) {
		d.x += dt * a;
	}
	if (CP_Input_KeyDown(KEY_A)) {
		d.x -= dt * a;
	}

	if (d.x > 0.00) {
		d.x = d.x - dt < 0 ? 0 : d.x - dt;
	}
	if (d.x < 0.00) {
		d.x = d.x + dt > 0 ? 0 : d.x + dt;
	}
	if (d.y > 0.00) {
		d.y = d.y - dt < 0 ? 0 : d.y - dt;
	}
	if (d.y < 0.00) {
		d.y = d.y + dt > 0 ? 0 : d.y + dt;
	}

	d.x = CP_Math_ClampFloat(d.x, -1, 1);
	d.y = CP_Math_ClampFloat(d.y, -1, 1);

	x += d.x * s;
	y += d.y * s;

	p->direction.x = d.x;
	p->direction.y = d.y;
	p->position.x = x;
	p->position.y = y;

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Graphics_DrawCircle(x, y, p->diameter);
}

void init_zone(struct Zone* z, int position_x, int position_y, int diameter, CP_Color c) {
	z->position = CP_Vector_Set(position_x, position_y);
	z->diameter = diameter;
	z->color = c;
}

void init_player(struct Player* p, int position_x, int position_y, int diameter, int speed, int acc ) {
	p->position = CP_Vector_Set(position_x, position_y);
	p->direction = CP_Vector_Set(0, 0);
	p->diameter = diameter;
	p->speed = speed;
	p->acc = acc;
}

void init_healthbar(struct Health* h, int position_x , int position_y, int max_health, int width, int height) {
	h->max_health = max_health;
	h->current_health = max_health;
	h->position = CP_Vector_Set(position_x, position_y);
	h->scale = CP_Vector_Set(width, height);
}

void Game_Init(void)
{
	int window_width = CP_System_GetWindowWidth();
	int window_height = CP_System_GetWindowHeight();

	init_player(&p1, window_width/2, 2 * window_height/3, 100, 10, 10);
	init_zone(&damage_zone, window_width / 4, 2 * window_height / 3, 500, CP_Color_Create(255,0,0,255));
	init_zone(&healing_zone, 3 * window_width / 4, 2 * window_height / 3, 500, CP_Color_Create(0,255,0,255));
	init_healthbar(&healthbar, window_width/10, window_height / 10, 100, 8 * window_width/10, window_height / 10);

}


void Game_Update(void)
{
	if (CP_Input_KeyDown(KEY_Q)) {
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}


	dt = CP_System_GetDt();
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	zone_draw(&damage_zone, lose_health);
	zone_draw(&healing_zone, gain_health);
	healthbar_draw(&healthbar);
	health_brick(&healthbar);

	player_draw(&p1);

}

void Game_Exit(void)
{
}