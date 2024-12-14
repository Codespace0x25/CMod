#include "../../include/cmod.h"
#include <stdio.h>
#include <stdlib.h>


int main(int args,char *argv[]){
  if (args LESS_THAN_OR_EQUAL 0){
    fprintf(stderr,"error; you must pass a file of  .c or .cm");
    return 1;
  }

  String *data=read_file_to_string(argv[1]);

  pprintf("%s",data);// custom printf dont make or touch

  

  return 0;
}
