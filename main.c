#include "ncurses.h"

#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>

#include "fire.h"
#include "menu.h"

const char* init(void)
{
  // Init ncurses
  initscr();

  if(noecho() == ERR)
	return "noecho()";

  if(cbreak() == ERR)
	return "cbreak()";
  
  if(keypad(stdscr, TRUE) == ERR)
	return "keypad(stdscr, TRUE)";
  
  if(!has_colors())
    return "terminal does not support colors";
  else{
    if(!can_change_color())
      return "terminal cannot change colors";
    
    else if(start_color() == ERR)
      return "start_color()";
  }

  if(curs_set(0) == ERR)
	return "curs_set(0)";

  // Create the reserved colors
  init_menu_palette();
  init_fire_palette();

  return NULL;
}

// These will come from a config
char* choices[] = {
  "Choice 0",
  "Choice 1",
  "Choice 2",
  "Choice 3",
  "Choice 4",
  "Choice 5",
  "Choice 6",
  "Choice 7",
  "Choice 8",
  "Choice 9",
  "Choice 10",
  "Choice 11",
  "Choice 12",
  "Choice 13",
  "Choice 14",
  "Choice 15",
  "Exit",
  (char *)NULL
};

const char* operations[] = {
  "Select",
  "Exit",
  (char *)NULL
};

const char* loop(char** t_items, const uint8_t t_items_size)
{
  uint width = 0, height = 0;
  get_term_dim(&width, &height);

  uint menu_w = 0, menu_h =0;
  get_term_dim_one_third(&menu_w, &menu_h);
  
  if(width < 100 || height < 40)
	return "terminal to small";

  // Create a new perfectly centered window
  WINDOW* win_menu = newwin(menu_h, menu_w, menu_h, menu_w);
  WINDOW* win_menu_options    = derwin(win_menu, menu_h - 5, menu_w - 4, 2, 2);
  WINDOW* win_menu_operations = derwin(win_menu, 3, menu_w, menu_h - 3, 0);

  // Create the menu with its items
  ITEM** items = create_items(t_items, t_items_size);
  MENU*  menu  = create_menu(win_menu_options, items);

  for(int character = 'X'; character != 'q'; character = getch())
    {
	  switch(character)
		{
		case 'j':
		  menu_driver(menu, REQ_DOWN_ITEM);
		  break;
		  
		case 'k':
		  menu_driver(menu, REQ_UP_ITEM);
		  break;
		}
	  
	  if(isdigit((char)character))
		{
		  const uint8_t integer = (character - 48);
		  menu_driver(menu, REQ_FIRST_ITEM);
		  
		  for(uint8_t index = 0; (index < integer) && (index < 10) && (index < t_items_size); index++)
			menu_driver(menu, REQ_DOWN_ITEM);
		}

	  refresh();
	  draw_shade(menu_w, menu_h, menu_w, menu_h);
	  draw_menu(win_menu, win_menu_options, win_menu_operations, menu_w);
    }

  free_menu_resources(menu, items, t_items_size, win_menu, win_menu_options, win_menu_operations);
  return NULL;
}

int main(int argc, char *argv[])
{
  printf("argcount%d path:%s", argc, argv[0]);

  const char* error = init();
  if(error != NULL)
    {
	  endwin();

	  printf("ERROR in init(): %s\n", error);
      return -1;
    }
  
  error = loop(choices, 16);
  if(error != NULL)
    {
	  endwin();

	  printf("ERROR in loop(): %s\n", error);
      return -2;
    }
  
  endwin();
  return 0;
}
