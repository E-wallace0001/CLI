/*
** A simple, expandable, and dynamic CLI
*/

// C library headers

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "cli.h"

#define command_list_size(list) sizeof(list) / sizeof(char *)
#define copy_buffer(buff_a, buff_b, length) memcpy(buff_a, buff_b, length*sizeof(char)) 



// prototype function pointer to a function
int ( *builtin_functions[]) (token);

/*
** a list of instrunctions to execute
*/
instruct_cap **instruct_list;

int inst_length = 0 ;

/*
** appends an instrunction to an array to be executed
*/

int add_instr( token args)
{
    if (inst_length == args.cur)
    {
        printf(" no instuctions to add");
        return 0;
    }

    int ret = is_function( args.tokens[args.cur+1] );
    if (ret == -1)
    {
        printf("error!");
        exit(0);
    }

    args.cur++;
    inst_length++;
    
    printf("check \n ");
 
    //add instruction here
    instruct_cap *capsule= malloc(sizeof(*capsule));
    capsule->args = args;
    capsule->saved_func =&(*builtin_functions[ret]);

    instruct_list = realloc(instruct_list, sizeof( *capsule) * inst_length );
    instruct_list[ inst_length ] = capsule;
    
}

/* 
** executes the set of instructions stored in a table
*/

int run_instr( token args)
{
    
    instruct_cap *prog = instruct_list[1];
    for( uint8_t i=1; i <=inst_length; i++ )
    {
        printf(" running %p \n ", instruct_list[i]);
        instruct_cap *prog = instruct_list[i];
        (*prog->saved_func)(prog->args);
        
    }
    printf("end \n");
}

/*
**  Example commands that can be called from the CLI
*/

int assert_clause( token args )
{
    printf("asserted \n");
    return 0 ;
}

/*
**closes the program from in the CLI
*/

int __exit( token args )
{
    exit(0);
}

int new_func( token args )
{
    printf("new_func %i \n", args.count);
    return 0;
}

/*
** A simple 'about' statement
*/
int about( token args )
{
    printf("CLI is a basic command line interface programmed by Edwin Wallace for the purpose of controlling subsystems using subroutines.\n");
}


/*
** help function be called from the CLI to give you the avilable commands
*/
int help( token args )
{
    printf("Available commands.\n");
    uint16_t position = 0;
    while(1)
    {
        if ( strcmp( builtin_string[ position ],"\0" ) == 0 )
            break;

        printf("%s \n ", builtin_string[ position ]);
        position ++;

    }
}

/* 
** Simple storing and recalling the strings and functions
** TODO: replace with hash table, and encapsulate into a struct so builint string and functions form single array of structs
*/

/*
**store strings of the built in commads
*/
char *builtin_string[] = 
{
    "help",
    "about",
    "add_instr",
    "run_instr",
    "assert_clause",
    "new_func",
    "exit",
    "\0"
};

/*
** array of function pointers to built in commands
*/

int ( *builtin_functions[]) (token) = {
    &help,
    &about,
    &add_instr,
    &run_instr,
    &assert_clause,
    &new_func,
    &__exit,
};

/*
** check whether a string correspons to a function
*/
int is_function(char *arg)
{
    for ( int i = 0 ; i < sizeof(builtin_string) / sizeof(char *); i ++)
    {
        if ( strcmp( arg, builtin_string[i]) == 0 ) return i;
    }
    return -1 ;
}

/*
** execute a command
*/
uint8_t cmd_execute(token *command_token)
{
    char* command = command_token->tokens[0];
    
    int8_t func_ret = is_function( command );
    if( func_ret != -1) return (*builtin_functions[func_ret])(*command_token);

    return 0;
}

char text[20]  ;
char command_line[50] ={0};
int cmd_ln_ptr = 0 ; 

char *args;


/*
** break up a string in to words, split by a space
*/
token tokenize(char* string){
    char **tokens = malloc(sizeof( *tokens) );
    char *p = strtok (string," ");

    int word_count = 0 ;

    while (p!= NULL)
    {
        tokens = realloc(tokens, sizeof( *tokens) * word_count+1 );
        tokens[word_count] = malloc(sizeof(char)*strlen(p));
        tokens[word_count] = p; 
        word_count ++;
        p = strtok (NULL, " ");
    }

    token tok_ret;
    tok_ret.count = word_count;
    tok_ret.tokens = tokens;
    tok_ret.cur = 0;
    return tok_ret;
}


