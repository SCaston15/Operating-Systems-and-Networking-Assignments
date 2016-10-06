/*
 Stephanie Caston
 ITCS 3146
 Bojan Cukic 
 9/15/2015
*/
#include <stdio.h>
main()
{
    char array[200][200] = {1}; //Fills an int array with all 1s
    int M;
    int N;
    printf("Enter the desired width of the maze.\n"); //Asks the user to enter the width
    scanf(" %d", &M);
    printf("Enter the desired height of the maze.\n"); //Asks the user to enter the height
    scanf(" %d", &N);
    
    // Code that reads in the text file with the field of 1s and 0s
    FILE *fptr;
    char c;
    char file_name[20];
    int i,j;
    
    printf("Type in the name of the file containing the Field\n");
    scanf("%s",file_name);
    fptr=fopen(file_name,"r");
    for (i=0; i<M; i++)
        for (j=0; j<N; j++){
            c=fgetc(fptr);
            while ( !((c == '1')||(c =='0')) ) c=fgetc(fptr);
            array[i][j]=c;
        }
    fclose(fptr);
    
    for (i=0; i<M; i++)
        for (j=0; j<N; j++)  {
            if (j == 0) printf("\n");
            printf("%c  ",array[i][j]);
        }
    printf("\n");
    printf("\n");
    
    int startx, starty = 0; //values to store entrance coordinate
    int endx, endy = 0; //values to store exit coordinate
    int foundEntrance = 0; //Set to false until entrance is found
    int foundExit = 0; // Set to false until exit is found
    
    for(i=0; i<M; i++){
        if(array[i][0] == '0') startx = i, starty = 0, foundEntrance = 1;
    }
    
    for(i=0; i<N; i++){
        if(array[M-1][i] == '0' && foundEntrance == 0) startx = M-1, starty = i, foundEntrance = 1;
        else if (array[M-1][i] == '0' && foundEntrance == 1) endx = M-1, endy = i, foundExit = 1;
    }
    
    for(i=M-1; i>-1; i--){
        if(array[i][N-1] == '0' && foundEntrance == 0) startx = i, starty = N-1, foundEntrance = 1;
        else if (array[i][N-1] == '0' && foundEntrance == 1) endx = i, endy = N-1, foundExit = 1;
        
    }
    
    for(i=N; i>0; i--){
        if(array[0][i-1] == '0' && foundExit == 0) endx = 0, endy = i-1, foundExit = 1;
    }
    
    printf("The entrance coordinates are: %d, %d", startx, starty); //Displays start coordinate
    printf("\n");
    printf("The exit coordinates are: %d, %d", endx, endy); //Displays end coordinate
    printf("\n");
    
    if(foundEntrance != 1 || foundExit!= 1)
    {
        printf("Cannot attempt maze because there is a missing entrance or exit.");
    }
    
    //startx = column
    //starty = row
    int row = startx;
    int col = starty;
    int beginning;
    int end;
    int direction; //holds directional number
    int counter = 0;
    char surpoint[4] = {'1'}; // Array to hold surrounding points
    
    if(row == (M - 1))
    {                        // Enter up
        direction = 1;
    }
    else if(col == (N - 1))
    {                        // Enter on left side of maze
        direction = 2;
    }
    else if(row == 0)
    {                       //Enter down
        direction = 3;
    }
    else{                       // Enter on right side of maze
        direction = 4;
    }
    
    /*               1
     * direction = 2   4
     *               3
     *
     */
    
    
    do{
        
        //assigns surpoint to clearer directions
        int forward = surpoint[0];
        int left = surpoint[1];
        int behind = surpoint[2];
        int right = surpoint[3];
        //Change current position to X
        array[row][col] = 'X';
        
        /*
         direction 1 = ^
         direction 2 = <
         direction 3 = v
         direction 4 = >
         */
        //Assigns surrounding map coordinates to array depending on which direction you are facing
        if(direction == 1){
            right = array[row][col+1];
            forward = array[row-1][col];
            left = array[row][col-1];
            behind = array[row+1][col];
        }
        else if (direction == 2){
            behind = array[row][col+1];
            right = array[row-1][col];
            forward = array[row][col-1];
            left = array[row+1][col];
        }
        else if (direction == 3){
            left = array[row][col+1];
            behind = array[row-1][col];
            right = array[row][col-1];
            forward = array[row+1][col];
        }
        else if (direction == 4){
            forward = array[row][col+1];
            left = array[row-1][col];
            behind = array[row][col-1];
            right = array[row+1][col];
        }
        
        //Maps the way through the maze
        
        if(forward != '1' && right == '1') //go forward one spot
        {
            if(direction == 1)
            {
                row--;
                direction = 1;
                array[row][col] = '^';
            }
            else if(direction == 2)
            {
                col--;
                direction = 2;
                array[row][col] = '<';
            }
            else if(direction == 3)
            {
                row++;
                direction = 3;
                array[row][col] = 'v';
            }
            else
            {
                col++;
                direction = 4;
                array[row][col] = '>';
            }
            
        }
        else if(right != '1') //go right one spot
        {
            if(direction == 1)
            {
                col++;
                direction = 4;
                array[row][col] = '>';
            }
            else if(direction == 2)
            {
                row--;
                direction = 1;
                array[row][col] = '^';
            }
            else if(direction == 3)
            {
                col--;
                direction = 2;
                array[row][col] = '<';
            }
            else
            {
                row++;
                direction = 3;
                array[row][col] = 'v';
            }
            
        }
        else if(left != '1') //go left one spot
        {
            if(direction == 1)
            {
                col--;
                direction = 2;
                array[row][col] = '<';
            }
            else if(direction == 2)
            {
                row++;
                direction = 3;
                array[row][col] = 'v';
            }
            else if(direction == 3)
            {
                col++;
                direction = 4;
                array[row][col] = '>';
            }
            else
            {
                row--;
                direction = 1;
                array[row][col] = '^';
            }
            
        }
        else if(behind != '1') //turn around and go forward one spot
        {
            if(direction == 1)
            {
                row++;
                direction = 3;
                array[row][col] = 'v';
            }
            else if(direction == 2)
            {
                col++;
                direction = 4;
                array[row][col] = '>';
            }
            else if(direction == 3)
            {
                row--;
                direction = 1;
                array[row][col] = '^';
            }
            else
            {
                col--;
                direction = 2;
                array[row][col] = '<';
            }
        }
        
        //Sets entrance to true if you return to starting coordinates
        if((row == startx && col == starty)){
            beginning = 1;
        }
        
        //Sets end to true if you make it to the exit coordinates
        if(row == endx && col == endy){
            end = 1;
        }
        
    }while(beginning != 1 && end != 1 && foundEntrance == 1 && foundExit == 1);  //end loop when you reach entrance again or exit
    
    for (i=0; i<M; i++)
        for (j=0; j<N; j++)  {
            if (j == 0) printf("\n");                
            printf("%c  ",array[i][j]);
        }
    
    printf("\n");
    printf("Path ended at row: %d ", row);
    printf("col: %d\n", col);
    //Prints out if an entrance or exit was found after traversing the maze 
    if(beginning == 1){
        printf("Path not found.");
    }
    else if(end == 1){
        printf("Path was found.");
    }
    
    printf("\n"); 
}
