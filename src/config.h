#ifndef CONFIG_H
#define CONFIG_H

#include <libconfig.h>

#include <ctype.h>
#include <limits.h>
#include <pwd.h>
#include <dirent.h>
#include <errno.h>

#include "utils.h"

// Macros:
#define MAX_CONFIG_VAR_SIZE 32

// Struct definitions:
typedef struct {
  uint8 m_animation;
  
  char* m_options[MAX_CONFIG_VAR_SIZE]; 
  uint8 m_options_size;

  char* m_commands[MAX_CONFIG_VAR_SIZE];
  uint8 m_commands_size;
  
} Config;

// Function declarations:
void get_config_dir(char* t_cfg_dir, char* t_buffer);

void parse_config(Config* t_config, config_t* t_cfg);
  
void free_config(config_t* t_cfg);

bool create_Config(Config* t_cfg, char* t_dir);

void destroy_Config(Config* t_config);

#endif
