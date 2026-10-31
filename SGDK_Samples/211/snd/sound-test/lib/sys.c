#include "sys.h"

const ROMHeader rom_header = { 0 };
u32 _stext = 0;
u32 _sdata = 0;
VoidCallback *busErrorCB = NULL;
VoidCallback *addressErrorCB = NULL;
VoidCallback *illegalInstCB = NULL;
VoidCallback *zeroDivideCB = NULL;
VoidCallback *chkInstCB = NULL;
VoidCallback *trapvInstCB = NULL;
VoidCallback *privilegeViolationCB = NULL;
VoidCallback *traceCB = NULL;
VoidCallback *line1x1xCB = NULL;
VoidCallback *errorExceptionCB = NULL;
VoidCallback *intCB = NULL;

void SYS_assertReset(void) {}

void SYS_reset(void) {}

void SYS_hardReset(void) {}

bool SYS_doVBlankProcess(void) { return 0; }

bool SYS_doVBlankProcessEx(VBlankProcessTime processTime) { return 0; }

bool SYS_nextFrame(void) { return 0; }

u16 SYS_getInterruptMaskLevel(void) { return 0; }

void SYS_setInterruptMaskLevel(u16 value) {}

u16 SYS_getAndSetInterruptMaskLevel(u16 value) { return 0; }

void SYS_disableInts(void) {}

void SYS_enableInts(void) {}

void SYS_setVBlankCallback(VoidCallback *CB) {}

void SYS_setVIntCallback(VoidCallback *CB) {}

void SYS_setHIntCallback(VoidCallback *CB) {}

void SYS_setExtIntCallback(VoidCallback *CB) {}

bool SYS_isInVInt(void) { return 0; }

u16 SYS_isNTSC(void) { return 0; }

u16 SYS_isPAL(void) { return 0; }

u32 SYS_getFPS(void) { return 0; }

fix32 SYS_getFPSAsFloat(void) { return 0; }

u16 SYS_getCPULoad(void) { return 0; }

bool SYS_getShowFrameLoad() { return 0; }

void SYS_showFrameLoad(bool mean) {}

void SYS_hideFrameLoad(void) {}

u16 SYS_computeChecksum(void) { return 0; }

bool SYS_isChecksumOk(void) { return 0; }

void SYS_die(char *err, ...) {}

