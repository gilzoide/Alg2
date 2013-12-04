/*! @page main Projeto
 * @section description Descrição
 * Sistema de microblog usando árvores binárias de busca balanceadas (@ref AVL).
 *
 * @subsection sistema Como funciona
 * Usuários se cadastram no sistema, e assim podem postar mensagens, as quais são armazenadas no sistema.
 * As mensagens são curtas, limitadas a 10 palavras, no máximo.
 * Um usuário pode postar quantas mensagens quiser e, quando achar conveniente, apagar uma dessas mensagens.
 * Pode-se também, a qualquer momento, procurar em todas as mensagens por palavras-chave utilizadas.
 * Para mais funcionalidades, veja @ref funcionalidades.
 *
 * @subsection funcionalidades Funcionalidades
 * 1. Inicializar/reinicializar cadastro (@ref users_create)
 * 2. Cadastrar usuário	(@ref user_add)
 * 3. Apagar cadastro (@ref user_delete)
 * 4. Inicializar/reinicializar mensagens (@ref users_with_messages_create)
 * 5. Postar uma mensagem (@ref users_post_message)
 * 6. Apagar uma mensagem (@ref users_delete_message)
 * 7. Listar cadastros (ordem alfabética) (@ref users_list_by_name)
 * 8. Listar cadastros (ordem de cadastro) (@ref users_list_by_entry)
 * 9. Listar usuários que postaram mensagens (ordem alfabética)	(@ref users_with_messages_list_by_name)
 * 10. Mostrar número de usuários que postaram mensagens (@ref users_with_messages_count)
 * 11. Mostrar número de mensagens (@ref users_with_messages_count_messages)
 * 12. Buscar mensagem por palavra-chave (@ref words_find_messages)
 * 13. Mostrar 3 palavras-chave mais usadas (@ref words_show_keywords)
 * 14. Mostrar usuário mais utilizado (@ref users_updated_user)
 * 15. Encerrar o sistema										
 *
 */
/*! @file main.h __Header pra main__
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
 * Função que pega uma _string_ do usuário; deve ser liberada a memória manualmente com _free_
 *
 * @return
 * _string_ de entrada do usuário
 */
string get_string(void);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

int get_int(void);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

int compare_users(void*, void*);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

int compare_users_by_name(void*, void*);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

string message_build_text(tweet* the_tweet);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

int compare_messages(void*, void*);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

int compare_messages_by_text(void*, void*);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

int compare_words_by_text(void* a, void* b);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

int compare_words_by_counter(void* a, void* b);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void show_menu();

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

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
 * Adiciona usuário na AVL de usuários
 *
 * @param users
 * AVL de usuários
 *
 * @param users_list
 * Lista dos usuários (em ordem de cadastro)
 *
 * @param compare_tweets
 * Função de comparação de mensagens
 * 
 */
void user_add(AVL* users, linked_list* users_list, int (*compare_tweets)(void*, void*));

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void user_delete(AVL* users, AVL* users_with_messages, linked_list* users_list);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void message_destroy(void* message);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void users_with_messages_create(AVL* users_with_messages, linked_list* words, int (*compare)(void*, void*));

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void users_post_message(AVL* users, AVL* users_with_messages, linked_list* words, int (*compare)(void*, void*));

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void users_delete_message(AVL* users, AVL* users_with_messages, linked_list* words);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void users_list_by_name(AVL* users);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void users_list_by_entry(linked_list* users_list);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void users_with_messages_list_by_name(AVL* users_with_messages);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void users_with_messages_count(AVL* users_with_messages);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void users_with_messages_count_messages(AVL* users_with_messages);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void words_find_messages(linked_list* words);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void words_show_keywords(linked_list* words);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void users_updated_user(AVL* users_with_messages, linked_list* words);

#endif
