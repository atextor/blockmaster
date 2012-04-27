#include "main.h"

void ReadConfig(char *configfile)
{
 printf("Reading Configfile: %s\n", configfile);

    FILE *cfgFile;
    char buffer[BUFLEN];
    char param[BUFLEN];
    int conf_line = 1;
    int i;

    cfgFile = fopen(configfile, "r");
    if (cfgFile == NULL) {
        printf("*** Could not open Configfile: %s\n", configfile);
        quit(0);
    }

    while(!feof(cfgFile)) {
        conf_line++;
        // get line from file
        fscanf(cfgFile, "%s%[^\n]\n", buffer, param);
        // remove commented and empty lines
        if ((*buffer == COMMENT) || (*buffer == '\r') || (*buffer == '\n')) continue;
        // remove the blank char in param
        for (i=0; i<strlen(param); i++) param[i]=param[i+1];
        // do something with it
        ConfigSetting(buffer, param, conf_line);
    }
}

void ConfigSetting(char *setting, char *param, int line)
{
    int i;
    char string[10];

    // remove the "-"
    if (line == COMMANDLINE)
        if (*setting == '-') for (i=0; i<(strlen(setting)); i++) setting[i]=setting[i+1];

   // graphic settings
   if ( strcmp(setting, "vid_fullscreen") == 0) {
        vid.fullscreen = atoi(param);
        printf ("Setting Fullscreen to %s\n", param);
    } // path settings
    else if ( strcmp(setting, "path_data") == 0) {
        strcpy(path.data, param);
        printf ("Setting Datapath to %s\n", param);
		sprintf(path.levels, "%s%s", path.data, LEVELPATH);
    } // unrecognized option!
    else {
        if (line != COMMANDLINE) {
            sprintf(string,"%d",line);
            printf ("*** Unrecognized Option: '%s' in configfile at line %s ", setting, string);
        } else
            printf ("*** Unrecognized Option: '%s' at commandline", setting);
    }
}
