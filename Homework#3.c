//
//  Homework#3.c
//  
//
//  Created by Stephanie Caston  on 11/27/15.
//
//

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

main ()
{
    //Variable for choice to be entered by the user
    int choice = 0;
    
    //Variable declaration for child_pid
    pid_t child_pid;
    
    //Prints initial child and parent processes
    printf("Child Process ID: %ld, parent ID: %ld \n",(long)getpid(),(long)getppid());
    
    //loop that does all the work based on the users choice. Exits if user picks number 4.
    while(choice < 4){
        
        //Menu to be displayed in each loop
        printf("Choose the function to be performed by the child.\n");
        printf("\t(1)  Display current date and time.\n");
        printf("\t(2)  Display the calendar of the current month.\n");
        printf("\t(3)  List the files in the current directory.\n");
        printf("\t(4)  Exit from the program.\n");
        printf("Enter your choice: ");
        
        //Takes in the choice from the user
        scanf("%d", &choice);
        printf("\n");
        
        if(choice == 1){
            child_pid=fork(); //creates child process
            if (child_pid<0){
                printf("Failed to fork\n"); exit(-1);
                
            }  // if child process is created, child and parent processes are displayed
            if(child_pid == 0){
                printf("Child process ID: %ld, parent ID: %ld \n",(long)getpid(),(long)getppid());
                system("date"); //System call to date
                printf("\n");
                exit(0);//exits current child process
            }
            else{
                wait(NULL); //Parent process waits until child process is finished
                printf("Current process PID: %ld\n\n",(long)getpid()); //prints parent process
            }
        }
        if(choice == 2){
            child_pid=fork();
            if (child_pid<0){
                printf("Failed to fork\n"); exit(-1);
                
            } //if child process is created, parent and child processes are displayed
            if(child_pid == 0){
                printf("Child process ID: %ld, parent ID: %ld \n",(long)getpid(),(long)getppid());
                system("cal"); //System call to calendar
                printf("\n");
                exit(0);
            }
            else{
                wait(NULL); //Makes parent process wait
                printf("Current process PID: %ld\n\n",(long)getpid());
            }
        }
        if(choice == 3){
            child_pid=fork();
            if (child_pid<0){
                printf("Failed to fork\n"); exit(-1);
                
            } //if child process is created, parent and child processes are displayed
            if(child_pid == 0){
                printf("Child process ID: %ld, parent ID: %ld \n",(long)getpid(),(long)getppid());
                system("ls -l"); //System call to ls-l which displays current files in directory
                printf("\n");
                exit(0);
            }
            else{
                wait(NULL); //makes parent process wait
                printf("Current process PID: %ld\n\n",(long)getpid());
            }
        }
        if(choice == 4){
            printf("Current process PID: %ld\n",(long)getpid()); //prints parent process one more time
            printf("You chose to exit the program.\n\n"); //tells the user they exited the program
            //user has picked number 4 so loop exits 
        }
    } 
}