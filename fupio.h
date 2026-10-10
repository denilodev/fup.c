#include <errno.h>
#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FUPIO_MAX_BUFFER 64

long long get_long(char* prompt)
{
    char buffer[FUPIO_MAX_BUFFER];
    while(1)
    {
        printf("%s", prompt);
        fflush(stdout);
        
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        {
            clearerr(stdin);
            continue;
        }

        int len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n')
        {
            buffer[len-1] = '\0';
        }
        else
        {
            char c;
            while((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        
        char* end_ptr;
        errno = 0;
        long long num = strtoll(buffer, &end_ptr, 10);

        if (end_ptr != buffer && *end_ptr == '\0' && errno != ERANGE)
        {
            return num;
        }
    }
}

int get_int(char* prompt)
{
    while(1)
    {
        long input_flow = get_long(prompt);
        if (input_flow <= INT_MAX && input_flow >= INT_MIN) return (int)input_flow;
    }
}

double get_double(char* prompt)
{
    char buffer[FUPIO_MAX_BUFFER];
    while(1)
    {
        printf("%s", prompt);
        fflush(stdout);
        
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        {
            clearerr(stdin);
            continue;
        }

        int len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n')
        {
            buffer[len-1] = '\0';
        }
        else
        {
            char c;
            while((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        
        char* end_ptr;
        errno = 0;
        double num = strtod(buffer, &end_ptr);

        if (end_ptr != buffer && *end_ptr == '\0' && errno != ERANGE)
        {
            return num;
        }
    }
}

float get_float(char* prompt)
{
    while(1)
    {
        double input_flow = get_double(prompt);
        if (input_flow <= FLT_MAX && input_flow >= -FLT_MAX) return (float)input_flow;
    }
}

char* get_string(char* prompt)
{
    char* buffer, * aux_buffer;
    int actual_buffer_size, buff_start, buff_limit, len;
    while(1)
    {
        printf("%s", prompt);
        fflush(stdout);

        actual_buffer_size = FUPIO_MAX_BUFFER;
        buffer = malloc(actual_buffer_size * sizeof(char));

        if(fgets(buffer, actual_buffer_size, stdin) == NULL)
        {
            clearerr(stdin);
            free(buffer);
            continue;
        }

        len = strlen(buffer);
        while (buffer[len-1] != '\n')
        {
            buff_start = actual_buffer_size-1;
            buff_limit = actual_buffer_size+1;
            actual_buffer_size *= 2;
            aux_buffer = realloc(buffer, actual_buffer_size);
            buffer = aux_buffer;
            if(fgets(&buffer[buff_start], buff_limit, stdin) == NULL)
            {
                clearerr(stdin);
                free(buffer);
                continue;
            }
            len = strlen(buffer);
        }
        
        buffer[len-1] = '\0';

        return buffer;
    }
}

char get_char(char* prompt)
{
    while(1)
    {
        char* input_flow = get_string(prompt);
        if(strlen(input_flow) != 1)
        {
            free(input_flow);
            continue;
        }
        return input_flow[0];
    }
}