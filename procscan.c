#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
//searches for process with name in argument 1
//if process is running write a 1 to target file in argument 2
//else write a 0 to target file in argument 2
//
//TODO: use /tmp for everything

char* concat_at_home(char* destination, char* source){
	//the string concatenation we have at home
	int destination_length = strlen(destination)*sizeof(char);
	int source_length = strlen(source)*sizeof(char);
	char* concatenated_string = malloc((source_length + destination_length) * sizeof(char));
	strcpy(concatenated_string, destination);
	strcpy(concatenated_string + destination_length, source);
	return concatenated_string;	
}





int main(int argc, char* argv[]){
	if(argc != 3){
		printf("error, requires 2 arguments (process_name file_path_to_update)\n");
		return 1;
	}	
			
	char* mundane_command = "ps -c | grep ";
	char* mundane_file_write = "echo \"X\" > ";	
	char* ready_command = concat_at_home(mundane_command, argv[1]);
	char* ready_file_write = concat_at_home(mundane_file_write, argv[2]);
	
	int process_is_running = 0;
	int previous_status = 0;
	
	while(1){
		process_is_running = 0 == system((const char*)(ready_command));
		//turn boolean into character (thank you ascii)
		if(process_is_running != previous_status){
			ready_file_write[6] = process_is_running + 48;
			system(ready_file_write);
		}
		previous_status = process_is_running;
		usleep(500000);
	}
	return 0;
}
