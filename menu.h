#ifndef WINDOW_H
#define WINDOW_H

#include <menu.h>
#include <ncurses.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/ioctl.h>

// Macros:
#define DIALOG_PRIMARY 16
#define DIALOG_SECONDARY 17

#define DIALOG_SELECTED 16
#define DIALOG_UNSELECTED 17

#define OPERATIONS_SIZE 2

// Typedefs:
typedef unsigned int uint;
typedef const uint k_uint;

typedef const uint8_t k_uint8_t;
typedef const uint16_t k_uint16_t;

typedef struct
{
  
  
} Dimensions;

typedef struct
{ // Wrap all the resources together
  WINDOW* m_win_main, *m_win_options, *m_win_operations;
  
  ITEM**  m_items_options, **m_items_operations;
  MENU*   m_menu_options,   *m_menu_operations;

  uint8_t m_options_size;
} Menu;

// Function declarations:
void init_menu_palette(void);

// Should be places elsewhere? utilities.h/c?
void get_term_dim(uint* t_width, uint* t_height);
void get_term_dim_one_third(uint* t_width, uint* t_height);
  
void number_items(char** t_items, k_uint8_t t_items_size);

void create_menu_resources(Menu* t_menu, k_uint t_x, k_uint t_y, k_uint t_w, k_uint t_h, char* t_items[], k_uint8_t t_items_size);

ITEM** create_items(char* t_items[], k_uint8_t t_items_size);

MENU* create_menu_options(WINDOW* t_window, ITEM** t_items);
MENU* create_menu_operations(WINDOW* t_window, ITEM** t_items);

void draw_shade(WINDOW* t_window);
void draw_menu(Menu* t_menu);

void free_items(ITEM** t_items, k_uint8_t t_items_size);
void free_menu_resources(Menu* t_menu);

#endif
