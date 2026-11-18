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

		int r=	mouspoistion.x/CELLSIZE;
		int c=mouspoistion.y/CELLSIZE;

		grid[r][c]=1;

		for (int i = 0; i < GRIDROW; i++){
			memset(grid2[i], 0, GRIDCOL);
		}

		for (int i=0;i<GRIDROW;i++){
			for (int j = GRIDCOL - 1; j >= 0; j--){
				if(grid[i][j]==1){
					if (j + 1 < GRIDCOL && grid2[i][j+1] == 0) {
						grid2[i][j+1] = 1;   
					} else {
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

