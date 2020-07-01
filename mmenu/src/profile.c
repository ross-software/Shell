#include<stdio.h>
#include<unistd.h>


//A command, and what it's shown as
typedef struct{
	char* name;
	char* cmd;


} command;


int main(int argc, char* argv[]){
	char* arr[argc];
	for(int i=1; i<argc; i++){
		arr[i-1]=argv[i];
	}
	arr[argc-1]=NULL;

	execvp (arr[0], arr);

	return 0;


}
