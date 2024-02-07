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

    // Check if all argument were provided for use
    if (arg_n <= 0 || arg_s <= 0 || arg_t <= 0) {
        printf("All arguments are required\n");
        print_usage(argv[0]);

        return 1;
    }
    // Keep the iterator low to prevent confusion and time lag on OpSyS server
    if (atoi(arg_t) > 50) {
        printf("Please keep your iterator between 0 and 50 to reduce time strain");

        return (EXIT_FAILURE);
    }
    // Keep the number of simultaneous processes low to reduce lag on OpSys server
    if (arg_s > 20) {
        printf("Please keep the simultaneous number of processes below 20");
    }

    // Keeps track of all active Users
    int activeUser = 0;

    // Launch User Processes
    for (int i = 1; i <= arg_n; i++) {
        // Having a while loop keeps extra users from activating if greater than the limi
        while (activeUser > arg_s) {
            wait(0);
            activeUser--;
        }

        // fork the users when not full
        pid_t childPid  = fork();

        if (childPid == 0) {
            // An Array of Char to save space in the execvp command
            char* args[] = {"./user" , arg_t , 0};
            execvp(args[0] , args); // Begins the process
        } // Parent continues from here
        else {
            // increment active amount of Users
            activeUser++;
        }
    }
    // Wait till all users have finished
    while (activeUser > 0) {
        wait(0);
        activeUser--;
    }

    return EXIT_SUCCESS;
}




