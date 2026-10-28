#include "_genesis.h"
#include "vdp_tile.h"

u16 VDP_getPlaneAddress(VDPPlane plane, u16 x, u16 y) { return 0; }

void VDP_loadTileData(const u32 *data, u16 index, u16 num, TransferMethod tm) {}

u16 VDP_loadTileSet(const TileSet *tileset, u16 index, TransferMethod tm) { return 0; }

void VDP_loadFontData(const u32 *font, u16 length, TransferMethod tm) {}

u16 VDP_loadFont(const TileSet *font, TransferMethod tm) { return 0; }

void VDP_loadBMPTileData(const u32 *data, u16 index, u16 w, u16 h, u16 bmp_w) {}

void VDP_loadBMPTileDataEx(const u32 *data, u16 index, u16 x, u16 y, u16 w, u16 h, u16 bmp_w) {}

void VDP_fillTileData(u8 value, u16 index, u16 num, bool wait) {}

void VDP_clearTileMap(u16 planeAddr, u16 ind, u16 num, bool wait) {}

void VDP_fillTileMap(u16 planeAddr, u16 tile, u16 ind, u16 num) {}

void VDP_setTileMapData(u16 planeAddr, const u16 *data, u16 ind, u16 num, u16 vramStep, TransferMethod tm) {}

void VDP_setTileMapDataEx(u16 planeAddr, const u16 *data, u16 basetile, u16 ind, u16 num, u16 vramStep) {}

void VDP_setTileMapXY(VDPPlane plane, u16 tile, u16 x, u16 y) {}

void VDP_clearTileMapRect(VDPPlane plane, u16 x, u16 y, u16 w, u16 h) {}

void VDP_fillTileMapRect(VDPPlane plane, u16 tile, u16 x, u16 y, u16 w, u16 h) {}

void VDP_fillTileMapRectInc(VDPPlane plane, u16 basetile, u16 x, u16 y, u16 w, u16 h) {}

void VDP_setTileMapDataRect(VDPPlane plane, const u16 *data, u16 x, u16 y, u16 w, u16 h, u16 wm, TransferMethod tm) {}

void VDP_setTileMapDataRectEx(VDPPlane plane, const u16 *data, u16 basetile, u16 x, u16 y, u16 w, u16 h, u16 wm, TransferMethod tm) {}

void VDP_setTileMapDataRow(VDPPlane plane, const u16 *data, u16 row, u16 x, u16 w, TransferMethod tm) {}

void VDP_setTileMapDataRowEx(VDPPlane plane, const u16 *data, u16 basetile, u16 row, u16 x, u16 w, TransferMethod tm) {}

void VDP_setTileMapDataColumnFast(VDPPlane plane, u16* data, u16 column, u16 y, u16 h, TransferMethod tm) {}

void VDP_setTileMapDataColumn(VDPPlane plane, const u16 *data, u16 column, u16 y, u16 h, u16 wm, TransferMethod tm) {}

void VDP_setTileMapDataColumnEx(VDPPlane plane, const u16 *data, u16 basetile, u16 column, u16 y, u16 h, u16 wm, TransferMethod tm) {}

bool VDP_setTileMap(VDPPlane plane, const TileMap *tilemap, u16 x, u16 y, u16 w, u16 h, TransferMethod tm) { return 0; }

bool VDP_setTileMapEx(VDPPlane plane, const TileMap *tilemap, u16 basetile, u16 xp, u16 yp, u16 x, u16 y, u16 w, u16 h, TransferMethod tm) { return 0; }

bool VDP_setTileMapRow(VDPPlane plane, const TileMap *tilemap, u16 row, u16 x, u16 w, TransferMethod tm) { return 0; }

bool VDP_setTileMapRowEx(VDPPlane plane, const TileMap *tilemap, u16 basetile, u16 row, u16 x, u16 y, u16 w, TransferMethod tm) { return 0; }

bool VDP_setTileMapColumn(VDPPlane plane, const TileMap *tilemap, u16 column, u16 y, u16 h, TransferMethod tm) { return 0; }

bool VDP_setTileMapColumnEx(VDPPlane plane, const TileMap *tilemap, u16 basetile, u16 column, u16 x, u16 y, u16 h, TransferMethod tm) { return 0; }

bool VDP_setMap(VDPPlane plane, const TileMap *tilemap, u16 basetile, u16 x, u16 y) { return 0; }

bool VDP_setMapEx(VDPPlane plane, const TileMap *tilemap, u16 basetile, u16 x, u16 y, u16 xm, u16 ym, u16 wm, u16 hm) { return 0; }

