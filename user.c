#include<unistd.h>
#include<sys/types.h>

#include<stdio.h>
#include<stdlib.h>

int main(int argc, char** argv) {

    int iter = atoi(argv[1]);

    pid_t cPid = getpid();
    pid_t pPid = getppid();

    for (int i = 0; i <= iter; ++i) {
        printf("USER PID:%d PPID:%d Iteration:%d before sleeping\n" , cPid, pPid, i);
        sleep(1);
        printf("USER PID:%d PPID:%d Iteration:%d after sleeping\n" , cPid, pPid, i);
    }

    return (EXIT_SUCCESS);
}
