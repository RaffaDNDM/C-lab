/**
  @file orders.h
  @author Di Nardo Di Maio Raffaele 1114463
*/

#ifndef ORDERS_H

/**
  @details set of functions and structs that describes operations on the orders (organized as a list)
*/
#define ORDERS_H

/**
  @details struct that describes a node (an order)
*/
struct order
{
  unsigned int time_stamp;/*!<month in which the order arrives*/
  int delivery_month;/*!<month in which the order will be completed (-1 if check=0)*/
  unsigned int board_quantity;/*!<number of boards required from the order*/
  struct board *board_point;/*!<pointer to the board in the order*/
  struct order *next;/*!<pointer to the next order*/
  int check;/*!< 1 if the order is in execution, else 0*/
};

/**
  @details creates the list (it can be called only once)
  @return the list of orders
  @param boards array of boards informations
  @param n_boards number of possible boards (size of boards)
  @param warehouse pointer to the space of arrived components
  @param shopping_cart pointer to the space of ordered and not arrived components
  @param file_name name of the file with orders
  @param money pointer to the money you have
  @param n_comps_info number of possible components
*/
struct order *create_orders(struct board *boards,int n_boards,struct component_need *warehouse,
                          struct component_need *shopping_cart,char *file_name,float *money,int n_comps_info);

/**
  @details updates the list looking to the month
  @return the list of orders
  @param orders pointer to the first element of the list
  @param shopping_cart pointer to the space of ordered and not arrived components
  @param n_comps_info number of possible components
  @param warehouse pointer to the space of arrived components
  @param boards_done pointer to the space of produced boards
  @param n_boards number of possible boards
  @param month this month
  @param money pointer to the money you have
*/
struct order *update_orders(struct order *orders,struct component_need* shopping_cart,int n_comps_info,
                           struct component_need *warehouse,struct board_need *boards_done,int n_boards,int month,float *money);

/**
  @details deallocation of the list, prints the profit and the boards that are in execution
  @param orders pointer to the first element of the list of orders
  @param month this month
  @param money money that you have in the moment you call the function
  @param init_money the money you had at the beginning of the programm
*/
void dealloc_orders(struct order *orders,int month,float money,float init_money);

#endif
