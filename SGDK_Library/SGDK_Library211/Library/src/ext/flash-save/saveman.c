#include "saveman.h"

int16_t sm_init(uint8_t num_slots, uint32_t max_length_restrict) { return 0; }

void sm_deinit(void) {}

int16_t sm_load(uint8_t slot, void *save_data, uint16_t len) { return 0; }

int16_t sm_save(uint8_t slot, const void *save_data, uint16_t len) { return 0; }

int16_t sm_delete(uint8_t slot) { return 0; }

int16_t sm_clear(uint8_t num_slots) { return 0; }

