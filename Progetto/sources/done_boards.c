/**
  @file done_boards.c
  @author Di Nardo Di Maio Raffaele 1114463
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "component.h"
#include "components_info.h"
#include "boards.h"
#include "done_boards.h"
#include "utility.h"

struct board_need *manage_done_boards(struct board* boards_info,int n_boards)
{
  static int check_init=0;

  //manage_done_boards can be called only once
  if(check_init>0)
    return NULL;

  //creation of the space of produced boards
  struct board_need *done_boards=malloc(sizeof(struct board_need)*n_boards);
  verify_pointer(done_boards,ALLOC,NULL);

  for(int i=0;i<n_boards;i++)
  {
      done_boards[i].pointer_to_board=&boards_info[i];
      done_boards[i].quantity=0;
  }

  check_init++;
  return done_boards;
}

struct board_need *add_done_board(struct board_need *b,int n_boards,int id_board,int quantity)
{
  int i=0;

  //adds quantity to quantity of board with id_board
  for(;i<n_boards;i++)
  {
    if((b[i].pointer_to_board->id_board)==id_board)
    {
      b[i].quantity+=quantity;
      return b;
    }
  }
}

void print_done_boards(struct board_need *b, int n_boards)
{
  printf(LINE);
  printf("             BOARDS\n");
  printf("  board_name          quantity\n");
  printf(LINE);

  int i=0;

  for(;i<n_boards;i++)
  {
    struct board *p=b[i].pointer_to_board;
    printf("    %-20s %-d\n",p->board_name,b[i].quantity);
  }
}
