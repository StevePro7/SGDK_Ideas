#ifndef INPUT_H
#define INPUT_H
#include "wl_types.h"

void IN_Init(void);
void IN_Update(void);           /* sample the pad(s) once per tic */
extern u16 in_held, in_pressed; /* BUTTON_* masks (Start/Mode included) */
extern volatile u16 in_latch;
boolean IN_AnyKey(void);
void IN_ClearKeys(void);
boolean IN_CheckAck(void);               /* any face/start button pressed since the last call */
void IN_Ack(void);                      /* wait for a button */
boolean IN_UserInput(u32 delay);        /* wait <delay> tics or a button, TRUE if pressed */
#endif
