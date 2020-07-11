/* Wheel is the data strucutre represtning a list of choices. 
 It's programed to be a tree, wtih it's leaves being commands,
and everything else being a wheel

This means that the user keeps tranversing the tree,
until they either stop the program, or they launch a command. */

#ifndef WHEEL_H
#define WHEEL_H

/* Header */
#include<assert.h>
#include<stdlib.h>
#include<stdio.h>
/*Needed for error message.
  TODO investiage if includgion stdio.h will cause errors in future*/

/*  Macro */
#define wheel_size 8

/*  Structs */
typedef struct  Wheel{
	 char* name;
	 char* command[wheel_size];
	 /* Type is what is the tyep of command at index.
	 -1 means invalid (aka there's no command/wheel at the index)
	 0 means a command is at the idnex
	 1 means there's a wheel at index */
	 int8_t type[wheel_size];
	 struct Wheel* entry_wheel;

	 /* Conditionals for wheels go here, but aren't implented yet. they are
	 Hide windows: windows this wheel will not appear in
	 Only windows: windows this wheel will only appear for 
	 Modifer: modifer used to invoke wheel. */
}wheel;


/*  Entry_type reprents a value in the wheel, and what can come.  */
typedef union Entry_Type{
	 wheel wheel;
	 char* cmd;
}entry_type;

/*  Entyr in the wheel. 0 is command to be exected, 1 is a wheel. */
typedef struct Entry{
	 entry_type entry;
	 int type;
}entry;

/*  Function */
void create_wheel(wheel* cur_wheel, char* name);
void connect_wheel(wheel* parent_wheel, wheel* child_wheel, int index);
void setcmd_wheel(wheel* cur_wheel, char* cmd, int index);

/*  Used for executing wheels. */
entry _extract_command(wheel* current_wheel, int index);
int _execute_entry(entry select_entry, wheel* current_wheel);
int exec_index(wheel* current_wheel, int index);

/* TODO find a way to set multiple values of wheel at same time.
Maybe use some regex magic? Such as a command with prefix wheel_*
is a wheel */
#endif
