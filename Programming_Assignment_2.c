/*
 Stephanie Caston
 ITCS 3146
 Programming Assignment 2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// nodes are created here
struct node{
    char *data;
    struct node *nextPtr;
};

//Declaration of all needed pointers
struct node *list, *end, *start, *listPtr, *currPtr;

void readFile(int charPL);
void printListTest(int charPL);
void printList(int charPL);

int main()
{
    //This is the variable used to store the number of characters
    int charPL = 0;
    
    //prompts the user to choose the number of characters desired
    //repeats until user enters between 40 and 100
    do{
        printf("Enter how many characters you want per line.(Between 40-100.)\n");
        scanf("%d", &charPL);
        if(charPL < 40 || charPL > 100){
            printf("Not a valid choice.\n");
        }
    }while(charPL < 40 || charPL > 100);
    
    //Calls each void function created
    readFile(charPL);
    printListTest(charPL);
    printList(charPL);
    return 0;
}

//This is the method that reads the text file into a linked l
void readFile(int charPL)
{
    char *String;
    char fileName[20];
    FILE *filePtr = NULL;
    String = malloc(30*sizeof(char));
    
    //prompts the user to enter the name of the file they wish to use.
    printf("Enter the name of the file containing the text you wish to justify.\n");
    scanf("%s", fileName);
    
    // If file is null/empty print "cannot  be opened"
    if((filePtr = fopen(fileName, "r")) == NULL){
        printf("File cannot be opened.\n");
    }
    else{
        filePtr = fopen(fileName, "r");
        fscanf(filePtr, "%s", String);
        list = malloc(sizeof(struct node));
        
        //stores words
        list->data = String;
        
        end = list;
        
        while(!feof(filePtr))
        {
            String = malloc(30*sizeof(char));
            fscanf(filePtr, "%s", String);
            end->nextPtr = malloc(sizeof(struct node));
            end = end->nextPtr;
            end->data = String;
        }
        fclose(filePtr);
    }
}

//function that prints the justified text
void printList(int charPL)
{
    printf("\n");
    end = list;
    listPtr = list;
    start = list;
    currPtr = start;
    
    //Until the end of the list is reached, keeps looping
    while(start->nextPtr != NULL){
        
        int avSpace[100] = {};
        int wSpace = 0;/*This variable keeps track of the spaces within a line*/
        int charLine = 0;
        int extraSpace = 0;/*This variable is used to determine leftover space so that it can be filled with spaces*/
        int counter = 0;
        int lastLine = 0;
        int j = 0;
        int i = 0;
        
        //gets the total number of characters for the word
        charLine = strlen(end->data)+1;
        counter = 1;
        end = end->nextPtr;
        
        //Counts the total amount of words that can fit per line without
        //going above the desired amount of characters
        while(charLine+strlen(end->data)+1 < charPL && lastLine == 0){
            counter = counter + 1;
            charLine = charLine + strlen(end->data) + 1;
            
            //Goes through the entire list
            if(end->nextPtr != NULL)
                end = end->nextPtr;
            else
            {
                lastLine = 1;
            }
        }
        
        //Determines the amount of extra space per line
        extraSpace = charPL - (charLine-1);
        
        //Helps to justify the last line correctly
        if(lastLine == 1){
            extraSpace = extraSpace - extraSpace + 2;
        }
        
        //allocates spaces to use on each line
        while(extraSpace > 0){
            if(wSpace < (counter - 1)){
                avSpace[wSpace] = avSpace[wSpace] + 1;
                wSpace = wSpace + 1;
                extraSpace = extraSpace - 1;
            }
            else
                wSpace = 0;
        }
        
        //This loop prints the words for the line it is on with the proper spacing
        for( i = 1; i <= counter; i++){
            if(i <= counter){
                printf("%s ", listPtr->data);
                for(j = 1; j <= avSpace[i-1]; j++){
                    printf(" ");
                }
            }
            else if(i =counter)
            {
                printf("%s\n", listPtr->data);
            }
            
            //goes through the list until the end of it is reached
            if(listPtr->nextPtr != NULL)
                listPtr = listPtr->nextPtr;
        }
        //assigns end to listPtr as it iterates through the list
        if(listPtr->nextPtr != NULL)
            end = listPtr;
        
        //determins the end of the list
        if(end->nextPtr == NULL){
            start = end;
        }
        printf("\n");
    }
}

//This function prints the linked list before the text is justified
void printListTest(charPL)
{
    //first word in list
    currPtr = list;
    
    //if nothing is in the list print that it is empty 
    if(list->nextPtr == NULL)
        printf("List is empty.\n\n");
    else{
        printf("The list is:\n\n");
        
        //Iterates through the list and prints it. 
        while(currPtr != NULL){
            printf("%s ", currPtr->data);
            currPtr = currPtr->nextPtr;
        }
    }
    
    //makes format clearer/easier to view output 
    printf("\n\n");
}
