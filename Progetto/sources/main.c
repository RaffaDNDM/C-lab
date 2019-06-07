/**
  @file main.c
  @author Di Nardo Di Maio Raffaele 1114463
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utility.h"
#include "component.h"
#include "components_info.h"
#include "warehouse_and_shopping_cart.h"
#include "boards.h"
#include "done_boards.h"
#include "orders.h"

/**
  @details compares s1 and s2
  @return 0 for matching,1 if s1 is greater than s2, -1 if s1 is lower than s2
  @param s1 first string
  @param length_s1 length of string s1
  @param s2 second string
  @param length_s2 length of string s2
*/
int compare_lower_case(char *s1,int length_s1,char *s2,int length_s2);

/**
  @details manages missing input of money and asks the max month of the forecast
  @param money pointer to the value of the money that you will use
  @param max_month pointer to the value of the last month you want to reach
  @param argc number of input strings from console
  @param argv array of strings from console
*/
void options_execution(float *money, int *max_month,int argc,char *argv[]);


int main (int argc, char *argv[])
{
  atexit(exit_output);

  char components_file[]="../dat/components_info.dat";/*!<file name of components*/
  char boards_file[]="../dat/boards.dat";/*!<file name of boards*/
  char orders_file[]="../dat/orders.dat";/*!<file name of orders*/
  char dat_path[]="../dat/";/*!<path name of data*/

  float money;//money that you have
  unsigned int max_month=10;//last month of forecast

  //input (money and max_month)
  options_execution(&money, &max_month,argc,argv);

  int init_money=money;

  int n_comps;//number of possible components
  float low_price;//cost of 1-10 components
  float mid_price;//cost of 11-50 components
  float high_price;//cost of 50+ components

  //creation of components informations
  struct component *components=comps_info(components_file,&n_comps,&low_price,&mid_price,&high_price);

  //creation of warehouse
  struct component_need *warehouse=create_space(components,n_comps);

  //creation of shopping_cart
  struct component_need *shopping_cart=create_space(components,n_comps);

  int n_boards;//number of possible boards

  //creation of boards informations
  struct board *boards=boards_info(boards_file,&n_boards,dat_path,components,n_comps,low_price,mid_price,high_price);

  //creation of register of produced boards
  struct board_need *boards_done=manage_done_boards(boards,n_boards);

  //creation of list of orders
  struct order *orders=create_orders(boards,n_boards,warehouse,shopping_cart,orders_file,&money,n_comps);


  //simulation of time
  int month=1;

  for(;month<=max_month;month++)
  {
    orders=update_orders(orders,shopping_cart,n_comps,warehouse,boards_done,n_boards,month,&money);
  }

  //deallocation of all data structures
  free(boards_done);
  free(warehouse);
  free(shopping_cart);
  dealloc_comps_info(components,n_comps);
  dealloc_orders(orders,max_month,money,init_money);
  dealloc_boards_info(boards,n_boards);

}

void options_execution(float *money, int *max_month,int argc,char *argv[])
{
  int n;

  //if money isn't included, asks it to user
  if(argc==1)
  {
    char s[80];
    char *f;
    do
    {
      printf("Write the amount of money you have \n");
      f=fgets(s,80,stdin);

      n=sscanf(s,"%f",money);
    }
    while(n!=1);
  }
  else
  {
    *money=atof(argv[1]);
  }

  //user can change default max_month
  int check=1;

  while(check)
  {
    printf("Write the number of months you want to test it \n");
    printf("(\"no\" to leave the default option of %d months)\n",*max_month);
    char s[80];
    char *control;
    control=fgets(s,80,stdin);

    char string[80];
    n=sscanf(s,"%s",string);

    n=compare_lower_case(string,strlen(string),"no",strlen("no"));

    //if string equals to "no" exits
    check=(!n)?n:check;

    //else checks if new max_month was included
    if(n)
    {
      n=sscanf(s,"%d",max_month);
      check=(n==1)?0:check;
    }
  }
}

int compare_lower_case(char *s1,int length_s1,char *s2,int length_s2)
{
  int i=0;

  for(;i<length_s2;i++)
  {
    s1[i]=tolower(s1[i]);
  }

  return strncmp(s1,s2,length_s2);
}
