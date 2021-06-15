
#ifndef CLI_H
#define CLI_H

/*
** function to check whether a command is a function
*/
int is_function(char *arg);

/*
** struct for holding CLI info
*/
typedef struct token{
    uint8_t cur;
    int count;
    char **tokens;
}token;

/*
** place holder for stringing commands together
*/ 

typedef struct instruct_cap{
    int ( *saved_func ) ( token );
    token args;
}instruct_cap;


/*
** add an instruction to an array to be executed in order
*/
int add_instr( token );

/*
** Executes instruction set
*/

int run_instr( token );

/*
** executes a command
*/
uint8_t cmd_execute(token*);

/*
** break up a string in to words, split by a space
*/
token tokenize(char* );

/*
** array of strings of available sub routines
*/
char *builtin_string[];

#endif