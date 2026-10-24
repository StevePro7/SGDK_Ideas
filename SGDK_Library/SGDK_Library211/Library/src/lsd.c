#include "lsd.h"

void lsd_init(void) {}

int lsd_ch_enable(uint8_t ch) { return 0; }

int lsd_ch_disable(uint8_t ch) { return 0; }

enum lsd_status lsd_send(uint8_t ch, const char *data, int16_t len, void *ctx, lsd_send_cb send_cb) { return 0; }

enum lsd_status lsd_send_sync(uint8_t ch, const char *data, int16_t len) { return 0; }

enum lsd_status lsd_recv(char *buf, int16_t len, void *ctx, lsd_recv_cb recv_cb) { return 0; }

enum lsd_status lsd_recv_sync(char *buf, uint16_t *len, uint8_t *ch) { return 0; }

void lsd_process(void) {}

void lsd_line_sync(void) {}

