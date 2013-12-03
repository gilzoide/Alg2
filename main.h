//
//  main.h
//  ALGI
//
//  Created by Léo Sampaio on 03/12/13.
//  Copyright (c) 2013 Léo Sampaio. All rights reserved.
//

#ifndef ALGI_main_h
#define ALGI_main_h

#include "AVL.h"
#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef char* string;

typedef struct {
    
    string name;
    linked_list tweets;
    
} user;

typedef struct {
    
    linked_list words;
    user* user_who_posted;
    
} tweet;

typedef struct {
    
    string text;
    linked_list tweets;
    int counter;
    
} word;

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

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

void users_create(AVL* users, linked_list* users_list, int (*compare)(void*, void*));

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

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
