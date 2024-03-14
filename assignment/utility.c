#include "myshell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //

extern char **environ;

void clear() {
    system("clear");
}

void changeDirectory(const char *path) {
    char cwd[MAX_BUFFER];
    if (path == NULL || strcmp(path, "") == 0) {
        // Optional: Change to the home directory if no path is given
        // path = getenv("HOME");
        // if (chdir(path) != 0) perror("chdir() to HOME failed");
        
        // Or simply print the current working directory
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s\n", cwd);
        } else {
            perror("getcwd() error");
        }
    } else {
        if (chdir(path) == 0) {
            // Successfully changed directory
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                printf("Changed directory to %s\n", cwd);
                setenv("PWD", cwd, 1); // update PWD environment variable
            } else {
                perror("getcwd() error");
            }
        } else {
            perror("chdir() error");
        }
    }
}

void printEnvironmentVariables() {
    for (char **env = environ; *env; ++env) {
        printf("%s\n", *env); // Print each environment string
    }
}

void listDirectory(const char *directory) {
    char command[MAX_BUFFER];
    strcpy(command, "ls -al ");
    if (directory) {
        strcat(command, directory); // Append the directory to the command
    } else {
        strcat(command, "."); // Default to current directory
    }
    system(command); // Execute the command
}

void pauseShell() {
    printf("Press 'Enter' to continue...");
    while (getchar() != '\n'); // Wait for 'Enter'
}

void echoCommand(char *args[], int argCount) {
    for (int i = 1; i < argCount; i++) { // Start from 1 to skip the command name
        printf("%s", args[i]);
        if (i < argCount - 1) {
            printf(" "); // Print a space between words
        }
    }
    printf("\n"); // Newline at the end
}

void echoCommand(char *args[], int argCount) {
    for (int i = 1; i < argCount; i++) { // Start from 1 to skip the command name
        printf("%s", args[i]);
        if (i < argCount - 1) {
            printf(" "); // Print a space between words
        }
    }
    printf("\n"); // Newline at the end
}

void quitShell() {
    exit(0); // Exit program with a zero return value
}
