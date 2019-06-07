/**
  @file components_info.h
  @author Di Nardo Di Maio Raffaele 1114463
*/

#ifndef COMPONENTS_INFO_H

/**
  @details set of functions and structs that describes operations on components informations
*/
#define COMPONENTS_INFO_H

/**
  @details struct that add the quantity of a component to a pointer to that component
*/
struct component_need
{
    struct component *pointer_to_comp;/*!<pointer to a component in array of components informations*/
    unsigned int quantity;/*!<number of components with the name pointed by pointer_to_comp*/
}component_need;

/**
  @details creates components informations (it can be called only once)
  @return pointer to the array of components
  @param file_name name of the file of components informations
  @param size_array pointer to the size of the array returned by the function
  @param low_price pointer to the cost of 0-10 components
  @param mid_price pointer to the cost of 11-50 components
  @param high_price pointer to the cost of over 51 components
*/
struct component *comps_info(char *file_name,int* size_array,float *low_price,float *mid_price,float *high_price);

/**
  @details looks for a component inside the array of components informations c
  @return pointer to the component
  @param c array of components informations
  @param comp_id id of the component
  @param comp_name name of the component
  @param n size of the array c
*/
struct component* search_info(struct component *c,int comp_id,char *comp_name,int n);

/**
  @details dealloc all the components
  @param c array of components
  @param n_comps size of array of components
*/
void dealloc_comps_info(struct component *c,int n_comps);


#endif
