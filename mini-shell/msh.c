#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_HISTORY 15
#define MAX_ARGS 10

char history[MAX_HISTORY][MAX_COMMAND_LENGTH];
pid_t pidhistory[MAX_HISTORY];
int history_count = 0, pid_count = 0;

void add_to_history(const char *command) {
    if (history_count < MAX_HISTORY) {
        strcpy(history[history_count++], command);
    } else {
        for (int i = 1; i < MAX_HISTORY; i++) {
            strcpy(history[i - 1], history[i]);
        }
        strcpy(history[MAX_HISTORY - 1], command);
    }
}

void add_to_pidhistory(pid_t pid) {
    if (pid_count < MAX_HISTORY) {
        pidhistory[pid_count++] = pid;
    } else {
        for (int i = 1; i < MAX_HISTORY; i++) {
            pidhistory[i - 1] = pidhistory[i];
        }
        pidhistory[MAX_HISTORY - 1] = pid;
    }
}

void print_history() {
    for (int i = 0; i < history_count; i++) {
        printf("%d %s\n", i, history[i]);
    }
}

void print_pidhistory() {
    for (int i = 0; i < pid_count; i++) {
        printf("%d\n", pidhistory[i]);
    }
}

int execute_command(char **args) {
    if (strcmp(args[0], "exit") == 0 || strcmp(args[0], "quit") == 0) {
        exit(0);
    }
    if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL || chdir(args[1]) != 0) {
            perror("cd failed");
        }
        return 1;
    }
    if (strcmp(args[0], "history") == 0) {
        print_history();
        return 1;
    }
    if (strcmp(args[0], "pidhistory") == 0) {
        print_pidhistory();
        return 1;
    }
    return 0;
}

void run_shell() {
    char input[MAX_COMMAND_LENGTH];
    char *args[MAX_ARGS + 2];
    while (1) {
        printf("msh> ");
        if (fgets(input, MAX_COMMAND_LENGTH, stdin) == NULL) {
            printf("\n");
            break;
        }
        input[strcspn(input, "\n")] = '\0';
        if (strlen(input) == 0) continue;
        add_to_history(input);
        char *token = strtok(input, " ");
        int arg_count = 0;
        while (token != NULL && arg_count < MAX_ARGS) {
            args[arg_count++] = token;
            token = strtok(NULL, " ");
        }
        args[arg_count] = NULL;
        if (execute_command(args)) continue;
        pid_t pid = fork();
        if (pid == 0) {
            execvp(args[0], args);
            perror("Command not found");
            exit(1);
        } else if (pid > 0) {
            add_to_pidhistory(pid);
            waitpid(pid, NULL, 0);
        } else {
            perror("fork failed");
        }
    }
}

int main() {
    run_shell();
    return 0;
}