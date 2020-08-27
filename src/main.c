#include "fire.h"
#include "menu.h"
#include "config.h"

// Macros:
#define ENTER_KEY 10
#define QUIT_KEY 'q'

// Function definitions:
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

  if(!can_change_color())
	return "terminal cannot change colors";
  
  if(start_color() == ERR)
	return "start_color()";

  if(curs_set(0) == ERR)
	return "curs_set(0)";

  // Have getch wait for 100ms for input
  timeout(100);
  
  // Create the reserved colors
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

const char* loop(Items* t_options_items)
{
  //  number_items(t_options_items); useable when config items use mallo
  Dimensions menu_dim = create_menu_dimensions();
  
  Menu menu;
  MenuPositions menu_positions;
  
  create_menu_resources(&menu, &menu_dim, t_options_items);

  int keypress = 'X';
  while(keypress != QUIT_KEY)
    {
	  keypress = getch();
	  
	  menu_handle_keypress(&menu, keypress);

	  if(keypress == ENTER_KEY)
		{
		  menu_positions = menu_handle_enter(&menu);
		  
		  if(menu_positions.m_operations == OPERATIONS_EXIT)
			keypress = QUIT_KEY;
		  
		}
	  
	  if(isdigit((char)keypress))
		menu_handle_number(&menu, char_to_int(keypress), t_options_items->m_size);

	  draw_fire(stdscr);
	  draw_shade(menu.m_win_main, 1);
	  draw_menu(&menu);

	  doupdate();
    }

  free_menu_resources(&menu);
  return NULL;
}

void error_check(const char* t_msg, const char* t_err, k_int t_exit_code)
{
  if(t_err != NULL){
	endwin();
	fprintf(stderr, "%s %s\n", t_msg, t_err);
	exit(t_exit_code);
  }
}

int main(int argc, char *argv[])
{
  const char* error = init();
  error_check("ERROR in init(): %s", error, -1);

  Items items = {choices, 16};

  error = loop(&items);
  error_check("ERROR in loop(): %s", error, -2);

  endwin();
  return 0;
}