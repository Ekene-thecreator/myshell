#include <string.h>
#include "builtins.h"
#include "io_helpers.h"
#include "variables.h"



void add_variable(char* name, char* value){
    struct linked_v* new_var = (struct linked_v*)malloc(sizeof(struct linked_v));
    strcpy(new_var->value, value);
    strcpy(new_var->name, name);
    new_var->next  = NULL;
    tail_var->next = new_var;
    tail_var = new_var;
};

struct linked_v* is_declared(char* name){
    struct linked_v* curr = head_var;
    while (curr != NULL)
    {
        if (strcmp(name, curr->name) == 0){
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
    
};

void change_variable(struct linked_v* var, char* value){
    strcpy(var->value, value);
};

void free_vars(){
    struct linked_v* curr = head_var;
    while(curr != NULL){
        struct linked_v* tmp = curr;
        curr = curr->next;
        free(tmp);
    }
}
