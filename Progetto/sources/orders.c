/**
  @file orders.c
  @author Di Nardo Di Maio Raffaele 1114463
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"
#include "component.h"
#include "components_info.h"
#include "warehouse_and_shopping_cart.h"
#include "boards.h"
#include "done_boards.h"
#include "orders.h"

/**
  @details checks if you have enough money and if time_stamp <= this month
  @return 1 if OK, 0 if a condition isn't true
  @param b pointer to the board that you want to control
  @param month this month
  @param time_stamp time_stamp of the order
  @param money pointer to the money that you have
  @param board_quantity number of boards that you want to produce
*/
int check_order(struct board *b, int month,int time_stamp,float money,int board_quantity);

/**
  @details creates a node and add it to the list of orders
  @return pointer to the first element of the list
  @param orders pointer to the first element of the list of orders
  @param b pointer to the board that you want to add
  @param shopping_cart pointer to the space of ordered and not arrived components
  @param month this month
  @param time_stamp month from first month in which the order arrives
  @param money pointer to the money that you have
  @param check value returned from checkOrder
  @param board_quantity number of boards in the order
  @param n_comps_info number of possible components
*/
struct order *add_order(struct order *orders,struct board *b,struct component_need* shopping_cart,
                      int month,int time_stamp,float *money,int check,int board_quantity,int n_comps_info);

/**
  @details change condition of an order from "not in execution" to "in_execution"
  @param order pointer to the order
  @param warehouse pointer to the space that manages arrived components
  @param shopping_cart pointer to the space that manages ordered and not arrived components
  @param num_comps_info number of possible components
  @param month this month
  @param money pointer to the money that you have
*/
void change_order_condition(struct order *order,struct component_need *warehouse,struct component_need *shopping_cart,
                          int num_comps_info,int month,float *money);


/**
  @details updates components inside warehouse and shopping cart
  @param order pointer to the order
  @param warehouse pointer to space that manages arrived components
  @param shopping_cart pointer to space that manage the space of order of components
  @param num_comps_info number of possible components
  @param month this month
*/
void update_orders_and_arrives(struct order *order,struct component_need *warehouse,struct component_need *shopping_cart,
                            int num_comps_info,int month);

/**
  @details removes an order from the list and update produced boards and warehouse
  @param order pointer to the order
  @param warehouse pointer to the space that manages arrived components
  @param num_comps_info number of possible components
  @param boards_done array of produced boards
  @param n_boards number of possible boards
  @param money pointer to the money that you have
*/
void order_done(struct order *order,struct component_need *warehouse,int num_comps_info,
                        struct board_need *boards_done,int n_boards,float *money);


struct order *create_orders(struct board *boards,int n_boards,struct component_need *warehouse,
                          struct component_need *shopping_cart,char *file_name,float *money,int n_comps_info)
{
    struct order *orders = NULL;
    static int check_init=0;

    FILE *f=NULL;
    f=fopen(file_name,"r");
    verify_pointer(f,FILE_IN,file_name);

    //createOrders can be called only once
    if(check_init>=1)
      return NULL;

    char *control;
    char s[80];
    char board_name[20];
    int time_stamp;
    int board_quantity;
    int flag=1;

    while(flag)
    {
      control=fgets(s,80,f);

      //reads the input line and creat the order
      if(control!=NULL)
      {
        int n=sscanf(s,"%d %s %d",&time_stamp,board_name,&board_quantity);
        verify_format(n,3,file_name);

        //looks for the board inside the boards informations
        struct board *board_point=search_board(boards,board_name,n_boards);

        //checks if the order can be executed
        int check=check_order(board_point,0,time_stamp,*money,board_quantity);

        //adds the order to the list
        orders=add_order(orders,board_point,shopping_cart,0,time_stamp,money,check,board_quantity,n_comps_info);
      }
      else
        flag=0;
    }

    fclose(f);

    check_init++;
    return orders;
}

int check_order(struct board *b, int month,int time_stamp,float money,int board_quantity)
{
  if(b!=NULL)
  {
    return ((time_stamp<=month) && (((b->cost_board)*board_quantity)<=money));
  }
  else
    return 0;
}

struct order *add_order(struct order *orders,struct board *b,struct component_need* shopping_cart,
                      int month,int time_stamp,float *money,int check,int board_quantity,int n_comps_info)
{
  //creates the new node
  struct order* new_node = malloc(sizeof(struct order));
  verify_pointer(new_node,ALLOC,NULL);

  new_node->time_stamp=time_stamp;
  new_node->board_quantity=board_quantity;
  new_node->board_point=b;
  new_node->check = check;

  //connects the new element with the previous list head
  new_node->next=orders;

  //creates the link to the components(pointer to component+quantity of component)
  if(check)
  {
    int i=0;

    for(int i=0;i<(b->num_comps);i++)
    {
      struct component_need c=(b->comps)[i];
      shopping_cart = add_component(shopping_cart,n_comps_info,(c.pointer_to_comp)->comp_id,(c.quantity)*(new_node->board_quantity));
    }

    new_node->delivery_month=month+(b->tot_time);
    (*money)-=((b->cost_board)*board_quantity);
  }
  else
  {
    new_node->delivery_month=-1;
  }

  //returns the new list head
  return new_node;

}

struct order *update_orders(struct order *orders,struct component_need* shopping_cart,int n_comps_info,
                          struct component_need *warehouse,struct board_need *boards_done,int n_boards,int month,float *money)
{
  struct order s;
  s.next=orders;
  struct order *p=&s;

  //updates orders in the list
  while(p->next!=NULL)
	{
		if((p->next)->check)
		{
      //done order
      if(((p->next)->delivery_month)==month)
      {
        printf(LINE);
        printf("#              month %d                     #\n",month);

        order_done(p->next,warehouse,n_comps_info,boards_done,n_boards,money);

        //prints elements of warehouse
        print_space(warehouse,n_comps_info,WAREHOUSE);

        //printss elements of shopping cart
        print_space(shopping_cart,n_comps_info,SHOPPING);

        //prints elements of warehouse
        print_done_boards(boards_done,n_boards);

        struct order *temp=p->next;

        //updates the head of the list
        if(orders==temp)
          orders=temp->next;

        p->next=temp->next;

				free(temp);
      }
      else
      {
        //updates components (warehouse and shopping cart)
        update_orders_and_arrives(p->next,warehouse,shopping_cart,n_comps_info,month);
        p=p->next;
      }
    }
    else
    {
      //checks if new order can be executed
      int check=check_order(p->next->board_point,month,p->next->time_stamp,*money,p->next->board_quantity);

      if(check)
        change_order_condition(p->next,warehouse,shopping_cart,n_comps_info,month,money);//updates order

      p=p->next;
    }
	}

  return orders;
}


void order_done(struct order *order,struct component_need *warehouse,int num_comps_info,
                        struct board_need *boards_done,int n_boards,float *money)
{
  int i=0;
  struct board* b=order->board_point;

  //removes the components inside the warehouse that I need to make the board
  for(;i<(b->num_comps);i++)
  {
    struct component_need c=(b->comps)[i];
    warehouse = remove_component(warehouse,num_comps_info,(c.pointer_to_comp)->comp_id,(c.quantity)*(order->board_quantity));
  }

  //adds completed boards
  boards_done=add_done_board(boards_done,n_boards,b->id_board,order->board_quantity);

  //updates the money
  (*money)+=(order->board_quantity)*(b->profit);

}

void update_orders_and_arrives(struct order *order,struct component_need *warehouse,struct component_need *shopping_cart,
                            int num_comps_info,int month)
{
  int i=0;
  struct board* b=order->board_point;

  //number of months from the beginning of execution of the order
  int month_from_beginProd=month-((order->delivery_month)-(b->tot_time));

  for(;i<(b->num_comps);i++)
  {
    struct component_need c=(b->comps)[i];

    if((c.pointer_to_comp)->months==month_from_beginProd)
    {
      //adds arrived components to warehouse
      warehouse = add_component(warehouse,num_comps_info,(c.pointer_to_comp)->comp_id,((c.quantity)*(order->board_quantity)));

      //removes arrived components to warehouse
      shopping_cart = remove_component(shopping_cart,num_comps_info,(c.pointer_to_comp)->comp_id,((c.quantity)*(order->board_quantity)));
    }
  }
}

void change_order_condition(struct order *order,struct component_need *warehouse,struct component_need *shopping_cart,
                          int num_comps_info,int month,float *money)
{
  struct board *b=order->board_point;

  order->delivery_month=month+(b->tot_time);
  order->check =1;

  //updates the money
  (*money)-=((b->cost_board)*(order->board_quantity));

  int i=0;

  //updates the shopping cart with new components
  for(int i=0;i<(b->num_comps);i++)
  {
    struct component_need c=(b->comps)[i];
    shopping_cart = add_component(shopping_cart,num_comps_info,(c.pointer_to_comp)->comp_id,(c.quantity)*(order->board_quantity));
  }
}

void dealloc_orders(struct order *orders,int month,float money,float init_money)
{
  struct order *p=orders;
  int check=0;

  if(p==NULL)
  {
    printf(LINE);
    printf("you've completed all the orders with %d months \n",month);
    printf(LINE);
  }
  else
  {
    while(p!=NULL)
    {
      struct order *temp=p;

      //checks if an order is in execution
      if((p->delivery_month)>=0)
      {
          printf(LINE);
          printf("You could complete the order of month %d composed of %d",p->time_stamp,p->board_quantity);
          printf(" %s with more %d months\n",p->board_point->board_name,(p->delivery_month)-month);
          printf(LINE);
          check=1;
      }

      p=p->next;
      free(temp);
    }

    if(!check)
    {
      printf(LINE);
      printf("You can't make the boards within the money you have \n");
      printf(LINE);
    }
  }

  //prints total profit
  if(money>=init_money)
    printf("You earned %.2f\n",money-init_money);
}
