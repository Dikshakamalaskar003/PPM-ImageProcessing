#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int i;
    int j;
} Point;

void group_zero(int start_i, int start_j, int width, int height,
                int **bright, int **visited, int *area) {
    Point *stack = malloc(width * height * sizeof(Point));
    int top = 0;
    
    stack[top].i = start_i;
    stack[top].j = start_j;
    top++;
    
    while (top > 0) {
        top--;
        int i = stack[top].i;
        int j = stack[top].j;
        
        // Check bounds
        if (i < 0 || j < 0 || i >= height || j >= width) continue;
        if (visited[i][j] || bright[i][j] == 1) continue;
        
        visited[i][j] = 1;
        (*area)++;
        
        // Push neighbors (ensure we don't overflow stack)
        if (top + 4 < width * height) {
            stack[top].i = i-1; stack[top].j = j; top++;
            stack[top].i = i+1; stack[top].j = j; top++;
            stack[top].i = i; stack[top].j = j-1; top++;
            stack[top].i = i; stack[top].j = j+1; top++;
        }
    }
    
    free(stack);
}

int main() {
    FILE *fp;
    int width, height, maxvalue;
    char format[3];
    
    fp = fopen("squares_p3.ppm", "r");
    if (!fp) {
        printf("file cannot be opened\n");
        return 1;
    }

    if (fscanf(fp, "%2s", format) != 1 || strcmp(format, "P3") != 0) {
        printf("Invalid PPM format\n");
        fclose(fp);
        return 1;
    }
    
    if (fscanf(fp, "%d %d", &width, &height) != 2) {
        printf("Invalid dimensions\n");
        fclose(fp);
        return 1;
    }
    
    if (fscanf(fp, "%d", &maxvalue) != 1) {
        printf("Invalid max value\n");
        fclose(fp);
        return 1;
    }

    // Validate dimensions
    if (width <= 0 || height <= 0 || width > 10000 || height > 10000) {
        printf("Invalid image dimensions\n");
        fclose(fp);
        return 1;
    }

    // Allocate memory
    int **bright = malloc(height * sizeof(int *));
    int **visited = malloc(height * sizeof(int *));
    for (int i = 0; i < height; i++) {
        bright[i] = malloc(width * sizeof(int));
        visited[i] = malloc(width * sizeof(int));
        memset(visited[i], 0, width * sizeof(int)); // Initialize to 0
    }

    // Read pixels
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int r, g, b;
            if (fscanf(fp, "%d %d %d", &r, &g, &b) != 3) {
                printf("Error reading pixel data\n");
                fclose(fp);
                return 1;
            }
            int gray = (r + g + b) / 3;
            bright[i][j] = (gray > 200) ? 1 : 0;
        }
    }
    fclose(fp);

    // Dynamic array for areas
    int *areas = NULL;
    int capacity = 1000;
    int count = 0;
    areas = malloc(capacity * sizeof(int));

    // Find regions
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (bright[i][j] == 0 && visited[i][j] == 0) {
                int area = 0;
                group_zero(i, j, width, height, bright, visited, &area);
                if (area > 0) {
                    if (count >= capacity) {
                        capacity *= 2;
                        areas = realloc(areas, capacity * sizeof(int));
                    }

		    printf("area %d\n",area);
                    areas[count++] = area;
                }
            }
        }
    }

    // Find max area and count squares
    int max_area = 0;
    for (int k = 0; k < count; k++) {
        if (areas[k] > max_area) max_area = areas[k];
    }

    int sq_count = 0;
    for (int k = 0; k < count; k++) {
	    
        if (areas[k] < max_area) sq_count++;
    }

    printf("Max zero area = %d\n", max_area);
    printf("Squares (smaller than max area) = %d\n", sq_count);

    // Free memory
    for (int i = 0; i < height; i++) {
        free(bright[i]);
        free(visited[i]);
    }
    free(bright);
    free(visited);
    free(areas);

    return 0;
}
