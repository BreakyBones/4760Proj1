Hello! Welcome to 4760 Project 1
To compile the project simply run the make command

To get help run ./oss -h
After compilation to run the program simply run ./oss -n <n-value> -s <s-value> -t <t-value>
Running without any arguments will default to the Help page
Running without ALL arguments needed will inform you to include all arguments and then display the Help

Limitations: there are limitations placed upon the arguments themselves to prevent bloat or error

n: Must be greater than 0
s: Greater than 0 but less than 20, this is to prevent lag on the opsys server
t: Greater than 0 but less than 50, this is to prevent lag on the opsys server

I'd say the greatest trouble I had with this is the one that you know of already...
I put that darn fork() outside my loop.