/**
	@file boards.h
  @author Di Nardo Di Maio Raffaele 1114463
*/

#ifndef BOARD_H

/**
  @details set of functions and structs that describes the operations on boards informations
*/
#define BOARD_H

/**
  @details struct that describes the informations about a single board
*/
struct board
{
    unsigned int id_board;/*!<serial number that identifies the board*/
    char *board_name;/*!<common name of the board */
    unsigned int tot_time;/*!<tot_time to create and delivery the board*/
    unsigned int num_comps;/*!<number of different types of components in the board*/
    float cost_board;/*!<cost of the board (tot_cost of components you need for the board)*/
    float profit;/*!<cost of the board for the client*/
    struct component_need *comps;/*!<array of components and their quantities*/
};

/**
  @details creates boards informations (it can be called only once)
  @return returns an array that contains boards informations
  @param file_name name of the file that contains boards names
  @param n_boards pointer to the number of possible boards
  @param path_name path of data
  @param comps array that contains components informations
  @param n_info size of the array comps
	@param low_price pointer to the cost of 1-10 components
	@param mid_price pointer to the cost of 11-50 components
	@param high_price pointer to the cost of 50+ components
*/
struct board *boards_info(char *file_name,int *n_boards,char *path_name,struct component *comps,int n_info,
                        float low_price,float mid_price, float high_price);

/**
  @details looks for the board with name board_name in b
  @return pointer to the board with board_name
  @param b array of boards_info
  @param board_name name of the board
	@param n_boards number of possible boards
*/
struct board *search_board(struct board* b,char *board_name, int n_boards);

/**
	@details dealloc of array of boards informations
	@param b array of boards informations
	@param n_boards number of possible boards
*/
void dealloc_boards_info(struct board *b,int n_boards);

#endif
