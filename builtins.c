#include <string.h>
#include <stdio.h>
#include "builtins.h"
#include "io_helpers.h"
#include "variables.h"


// ====== Command execution =====

/* Return: index of builtin or -1 if cmd doesn't match a builtin
 */
bn_ptr check_builtin(const char *cmd) {
    ssize_t cmd_num = 0;
    while (cmd_num < BUILTINS_COUNT &&
           strncmp(BUILTINS[cmd_num], cmd, MAX_STR_LEN) != 0) {
        cmd_num += 1;
    }
    return BUILTINS_FN[cmd_num];
}


// ===== Builtins =====

/* Prereq: tokens is a NULL terminated sequence of strings.
 * Return 0 on success and -1 on error ... but there are no errors on echo. 
 */
ssize_t bn_echo(char **tokens) {
    ssize_t index = 1;

    
    
    while (tokens[index] != NULL) {
        // TODO:
        // Implement the echo command
        char* entry = tokens[index];
        char* dollar = "$";
        if (strncmp(dollar, entry, 1) == 0)
        {   
            struct linked_v* variable = is_declared(entry + 1);
            if (variable != NULL)
            {
                display_message(variable->value);
            }
            else{
                display_message(tokens[index]);
            }         
        }
        else{
            display_message(tokens[index]);
                if (tokens[index +1] != NULL) {
                    display_message(" ");
                }
                
            }
    index += 1;
    }
    display_message("\n");

    return 0;
}

ssize_t bn_cat(char** tokens){
    char* filename = tokens[1];
    FILE * fptr = fopen(filename, "r");
    char line[64];
    while (fgets(line, 64, fptr) != 0)
    {
        printf("%s\n", line);
    }

    return 0;
}

ssize_t bn_wc(char** tokens){
    char* filename = tokens[1];
    FILE * fptr = fopen(filename, "r");
    char buff[64];
    int word_count, line_count, character_count;
    word_count = 0;
    line_count = 0;
    character_count = 0;
    while (fgets(buff, 64, fptr) != 0)
    {
        char line[64];
        strcpy(line, buff);
        char* word;
        word = strtok(line, " ");
        while (word != NULL)
        {
            word_count += 1;
            character_count += strlen(word);
            word = strtok(NULL, " ");
        }
        line_count += 1;
        
    }
    printf("\n=================\n");
    printf("Line count: %d\n", line_count);
    printf("Word count: %d\n", word_count);
    printf("Character count: %d\n", character_count);
    printf("=================\n\n");

    return 0;

}