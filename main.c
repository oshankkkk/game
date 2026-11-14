#include "raylib.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800

#define GRAVITY 9.8f 
#define JUMP_VELOCITY 4.4f
#define PLAYER_SPEED 5.f

#define PWIDTH 40.0f
#define PHEIGHT 40.0f

typedef struct{
	Vector2 position;
	Vector2 velocity;
	Vector2 acc;
	float mass;
}Player;

int game_init();
int game_update(float dt);
int game_draw();
int game_close();


int main(void){

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pixel Engine");

	SetTargetFPS(60);

	//game init

	Player p1={
		.acc={0,GRAVITY},
		.velocity={0,0},
		.position={0,0},
		.mass=80,
	};
		

	while (!WindowShouldClose()){

		float dt = GetFrameTime();

		//game update
		p1.velocity.x+=p1.acc.x*dt;
		p1.velocity.y+=p1.acc.y*dt;

		p1.position.x+=p1.velocity.x*dt;
		p1.position.y+=p1.velocity.y*dt;

		if (IsKeyDown(KEY_D)){
			p1.velocity.x=PLAYER_SPEED;
		}else if (IsKeyDown(KEY_A)){
			p1.velocity.x=-PLAYER_SPEED;
		}else if (IsKeyPressed(KEY_SPACE)){
			p1.velocity.y=JUMP_VELOCITY;
		}

		Rectangle prect={p1.position.x,p1.position.y,PWIDTH,PHEIGHT};

		//collision detection and then simulate normal force and gravity.
		//if collied with plateform normal force =-gravity or velocity.y=0? something
		//how that depends on slopes, make it colide and slide 

		BeginDrawing();

		ClearBackground(BLACK);

		DrawRectangleRec(prect, RED);

		EndDrawing();
	}

	//game close

	CloseWindow();

	return 0;
}


