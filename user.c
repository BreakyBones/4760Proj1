#include<unistd.h>
#include<sys/types.h>

#include<stdio.h>
#include<stdlib.h>

int main(int argc, char** argv) {

    // Iterator comes in as a char so convert it to a int with atoi
    int iter = atoi(argv[1]);

    // Iteration loop until iter is achieved
    for (int i = 0; i <= iter; ++i) {
        printf("USER PID:%d PPID:%d Iteration:%d before sleeping\n" , getpid(), getppid(), i);
        sleep(1);
        printf("USER PID:%d PPID:%d Iteration:%d after sleeping\n" , getpid(), getppid(), i);
    }

    return (EXIT_SUCCESS);
}
