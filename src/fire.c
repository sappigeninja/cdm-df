#include "fire.h"

// Static variables:
static k_Palette fire_p = {0, 6, 7};

// Function definitions
void init_fire_palette(void)
{
  // fire_p.m_begin is the 0th pair that defaults to the standard terminal bg
  init_pair(1, COLOR_BLACK, COLOR_BLACK); // BLACK
  init_pair(2, COLOR_RED,    COLOR_BLACK);
  init_pair(3, COLOR_RED,    COLOR_RED);
  init_pair(4, COLOR_RED,    COLOR_YELLOW);
  init_pair(5, COLOR_YELLOW, COLOR_YELLOW);
  
  init_pair(fire_p.m_end, COLOR_WHITE, COLOR_WHITE);
}

void spread_fire(Grid* t_grid, k_uint t_x, k_uint t_y)
{
  uint x = 0;
  k_uint offset_x = rand() % 3;
  
  if(t_x > offset_x)
	x = t_x - offset_x;
  
  uint y = 0;
  k_uint offset_y = rand() % 2 + 1;
  
  if(t_y > 1)
	y = t_y - 1;
  
  uint new_color = 0;

  if(CELL(t_grid, x, y) > offset_y)
	new_color = CELL(t_grid, x, y) - offset_y;

  CELL(t_grid, t_x, t_y) = new_color;
}

void draw_fgrid(WINDOW* t_window, const Grid* t_grid)
{ // Converts the value of a fire grid cell to a matching color pair and then draws it
  k_uint w = t_grid->m_w;
  k_uint h = t_grid->m_h;

  for(uint x = 0; x < w; x++)
	for(uint y = 0, fire_y = getmaxy(stdscr); y < h; y++, fire_y--){ 
	  {
		k_uint value = CELL(t_grid, x, y);
		k_uint color = value * fire_p.m_amount / h + fire_p.m_begin;
		
		if(color != 0)
		  {
			wattron(t_window, COLOR_PAIR(color));
			mvwaddch(t_window, fire_y, x, 'X');
			wattroff(t_window, COLOR_PAIR(color));
		  }
	  }
	}
}

void draw_fire(WINDOW* t_window, Grid* t_grid)
{
  k_uint w = t_grid->m_w;
  k_uint h = t_grid->m_h;

  for(uint x = 0; x < w; x++)
	for(uint y = 1; y < h; y++)
	  spread_fire(t_grid, x, y);
  
  draw_fgrid(t_window, t_grid);
  wnoutrefresh(t_window);
}
