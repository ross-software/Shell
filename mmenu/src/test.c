#include "wheel.h"
#define max_wheel 50

int test1_infintewheel(){
  wheel test; create_wheel(&test, "test");
  setcmd_wheel(&test, "notify-send '0 index'", 0);
  setcmd_wheel(&test, "notify-send '1 index'",1);
  setcmd_wheel(&test, "notify-send '2 index'",2);
  setcmd_wheel(&test, "notify-send '3 index'",3);

  setcmd_wheel(&test, "notify-send '4 index'",4);
  setcmd_wheel(&test, "notify-send '5 index'",5);
  setcmd_wheel(&test, "notify-send '6 index'",6);
  /* setcmd_wheel(&test, "notify-send '7 index'",7); */

  connect_wheel(&test, &test, 1);
  connect_wheel(&test.entry_wheel[1], &test, 1);
  test.entry_wheel[1].name="NICE";
  printf("%s\n", test.entry_wheel[1].name);
  printf("%s\n", test.name);


  int status=exec_index(&test, 1); 
  for(int i=0; i<max_wheel && status ; i++){
	printf("go to new wheel\n");
	status=exec_index(&test, 1); 
  }
  if(status)
	printf("Max wheel exit\n");
  else
	printf("Regular exit\n");

  return 0;
}

int test2_reg(){
  wheel test1; create_wheel(&test1, "test1");
  wheel test2; create_wheel(&test2, "test2");
  setcmd_wheel(&test1, "notify-send '0 index of test1 wheel'", 0);
  setcmd_wheel(&test1, "notify-send '1 index of test1 wheel'",1);
  setcmd_wheel(&test1, "notify-send '2 index of test1 wheel'",2);
  setcmd_wheel(&test1, "notify-send '3 index of test1 wheel'",3);
  setcmd_wheel(&test1, "notify-send '4 index of test1 wheel'",4);
  setcmd_wheel(&test1, "notify-send '5 index of test1 wheel'",5);
  setcmd_wheel(&test1, "notify-send '6 index of test1 wheel'",6);

  setcmd_wheel(&test2, "notify-send '0 index of test2 wheel'", 0);
  setcmd_wheel(&test2, "notify-send '1 index of test2 wheel'",1);
  setcmd_wheel(&test2, "notify-send '2 index of test2 wheel'",2);
  setcmd_wheel(&test2, "notify-send '3 index of test2 wheel'",3);
  setcmd_wheel(&test2, "notify-send '4 index of test2 wheel'",4);
  setcmd_wheel(&test2, "notify-send '5 index of test2 wheel'",5);
  setcmd_wheel(&test2, "notify-send '6 index of test2 wheel'",6);
  setcmd_wheel(&test2, "notify-send '7 index of test2 wheel'",7);

  connect_wheel(&test1, &test2, 7);

  int status=exec_index(&test1, 7);
  while(status){
	status=exec_index(&test1, 7);
  }

}

int main(){
  test2_reg();
  test1_infintewheel();
  return 0;
}
