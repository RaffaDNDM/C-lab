/**
  @@file component.h
  @author Di Nardo Di Maio Raffaele 1114463
*/

#ifndef COMPONENT_H
#define COMPONENT_H

/**
  @details struct that describes informations about a component
*/
struct component
{
    unsigned int comp_id;/*!<id of the component*/
    char *name;/*!<common name of the component*/
    unsigned int months;/*!<number of months necessary to receive the component*/
};

#endif
