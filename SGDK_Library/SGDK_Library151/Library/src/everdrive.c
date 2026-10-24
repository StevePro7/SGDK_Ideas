#include "everdrive.h"

u16 cfg = 0;


//SD/MMC card initialization. should be run just one times, aer this cart will be ready for work
//will return 0 success
u8 evd_mmcInit()
{
	return 0;
}


//read block (512b) from SD/MMC card. mmc_addr should be multiple to 512
//will return 0 success
u8 evd_mmcRdBlock( u32 mmc_addr, u8 *stor )
{
	return 0;
}


//write block (512b) to SD/MMC card. mmc_addr should be multiple to 512
//will return 0 success
u8 evd_mmcWrBlock( u32 mmc_addr, u8 *data_ptr )
{
	 return 0;
}


//erase flash memry sector(64kb). rom_addr should be multiple to 64k.
//code of this function should be placed in ram because rom memory inaccessible while erase process
//WARNING! this function may damage cart bios if sectors in range 0 - 0x40000 will be erased
void evd_eprEraseBlock( u32 rom_addr )
{
}


//write data to flash memory. len should be multiple to 4.
//each byte of flah memory should be erased before writeing by evd_eprEraseBlock
//code of this function should be placed in ram because rom memory inaccessible while writeing process
//WARNING! this function may damage cart bios if memory will be writen in area 0 - 0x40000
void evd_eprProgBlock( u16 *data, u32 rom_addr, u32 len )
{
}


//everdrive initialization.
//def_rom_bank = 0 if app placed in 0-0x400000 area, 1 if in 0x400000-0x800000 arae
//_is_ram_app = 0 if app assembled for work in rom, 1 if app assembleed for work in ram
void evd_init( u16 def_rom_bank, u8 _is_ram_app )
{
}