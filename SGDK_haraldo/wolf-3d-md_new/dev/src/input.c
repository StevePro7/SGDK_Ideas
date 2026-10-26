#include "input.h"
#include "vid.h"

u16 in_held, in_pressed;
volatile u16 in_latch;       /* buttons seen at any vblank since the last IN_Update (so short taps are not lost) */
static u16 in_prev;

void IN_Init(void)
{
    JOY_init();
    in_held = in_prev = in_pressed = 0;
}

void IN_Update(void)
{
    u16 j;
    SYS_disableInts();
    j = JOY_readJoypad(JOY_1) | in_latch;
    in_latch = 0;
    SYS_enableInts();
    in_prev = in_held;
    in_held = j;
    in_pressed = j & ~in_prev;
}

boolean IN_AnyKey(void)
{
    IN_Update();
    return (in_pressed & (BUTTON_A | BUTTON_B | BUTTON_C | BUTTON_START)) != 0;
}

void IN_ClearKeys(void)
{
    IN_Update();
    in_pressed = 0;
}

#include "vid.h"

boolean IN_CheckAck(void)
{
    IN_Update();
    return (in_pressed & (BUTTON_A | BUTTON_B | BUTTON_C | BUTTON_START)) != 0;
}

void IN_Ack(void)
{
    IN_ClearKeys();
    while (!IN_CheckAck())
        vid_frame();
}

boolean IN_UserInput(u32 delay)
{
    u32 lasttime = TimeCount;
    IN_ClearKeys();
    do
    {
        vid_frame();
        if (IN_CheckAck())
            return TRUE;
    } while (TimeCount - lasttime < delay);
    return FALSE;
}
