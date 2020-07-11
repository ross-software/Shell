#include "wheel.h"

void
create_wheel(wheel* cur_wheel, char* name)
{
	 cur_wheel->name=name;
	 for (int i=0; i<wheel_size; i++){
		  cur_wheel->type[i]=-1;
	 }
	 cur_wheel->entry_wheel=malloc(wheel_size*sizeof(wheel));
}

void
connect_wheel(wheel* parent_wheel, wheel* child_wheel, int index)
{
	 assert(index<wheel_size && index>=0);
	 parent_wheel->entry_wheel[index]=*child_wheel;
	 parent_wheel->type[index]=1;
}

void
setcmd_wheel(wheel* cur_wheel, char* cmd, int index)
{
	 assert(index<wheel_size && index>=0);
	 cur_wheel->command[index]=cmd;
	 cur_wheel->type[index]=0;
}



//entrys are just for executing a wheel
entry
_extract_command(wheel* current_wheel, int index)
{
	 assert(index<wheel_size && index>=0);
	 entry retme;
	 switch( current_wheel->type[index]){
	 case -1: //No valid value is at index
		  fprintf(stderr, "No value at %d for %s\n", index, current_wheel->name);
		  exit(1);
		  break;
	 case 0: // A command is at index
		  retme.entry.cmd=current_wheel->command[index];
		  retme.type=0;
		  return retme;
	 case 1: // A wheel is at indexcmd
		  retme.entry.wheel=current_wheel->entry_wheel[index];
		  retme.entry.cmd=retme.entry.wheel.name;
		  retme.type=1;
		  return retme;

	 }

}


// Execute the entry
// If the entry is a wheel, return 0 and change wheel to entry.
// Else if entry is a commadn, return 1, execute command, and exit program.
int
_execute_entry(entry select_entry, wheel* current_wheel)
{
	 if(select_entry.type==0){
		  system(select_entry.entry.cmd);
		  return 1;
	 } else{
		  current_wheel->name=select_entry.entry.wheel.name;
		  for(int i=0; i<wheel_size; i++){
			   current_wheel->command[i]=select_entry.entry.wheel.command[i];
			   current_wheel->type[i]=select_entry.entry.wheel.type[i];
			   current_wheel->entry_wheel[i]=select_entry.entry.wheel.entry_wheel[i];
		  }
		  return 0;
	 }
}


// Main executing function.
int
exec_index(wheel* current_wheel, int index)
{
	 /* Reason for splitting the extract command and execute entry into two different places
		is just in case we need to use one of the functions.
		If not than they can be folded. */
	 entry run= _extract_command(current_wheel, index);
	 _execute_entry(run, current_wheel);
	 return run.type;
	 

}
