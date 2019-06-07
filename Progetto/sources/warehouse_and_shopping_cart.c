/**
  @file warehouse_and_shopping_cart.c
  @author Di Nardo Di Maio Raffaele 1114463
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "component.h"
#include "components_info.h"
#include "utility.h"

struct component_need *create_space(struct component* components_info,int n_comps)
{
  struct component_need *space=malloc(sizeof(struct component_need)*n_comps);
  verify_pointer(space,ALLOC,NULL);

  int i=0;

  for(;i<n_comps;i++)
  {
    space[i].pointer_to_comp=&components_info[i];
    space[i].quantity=0;
  }

  return space;
}

struct component_need *add_component(struct component_need *c,int n_comps,int comp_id,int quantity)
{
  int i=0;

  for(i=0;i<n_comps;i++)
  {
    if((c[i].pointer_to_comp->comp_id)==comp_id)
    {
      c[i].quantity+=quantity;
      return c;
    }
  }
}

struct component_need *remove_component(struct component_need *c,int n_comps,int comp_id,int quantity)
{
  int i=0;

  for(i=0;i<n_comps;i++)
  {
    if((c[i].pointer_to_comp->comp_id)==comp_id)
    {
      c[i].quantity-=quantity;
      return c;
    }
  }
}

void print_space(struct component_need *space,int n_comps,char *space_name)
{
  printf(LINE);
  printf("%s",space_name);
  printf("id              nome             quantity \n");
  printf(LINE);

  for(int i=0;i<n_comps;i++)
  {
    int id=(space[i].pointer_to_comp)->comp_id;
    char *name=(space[i].pointer_to_comp)->name;

    printf("%-13d %-22s %-d\n",id,name,space[i].quantity);
  }
}
