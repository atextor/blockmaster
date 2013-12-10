#include <stdlib.h>
#include <stdio.h>
#include "main.h"

void LoadLevel(char levelfile[])
{
    char string[80];
    char buffer[BUFLEN];
    char param[BUFLEN];
	FILE *stream;
	int x,y,i;
	
    char levelDir[150];
    char fileToLoad[150];
    strcpy(levelDir, path.levels);
    strcat(levelDir, levelfile);

    // just to make sure
    if (levelDir[strlen(levelDir)] != '/') strcat(levelDir, "/");

    printf("Loading Level: %s\n", levelDir);

	// level structure	
    strcpy(fileToLoad, levelDir);
    strcat(fileToLoad, "level.txt");

	if ( (stream = fopen(fileToLoad, "r")) == NULL) {
        printf ("*** Could not open Levelfile: %s\n", fileToLoad);
        quit(1);
    }

    x=0; y=0;
    while ( !feof(stream) ) {
        if (x >= 50) {
            x=0;
            y++;
        }
        fscanf(stream, "%s", string);
        level.data[x][y]=atoi(string);
        x++;
	}
    fclose(stream);

	// level information
    strcpy(fileToLoad, levelDir);
    strcat(fileToLoad, "infos.txt");

	if ( (stream = fopen(fileToLoad, "r")) == NULL) {
        printf ("*** Could not open Levelfile: %s\n", fileToLoad);
        quit(1);
    }

    while(!feof(stream)) {
        // get line from file
        fscanf(stream, "%s%[^\n]\n", buffer, param);
        // remove commented and empty lines
        if ((*buffer == COMMENT) || (*buffer == '\r') || (*buffer == '\n')) continue;
        // remove the blank char in param
        for (i=0; i<strlen(param); i++) param[i]=param[i+1];
        // do something with it
        LevelInfo(buffer, param);
    }
    fclose(stream);
	
	LoadTheme(level.theme);
}

void LevelInfo(char *info, char *param)
{
    char string1[10];
    char string2[10];

    // general level info
   if ( strcmp(info, "requiredversion") == 0) {
        sprintf(string1, "%d%d%d", VERSION_MAJOR, VERSION_MINOR, VERSION_REV);
        sprintf(string2, "%c%c%c", param[0], param[2], param[3]);
        if (atoi(string1) < atoi(string2)) { 
            printf ("*** Engine Version too old. This Level requires a newer Version: %s\n", param);
            quit(1);
        }
        printf (" Required Version: %s\n", param);
    } else if ( strcmp(info, "authorname") == 0) {
        strcpy(level.author, param);
        printf (" Author: %s\n", param);
    } else if ( strcmp(info, "levelname") == 0) {
        strcpy(level.title, param);
        printf (" Levelname: %s\n", param);
    } else if ( strcmp(info, "shortdesc") == 0) {
        strcpy(level.desc, param);
        printf (" Description: %s\n", param);
    } else if ( strcmp(info, "difficulty") == 0) {
        strcpy(level.difficulty, param);
        printf (" Difficulty: %s\n", param);
    } // player count and coordinates
	else if ( strcmp(info, "playercount") == 0) {
        playerCount = atoi(param);
		if ((playerCount > 3) || (playerCount < 1)) {
			playerCount = 1;
			printf ("*** Playercount out of range (setting to 1)");
		}
        #ifdef _DEBUG        
        printf(" Number of Players: %s\n", param);
        #endif
    } else if ( strcmp(info, "playerstart_x1") == 0) {
        player[0].coord_x = atoi(param);
        #ifdef _DEBUG        
        printf(" Player 1 Start X: %s\n", param);
        #endif
    } else if ( strcmp(info, "playerstart_x2") == 0) {
        player[1].coord_x = atoi(param);
        #ifdef _DEBUG        
        printf(" Player 2 Start X: %s\n", param);
        #endif
    } else if ( strcmp(info, "playerstart_x3") == 0) {
        player[2].coord_x = atoi(param);
        #ifdef _DEBUG        
        printf(" Player 3 Start X: %s\n", param);
        #endif
    } else if ( strcmp(info, "playerstart_y1") == 0) {
        player[0].coord_y = atoi(param);
        #ifdef _DEBUG        
        printf(" Player 1 Start Y: %s\n", param);
        #endif
    } else if ( strcmp(info, "playerstart_y2") == 0) {
        player[1].coord_y = atoi(param);
        #ifdef _DEBUG        
        printf(" Player 2 Start Y: %s\n", param);
        #endif
    } else if ( strcmp(info, "playerstart_y3") == 0) {
        player[2].coord_y = atoi(param);
        #ifdef _DEBUG        
        printf(" Player 3 Start Y: %s\n", param);
        #endif
	} else if ( strcmp(info, "playerdirection_1") == 0) {
		player[0].direction = atoi(param);
		#ifdef _DEBUG
		printf(" Player 1 Direction: %s\n", param);
		#endif
	} else if ( strcmp(info, "playerdirection_2") == 0) {
		player[1].direction = atoi(param);
		#ifdef _DEBUG
		printf(" Player 2 Direction: %s\n", param);
		#endif
	} else if ( strcmp(info, "playerdirection_3") == 0) {
		player[2].direction = atoi(param);
		#ifdef _DEBUG
		printf(" Player 3 Direction: %s\n", param);
		#endif
    } // level messages
    else if ( strcmp(info, "message1") == 0) {
        strcpy(level.message1, param);
        #ifdef _DEBUG
        printf(" Message 1: %s\n", param);
        #endif
    } else if ( strcmp(info, "message2") == 0) {
        strcpy(level.message2, param);
        #ifdef _DEBUG
        printf(" Message 2: %s\n", param);
        #endif
    } else if ( strcmp(info, "message3") == 0) {
        strcpy(level.message3, param);
        #ifdef _DEBUG
        printf(" Message 3: %s\n", param);
        #endif
    } else if ( strcmp(info, "message4") == 0) {
        strcpy(level.message4, param);
        #ifdef _DEBUG
        printf(" Message 4: %s\n", param);
        #endif
    } else if ( strcmp(info, "message5") == 0) {
        strcpy(level.message5, param);
        #ifdef _DEBUG
        printf(" Message 5: %s\n", param);
        #endif
    } // theme
    else if ( strcmp(info, "theme") == 0) {
		strcpy(level.theme, param);
    } // unrecognized info!
    else {
        printf ("*** Unrecognized Levelinfo: %s\n", info);
    }
}
