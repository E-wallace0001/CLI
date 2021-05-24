#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "cli.h"

/*
**simple program that just awaits input and parses the string, and executes the data
*/

int main(){

    char input;
    char command_buffer[256]={0};
    uint8_t input_position = 0 ;
    char *buff;

    while(1)
    {
      while(1)
      {
        if( input_postion == 256 )
        {
          printf(" string limit hit");
          break;
        } 

        input = getchar();

        // give a null charachter at the end of file or new line
        if( input == EOF || input == '\n')
        {
            break;
        }
        else
        {
            command_buffer[ input_position ] = input; 
        }
        input_position++; 
      }

      buff = malloc( sizeof(char) * input_position);


      memcpy(buff, command_buffer, input_position);

      token cmd = tokenize(buff);

      cmd_execute(&cmd);

      free(buff)
      
      input_position = 0;
    }
}