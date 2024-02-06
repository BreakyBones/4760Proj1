#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>

// This is the help program that shows when the user ask for the -h command
void print_usage(const char *progName) {
    printf("Usage for %s: -n <n_value> -s <s_value> -t <t_value>\n", progName);
    printf("Options:\n");
    printf("-n: stands for the total number of users to launch\n");
    printf("-s: Defines how many users are allowed to run simultaneously\n");
    printf("-t: The number that passes to the User Process");
}


int main(int argc, char **argv) {
    // This is the params for the getopt
    const char optstr[] = "hn:s:t:";
    char opt;
    pid_t cPid;
    // This is the actual variable for the arguments to use later on
    int arg_n = 0;
    int arg_s = 0;
    char *arg_t;

    // Get your arguments with getopt, save them to their respective variables, they will be used to check if all required variables are filled later
    while ((opt = getopt(argc, argv, optstr)) != -1) {

        switch (opt) {
            case 'h':
                print_usage(argv[0]);
                return (EXIT_SUCCESS);
            case 'n':
                arg_n = atoi(optarg);
                break;
            case 's':
                arg_s = atoi(optarg);
                break;
            case 't':
                arg_t = optarg;
                break;
            case '?':
                print_usage(argv[0]);
                break;
            default: /* '?' */
                printf("Invalid option %c\n", optopt);
                print_usage(argv[0]);
                return (EXIT_FAILURE);
        }

    }

    if (arg_n <= 0 || arg_s <= 0 || arg_t <= 0) {
        printf("All arguments are required\n");
        print_usage(argv[0]);

        return 1;
    }

    int activeChild = 0;

    // Launch User Processes
    for (int i; i < arg_n; ++i) {
        if (activeChild >= arg_s) {
            int status;
            pid_t childPid = waitpid(-1, &status, WNOHANG);

            while (childPid > 0) {
                printf("Parent process (oss): Child process with PID %d exited with status %d\n" , childPid , WEXITSTATUS(status));
                activeChild--;

                childPid  = waitpid(-1, &status, WNOHANG);
            }
        }
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("Error in forking user process");
        return (EXIT_FAILURE);
    }



    if (pid == 0) {
        // User process launch
        execl("./user", "user" , arg_t, (char *)NULL);
        perror("Error in execl");
        return (EXIT_FAILURE);
    } else {
        activeChild++;
    }
    // Wait for the remaining child processes to finish
    int status;
    pid_t childPid;
    while ((childPid = waitpid(-1, &status, WNOHANG)) > 0) {
        printf("Parent process (oss): Child process with PID %d exited with status %d\n", childPid , WEXITSTATUS(status));
        activeChild--;
    }

    return EXIT_SUCCESS;
}




