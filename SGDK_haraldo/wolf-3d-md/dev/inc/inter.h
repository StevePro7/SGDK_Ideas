#ifndef INTER_H
#define INTER_H
#include "wl_types.h"
void Inter_FadeToColor(u16 color);
void Inter_GetPsyched(void);
void LevelCompleted(void);
void Victory(void);
void CheckHighScore(s32 score, u16 other);
void DrawHighScores(void);
void ViewScores(void);
void PG13(void);
boolean AttractLoop(void);
void Scores_Defaults(void);
void *Scores_Ptr(void);
u16 Scores_Size(void);
#endif
