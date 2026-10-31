#include "flash.h"

int16_t flash_init(void) { return 0; }

void flash_deinit(void) {}

const struct flash_chip *flash_metadata_get(void) { return 0; }

uint32_t flash_sector_erase(uint32_t addr) { return 0; }

uint16_t flash_program(uint32_t addr, const uint8_t *data, uint16_t len) { return 0; }

int16_t flash_read(uint32_t addr, uint8_t *data, uint16_t len) { return 0; }

int16_t flash_copy(uint32_t dst, uint32_t src, uint16_t len) { return 0; }

int16_t flash_sector_limits(uint32_t addr, uint32_t *start, uint32_t *next) { return 0; }

