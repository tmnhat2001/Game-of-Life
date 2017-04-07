#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// Initialize a grid of size w x h
void fill_grid(int** grid, int w, int h) {
	int i = 0;
	for(; i < w; i++) {
		grid[i] = (int*) malloc(sizeof(int)*h);
		int j = 0;
		for(; j < h; j++) {
			grid[i][j] = 0;
		}
	}
}

// Deallocate memory from a grid
void free2d(int** grid, int w) {
	int i = 0;
	for(; i < w; i++) {
		free(grid[i]);
	}
	free(grid);
}

int main(int argc, char* argv[]) {
	if (argc < 3) puts("Usage: ./serial rows cols");

	int w = atoi(argv[1]);
	int h = atoi(argv[2]);

	if (w < 10 || h < 10) puts("Number of rows and columns must be at least 20");

	int** grid = (int**) malloc(sizeof(int*) * w);
	fill_grid(grid, w, h);
	
	// temporary grid to store new cells
	int** tmp = (int**) malloc(sizeof(int*) * w);

	// glider configuration
	grid[5][5] = 1;
	grid[6][6] = 1;
	grid[7][4] = 1;
	grid[7][5] = 1;
	grid[7][6] = 1;
	
	int k = 0;
	while(1) {
		printf("Time %d\n", k);
		
		fill_grid(tmp, w, h);
		
		int i = 0;
		for(; i < w; i++) {
			int j = 0;
			for(; j < h; j++) {
				int count = 0;
				int r1,r2,c1,c2;
				
				// check for boundary conditions
				c1 = (j+1) % h;
				c2 = (j-1) % h;
				if (c2 < 0) c2 = c2 + h;

				r1 = (i+1) % w;
				r2 = (i-1) % w;
				if (r2 < 0) r2 = r2 + w;
 			
				// count number of neighbor cells
				if (grid[i][c1] == 1) count++;
				if (grid[i][c2] == 1) count++;
				if (grid[r1][c1] == 1) count++;
				if (grid[r1][j] == 1) count++;
				if (grid[r1][c2] == 1) count++;
				if (grid[r2][c1] == 1) count++;
				if (grid[r2][j] == 1) count++;
				if (grid[r2][c2] == 1) count++;
				
				// make decision for next stage and display current stage
				if (grid[i][j] == 0) {
                                        printf("-");
					if (count == 3) tmp[i][j] = 1;
                                } else {
                                        printf("O");
					
					if (count < 2 || count > 3) tmp[i][j] = 0;
					else if (count == 2 || count == 3) tmp[i][j] = 1;
                                }
 
			}
			puts("");
		}
		
		// copy current grid with new grid
		int t = 0;
		for(; t < w; t++) {
			memcpy(grid[t], tmp[t], sizeof(int)*h);
		}
		
		k++;

		puts("");
		sleep(1);
	}
	free2d(grid, w);
	free2d(tmp, w);
	return 0;
}
