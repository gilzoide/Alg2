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
    
    char option;
    AVL users, users_with_messages;
    linked_list users_list, words;
    
    do {
        
        option = get_int();
        show_menu();
        
        switch (option) {
            
            case 1: // Inicializar/Resetar cadastro
                users_create(&users, &users_list, &compare_users);
                break;
                
            case 2: // Cadastrar usuario
                user_add(&users, &users_list, &compare_messages);
                break;
                
            case 3: // Descadastrar usuario
                user_delete(&users, &users_list);
                break;
                
            case 4: // Inicializar/Resetar tweets
                users_with_messages_create(&users, &compare_users);
                break;
                
            case 5: // Postar uma mensagem
                users_post_message(&users, &users_with_messages, &words, &compare_messages);
                break;
                
            case 16: // Apagar uma mensagem
                users_delete_message(&users, &users_with_messages, &words);
                break;
                
            case 7: // Listar usuarios em ordem alfabetica
                users_list_by_name(&users);
                break;
                
            case 8: // Listar usuarios cadastrados na ordem em que se cadastraram
                users_list_by_entry(&users_list);
                break;
                
            case 9: // Listar usuarios que postaram tweets, em ordem alfabetica
                users_with_messages_list_by_name(&users_with_messages);
                break;
                
            case 10: // Mostrar numero de usuarios que postaram tweets
                users_with_messages_count(&users_with_messages);
                break;
                
            case 11: // Mostrar numero de tweets
                users_with_messages_count_messages(&users_with_messages);
                break;
                
            case 12: // buscar tweets por palavra-chave
                words_find_messages(&words);
                break;
                
            case 13: // mostrar 3 palavras-chave das mensagens
                words_show_keywords(&words);
                break;
                
            case 14: // mostrar usuario mais atualizado
                users_updated_user(&users_with_messages, &words);
                break;
                
            case 15: // encerrar o sistema
                
                break;
                
            default:
                printf("Opção Inválida\n\n");
        }
        
    } while (option != 15);
    
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

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

int compare_users(void*, void*) {
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

int compare_users_by_name(void*, void*) {
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

int compare_messages(void*, void*) {
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

int compare_messages_by_text(void*, void*) {
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

int compare_words(void*, void*) {
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void show_menu() {
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void users_create(AVL* users, linked_list* users_list, int (*compare)(void*, void*)) {
    
    AVL_create(users, compare);
    
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void user_add(AVL* users, linked_list* users_list, int (*compare_tweets)(void*, void*)) {
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void user_delete(AVL* users, linked_list* users_list) {
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void users_with_messages_create(AVL* users_with_messages, int (*compare)(void*, void*)) {
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void users_post_message(AVL* users, AVL* users_with_messages, linked_list* words, int (*compare)(void*, void*)) {
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void users_delete_message(AVL* users, AVL* users_with_messages, linked_list* words) {
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void users_list_by_name(AVL* users) {
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void users_list_by_entry(linked_list* users_list) {
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void users_with_messages_list_by_name(AVL* users_with_messages) {
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void users_with_messages_count(AVL* users_with_messages) {
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void users_with_messages_count_messages(AVL* users_with_messages) {
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void words_find_messages(linked_list* words) {
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void words_show_keywords(linked_list* words) {
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void users_updated_user(AVL* users_with_messages, linked_list* words) {
    
}
