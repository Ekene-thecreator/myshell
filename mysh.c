#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "builtins.h"
#include "io_helpers.h"
#include "variables.h"




int main(int argc, char* argv[]) {
    char *prompt = "shelly$ "; // TODO Step 1, Uncomment this.

    char input_buf[MAX_STR_LEN + 1];
    input_buf[MAX_STR_LEN] = '\0';
    char *token_arr[MAX_STR_LEN] = {NULL};

    // Declare linked variables
    head_var = (struct linked_v*)malloc(sizeof(struct linked_v));
    char* firstname = "Author";
    char* firstval = "Ekenedillichukwu Akuneme";
    strcpy(head_var->name, firstname);
    strcpy(head_var->value, firstval);
    head_var->next = NULL;
    tail_var = head_var;
    
   


    while (1) {
        // Prompt and input tokenization

        // TODO Step 2:
        // Display the prompt via the display_message function.
        display_message(prompt);


        int ret = get_input(input_buf);
        size_t token_count = tokenize_input(input_buf, token_arr);

        // Clean exit
        if (ret != -1 && token_count == 1 && (strcmp("exit", token_arr[0]) == 0)) {
            printf("Exiting.....\n");
            sleep(1);
            break;
        }

        // Command execution
        else if (token_count == 1){
            char* needle = "=";
            char* substr = strstr(token_arr[0], needle);
            if (substr != NULL){
                //variable implementation
                char declaration[64];
                char* name; 
                char value[64]; 
                strcpy(declaration, token_arr[0]);
                name = strtok(declaration, needle);
                strcpy(value, substr + 1);
                struct linked_v* present;
                present = is_declared(name);
                if (strncmp("$", value, 1)==0 && strlen(value) > 1)
                {
                    struct linked_v* var = is_declared(value + 1);
                    if (var != NULL)
                    {
                        strcpy(value, var->value);
                    }
                        
                }

                if (present != NULL)
                {
                    change_variable(present, value);
                }
                else
                {   
                    add_variable(name, value);
                }


            }
        }
        else if (token_count > 1) {
            bn_ptr builtin_fn = check_builtin(token_arr[0]);
            if (builtin_fn != NULL) {
                ssize_t err = builtin_fn(token_arr);
                if (err == - 1) {
                    display_error("ERROR: Builtin failed: ", token_arr[0]);
                }
            } else {
                display_error("ERROR: Unrecognized command: ", token_arr[0]);
            }
        }

    }
    free_vars();
    return 0;
}
