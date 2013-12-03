/* * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *  ALG1 - Trabalho 2
 *  main.c
 *
 *  Gil Barbosa Reis                    Nº8532248
 *  gil.reis@usp.br
 *
 *  Leonardo Sampaio Ferraz Ribeiro     Nº8532300
 *  leonardo.sampaio.ribeiro@usp.br
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "main.h"

void print_int(void* x) {
    printf("%d ", *((int*)x));
}

int compare_int(void* a, void* b) {
    return *((int*)a) - *((int*)b);
}

int main(int argc, const char * argv[])
{
    
    return 0;
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

string get_string(void) {
    
    // growable buffer for chars
    string buffer = NULL;
    
    // capacity of buffer
    unsigned int capacity = 0;
    
    // number of chars actually in buffer
    unsigned int n = 0;
    
    // character read or EOF
    int c;
    
    // iteratively get chars from standard input
    while ((c = fgetc(stdin)) != '\n' && c != EOF) {
        // grow buffer if necessary
        if (n + 1 > capacity) {
            // determine new capacity: start at 32 then double
            if (capacity == 0)
                capacity = 32;
            else if (capacity <= (UINT_MAX / 2))
                capacity *= 2;
            else {
                free(buffer);
                return NULL;
            }
            
            // extend buffer's capacity
            string temp = realloc(buffer, capacity * sizeof(char));
            if (temp == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = temp;
        }
        
        // append current character to buffer
        buffer[n++] = c;
    }
    
    // return NULL if user provided no input
    if (n == 0 && c == EOF)
        return NULL;
    
    // minimize buffer
    string minimal = malloc((n + 1) * sizeof(char));
    strncpy(minimal, buffer, n);
    free(buffer);
    
    // terminate string
    minimal[n] = '\0';
    
    // return string
    return minimal;
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

int get_int(void) {
    
    // try to get an int from user
    while (1) {
        
        // get line of text, returning INT_MAX on failure
        string line = get_string();
        
        if (line == NULL)
            return INT_MAX;
        
        // return an int if only an int (possibly with
        // leading and/or trailing whitespace) was provided
        int n; char c;
        
        if (sscanf(line, " %d %c", &n, &c) == 1) {
            free(line);
            return n;
        }
        
        else {
            free(line);
            printf("Retry: ");
        }
    }
    
}
