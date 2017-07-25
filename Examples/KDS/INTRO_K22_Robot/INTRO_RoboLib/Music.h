/*
 * Music.h
 *
 *  Created on: 07.12.2014
 *      Author: Erich Styger
 */

#ifndef MUSIC_H_
#define MUSIC_H_

#include "CLS1.h" /* shell interface */
/*!
 * \brief Module command line parser
 * \param cmd Pointer to the command
 * \param handled Return value if the command has been handled by parser
 * \param io Shell standard I/O handle
 * \return Error code, ERR_OK if everything is OK
 */
uint8_t MUSIC_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

typedef enum {
  MUSIC_THEME_BREATHING,    /* Darth Vader breathing */
  MUSIC_THEME_DARK_SIDE,    /* you don't know the power of the dark side */
  MUSIC_THEME_FAILED_ME,    /* you have failed me for the last time */
  MUSIC_THEME_DONT_MAKE,    /* don't make me destroy you */
  MUSIC_THEME_COME_BACK,    /* you should not come back */
  MUSIC_THEME_IMPERIAL,     /* imperial theme */
  MUSIC_THEME_GIVEYOURSELF, /* give yourself to the dark side */
  MUSIC_THEME_DAVE,         /* I'm sorry Dave, I can't do that */
  MUSIC_THEME_LASER_LEFT,   /* left laser contact */
  MUSIC_THEME_LASER_RIGHT,  /* right laser contact */
  MUSIC_THEME_LASER_BOTH,   /* both laser contact */
  MUSIC_THEME_LAST /* sentinel, must be last in list! */
} MUSIC_Theme;

/*!
 * \brief Play a theme
 * \param theme Theme to play
 */
void MUSIC_PlayTheme(MUSIC_Theme theme);

/*!
 * \brief Used to find out if we are still playing a song.
 * \return TRUE if playing, FALSE if not.
 */
bool MUSIC_IsPlaying(void);

/*!
 * \brief Starts playing music
 */
void MUSIC_Start(void);

/*!
 * \brief Stops playing music
 */
void MUSIC_Stop(void);

/*!
 * \brief Driver initialization.
 */
void MUSIC_Init(void);

/*!
 * \brief Driver de-initialization.
 */
void MUSIC_Deinit(void);

#endif /* MUSIC_H_ */
