/* DUNGEON-- MAIN PROGRAM */

/*COPYRIGHT 1980, INFOCOM COMPUTERS AND COMMUNICATIONS, CAMBRIDGE MA. 02142*/
/* ALL RIGHTS RESERVED, COMMERCIAL USAGE STRICTLY PROHIBITED */
/* WRITTEN BY R. M. SUPNIK */

#define EXTERN
#define INIT

#include "funcs.h"
#include "vars.h"

int run_zork_game(void) {
/* 1) INITIALIZE DATA STRUCTURES */
/* 2) PLAY GAME */

    if (init_()) {
	     game_();
	     return 0; /* ok */
    }
    return -1; /* failure */
} /* MAIN__ */
