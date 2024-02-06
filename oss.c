#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>

// This is the help program that shows when the user ask for the -h command
void print_usage(const char *progName) {
    printf("Usage for %s: -n <n_value> -s <s_value> -t <t_value>\n" , progName);
    printf("Options:\n");
    printf("-n: stands for the total number of users to launch\n");
    printf("-s: Defines how many users are allowed to run simultaneously\n");
    printf("-t: The number that passes to the User Process");
}


int main(int argc, char** argv) {
    // This is the params for the getopt
    const char optstr[] = "hn:s:t:";
    char opt;

    // This is the actual variable for the arguments to use later on
    int arg_n = 0;
    int arg_s = 0;
    int arg_t = 0;

    // Get your arguments with getopt, save them to their respective variables, they will be used to check if all required variables are filled later
    while ( ( opt = getopt(argc , argv,  optstr) ) != -1) {

        switch (opt) {
            case 'h':
                print_usage (argv[0]);
                return (EXIT_SUCCESS);
            case 'n':
                arg_n = atoi(optarg);
                printf("n command is working: %d\n" , arg_n);
                break;
            case 's':
                arg_s = atoi(optarg);
                printf("s command is working: %d\n" , arg_s);
                break;
            case 't':
                arg_t = atoi(optarg);
                printf("t command is working: %d\n" , arg_t);
                break;
            case '?':
                print_usage(argv[0]);
                break;
            default: /* '?' */
                printf("Invalid option %c\n" , optopt);
                print_usage(argv[0]);
                return(EXIT_FAILURE);
        }

    }

    if (arg_n <= 0 || arg_s <= 0 || arg_t <= 0) {
        printf("All arguments are required\n");
        print_usage(argv[0]);

        return 1;
    }

    for (int i = 0; i < arg_n; i++) {
        if (arg_s > 0 && i % arg_s == 0) { // If the number of processes is equal to the number of active ppid
            // Wait to launch the next user
            int status;
            pid_t cPid = waitpid(-1 &status, 0);
            if (cPid == -1) {
                perror("Error in waitpid");
                return(EXIT_FAILURE);
            }
            printf("Child with PID:%d exited successfully\n" , cPid);
        }
        pid_t pid = fork();

        if (pid == -1) {
            perror("Error in forking user process");
            return(EXIT_FAILURE);
        }

        if (pid == 0) {
            // User process launch
            execl("./user" , "user" , "-t" , arg_t, 0);
            perror("Error in execl");
            return(EXIT_FAILURE);
        }
        // Wait for the remaining child processes to finish
        int status;
        for (int i = 0; i < arg_n % arg_s; ++i) {
            pid_t cPid = waitpid(-1, &status, 0);
            if (cPid == -1) {
                perror("error in waitpid");
                return(EXIT_FAILURE);
            }
        }
        printf("Child with PID:%d exited successfully\n");
    }

    return EXIT_SUCCESS;
}

