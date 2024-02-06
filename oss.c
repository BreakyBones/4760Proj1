#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>

void print_usage(const char *progName) {
    printf("Usage for %s: -n <n_value> -s <s_value> -t <t_value>\n" , progName);
    printf("Options:\n");
    printf("-n: stands for the total number of users to launch\n");
    printf("-s: Defines how many users are allowed to run simultaneously\n");
    printf("-t: The number that passes to the User Process");
}


int main(int argc, char** argv) {
const char optstr[] = "hn:s:t:";
char opt;
int arg_n = 0;
int arg_s = 0;
int arg_t = 0;

    while ( ( opt = getopt(argc , argv,  optstr) ) != -1) {

        switch (opt) {
            case 'h':
                print_usage (argv[0]);
                return (EXIT_SUCCESS);
            case 'n':
                arg_n = atoi(optarg);
                printf("n command is working\n");
                break;
            case 's':
                arg_s = atoi(optarg);
                printf("s command is working\n");
                break;
            case 't':
                arg_s = atoi(optarg);
                printf("t command is working\n");
                break;
        }

    }



    return EXIT_SUCCESS;
}

