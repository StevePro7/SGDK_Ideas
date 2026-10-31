#include "maths.h"

const fix16 trigtab_f16[90 + 1] = { 0 };
const fix32 trigtab_f32[(90 * 4) + 1] = { 0 };
const fix16 log2tab_f16[0x10000] = { 0 };
const fix16 log10tab_f16[0x10000] = { 0 };
const fix16 sqrttab_f16[0x10000] = { 0 };

u32 mulu(u16 op1, u16 op2) { return 0; }

s32 muls(s16 op1, s16 op2) { return 0; }

u16 divu(u32 op1, u16 op2) { return 0; }

s16 divs(s32 op1, s16 op2) { return 0; }

u16 modu(u32 op1, u16 op2) { return 0; }

s16 mods(s32 op1, s16 op2) { return 0; }

u32 divmodu(u32 op1, u16 op2) { return 0; }

s32 divmods(s32 op1, s16 op2) { return 0; }

u32 u16ToBCD(u16 value) { return 0; }

u32 u32ToBCD(u32 value) { return 0; }

u32 getNextPow2(u32 value) { return 0; }

u16 getLog2(u32 value) { return 0; }

u32 getApproximatedDistance(s32 dx, s32 dy) { return 0; }

//u32 getApproximatedDistanceV(V2s32* v) { return 0; }

s16 F16_toInt(fix16 value) { return 0; }

fix32 F16_toFix32(fix16 value) { return 0; }

fastfix16 F16_toFastFix16(fix16 value) { return 0; }

fastfix32 F16_toFastFix32(fix16 value) { return 0; }

fix16 F16_frac(fix16 value) { return 0; }

fix16 F16_int(fix16 value) { return 0; }

fix16 F16_abs(fix16 x) { return 0; }

fix16 F16_round(fix16 value) { return 0; }

s16 F16_toRoundedInt(fix16 value) { return 0; }

fix16 F16_mul(fix16 val1, fix16 val2) { return 0; }

fix16 F16_div(fix16 val1, fix16 val2) { return 0; }

fix16 F16_avg(fix16 val1, fix16 val2) { return 0; }

fix16 F16_log2(fix16 value) { return 0; }

fix16 F16_log10(fix16 value) { return 0; }

fix16 F16_sqrt(fix16 value) { return 0; }

fix16 F16_normalizeAngle(fix16 angle) { return 0; }

fix16 F16_sin(fix16 angle) { return 0; }

fix16 F16_cos(fix16 angle) { return 0; }

fix16 F16_tan(fix16 angle) { return 0; }

fix16 F16_atan(fix16 x) { return 0; }

fix16 F16_atan2(fix16 y, fix16 x) { return 0; }

fix16 sinFix16(u16 value) { return 0; }

fix16 cosFix16(u16 value) { return 0; }

fix16 F16_degreeToRadian(fix16 degree) { return 0; }

fix16 F16_radianToDegree(fix16 radian) { return 0; }

fix16 F16_getAngle(fix16 x1, fix16 y1, fix16 x2, fix16 y2) { return 0; }

void F16_computePosition(fix16 *x2, fix16 *y2, fix16 x1, fix16 y1, fix16 ang, fix16 dist) {}

void F16_computePositionEx(fix16 *x2, fix16 *y2, fix16 x1, fix16 y1, fix16 ang, fix16 dist, fix16 cosMul, fix16 sinMul) {}

s32 F32_toInt(fix32 value) { return 0; }

fix16 F32_toFix16(fix32 value) { return 0; }

fastfix16 F32_toFastFix16(fix32 value) { return 0; }

fastfix32 F32_toFastFix32(fix32 value) { return 0; }

fix32 F32_frac(fix32 value) { return 0; }

fix32 F32_int(fix32 value) { return 0; }

fix32 F32_round(fix32 value) { return 0; }

s32 F32_toRoundedInt(fix32 value) { return 0; }

fix32 F32_mul(fix32 val1, fix32 val2) { return 0; }

fix32 F32_div(fix32 val1, fix32 val2) { return 0; }

fix32 F32_avg(fix32 val1, fix32 val2) { return 0; }

fix32 F32_sin(fix16 angle) { return 0; }

fix32 F32_cos(fix16 angle) { return 0; }

fix32 sinFix32(u16 value) { return 0; }

fix32 cosFix32(u16 value) { return 0; }

s16 FF16_toInt(fastfix16 value) { return 0; }

fix16 FF16_toFix16(fastfix16 value) { return 0; }

fix32 FF16_toFix32(fastfix16 value) { return 0; }

fastfix32 FF16_toFastFix32(fastfix16 value) { return 0; }

fastfix16 FF16_frac(fastfix16 value) { return 0; }

fastfix16 FF16_int(fastfix16 value) { return 0; }

fastfix16 FF16_round(fastfix16 value) { return 0; }

s16 FF16_toRoundedInt(fastfix16 value) { return 0; }

fastfix16 FF16_mul(fastfix16 val1, fastfix16 val2) { return 0; }

fastfix16 FF16_div(fastfix16 val1, fastfix16 val2) { return 0; }

fastfix32 FF32_fromInt(s16 value) { return 0; }

s16 FF32_toInt(fastfix32 value) { return 0; }

fix16 FF32_toFix16(fastfix32 value) { return 0; }

fix32 FF32_toFix32(fastfix32 value) { return 0; }

fastfix16 FF32_toFastFix16(fastfix32 value) { return 0; }

fastfix32 FF32_frac(fastfix32 value) { return 0; }

fastfix32 FF32_int(fastfix32 value) { return 0; }

fastfix32 FF32_round(fastfix32 value) { return 0; }

s32 FF32_toRoundedInt(fastfix32 value) { return 0; }

fastfix32 FF32_mul(fastfix32 val1, fastfix32 val2) { return 0; }

fastfix32 FF32_div(fastfix32 val1, fastfix32 val2) { return 0; }

fastfix32 FF32_getLog2Fast(fastfix32 value) { return 0; }

fix16 V2D_F16_getAngle(V2f16* pt1, V2f16* pt2) { return 0; }

void V2D_F16_computePosition(V2f16* pt, fix16 ang, fix16 dist) {}

void V2D_F16_computePositionEx(V2f16* pt, fix16 ang, fix16 dist, fix16 cosMul, fix16 sinMUl) {}

u32 V2D_S32_getApproximatedDistance(V2s32* v) { return 0; }

