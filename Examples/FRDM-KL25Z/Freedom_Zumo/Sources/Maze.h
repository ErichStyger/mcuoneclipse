/*
 * Maze.h
 *
 *  Created on: Mar 11, 2013
 *      Author: Erich Styger
 */

#ifndef MAZE_H_
#define MAZE_H_

#include "Turn.h"
#include "CLS1.h"

void MAZE_AddPath(TURN_Kind kind);

void MAZE_SimplifyPath(void);

bool MAZE_IsSolved(void);
void MAZE_SetSolved(void);

/**
 * \brief reverts the path 
 */
void MAZE_RevertPath(void);

TURN_Kind MAZE_GetSolvedTurn(uint8_t *solvedIdx);
void MAZE_ClearSolution(void);

/*!
 * \brief Selects the new turn based on left-or-right hand rule.
 * \param prev Line previous the intersection
 * \param curr Line kind of the intersection.
 * \return The new turn.
 */
TURN_Kind MAZE_SelectTurn(REF_LineKind prev, REF_LineKind curr);

uint8_t MAZE_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

void MAZE_Init(void);


#endif /* MAZE_H_ */
