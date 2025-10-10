#include<stdio.h>
#include<stdlib.h>

void group_dot(int i,int j,int width,int height,int **bright,int **visited,int *min_x,int *max_x,int *min_y,int *max_y,int *area){
		       if( i < 0 || j < 0 || i >= height || j >= width )return;
		       if(bright[i][j] == 0 || visited[i][j] == 1)return;
		       

		       visited[i][j]=1;
		       (*area)++;
		       //value is all 1 and 0 so comparing with index;
		       if(*min_x > j) *min_x=j;
		       if(*max_x < j) *max_x=j;
		       if(*min_y > i) *min_y=i;
		       if(*max_y < i) *max_y=i; 
		            
		       group_dot(i-1,j,width,height,bright,visited,min_x,max_x,min_y,max_y,area); //for looking the up element
		       group_dot(i+1,j,width,height,bright,visited,min_x,max_x,min_y,max_y,area);  //down
		       group_dot(i,j-1,width,height,bright,visited,min_x,max_x,min_y,max_y,area); //left
		       group_dot(i,j+1,width,height,bright,visited,min_x,max_x,min_y,max_y,area);  //right
		       
	       }
    

int main(){
	FILE *fp;
	int width,height,maxvalue;
	char format[3];
	fp=fopen("blackboard_dot_p3.ppm","r+");
	if(!fp){
		printf("file cannot be open");
	}
	fscanf(fp, "%s", format); 
	fscanf(fp, "%d %d", &width, &height); 
	fscanf(fp, "%d", &maxvalue);

        int r,g,b;	
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
		if((r+g+b)/3 > 200){   
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
				       group_dot(i,j,width,height,bright,visited,&min_x,&max_x,&min_y,&max_y,&area);
				       //dot_count++;
				         if(area > 300){
					    dot_count++;
				      //  if (dot_w >= 10  && dot_h >= 10) {
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
    					//}
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
	
