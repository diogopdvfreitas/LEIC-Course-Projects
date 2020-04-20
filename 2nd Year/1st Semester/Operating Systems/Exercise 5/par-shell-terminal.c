#include <sys/stat.h>
#include <sys/types.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define EXIT_COMMAND  "exit\n"
#define STAT_COMMAND  "stats\n"
#define BUFF_SIZE 100

int main(int argc, char** argv){
   	int par_shell_in;
   	int par_shell_process;
    char *pathname = argv[1];
    char *pathprocess;
    char buffer[BUFF_SIZE];
    char pipename[BUFF_SIZE];

    sprintf(pipename, "/tmp/par-shell-in-%d", getpid());
    pathprocess = pipename;
    
    if((par_shell_in = open(pathname, O_WRONLY)) < 0){
		fprintf(stderr, "Error opening pipe.\n");
		exit(EXIT_FAILURE);
	}

	sprintf(buffer, "<new> %d", getpid());
	if((write(par_shell_in, buffer, BUFF_SIZE)) < 0){
		fprintf(stderr, "Error writing pipe.\n");
		exit(EXIT_FAILURE);
	}
	while(1){
		printf("Insert your command: ");
		fgets(buffer, BUFF_SIZE, stdin);

		if(strcmp(buffer, EXIT_COMMAND) == 0){
			sprintf(buffer, "exit %d %s", getpid(), pathprocess);
			
			if(write(par_shell_in, buffer, BUFF_SIZE) < 0){
				fprintf(stderr, "Error writing pipe.\n");
				exit(EXIT_FAILURE);
			}
			break;
		}
		
		
		if(strcmp(buffer, STAT_COMMAND) == 0){
			if(unlink(pathprocess) < 0){
        		if(errno != ENOENT)
          			fprintf(stderr, "Error unliking pipe\n");
      		}
      		if(mkfifo(pathprocess, 0777) < 0){
        		fprintf(stderr, "Error in mkfifo.\n");
        		exit(EXIT_FAILURE);
      		}


			sprintf(buffer, "stats %s", pathprocess);

			if(write(par_shell_in, buffer, BUFF_SIZE) < 0){
				fprintf(stderr, "Error writing pipe.\n");
				exit(EXIT_FAILURE);
			}

			if((par_shell_process = open(pathprocess, O_RDONLY)) < 0){
				fprintf(stderr, "Error opening pipe2.\n");
				exit(EXIT_FAILURE);
			} 
    		

			if(read(par_shell_process, buffer, BUFF_SIZE) < 0){
   				fprintf(stderr, "Error reading pipe.\n");
   				exit(EXIT_FAILURE);
			}

			else{
				printf("%s\n",buffer);
			}
			if(close(par_shell_process) == -1){
				perror("Error in close()\n");
				exit(EXIT_FAILURE);
			}
			if(unlink(pathprocess) < 0){
				perror("Error in unlink()\n");
				exit(EXIT_FAILURE);
			}
			continue;
			
		}

		if(write(par_shell_in, buffer, BUFF_SIZE) < 0){
			fprintf(stderr, "Error writing pipe.\n");
			exit(EXIT_FAILURE);
		}

	}
	if(close(par_shell_in) == -1){
		perror("Error in close()\n");
		exit(EXIT_FAILURE);
	}
	return 0;

}