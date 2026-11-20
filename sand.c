#include "raylib.h"
#include <stdlib.h>
#include <string.h>

#define CELLSIZE 8
#define SCREENW 1200
#define SCREENH 850
#define GRIDROW SCREENW/CELLSIZE
#define GRIDCOL SCREENH/CELLSIZE
#define GRAVITY .25f

typedef struct{
	Vector2 velocity;
	Vector2 acc;
	int mass;
	int filled;
	float accum;
}Grain ;

int main(void){

	InitWindow(SCREENW, SCREENH, "sand sim");

	SetTargetFPS(60);               

	Grain **grid=calloc(GRIDROW, sizeof(*grid));

	for (int i=0;i<GRIDROW;i++){
		grid[i]=calloc(GRIDCOL,sizeof(**grid));
		if (grid[i] == NULL) {
			for (int j = 0; j < i; j++) {
				free(grid[j]);
			}
			free(grid);
			return 1;
		}
	}

	Vector2 mouspoistion;

	while (!WindowShouldClose()){

		mouspoistion=GetMousePosition();

		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
			int r = mouspoistion.x / CELLSIZE;
			int c = mouspoistion.y / CELLSIZE;

			if (r >= 0 && r < GRIDROW && c >= 0 && c < GRIDCOL && !grid[r][c].filled ) {
				grid[r][c] = (Grain){.velocity={0,0},.acc={0,GRAVITY},.filled=1,.mass=10,.accum=0};
			}
		}
	
		for (int j = GRIDCOL - 1; j >= 0; j--){
			for (int i = 0; i < GRIDROW; i++){

				if (!grid[i][j].filled) continue;

				Grain g = grid[i][j];

				g.velocity.y += g.acc.y;

				g.accum += g.velocity.y;
				int steps = (int)g.accum;
				g.accum -= steps;

				int x = i, y = j;

				while (steps > 0){

					steps--;

					if (y + 1 >= GRIDCOL) { 
						g.velocity.y = 0; 
						g.accum = 0;
						break; 
					}

					int dir = GetRandomValue(0, 1) ? 1 : -1;

					if (!grid[x][y+1].filled) {
						y++;
					} else if (x+dir >= 0 && x+dir < GRIDROW && !grid[x+dir][y+1].filled) {
						x += dir; y++;
					} else if (x-dir >= 0 && x-dir < GRIDROW && !grid[x-dir][y+1].filled) {
						x -= dir; y++;
					} else {
						g.velocity.y = 0; 
						g.accum = 0;
						break;
					}
				}

				if (y == GRIDCOL - 1) { g.velocity.y = 0; g.accum = 0; }
				grid[i][j] = (Grain){0};  
				grid[x][y] = g;  

			}
		}

		BeginDrawing();

		ClearBackground(BLACK);

		for (int i=0;i<GRIDROW;i++){
			for (int j=0;j<GRIDCOL;j++){
				if(grid[i][j].filled==1){
					DrawRectangle(i*CELLSIZE,j*CELLSIZE,CELLSIZE,CELLSIZE,RED);
				}
			}
		}

		EndDrawing();
	}

	CloseWindow();        

	return 0;
}

