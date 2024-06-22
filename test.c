#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>

void init_shell();
void handle_signal(int signo);
void parse_command(char *cmd);
void execute_command(char **args);
void handle_redirection(char **args);
void handle_pipes(char **args);

int main() {
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    init_shell();

    while (1) {
        printf("minishell :");
        nread = getline(&line, &len, stdin);
        if (nread == -1) break;

        line[nread - 1] = '\0';

        parse_command(line);
    }

    free(line);
    return 0;
}

void init_shell() {
    signal(SIGINT, handle_signal);
    signal(SIGQUIT, handle_signal);
}

void handle_signal(int signo) {
    if (signo == SIGINT) {
        printf("\nminishell: received SIGINT\n");
    } else if (signo == SIGQUIT) {
        printf("\nminishell: received SIGQUIT\n");
    }
}

void parse_command(char *cmd) {
    char *args[100];
    int i = 0;
    args[i] = strtok(cmd, " ");
    while (args[i] != NULL) {
        i++;
        args[i] = strtok(NULL, " ");
    }

    execute_command(args);
}

void execute_command(char **args) {
    pid_t pid = fork();
    if (pid == 0) {
        handle_redirection(args);
        handle_pipes(args);
        execvp(args[0], args);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        wait(NULL);
    } else {
        perror("fork");
    }
}

void handle_redirection(char **args) {
}
void handle_pipes(char **args) {
}
