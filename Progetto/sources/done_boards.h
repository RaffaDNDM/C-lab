/**
  @file done_boards.h
  @author Di Nardo Di Maio Raffaele 1114463
*/
#ifndef DONE_BOARDS_H

/**
  @details set of functions and structs that describes operations on produced boards
*/
#define DONE_BOARDS_H


/**
  @details struct that adds to a board an information (number of boards)
*/
struct board_need
{
  struct board *pointer_to_board;/*!<pointer to a board*/
  unsigned int quantity;/*!<number of these boards that have been produced*/
};


/**
  @details creates the array that contains produced boards
  @return array of board_need
  @param boards_info array of possible boards
  @param n_boards number of possible boards
*/
struct board_need *manage_done_boards(struct board* boards_info,int n_boards);


/**
  @details updates the quantity of boards produced with name id_board
  @return array of board_need updated
  @param b array of board_need that you want to update
  @param n_boards number of possible boards
  @param id_board id of the board
  @param quantity quantity of this board that has been produced
*/
struct board_need *add_done_board(struct board_need *b,int n_boards,int id_board,int quantity);

/**
	@details prints all the boards produced
	@param b array of board_need with all the boards produced
	@param n_boards number of possible boards
*/
void print_done_boards(struct board_need *b, int n_boards);

#endif
