/*! @file main.h @brief Header pra main
 *
 * Contém as funções usadas na main, usando das funções presentes nos TADs AVL.h e linked_list.h
 */
/* * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *  ALG1 - Trabalho 2
 *  AVL.h
 *
 *  Gil Barbosa Reis                    Nº8532248
 *  gil.reis@usp.br
 *
 *  Leonardo Sampaio Ferraz Ribeiro     Nº8532300
 *  leonardo.sampaio.ribeiro@usp.br
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * */


#ifndef ALGI_main_h
#define ALGI_main_h

#include "AVL.h"
#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef char* string;

/*!
 * Cadastro de Usuário
 */
typedef struct {
    
    string name;	/*!< Nome do usuário */
    linked_list tweets;	/*!< Lista encadeada de mensagens */
    
} user;

/*!
 * Mensagem limitada a 10 palavras
 */
typedef struct {
    
    linked_list words;	/*!< Lista encadeada das 10 palavras do tweet */
    user* user_who_posted;	/*!< Ponteiro pro usuário que postou o tweet */
    
} tweet;

/*!
 * Palavras dos tweets
 */
typedef struct {
    
    string text;	/*!< Palavra */
    linked_list tweets;	/*!< Lista encadeada dos tweets em que tal palavra aparece */
    int counter;	/*!< Contador de quantas vezes essa palavra aparece em tweets */
    
} word;

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Função que pega uma _string_ do usuário.
 * 
 * @warning Memória deve ser liberada manualmente com `free()`
 *
 * @return
 * _string_ digitada
 */
string get_string(void);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Função que pega um _int_ do usuário
 * 
 * @note @ref get_int filtra a entrada, de forma que só números inteiros sejam aceitos
 * 
 * @return
 * Inteiro digitado
 */
int get_int(void);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Função que compara dois usuários
 * 
 * @param a
 * Cadastro A
 * 
 * @param b
 * Cadastro B
 * 
 * @return
 * Retorna 0 se nomes dos usuários forem iguais
 */
int compare_users(void* a, void* b);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Função que compara nome de usuário com string
 * 
 * @param a
 * Cadastro
 * 
 * @param b
 * _string_ com o nome
 * 
 * @return
 * Retorna 0 se cadastro tiver o nome dado
 */
int compare_users_by_name(void* a, void* b);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Reconstitui mensagem a partir de um tweet
 * 
 * @param the_tweet
 * tweet a ser reconstruído
 * 
 * @return
 * _string_ correspondente
 */
string message_build_text(tweet* the_tweet);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Função que compara duas mensagens
 * 
 * @param a
 * Mensagem A
 * 
 * @param b
 * Mensagem B
 * 
 * @return
 * Retorna 0 caso mensagens sejam iguais
 */
int compare_messages(void* a, void* b);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Função que compara mensagem com uma string
 * 
 * @param a
 * Mensagem
 * 
 * @param b
 * _string_ a ser comparada
 * 
 * @return
 * Retorna 0 caso mensagens sejam iguais
 */
int compare_messages_by_text(void* a, void* b);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Função que compara uma _string_ com uma palavra (@ref word)
 * 
 * @param a
 * _string_ a ser comparada
 * 
 * @param b
 * Palavra
 * 
 * @return
 * Retorna 0 caso mensagens sejam iguais
 */
int compare_words_by_text(void* a, void* b);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Função que compara a contagem de duas palavras (@ref word::counter)
 * 
 * @param a
 * Palavra A
 * 
 * @param b
 * Palavra B
 * 
 * @return
 * Retorna 0 caso palavras tenham mesmo contador
 */
int compare_words_by_counter(void* a, void* b);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Mostra menu de opções de  @ref funcionalidades para o usuário
 */
void show_menu();



// Funções usadas no 'switch' das opções / / / / / / / /

/*!
 * Inicializa a AVL e lista de usuários
 *
 * @param users
 * AVL de usuários
 *
 * @param users_list
 * Lista dos usuários (em ordem de cadastro)
 *
 * @param compare
 * Função de comparação entre usuários
 * 
 */
void users_create(AVL* users, linked_list* users_list, int (*compare)(void*, void*));

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Adiciona cadastro na AVL de usuários
 *
 * @param users
 * AVL de usuários
 *
 * @param users_list
 * Lista dos usuários (em ordem de cadastro)
 *
 * @param compare_tweets
 * Função de comparação de mensagens
 */
void user_add(AVL* users, linked_list* users_list, int (*compare_tweets)(void*, void*));

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Apaga cadastro da AVL de usuários
 * 
 * @param users
 * AVL de usuários
 * 
 * @param users_with_messages
 * AVL de usuários com mensagens
 * 
 * @param users_list
 * Lista dos usuários (em ordem de cadastro)
 */
void user_delete(AVL* users, AVL* users_with_messages, linked_list* users_list);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Apaga uma mensagem, liberando a memória alocada
 * 
 * @param message
 * tweet a ser apagado
 */
void message_destroy(void* message);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Cria a AVL de mensagens vinculadas aos cadastros
 * 
 * @param users_with_messages
 * AVL a ser criada
 * 
 * @param words
 * Lista de palavras a ser criada
 * 
 * @param compare
 * Função de comparação de cadastros
 */
void users_with_messages_create(AVL* users_with_messages, linked_list* words, int (*compare)(void*, void*));

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Posta mensagem, adicionando novas palavras à lista e atualizando suas contagens  
 * 
 * @param users
 * AVL de cadastros
 * 
 * @param users_with_messages
 * AVL de mensagens vinculadas aos cadastros
 * 
 * @param words
 * Lista de palavras existentes
 * 
 * @param compare
 * Função de comparação de tweets
 */
void users_post_message(AVL* users, AVL* users_with_messages, linked_list* words, int (*compare)(void*, void*));

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Apaga uma mensagem postada, retirando palavras que não mais existem e atualizando suas contagens
 * 
 * @param users
 * AVL de cadastros
 * 
 * @param users_with_messages
 * AVL de mensagens vinculadas aos cadastros
 * 
 * @param words
 * Lista de palavras existentes
 */
void users_delete_message(AVL* users, AVL* users_with_messages, linked_list* words);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Imprime os nomes dos usuários cadastrados, em ordem alfabética
 * 
 * @param users
 * AVL de cadastros
 */
void users_list_by_name(AVL* users);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Imprime os nomes dos usuários cadastrados, em ordem de cadastro
 * 
 * @param users_list
 * Lista de usuários (em ordem de cadastro)
 */
void users_list_by_entry(linked_list* users_list);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Imprime os nomes dos usuários que postaram mensagens, em ordem alfabética
 * 
 * @param users_with_messages
 * AVL de mensagens vinculadas aos cadastros
 */
void users_with_messages_list_by_name(AVL* users_with_messages);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Imprime o número de usuários que postaram mensagens
 * 
 * @param users_with_messages
 * AVL de mensagens vinculadas aos cadastros
 */
void users_with_messages_count(AVL* users_with_messages);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Imprime o número de mensagens postadas
 * 
 * @param users_with_messages
 * AVL de mensagens vinculadas aos cadastros
 */
void users_with_messages_count_messages(AVL* users_with_messages);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Busca mensagens a partir de uma ou mais palavras-chave
 * 
 * @param words
 * Lista de palavras existentes
 */
void words_find_messages(linked_list* words);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Imprime as três palavras-chave mais usadas
 * 
 * @param words
 * Lista de palavras existentes
 */
void words_show_keywords(linked_list* words);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Imprime o nome do usuário mais atualizado
 * 
 * @param users_with_messages
 * AVL de mensagens vinculadas aos cadastros
 * 
 * @param words
 * Lista de palavras existentes
 */
void users_updated_user(AVL* users_with_messages, linked_list* words);

void free_everything(AVL* users, AVL* users_with_messages, linked_list* users_list, linked_list* words);

#endif
