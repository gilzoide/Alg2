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
    
} tweet;

typedef struct {
    
    string text;
    int counter;
    
} word;

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

string get_string(void);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

int get_int(void);

#endif
