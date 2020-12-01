#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

static void sighandler(int signo) {
    if (signo == SIGINT) {
        int toWrite = open("error", O_CREAT | O_WRONLY, 0664);
        if (toWrite == -1) {
            printf("errno: %d - error: %s\n", errno, strerror(errno));
        }
        char text[100] = "main.c exited due to SIGINT\n";
        int checkWrite = write(toWrite, text, sizeof(text));
        close(toWrite);
        exit(0);
    }
    else if (signo == SIGUSR1) {
        printf("Parent ID: %d\n", getppid());
    }
}

int main() {
    signal(SIGUSR1, sighandler);
    signal(SIGINT, sighandler);
    while (1) {
        printf("Process #%d\n", getpid());
        sleep(1);
    }
}
