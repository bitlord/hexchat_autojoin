/* joinmychannels.c */
/* 
 * AUTHOR: Branko Grubic 
 * LICENSE: GPLv2
 * COMPILE_COMMAND: gcc -Wl,--export-dynamic -Wall -O1 -shared -fPIC 
 * -DCONFFILEPATH='"/.config/hexchat/addon_joinmychannels.conf"'
 * joinmychannels.c -o joinmychannels.so
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hexchat-plugin.h"

#define PNAME "JoinMyChannels"
#define PDESC "Joins multiple predefined channels read from a config file"
#define PVERSION "0.2"

/* 
 * Define default if not provided via commandline during compile
 * path to a configfile relative to users $HOME 
 */
#ifndef CONFFILEPATH
#define CONFFILEPATH "/.config/hexchat/addon_joinmychannels.conf"
#endif

static hexchat_plugin *ph;

void hexchat_plugin_get_info(char **name,
			   char **desc, 
			   char **version,
			   void **reserverd)
{
  *name = PNAME;
  *desc = PDESC;
  *version = PVERSION;
}

/* joinchannel callback function */
static int joinmychannels_cb(char *word[], 
			     char *word_eol[], 
			     void *userdata)
{
  char *homedir = NULL;
  char *conffile = NULL;
  
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;


  /* Get HOME environment variable */
  homedir = getenv("HOME");
  if (homedir) {
    conffile = malloc(strlen(homedir) + strlen(CONFFILEPATH) + 1);
    if (conffile == NULL) {
        /* failed to allocate memory for conffile path */
        hexchat_print(ph, "JoinMyChannels: Error while allocating memory!\n");
        free(conffile);
        return HEXCHAT_EAT_ALL;
     }
   /* make conffile path based on HOME env variable */
   strcpy(conffile, homedir);
   strcat(conffile, CONFFILEPATH);
   *(conffile+strlen(conffile)) = '\0';
   
   fp = fopen(conffile, "r");
   free(conffile);
   if (fp == NULL) {
     hexchat_print(ph, "JoinMyChannels: Error loading config file!\n");
     return HEXCHAT_EAT_ALL;
   }
  
   while ((nread = getline(&line, &len, fp)) != -1) {
     /* replace a new line with NULL byte ("shift NULL byte over \n") */
     *(line + strlen(line) - 1) = '\0';
     hexchat_commandf(ph, "JOIN %s", line);
   }
  
   free(line);
   fclose(fp);
   
   return HEXCHAT_EAT_ALL;
  }
  else {
    hexchat_print(ph, "JoinMyChannels: Error compiling config file path!\n");
    return HEXCHAT_EAT_ALL;
  }
}


int hexchat_plugin_init(hexchat_plugin *plugin_handle,
		      char **plugin_name,
		      char **plugin_desc,
		      char **plugin_version,
		      char **arg)
{
  /* we need to save this to use with any xchat_* function */
  ph = plugin_handle;

  /* tell xchat our info */
  *plugin_name = PNAME;
  *plugin_desc = PDESC;
  *plugin_version = PVERSION;

  hexchat_hook_command(ph, "JoinMyChannels", HEXCHAT_PRI_NORM, joinmychannels_cb, 
		     "Usage: JoinMyChannels, Join channels in predefined list",
		     0);

  hexchat_print(ph, "JoinMyChannels loaded\n");
  
  return 1; /* return 1 for success */
}
