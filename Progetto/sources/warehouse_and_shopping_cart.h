/**
  @file warehouse_and_shopping_cart.h
  @author Di Nardo Di Maio Raffaele 1114463
*/

#ifndef MAGAZINE_SHOPPING_CART_H

/**
  @details  set of functions and structs that describes the operations on the set of ordered components
*/
#define MAGAZINE_SHOPPING_CART_H

/**
  @details creates magazine or shopping cart
  @return array that contains the components informations and quantities
  @param components_info array of the components informations
  @param n_comps size of the array of components informations
*/
struct component_need *create_space(struct component* components_info,int n_comps);

/**
  @details increases the quantity of a component inside the space
  @return array that contains the components informations and quantities
  @param c array of components informations and quantities
  @param n_comps size of the array of components informations
  @param comp_id id of the component you want update
  @param quantity number of components with id comp_id you want to add
*/
struct component_need *add_component(struct component_need *c,int n_comps,int comp_id,int quantity);

/**
  @details decreases the quantity of a component inside the space
  @return array that contains the components informations and quantities
  @param c array of components informations and quantities
  @param n_comps size of the array of components informations
  @param comp_id id of the component you want update
  @param quantity number of components with id comp_id you want to remove
*/
struct component_need *remove_component(struct component_need *c,int n_comps,int comp_id,int quantity);

/**
  @details prints all the components names and quantities inside space
  @return array that contains the components informations and quantities
  @param space array of components informations and quantities
  @param n_comps size of the array of components informations
  @param space_name name of the space in which there are the components you want to print
*/
void print_space(struct component_need *space,int n_comps,char *space_name);

#endif
