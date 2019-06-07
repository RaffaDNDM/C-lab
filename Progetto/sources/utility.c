/**
  @file utility.c
  @author Di Nardo Di Maio Raffaele 1114463
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"

void verify_pointer(void* pointer,control_alloc c,char *file_name)
{
  if(pointer==NULL)
  {
    printf(LINE);
    printf("problems with ");
    switch(c)
    {
      case(FILE_IN):
        printf("the opening of the file %s\n",file_name);
        break;

      case(ALLOC):
        printf("the allocation of memory\n");
        break;
    }
    exit(EXIT_FAILURE);
  }
}

void verify_format(int num_input,int control,char *file_name)
{
  if(num_input!=control)
  {
    printf(LINE);
    printf("problems with the input format of %s\n",file_name);
    exit(EXIT_FAILURE);
  }
}

void exit_output(void)
{
  printf(LINE);
  printf("Thanks for the use of this app\n");
  printf(LINE);
}
