#include<stdio.h>
#include<stdlib.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
} Point;

// Iterative BFS version of group_dot
void group_dot_bfs(int start_i, int start_j,
                   int width, int height,
                   int **bright,
                   int *min_x, int *max_x,
                   int *min_y, int *max_y) {
    int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}}; // 4-connectivity

    Point *queue = malloc(width * height * sizeof(Point));
    int front = 0, back = 0;

    // push start
    queue[back++] = (Point){start_i, start_j};

    while (front < back) {
        Point p = queue[front++];
        int i = p.x;
        int j = p.y;

        // bounds check
        if (i < 0 || i >= height || j < 0 || j >= width) continue;

        // skip if already visited or dark
        if (bright[i][j] == 0) continue;

        // mark visited
        bright[i][j] = 0;

        // update bounding box
        if (j < *min_x) *min_x = j;
        if (j > *max_x) *max_x = j;
        if (i < *min_y) *min_y = i;
        if (i > *max_y) *max_y = i;

        // push neighbors
        for (int d = 0; d < 4; d++) {
            int ni = i + dirs[d][0];
            int nj = j + dirs[d][1];
            if (ni >= 0 && ni < height && nj >= 0 && nj < width && bright[ni][nj] == 1) {
                queue[back++] = (Point){ni, nj};
            }
        }
    }

    free(queue);
}

/*void boundry_zero_to_ones(int i,int j,int width,int height,int **bright,int **visited,int *count_zero, int **arr);
{
	 if( i < 0 || j < 0 || i >= height || j >= width )return;
	 if(bright[i][j]==1  && visited[i][j]==1)return;
	 if(bright[i][j] == 1 && bright[i][j] == 0){ //store the index where 0 is beside 1 and keep a count; 
	 // arr[heigth][width] will contain all index boundes 0 by 1's 
	 arr[i][j+1]=bright[i][j];
	 (*count_zero)++;
	 }
	 if((count_zero) > 50){
		 //call another function that will fill that bounded zeros with 1(that is bright pixel)
		 fill_zeros(i,j,width,height,bright,visited,count_zeros,arr);
	 }
	 //check all bounded 0 in digonally 
	 bounder_zero_to_ones(i,j+1,width,height,bright,visited,count_zero,arr);
	 bounder_zero_to_ones(i,j-1,width,height,bright,visited,count_zero,arr);
	 bounder_zero_to_ones(i+1,j,width,height,bright,visited,count_zero,arr);
         bounder_zero_to_ones(i-1,j,width,height,bright,visited,count_zero,arr);

         bounder_zero_to_ones(i+1,j-1,width,height,bright,visited,count_zero,arr);
         bounder_zero_to_ones(i+1,j+1,width,height,bright,visited,count_zero,arr);
         bounder_zero_to_ones(i-1,j+1,width,height,bright,visited,count_zero,arr);
         bounder_zero_to_ones(i-1,j-1,width,height,bright,visited,count_zero,arr);
	 
}
  void fill_zeros(int i,int j,int width,int height,int **bright,int **visited,int *count_zeros,int **arr){
	  for(i=0;i<height;i++){
		 for(j=0;j<width;j++){
			

		 }
	  }

*/
/*void group_dot(int i,int j,int width,int height,int **bright,int **visited,int *min_x,int *max_x,int *min_y,int *max_y,int *area,int *threshold,int *zero_count){
		       if( i < 0 || j < 0 || i >= height || j >= width )return;
		       if(visited[i][j] == 1)return;
		       if (bright[i][j] == 0) {
		       	    if (*zero_count >= *threshold) return;  // too many zeros -> stop
		       		(*zero_count)++; 
                       }
		       bright[i][j]=1;

    
     
		       visited[i][j]=1;
		       
		       (*area)++;
		       //value is all 1 and 0 so comparing with index;
		       if(*min_x > j) *min_x=j;
		       if(*max_x < j) *max_x=j;
		       if(*min_y > i) *min_y=i;
		       if(*max_y < i) *max_y=i; 
		            
		       group_dot(i-1,j,width,height,bright,visited,min_x,max_x,min_y,max_y,area,threshold,zero_count); //for looking the up element
		       group_dot(i+1,j,width,height,bright,visited,min_x,max_x,min_y,max_y,area,threshold,zero_count);  //down
		       group_dot(i,j-1,width,height,bright,visited,min_x,max_x,min_y,max_y,area,threshold,zero_count); //left
		       group_dot(i,j+1,width,height,bright,visited,min_x,max_x,min_y,max_y,area,threshold,zero_count);  //right
		      
		       //group_dot(i+1,j+1,width,height,bright,visited,min_x,max_x,min_y,max_y,area,threshold,zero_count); 			
		       //group_dot(i+1,j-1,width,height,bright,visited,min_x,max_x,min_y,max_y,area,threshold,zero_count); 
		       //group_dot(i-1,j-1,width,height,bright,visited,min_x,max_x,min_y,max_y,area,threshold,zero_count); 
		       //group_dot(i-1,j+1,width,height,bright,visited,min_x,max_x,min_y,max_y,area,threshold,zero_count); 
	       }
*/
int main(){

	FILE *fp;
	int width,height,maxvalue;
	char format[3];
	fp=fopen("blackboard_dot_p3.ppm","r+");
	if(!fp){
		printf("file cannot be open");
		return 1;
	}
	fscanf(fp, "%s", format); 
	fscanf(fp, "%d %d", &width, &height); 
	fscanf(fp, "%d", &maxvalue);

        int r,g,b;	;
//	int bright_pixel,bright[height][width];
//	int visited[height][width];
//	int image[height][width][3];
         int **bright = malloc(height * sizeof(int *));
         int **visited = malloc(height * sizeof(int *));
         int (*image)[width][3] = malloc(height * sizeof(*image));

         for (int i = 0; i < height; i++) {
         bright[i] = malloc(width * sizeof(int));
         visited[i] = malloc(width * sizeof(int));
	 }
	
	for(int i=0; i < height ; i++){
		for(int j=0;j< width;j++){
			visited[i][j]=0;
			fscanf(fp, "%d %d %d", &r, &g, &b);

                        image[i][j][0] = r;
                        image[i][j][1] = g;
                        image[i][j][2] = b;

//		printf("R = %d ,G = %d , B = %d ",r,g,b);
			if((r+g+b)/3 > 150){   
				bright[i][j]=1;
			}
			else{
				bright[i][j]=0;
			}
		}
	}
	fclose(fp);
	int dot_count=0;
	for(int i=0; i<height ;i++){
		 for(int j=0;j < width;j++){
			 int area;
			 if(bright[i][j] == 1 && visited[i][j] == 0){
		         	int min_x=j,max_x=j,min_y=i,max_y=i;
				area=0;
				//int dot_w=max_x-min_x+1;
		 		// int dot_h=max_y-min_y+1;
			        // int area_dot=dot_w*dot_h;
				//found the new dot
				int zero_count = 0;
                                int threshold =10;
				group_dot_bfs(i, j, width, height, bright, &min_x, &max_x, &min_y, &max_y);

				//group_dot(i,j,width,height,bright,visited,&min_x,&max_x,&min_y,&max_y,&area,&threshold,&zero_count);
//				boundry_zero(i,j,width,height,bright,visited,&min_x,&max_x,&min_y,&max_y,&area);
				//dot_count++;
				if(area > 400){
			        dot_count++;
				//if (dot_w >= 10  && dot_h >= 10) {
       			        // Draw top/bottom edges
       			        	for (int x = min_x; x <= max_x; x++) {
            					image[min_y][x][0] = 255; image[min_y][x][1] = 255; image[min_y][x][2] = 0;
            					image[max_y][x][0] = 255; image[max_y][x][1] = 255; image[max_y][x][2] = 0;
        					}		
        				//draw left/right edges
        				for (int y = min_y; y <= max_y; y++) {
            					image[y][min_x][0] = 255; image[y][min_x][1] = 255; image[y][min_x][2] = 0;
            					image[y][max_x][0] = 255; image[y][max_x][1] = 255; image[y][max_x][2] = 0; 				 					
    						}
			               // }
				}        
				else{
					 continue;
				}		 				     
		          }       
	            }
	}

	printf("Total dot are : %d",dot_count);

			
	FILE *out = fopen("output.ppm", "w");
    	fprintf(out, "P3\n%d %d\n255\n", width, height);
    	for (int i = 0; i < height; i++) {
        	 for (int j = 0; j < width; j++) {
           		fprintf(out, "%d %d %d\n", image[i][j][0], image[i][j][1], image[i][j][2]);
       			}	
		}

    	fclose(out);
    	for (int i = 0; i < height; i++) {
        	free(bright[i]);
        	free(visited[i]);
    	}
    	free(bright);
    	free(visited);
    	free(image);
    	return 0;
}
	
