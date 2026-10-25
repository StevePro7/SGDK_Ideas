#include "_genesis.h"
#include "everdrive.h"

u8 evd_mmcInit() { return 0; }

u8 evd_mmcRdBlock(u32 mmc_addr, u8 *stor) { return 0; }

u8 evd_mmcWrBlock(u32 mmc_addr, u8 *data_ptr) { return 0; }

void evd_eprEraseBlock(u32 rom_addr) {}

void evd_eprProgBlock(u16 *data, u32 rom_addr, u32 len) {}

void evd_init(u16 def_rom_bank, u8 _is_ram_app) {}

