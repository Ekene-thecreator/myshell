#include <string.h>
#include "stdlib.h"

struct linked_v
{
    char name[64];
    char value[64];
    struct linked_v* next;
    
};

struct linked_v* head_var;
struct linked_v* tail_var;
void add_variable(char * name, char* value);
void change_variable(struct linked_v* var, char* value);
struct linked_v* is_declared(char* name);
void free_vars();