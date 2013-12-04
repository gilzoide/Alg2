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
        
        show_menu();
        option = get_int();
        
        switch (option) {
            
            case 1: // Inicializar/Resetar cadastro
                users_create(&users, &users_list, &compare_users);
                break;
                
            case 2: // Cadastrar usuario
                user_add(&users, &users_list, &compare_messages);
                break;
                
            case 3: // Descadastrar usuario
                user_delete(&users, &users_with_messages, &users_list);
                break;
                
            case 4: // Inicializar/Resetar tweets
                users_with_messages_create(&users_with_messages, &words, &compare_users);
                break;
                
            case 5: // Postar uma mensagem
                users_post_message(&users, &users_with_messages, &words, &compare_messages);
                break;
                
            case 6: // Apagar uma mensagem
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

int compare_users(void* a, void* b) {
    
    user* first_user = (user*) a;
    user* second_user = (user*) b;
    
    string first_name = first_user->name;
    string second_name = second_user->name;
    
    return strcmp(first_name, second_name);
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

int compare_users_by_name(void* a, void* b) {
    
    user* first_user = (user*) b;
    string second_user_name = (string) a;
    
    return strcmp(second_user_name, first_user->name);
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

string message_build_text(tweet* the_tweet) {
    
    int size = 0;
    string result = NULL;
    linked_list L = the_tweet->words;
    LL_node* p = NULL;
    
    // percorre a lista encadeada
    for (p = L.head; p != NULL; p = p->next) {
        
        // identifica a palavra
        word* a_word = (word*) p->info;
        size += strlen(a_word->text) + 1;
        
        // concatena ao resultado
        result = realloc(result, size*sizeof(char) + 1);
        strcat(result, a_word->text);
        strcat(result, " ");
        
    }
    
    return result;
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

int compare_messages(void* a, void* b) {
    
    tweet* first_tweet = (tweet*) a;
    tweet* second_tweet = (tweet*) b;
    
    string first_text = message_build_text(first_tweet);
    string second_text = message_build_text(second_tweet);
    
    int result = strcmp(first_text, second_text);
    
    free(first_text);
    free(second_text);
    
    return result;
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

int compare_messages_by_text(void* a, void* b) {
    
    tweet* first_tweet = (tweet*) b;
    
    string first_text = message_build_text(first_tweet);
    string second_text = (string) a;
    
    int result = strcmp(second_text, first_text);
    
    free(first_text);
    
    return result;
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

int compare_words_by_text(void* a, void* b) {
    
    string first_word_text = (string) a;
    word* second_word = (word*) b;
    
    return strcmp(first_word_text, second_word->text);
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

int compare_words_by_counter(void* a, void* b) {
    
    word* first_word = (word*) a;
    word* second_word = (word*) b;
    
    return first_word->counter - second_word->counter;
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void show_menu() {
    
    printf("\nCaro usuário, suas opções são:                            \n\
    1) Inicializar/resetar cadastro                                     \n\
    2) Cadastrar usuário                                                \n\
    3) Descadastrar usuário                                             \n\
    4) Inicializar/resetar mensagens                                    \n\
    5) Postar uma mensagem                                              \n\
    6) Apagar uma mensagem                                              \n\
    7) Listar usuários cadastrados em ordem alfabética                  \n\
    8) Listar usuários cadastrados na ordem em que se cadastraram       \n\
    9) Listar usuários que postaram mensagens, em ordem alfabética      \n\
    10) Mostrar número de usuários que postaram mensagens               \n\
    11) Mostrar número de mensagens                                     \n\
    12) Buscar mensagens por palavra-chave                              \n\
    13) Mostrar 3 palavras-chave das mensagens                          \n\
    14) Mostrar usuário mais atualizado                                 \n\
    15) Encerrar o sistema                                              \n\
    O que deseja fazer? ");
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void users_create(AVL* users, linked_list* users_list, int (*compare)(void*, void*)) {
    
    AVL_create(users, compare);
    LL_create(users_list, compare);
    
    printf("\nCadastro Inicializado!\n");
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void user_add(AVL* users, linked_list* users_list, int (*compare_tweets)(void*, void*)) {
    
    printf("\nEntre com o nome de usuário: ");
    
    // aloca memoria
    user* new_user = (user*) malloc(sizeof(user));
    if (new_user == NULL) { printf("\nHouve uma falha!\n"); return; }
    
    // cria o usuario e inicializa sua lista de tweets
    new_user->name = get_string();
    LL_create(&new_user->tweets, compare_tweets);
    
    // insere na AVL e na lista encadeada
    AVL_insert(users, new_user);
    LL_insert(users_list, new_user);
    
    printf("\nUsuário cadastrado com sucesso!\n\n");
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void user_delete(AVL* users, AVL* users_with_messages, linked_list* users_list) {
    
    printf("\nEntre com o nome do usuário que será apagado: ");
    
    string name = get_string();
    
    // apaga o usuario das tres estruturas onde ele pode estar
    LL_delete_with_another_compare(users_list, name, &compare_users_by_name);
    void* had_messages = AVL_delete_with_another_compare(users_with_messages, name, &compare_users_by_name);
    
    // mas salva seu ponteiro para liberar o resto da memoria
    user* deleted_user = (user*) AVL_delete_with_another_compare(users, name, &compare_users_by_name);
    
    if (deleted_user == NULL) {
        printf("\nUsuário não encontrado!\n");
        return;
    }
    
    // libera o nome
    free(deleted_user->name);
    
    // se tiver, libera as mensagens
    if (had_messages != NULL) {
        
        LL_destroy_with_function(&deleted_user->tweets, &message_destroy);
    }
    
    printf("\nUsuário apagado com sucesso!\n");
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void message_destroy(void* message) {
    
    tweet* deleted_tweet = (tweet*) message;
    linked_list L = deleted_tweet->words;
    LL_node* p = NULL;
    
    // percorre a lista encadeada
    for (p = L.head; p != NULL; p = p->next) {
        
        // identifica a palavra
        word* a_word = (word*) p->info;
        
        LL_delete(&a_word->tweets, message);
        a_word->counter--;
        
    }
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void users_with_messages_create(AVL* users_with_messages, linked_list* words, int (*compare)(void*, void*)) {
    
    AVL_create(users_with_messages, compare);
    LL_create(words, &compare_words_by_counter);
    
    printf("\nLista de mensagens inicializada!\n\n");
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void users_post_message(AVL* users, AVL* users_with_messages, linked_list* words, int (*compare)(void*, void*)) {
    
    printf("\nEntre com o nome do usuário: ");
    
    string username = get_string();
    
    // encontra usuario
    user* logged_user = (user*) AVL_search_with_another_compare(users, username, &compare_users_by_name);
    
    // erro se nao encontrou
    if (logged_user == NULL) {
        printf("\nUsuário não cadastrado!\n");
        return;
    }
    
    // checa se o usuario esta na avl de usuarios que postaram mensagens
    user* is_on_users_with_messages = (user*) AVL_search_with_another_compare(users_with_messages, username, &compare_users_by_name);
    
    // se nao estiver, o insere
    if (is_on_users_with_messages == NULL) {
        
        AVL_insert(users_with_messages, logged_user);
        
    }
    
    // cria novo tweet
    tweet* new_tweet = (tweet*) malloc(sizeof(tweet));
    if (new_tweet == NULL) { printf("\nHouve uma falha!\n"); return; }
    
    new_tweet->user_who_posted = logged_user;
    
    // inicializa lista de palavras
    LL_create(&new_tweet->words, compare);
    
    printf("\nEntre com a mensagem: ");
    
    string tweet_text = get_string();
    
    tweet_text = strtok(tweet_text, " \t");
    
    // percorre as palavras
    int i = 0;
    while (tweet_text != NULL && i < 10) {
    
        // cria nova palavra
        word* new_word = (word*) malloc(sizeof(word));
        if (new_word == NULL) { printf("\nHouve uma falha!\n"); return; }
        
        new_word->text = tweet_text;
        
        // checa se palavra ja existe
        word* found_word = (word*) LL_search_with_another_compare(words, tweet_text, &compare_words_by_text);
        
        // se existe
        if (found_word != NULL) {
            
            // libera nova palavra
            free(new_word);
            
            // insere tweet na lista de tweets da palavra
            LL_insert(&found_word->tweets, new_tweet);
            
            // incrementa o contador da palavra
            found_word->counter++;
            
            // mantem a ordenacao da lista
            LL_delete(words, found_word);
            LL_insert_ordered(words, found_word);
            
            // adiciona palavra ao tweet
            LL_insert(&new_tweet->words, found_word);
            
        }
        
        // se nao
        else {
            
            // cria nova palavra
            new_word->counter = 1;
            LL_create(&new_word->tweets, &compare_words_by_counter);
            LL_insert(&new_word->tweets, new_tweet);
            
            // adiciona palavra ao tweet
            LL_insert(&new_tweet->words, new_word);
            
            // isere palavra na lista de palavras
            LL_insert_ordered(words, new_word);
            
            
        }
        
        
        // prossegue para próxima palavra
        tweet_text = strtok(NULL, " ");
        i++;
    }
    
    LL_insert(&logged_user->tweets, new_tweet);
    
    printf("\nMensagem postada!\n");
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void users_delete_message(AVL* users, AVL* users_with_messages, linked_list* words) {
    
    printf("\nEntre com o nome do usuário: ");
    
    string username = get_string();
    
    // encontra usuario
    user* logged_user = (user*) AVL_search_with_another_compare(users_with_messages, username, &compare_users_by_name);
    
    if (logged_user == NULL) {
        
        printf("\nUsuário não postou mensagens, ou não existe\n");
        return;
        
    }
    
    linked_list L = logged_user->tweets;
    LL_node* p = NULL;
    
    printf("\nMensagens de %s:\n\n", username);
    
    // percorre a lista encadeada
    int i;
    for (p = L.head, i = 1; p != NULL; p = p->next, i++) {
        
        tweet* a_tweet = (tweet*) p->info;
        string message_text = message_build_text(a_tweet);
        printf("%d. %s\n", i, message_text);
        
    }
    
    printf("\nEntre com o número da mensagem que deseja apagar: ");
    int message_id = get_int();
    
    tweet* deleted_message = (tweet*) LL_delete_nth_element(&logged_user->tweets, message_id);
    if (deleted_message == NULL) { printf("\nMensagem não encontrada\n"); return; }
    
    message_destroy(deleted_message);
    
    printf("\nMensagem apagada com sucesso!\n");
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void users_print(void* x) {
    
    user* printed_user = (user*) x;
    printf("%s\n", printed_user->name);
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void users_list_by_name(AVL* users) {
    
    printf("\nUsuários em ordem alfabética:\n\n");
    if (users->root == NULL)
        printf("nenhum usuário\n");
    else
        AVL_in_order(users, &users_print);
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void users_list_by_entry(linked_list* users_list) {
    
    printf("\nUsuários em ordem de cadastro:\n\n");
    if (users_list->head == NULL)
        printf("nenhum usuário\n");
    else
        LL_print(users_list, &users_print);
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void users_with_messages_list_by_name(AVL* users_with_messages) {
    
    printf("\nUsuários que postaram mensagens em ordem alfabética:\n\n");
    if (users_with_messages->root == NULL)
        printf("nenhum usuário\n");
    else
        AVL_in_order(users_with_messages, &users_print);
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void users_with_messages_count(AVL* users_with_messages) {
    
    
    int n = AVL_count(users_with_messages);
    printf("\nNúmero de usuários que postaram mensagens: %d\n", n);
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

int messages_counter(void* a_user) {
    
    user* the_user = (user*) a_user;
    return LL_count(&the_user->tweets);
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void users_with_messages_count_messages(AVL* users_with_messages) {
    
    int n = AVL_count_with_function(users_with_messages, &messages_counter);
    printf("\nNúmero de mensagens cadastradas: %d\n", n);
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void word_print_messages(void* a_tweet) {
    
    tweet* the_tweet = (tweet*) a_tweet;
    string tweet_text = message_build_text(the_tweet);
    printf("%s: %s\n", the_tweet->user_who_posted->name, tweet_text);
    
    free(tweet_text);
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void words_find_messages(linked_list* words) {
    
    printf("\nDigite a palavra-chave a buscar: ");
    char* keyword = get_string();
    
    word* word_found = (word*) LL_search_with_another_compare(words, keyword, &compare_words_by_text);
    
    if (word_found == NULL) {
        printf("\nNão foi possível encontrar mensagens com essa palavra-chave\n");
        return;
    }
    
    else
        LL_print(&word_found->tweets, &word_print_messages);
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void words_show_keywords(linked_list* words) {
    
    printf("\nAs três palavras-chave mais mencionadas:\n");
    
    word** keywords = NULL;
    
    int i = 0, tie = 0, counter = 0; int last_word = 0;
    while (i < 3 || tie == 1) {
        
        word* a_word = LL_delete_nth_element(words, 0);
        
        if (a_word == NULL)
            break;
        
        counter++;
        i++;
        keywords = (word**) realloc(keywords, counter*sizeof(word*));
        
        keywords[counter-1] = a_word;
        
        if (a_word->counter == last_word)
            tie = 1;
        else
            tie = 0;
        
        last_word = a_word->counter;
        
    }
    
    for (i = 0; i < counter; i++) {
        
        printf("%d. %s, mencionada %d vezes\n", i + 1, keywords[i]->text, keywords[i]->counter);
        LL_insert_ordered(words, keywords[i]);
        
        
    }
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

typedef struct {
    string name;
    int counter;
} user_with_counter;

int compare_users_by_counter(void* a, void* b) {
    
    user_with_counter* first_user = (user_with_counter*) a;
    user_with_counter* second_user = (user_with_counter*) b;
    
    return first_user->counter - second_user->counter;
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void users_updated_user(AVL* users_with_messages, linked_list* words) {
    
    typedef struct {
        string name;
        int counter;
    } user_with_counter;
    
    linked_list list_of_users;
    LL_create(&list_of_users, &compare_users_by_counter);
    
    word** keywords = NULL;
    
    int i = 0, tie = 0, counter = 0; int last_word = 0;
    while (i < 3 || tie == 1) {
        
        word* a_word = LL_delete_nth_element(words, 0);
        
        if (a_word == NULL)
            break;
        
        counter++;
        i++;
        keywords = (word**) realloc(keywords, counter*sizeof(word*));
        
        keywords[counter-1] = a_word;
        
        if (a_word->counter == last_word)
            tie = 1;
        else
            tie = 0;
        
        last_word = a_word->counter;
        
    }

    for (i = 0; i < counter; i++) {
        
        // percorre a lista encadeada de tweets
        linked_list L = keywords[i]->tweets; LL_node* p;
        for (p = L.head; p != NULL; p = p->next) {
            
            tweet* a_tweet = (tweet*) p->info;
            user* a_user = a_tweet->user_who_posted;
            
            // procura usuario na lista nova
            user_with_counter* user_counter_found = (user_with_counter*) LL_search_with_another_compare(&list_of_users, a_user->name, compare_users_by_name);
            
            // ja esta na lista
            if (user_counter_found != NULL) {
                user_counter_found->counter++;
                LL_delete(&list_of_users, user_counter_found);
                LL_insert_ordered(&list_of_users, user_counter_found);
            }
            
            // ainda nao esta na lista
            else {
                
                user_with_counter* new_user_with_counter = (user_with_counter*) malloc(sizeof(user_with_counter));
                new_user_with_counter->name = a_user->name;
                new_user_with_counter->counter = 1;
                LL_insert(&list_of_users, new_user_with_counter);
            }
        }
    }
    
    user_with_counter* awesome_user = (user_with_counter*) LL_delete_nth_element(&list_of_users, 0);
    printf("\nUsuário mais atualizado: %s\n", awesome_user->name);
    
    LL_destroy_with_function(&list_of_users, &free);
    
}
