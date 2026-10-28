#include "maths3D.h"

void M3D_reset(void) {}

void M3D_setLightEnabled(u16 enabled) {}

u16 M3D_getLightEnabled(void) { return 0; }

void M3D_setViewport(u16 w, u16 h) {}

void M3D_setCamDistance(fix16 value) {}

void M3D_setLightXYZ(fix16 x, fix16 y, fix16 z) {}

void M3D_setLight(V3f16* value) {}

void M3D_resetTransform(Transformation3D* t) {}

void M3D_setTransform(Transformation3D* tr, Translation3D* t, Rotation3D *r) {}

void M3D_setTranslation(Transformation3D* t, fix16 x, fix16 y, fix16 z) {}

void M3D_setRotation(Transformation3D* t, fix16 x, fix16 y, fix16 z) {}

void M3D_combineTransform(Transformation3D* left, Transformation3D* right, Transformation3D* result) {}

void M3D_combineTranslationLeft(Translation3D* left, Transformation3D* right, Transformation3D* result) {}

void M3D_combineTranslationRight(Transformation3D* left, Translation3D* right, Transformation3D* result) {}

void M3D_buildMat3D(Transformation3D* t) {}

void M3D_buildMat3DOnly(Transformation3D* t) {}

void M3D_buildMat3DExtras(Transformation3D* t) {}

void M3D_translate(Transformation3D* t, V3f16* vertices, u16 numv) {}

void M3D_rotate(Transformation3D* t, const V3f16* src, V3f16* dest, u16 numv) {}

void M3D_rotateInv(Transformation3D* t, const V3f16* src, V3f16* dest) {}

void M3D_transform(Transformation3D* t, const V3f16* src, V3f16* dest, u16 numv) {}

void M3D_project_f16(const V3f16* src, V2f16* dest, u16 numv) {}

void M3D_project_s16(const V3f16* src, V2s16* dest, u16 numv) {}

