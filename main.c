#include "raylib.h"
#include "math.h"

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

typedef struct{
	Vector2 velocity; 	
	Vector2 position;
}Floor;

void kinematics(Player *player,float dt){
		player->velocity.x+=player->acc.x*dt;
		player->velocity.y+=player->acc.y*dt;
}

bool collisioncheck(Player *player){
	if(player->position.y+PHEIGHT>=500){
			return true;
		}else{
			return false;
		}
}

void groundcheck(Player *player,bool grounded){
		if(grounded){
			player->velocity.y=0;
		}else{
			player->acc.y=GRAVITY;
		}
}

int main(void){

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game");

	SetTargetFPS(60);

	Player p1={
		.acc={0,0},
		.velocity={0,0},
		.position={40,500-PHEIGHT},
		.mass=80,
	};
	
	Floor floor={
		.velocity={0},
		.position={-5000,500},
	};

	Color playercol=RED;
	bool grounded=true;
		
	Rectangle floorrect={floor.position.x,floor.position.y,10000,SCREEN_HEIGHT-500};				

	Camera2D cam={0};
	cam.offset=(Vector2){SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f};

	// player appears at screen center
	cam.target=(Vector2){p1.position.x+PWIDTH/2,p1.position.y+PHEIGHT/2};

	cam.rotation=0.0f;
	cam.zoom=1.0f;

	while (!WindowShouldClose()){

		float dt = GetFrameTime();

		kinematics(&p1,dt);

		grounded=collisioncheck(&p1);

		groundcheck(&p1, grounded);

		if (IsKeyDown(KEY_A)){
			p1.velocity.x=-PLAYER_SPEED;
		}else if (IsKeyReleased(KEY_A)){
			p1.velocity.x=0;
		}else if (IsKeyDown(KEY_D)){
			p1.velocity.x=PLAYER_SPEED;
		}else if (IsKeyReleased(KEY_D)){
			p1.velocity.x=0;
		} 

		if (IsKeyPressed(KEY_SPACE) && grounded){
			p1.velocity.y=-JUMP_VELOCITY;
		}

		p1.position.x+=p1.velocity.x*dt;
		p1.position.y+=p1.velocity.y*dt;

		Vector2 goal={p1.position.x+PWIDTH/2,p1.position.y+PHEIGHT/2};

		float t=1.0f-expf(-8.0f*dt);    
		cam.target.x+=(goal.x-cam.target.x)*t;

		Rectangle prect={p1.position.x,p1.position.y,PWIDTH,PHEIGHT};

		BeginDrawing();

		ClearBackground(BLACK);

		BeginMode2D(cam);                       

		DrawRectangleRec(prect, playercol);
		DrawRectangleRec(floorrect, GREEN);

		EndMode2D();                            

		DrawText(TextFormat(" y velocity: %f",p1.velocity.y), 500, 10, 20,WHITE);
		DrawText(TextFormat("y acc: %f",p1.acc.y), 500, 45, 20,BLUE);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}

