#include <stdio.h>
#include <stdlib.h>
#include "./lib/Lib.c"
#define MAX_COMMAND_LENGTH 1024


// Main function
int main() {
    char command[MAX_COMMAND_LENGTH];
    char arg1[MAX_COMMAND_LENGTH], arg2[MAX_COMMAND_LENGTH];
    
    while (1) {
        // printf("NerdyGamer611@Desktop:~/> ");
        display_prompt();
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0; // Remove newline character

        if (strcmp(command, "pwd") == 0) {
            display_pwd();
        } 
        
        else if (strcmp(command, "exit") == 0) {
            printf("\033[35m\nExiting my_shell...\n\033[0m");
            sleep(2);
            break;
        } 
        
        else if (strcmp(command, "help") == 0) {
            display_commands();
        } 
        
        else if (sscanf(command, "mv %s %s", arg1, arg2) == 2) {
            move_file(arg1, arg2);
        } 
        
        else if (strncmp(command, "grep ", 5) == 0) {
            sscanf(command, "grep %s %s", arg1, arg2);
            search_in_file(arg1, arg2);
        } 
        
        else if (strncmp(command, "split ", 6) == 0) {
            sscanf(command, "split %s %s", arg1, arg2);
            int num_chunks = atoi(arg2);
            if (num_chunks <= 0) {
                printf("\033[31mError: Number of chunks must be a positive integer.\n\033[0m");
            } 
            
            else {
                split_file(arg1, num_chunks);
            }
        } 
        
        else {
            printf("\033[31mError: Unrecognized command:\033[0m '%s'\n", command);
        }
    }

    return EXIT_SUCCESS;
}


