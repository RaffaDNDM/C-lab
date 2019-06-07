/**
  @file utility.h
  @author Di Nardo Di Maio Raffaele 1114463
*/

#ifndef UTILITY_H

/**
  @details set of usefull functions for execution,formatting of data and debugging
*/
#define UTILITY_H

/**
  @details enum that describes the possible operations of verify_pointer
*/
typedef enum control_alloc
{FILE_IN,ALLOC}control_alloc;

/**
  @details verify the value of the pointer (if NULL exits from program)
  @param pointer pointer you want to check
  @param c option for the control (FILE_IN for opening of file,ALLOC for request of allocation)
  @param file_name (only for FILE_IN) the name of the file that you're trying to open
*/
void verify_pointer(void* pointer,control_alloc c,char *file_name);

/**
  @details verify if num_input is equal to control (if not, exits from program)
  @param num_input number of inputs generate from scanf,ssccanf..
  @param control number of inputs you would like to have from scanf,sscan..
  @param file_name file in which you are verifying this format
*/
void verify_format(int num_input,int control,char *file_name);

/**
  @details print the exit message and it's called by atexit()
*/
void exit_output(void);

#endif


#ifndef LINE
/**
  @details MACRO that defines the format of line separator
*/
#define LINE "############################################\n"
#endif

#ifndef WAREHOUSE
/**
  @details MACRO that defines the format of warehouse title
*/
#define WAREHOUSE "              WAREHOUSE\n"
#endif

#ifndef SHOPPING
/**
  @details MACRO that defines the format of shopping cart title
*/
#define SHOPPING "            SHOPPING CART\n"
#endif
