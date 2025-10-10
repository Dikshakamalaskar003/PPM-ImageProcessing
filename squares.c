#include<stdio.h>
void group_zero(int i,int j,int width,int height,int **bright,int **visited, int *area,int *max_area){
                       if( i < 0 || j < 0 || i >= height || j >= width )return;
                       if(visited[i][j] == 1 && bright[i][j]==1)return;
                      
                       visited[i][j]=1;
//calculating max zero area then i want to count all area which is smaller than than max area
                       (*area)++;
		       if(*max_area < *area){ // maximum zero area will be calculated
			       *max_area=*area;
		   	 }
                       //value is all 1 and 0 so comparing with index;
                   //  if(*min_x > j) *min_x=j;
                    // if(*max_x < j) *max_x=j;
                     //if(*min_y > i) *min_y=i;
                      //f(*max_y < i) *max_y=i;
		       group_zero(i-1,j,width,height,bright,visited,area,max_area);
		       //for looking the up element
                       group_zero(i+1,j,width,height,bright,visited,area,max_area);  //down
                       group_zero(i,j-1,width,height,bright,visited,area,max_area)
                       group_zero(i,j+1,width,height,bright,visited,area,max_area);

                       //group_dot(i+1,j+1,width,height,bright,visited,min_x,max_x,min_y,max_y,area,threshold,zero_count);
                       //group_dot(i+1,j-1,width,height,bright,visited,min_x,max_x,min_y,max_y,area,threshold,zero_count);
                       //group_dot(i-1,j-1,width,height,bright,visited,min_x,max_x,min_y,max_y,area,threshold,zero_count);
                       //group_dot(i-1,j+1,width,height,bright,visited,min_x,max_x,min_y,max_y,area,threshold,zero_count);
               }


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

        int r,g,b;      ;
//      int bright_pixel,bright[height][width];
//      int visited[height][width];
//      int image[height][width][3];
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

			fscanf(fp,"%d %d %d",&r, &g, &b);
			image[i][j][0]=r;
			image[i][j][1]=g;
			image[i][j][2]=b;

			if((r+g+b)/3 > 200){
				bright[i][j]=1;
			}
			else{
				bright[i][j]=0;
			}

		}
          }
	fclose(fp);
	int sq_count=0;
	for(int i=0;i<height;i++){
		for(int j=0;j< width; j++){
			int area=0;
			if(bright[i][j]==0 && visited[i][j]==0){
				group_zero(i,j,width,height,bright,visited,area,max_area);
				if(max_area > area){
					sq_count++; //calculate tha total square
				}
			}
		}
	}

}
