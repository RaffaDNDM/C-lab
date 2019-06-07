/**
  @file boards.c
  @author Di Nardo Di Maio Raffaele 1114463
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "component.h"
#include "components_info.h"
#include "boards.h"
#include "utility.h"

/**
  @details returns the cost of a board
  @param num_comps number of components for the creation of the board
  @param low cost of 1-10 components
  @param mid cost of 11-50 components
  @param high cost of 50+ components
*/
float cost(int num_comps,float low, float mid,float high);

/**
  @details creates the informations about a board
  @param file_name name of the file with informations of the board
  @param board pointer pointer to the board you want to create
  @param comps_info array of components informations
  @param n_info size of array of comps_info
  @param low cost of 1-10 components
  @param mid cost of 11-50 components
  @param high cost of 50+ components
*/
void create_board(char *file_name,struct board *board,struct component *comps_info,int n_info,float low,float mid,float high);

struct board *boards_info(char *file_name,int *n_boards,char *path_name,struct component *comps,int n_info
                        ,float low_price,float mid_price, float high_price)
{
  static int check_init=0;

  //boards_info can be called only once
  if(check_init>0)
    return NULL;

  int size=0;
  int n_comps;

  FILE *f;
  f=fopen(file_name,"r");
  verify_pointer(f,FILE_IN,file_name);

  char **s=malloc(sizeof(char *));
  verify_pointer(s,ALLOC,NULL);

  char temp[20];
  char path_complete[80];
  char *control;
  int check=1;

  //reads the names of boards files and saves them in s
  while(check)
  {
    strcpy(path_complete,path_name);
    control=fgets(temp,20,f);

    if(control!=NULL)
    {
      if(size>=1)
      {
        s=realloc(s,sizeof(char *)*(size+1));
        verify_pointer(s,ALLOC,NULL);
      }

      int length=strlen(temp);
      strncat(path_complete,temp,length-1);

      s[size]=malloc(sizeof(char)*(strlen(path_complete)+1));
      verify_pointer(s[size],ALLOC,NULL);

      strcpy(s[size],path_complete);
      size++;
    }
    else
    {
      check=0;
    }
  }

  fclose(f);

  //creates the array of boards
  struct board *set_of_boards=malloc(sizeof(struct board)*size);
  verify_pointer(set_of_boards,ALLOC,NULL);

  int i=0;
  for(;i<size;i++)
  {
    create_board(s[i],&set_of_boards[i],comps,n_info,low_price,mid_price,high_price);
  }

  //free of the array of strings
  i=0;
  for(;i<size;i++)
  {
    free(s[i]);
  }
  free(s);

  *n_boards=size;//number of possible boards
  check_init++;

  return set_of_boards;
}


void create_board(char *file_name,struct board *board,struct component *comps_info,int n_info,float low,float mid,float high)
{
  int max_months=0;//max number of months you need to wait for the creation of the board
  int num_comps=0;//number of different types of components

  FILE *f;
  f=fopen(file_name,"r");
  verify_pointer(f,FILE_IN,file_name);

  char *control;
  char s[80];
  control=fgets(s,80,f);

  int id_board;//id of the board
  char board_name[20];//name of the board
  float profit;//profit of the board

  int n=sscanf(s,"%d %s %f",&id_board,board_name,&profit);
  verify_format(n,3,file_name);

  int length=strlen(board_name);

  struct component_need *comps=malloc(sizeof(struct component_need));
  verify_pointer(comps,ALLOC,NULL);

  int size=0;
  int check=1;

  while(check)
  {
    control=fgets(s,80,f);

    if(control!=NULL)
    {
      int id,quantity;
      char name_comp[20];

      n=sscanf(s,"%d %s %d",&id,name_comp,&quantity);
      verify_format(n,3,file_name);

      num_comps+=quantity;

      //searchs the component inside the array of components informations
      struct component *c=search_info(comps_info,id,name_comp,n_info);

      if((c->months) > (max_months))
        max_months=c->months;

      if(size>=1)
      {
        comps=realloc(comps,sizeof(struct board)*(size+1));
        verify_pointer(comps,ALLOC,NULL);
      }

      comps[size].pointer_to_comp=c;
      comps[size].quantity=quantity;

      size++;
    }
    else
    {
      check=0;
    }
  }

  fclose(f);

  board->board_name=malloc(sizeof(char)*(length+1));
  board->id_board=id_board;
  strcpy(board->board_name,board_name);
  board->tot_time=max_months+1; //wait + creation of board(1 month)
  board->num_comps=size;
  board->cost_board=cost(num_comps,low,mid,high);//cost of this board
  board->profit=profit;
  board->comps=comps;
}

float cost(int num_comps,float low, float mid,float high)
{
  if(num_comps>0 && num_comps<11)
    return low;
  else if(num_comps>50)
    return high;
  else
    return mid;
}

struct board *search_board(struct board* b,char *board_name, int n_boards)
{
  int i=0;

  //looks for the board with name board_name inside the array of boards b
  while(i<n_boards)
  {
    if(!strcmp(board_name,b[i].board_name))
      return &(b[i]);

    i++;
  }

  printf("the component \"%s\" was not found",board_name);

  return NULL;
}

void dealloc_boards_info(struct board *b,int n_boards)
{
  int i=0;

  for(;i<n_boards;i++)
  {
    free(b[i].board_name);
    free(b[i].comps);
  }

  free(b);
}
