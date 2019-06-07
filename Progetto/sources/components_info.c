/**
  @file components_info.c
  @author Di Nardo Di Maio Raffaele 1114463
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "component.h"
#include "components_info.h"
#include "utility.h"

struct component *comps_info(char *file_name,int* size_array,float *low_price,float *mid_price,float *high_price)
{
  static int check_init=0;

  if(check_init>0)
    return NULL;

  FILE *f=NULL;

  f=fopen(file_name,"r");
  verify_pointer(f,FILE_IN,file_name);

  struct component* all_components=malloc(sizeof(struct component));
  verify_pointer(all_components,ALLOC,NULL);

  int size=0;

  //reads the prices of components
  char* control;
  char s[80];
  control=fgets(s,80,f);

  int n;
  n=sscanf(s,"%f %f %f",low_price,mid_price,high_price);
  verify_format(n,3,file_name);

  int check=1;
  while(check)
  {
    control=fgets(s,80,f);

    if(control!=NULL)
    {
      unsigned int id;
      char name[20];
      unsigned int months;

      //reads informations about compomemt
      int n=sscanf(s,"%d %s %d",&id,name,&months);
      verify_format(n,3,file_name);

      if(size>=1)
      {
        all_components=realloc(all_components,sizeof(struct component)*(size+1));
        verify_pointer(all_components,ALLOC,NULL);
      }

      int length=strlen(name);
      all_components[size].name=malloc(sizeof(char)*(length+1));
      verify_pointer(all_components[size].name,ALLOC,NULL);

      //creates the compoent
      all_components[size].comp_id=id;
      strcpy(all_components[size].name,name);
      all_components[size].months=months;
      size++;
    }
    else
      check=0;
  }

  fclose(f);

  *size_array=size;
  check_init++;

  return all_components;
}

struct component* search_info(struct component *c,int comp_id,char *comp_name,int n)
{
  int i=0;
  while(i<n)
  {
    if(comp_id==c[i].comp_id)
      return &(c[i]);
    i++;
  }

  printf("the component \"%s\" was not found",comp_name);
}

void dealloc_comps_info(struct component *c,int n_comps)
{
  int i=0;

  for(;i<n_comps;i++)
  {
    free(c[i].name);
  }

  free(c);
}
