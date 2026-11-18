#include "raylib.h"
#include <stdlib.h>
#include <string.h>

#define CELLSIZE 8
#define SCREENW 1200
#define SCREENH 850
#define GRIDROW SCREENW/CELLSIZE
#define GRIDCOL SCREENH/CELLSIZE


int main(void){

	InitWindow(SCREENW, SCREENH, "sand sim");

	SetTargetFPS(60);               

	char **grid=calloc(GRIDROW, sizeof(int *));

	for (int i=0;i<GRIDROW;i++){
		grid[i]=calloc(GRIDCOL,sizeof(int));
		if (grid[i] == NULL) {
			for (int j = 0; j < i; j++) {
				free(grid[j]);
			}
			free(grid);
			return 1;
		}
	}

	char **grid2=calloc(GRIDROW, sizeof(int *));

	for (int i=0;i<GRIDROW;i++){
		grid2[i]=calloc(GRIDCOL,sizeof(int));
		if (grid2[i] == NULL) {
			for (int j = 0; j < i; j++) {
				free(grid2[j]);
			}
			free(grid2);
			return 1;
		}
	}

	Vector2 mouspoistion;

	while (!WindowShouldClose()){

		mouspoistion=GetMousePosition();

		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
			int r = mouspoistion.x / CELLSIZE;
			int c = mouspoistion.y / CELLSIZE;

			if (r >= 0 && r < GRIDROW && c >= 0 && c < GRIDCOL) {
				grid[r][c] = 1;
			}
		}

		for (int i = 0; i < GRIDROW; i++){
			memset(grid2[i], 0, GRIDCOL);
		}


		for (int i=0;i<GRIDROW;i++){
			for (int j = GRIDCOL - 1; j >= 0; j--){
				if (grid[i][j] != 1) continue;
				if(j + 1 >= GRIDCOL){
					grid2[i][j] = 1;
					continue;
				}	

				int dir =GetRandomValue(0,1)?1:-1;
				int a=i+dir;
				int b=i-dir;

				if(grid[i][j]==1){
					if (grid2[i][j+1] == 0){
						grid2[i][j+1] = 1;   
					}else if(a>=0 && a < GRIDROW && grid[a][j+1] == 0){
						grid2[a][j+1] = 1;
					}else if(b>=0 && b < GRIDROW && grid[b][j+1] == 0){
						grid2[b][j+1] = 1;
					}else {
						grid2[i][j] = 1;
					}	
				}	
			}
		}

		char **temp	=grid;
		grid=grid2;
		grid2 = temp;

		BeginDrawing();

		ClearBackground(BLACK);

		for (int i=0;i<GRIDROW;i++){
			for (int j=0;j<GRIDCOL;j++){
				if(grid[i][j]==1){
					DrawRectangle(i*CELLSIZE,j*CELLSIZE,CELLSIZE,CELLSIZE,RED);

				}
			}
		}

		EndDrawing();
	}

	CloseWindow();        

	return 0;
}

