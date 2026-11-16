#include "raylib.h"
#include <stdio.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800

#define PIXELS_PER_METER 100 

#define GRAVITY (9.8f * PIXELS_PER_METER)
#define JUMP_VELOCITY (4.4f * PIXELS_PER_METER)
#define PLAYER_SPEED (5.f * PIXELS_PER_METER)

#define PWIDTH 40.0f
#define PHEIGHT 40.0f

typedef struct{
	Vector2 position;
	Vector2 velocity;
	Vector2 acc;
	float mass;
}Player;

int main(void){

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game");

	SetTargetFPS(60);

	Player p1={
		.acc={0,0},
		.velocity={0,0},
		.position={40,500-PHEIGHT},
		.mass=80,
	};

	Color playercol=RED;

	Rectangle floor={0,500,SCREEN_WIDTH,SCREEN_HEIGHT-500};				

	while (!WindowShouldClose()){

		float dt = GetFrameTime();

		p1.velocity.x+=p1.acc.x*dt;
		p1.velocity.y+=p1.acc.y*dt;

		p1.position.x+=p1.velocity.x*dt;
		p1.position.y+=p1.velocity.y*dt;

		Rectangle prect={p1.position.x,p1.position.y,PWIDTH,PHEIGHT};

		if(p1.position.y+PHEIGHT>=500){
			printf("grounded\n");
			fflush(stdout);
			
			p1.acc.y=0;
			p1.velocity.y=0;
		}else{
			p1.acc.y=GRAVITY;
		}
		 
		if (IsKeyDown(KEY_D)){
			p1.velocity.x=PLAYER_SPEED;
		}else if (IsKeyDown(KEY_A)){
			p1.velocity.x=-PLAYER_SPEED;
		}else if (IsKeyPressed(KEY_SPACE)){
			p1.velocity.y=-JUMP_VELOCITY;
		}


		BeginDrawing();

		ClearBackground(BLACK);

		DrawRectangleRec(prect, playercol);
		DrawRectangleRec(floor, GREEN);

		DrawText(TextFormat(" y velocity: %f",p1.velocity.y), 500, 10, 20,WHITE);
		DrawText(TextFormat("y acc: %f",p1.acc.y), 500, 45, 20,BLUE);

		EndDrawing();
	}

	//game close

	CloseWindow();

	return 0;
}


