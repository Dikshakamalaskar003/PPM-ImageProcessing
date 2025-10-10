#include <stdio.h>
#include <stdlib.h>

void group_zero(int i, int j, int width, int height,
                int **bright, int **visited, int *area) {
    if (i < 0 || j < 0 || i >= height || j >= width) return;
    if (visited[i][j] || bright[i][j] == 1) return; // skip visited or bright

    visited[i][j] = 1;
    (*area)++;

    // explore 4-neighbors
    group_zero(i-1, j, width, height, bright, visited, area);
    group_zero(i+1, j, width, height, bright, visited, area);
    group_zero(i, j-1, width, height, bright, visited, area);
    group_zero(i, j+1, width, height, bright, visited, area);
}

int main() {
    FILE *fp;
    int width, height, maxvalue;
    char format[3];
    fp = fopen("squares_p3.ppm", "r+");
    if (!fp) {
        printf("file cannot be opened\n");
        return 1;
    }

    fscanf(fp, "%s", format);
    fscanf(fp, "%d %d", &width, &height);
    fscanf(fp, "%d", &maxvalue);

    int r, g, b;
    int **bright = malloc(height * sizeof(int *));
    int **visited = malloc(height * sizeof(int *));
    for (int i = 0; i < height; i++) {
        bright[i] = malloc(width * sizeof(int));
        visited[i] = malloc(width * sizeof(int));
    }

    // Read P3 pixels and threshold to bright/dark
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fscanf(fp, "%d %d %d", &r, &g, &b);
            visited[i][j] = 0;
            int gray = (r + g + b) / 3;
            bright[i][j] = (gray > 200) ? 1 : 0; // white=1, black=0
        }
    }
    fclose(fp);

    // Collect all region areas
    int areas[10000]; // assume <=10000 regions
    int count = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (bright[i][j] == 0 && visited[i][j] == 0) {
                int area = 0;
                group_zero(i, j, width, height, bright, visited, &area);
                if (area > 0) {
                    areas[count++] = area;
                }
            }
        }
    }

    // Find max area
    int max_area = 0;
    for (int k = 0; k < count; k++) {
        if (areas[k] > max_area) max_area = areas[k];
    }

    // Count regions smaller than max
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

    return 0;
}

