#include "_genesis.h"
#include "map.h"

Map*MAP_create(const MapDefinition* mapDef, VDPPlane plane, u16 baseTile) { return 0; }

void MAP_release(Map* map) {}

void MAP_scrollTo(Map* map, u32 x, u32 y) {}

void MAP_scrollToEx(Map* map, u32 x, u32 y, bool forceRedraw) {}

u16 MAP_getMetaTile(Map* map, u16 x, u16 y) { return 0; }

u16 MAP_getTile(Map* map, u16 x, u16 y) { return 0; }

void MAP_getMetaTilemapRect(Map* map, u16 x, u16 y, u16 w, u16 h, u16* dest) {}

void MAP_getTilemapRect(Map* map, u16 x, u16 y, u16 w, u16 h, bool column, u16* dest) {}

void MAP_setDataPatchCallback(Map* map, MapDataPatchCallback *CB) {}

void MAP_overridePlaneSize(Map* map, u16 w, u16 h) {}

