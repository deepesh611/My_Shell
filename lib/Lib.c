// Include the necessary header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>                 // For getcwd
#include <sys/types.h>              // For stat
#include <sys/stat.h>               // For stat
#include <dirent.h>                 // For opendir, readdir
#include <fcntl.h>                  // For open, O_RDONLY, O_WRONLY, O_CREAT
#include <errno.h>                  // For errno

// Define the constants
#define MAX_COMMAND_LENGTH 1024
#define MAX_FILENAME_LENGTH 256
#define BUFFER_SIZE 1024

// Define the root directory
const char *root = "<ROOT_PATH>";


// Function to display current working directory
void display_pwd() {
    char cwd[MAX_FILENAME_LENGTH];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } 
    
    else {
        perror("\033[31mgetcwd() error\033[0m");
    }
}


// Function to move/rename a file
void move_file(const char *source, const char *destination) {
    if (rename(source, destination) == -1) {
        perror("\033[31mrename() error\033[0m");
    } 
    
    else {
        printf("File '%s' moved to '%s'\n", source, destination);
    }
}


// Function to display the shell prompt
void display_prompt() {
    char cwd[MAX_FILENAME_LENGTH];
    
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        char *username = "NerdyGamer611"; // Change this to get the actual username
        const char *hostname = "Desktop"; // Change this to get the actual hostname
        
        // Check if the current directory is within the root directory
        if (strncmp(cwd, root, strlen(root)) == 0) {
            // Replace the root directory with "~" in the current directory path
            printf("\033[1m\033[32m%s@%s:\033[36m~%s> \033[0m", username, hostname, cwd + strlen(root));
        } 
        
        else {
            printf("\033[32m%s@%s:\033[36m~%s> \033[0m", username, hostname, cwd);
        }
    } 
    
    else {
        perror("\033[31mgetcwd() error\033[0m");
    }
}


// Function to search for a string in a file
void search_in_file(const char *search_string, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("\033[31mfopen() error\033[0m");
        return;
    }

    char line[MAX_COMMAND_LENGTH];
    int line_number = 1;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, search_string) != NULL) {
            printf("Match found in line %d: %s", line_number, line);
        }
        line_number++;
    }

    fclose(file);
}


// Function to split a file into chunks
void split_file(const char *filename, int num_chunks) {
    FILE *input_file = fopen(filename, "rb");
    if (input_file == NULL) {
        perror("\033[31mError opening input file\033[0m");
        return;
    }

    fseek(input_file, 0, SEEK_END); // Move file pointer to the end
    long file_size = ftell(input_file); // Get the size of the file
    rewind(input_file); // Reset file pointer to the beginning

    long chunk_size = file_size / num_chunks; // Calculate chunk size
    char output_filename[256];

    for (int i = 0; i < num_chunks; i++) {
        sprintf(output_filename, "%s.part%d", filename, i + 1);
        FILE *output_file = fopen(output_filename, "wb");
        if (output_file == NULL) {
            perror("\033[31mError opening output file\033[0m");
            fclose(input_file);
            return;
        }

        char buffer[BUFFER_SIZE];
        long bytes_written = 0;
        size_t bytes_to_write;

        while (bytes_written < chunk_size && (bytes_to_write = fread(buffer, 1, sizeof(buffer), input_file)) > 0) {
            size_t bytes_written_now = fwrite(buffer, 1, bytes_to_write, output_file);
            if (bytes_written_now != bytes_to_write) {
                perror("\033[31mError writing to output file\033[0m");
                fclose(input_file);
                fclose(output_file);
                return;
            }
            bytes_written += bytes_written_now;
        }

        fclose(output_file);
    }

    fclose(input_file);
    printf("\033[32mFile '%s' split into %d chunks successfully\n\033[0m", filename, num_chunks);
}


// Function to display the available commands
void display_commands(){
    printf("\n\t\t\tAvailable commands:\n");
    printf("------------------------------------------------------------------------\n");
    printf("pwd                             -   Display current working directory\n");
    printf("mv <source> <destination>       -   Move/rename a file\n");
    printf("grep <search_string> <filename> -   Search for a string in a file\n");
    printf("split <filename> <num_chunks>   -   Split a file into chunks\n");
    printf("exit                            -   Exit my_shell\n");
    printf("------------------------------------------------------------------------\n");
}



