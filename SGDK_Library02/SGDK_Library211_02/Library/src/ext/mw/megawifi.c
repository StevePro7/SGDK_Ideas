#include "megawifi.h"

int16_t mw_init( uint16_t *cmd_buf, uint16_t buf_len ) { return 0; }

void mw_cmd_data_cb_set( lsd_recv_cb cmd_recv_cb ) {}

enum mw_err mw_detect( uint8_t *major, uint8_t *minor, char **variant ) { return 0; }

enum mw_err mw_version_get( uint8_t version[ 3 ], char **variant ) { return 0; }

uint8_t *mw_bssid_get( enum mw_if_type interface_type ) { return 0; }

enum mw_err mw_default_cfg_set( void ) { return 0; }

enum mw_err mw_ap_cfg_set( uint8_t slot, const char *ssid, const char *pass, enum mw_phy_type phy_type ) { return 0; }

enum mw_err mw_ap_cfg_get( uint8_t slot, char **ssid, char **pass, enum mw_phy_type *phy_type ) { return 0; }

enum mw_err mw_ip_cfg_set( uint8_t slot, const struct mw_ip_cfg *ip ) { return 0; }

enum mw_err mw_ip_cfg_get( uint8_t slot, struct mw_ip_cfg **ip ) { return 0; }

enum mw_err mw_wifi_adv_cfg_set( const struct mw_wifi_adv_cfg *wifi ) { return 0; }

struct mw_wifi_adv_cfg *mw_wifi_adv_cfg_get( void ) { return 0; }

enum mw_err mw_cfg_save( void ) { return 0; }

enum mw_err mw_ip_current( struct mw_ip_cfg **ip ) { return 0; }

int16_t mw_ap_scan( enum mw_phy_type phy_type, char **ap_data, uint8_t *aps ) { return 0; }

int16_t mw_ap_fill_next( const char *ap_data, uint16_t pos, struct mw_ap_data *apd, uint16_t data_len ) { return 0; }

enum mw_err mw_ap_assoc( uint8_t slot ) { return 0; }

enum mw_err mw_ap_assoc_wait( int16_t tout_frames ) { return 0; }

enum mw_err mw_def_ap_cfg( uint8_t slot ) { return 0; }

enum mw_err mw_ap_disassoc( void ) { return 0; }

int16_t mw_def_ap_cfg_get( void ) { return 0; }

enum mw_err mw_tcp_connect( uint8_t ch, const char *dst_addr, const char *dst_port, const char *src_port ) { return 0; }

enum mw_err mw_close( uint8_t ch ) { return 0; }

enum mw_err mw_udp_set( uint8_t ch, const char *dst_addr, const char *dst_port, const char *src_port ) { return 0; }

enum mw_err mw_tcp_bind( uint8_t ch, uint16_t port ) { return 0; }

enum mw_err mw_sock_conn_wait( uint8_t ch, int16_t tout_frames ) { return 0; }

enum mw_err mw_recv_sync( uint8_t *ch, char *buf, int16_t *buf_len, int16_t tout_frames ) { return 0; }

enum mw_err mw_send_sync( uint8_t ch, const char *data, uint16_t len, int16_t tout_frames ) { return 0; }

union mw_msg_sys_stat *mw_sys_stat_get( void ) { return 0; }

enum mw_sock_stat mw_sock_stat_get( uint8_t ch ) { return 0; }

enum mw_err mw_sntp_cfg_set( const char *tz_str, const char *server[ 3 ] ) { return 0; }

enum mw_err mw_sntp_cfg_get( char **tz_str, char *server[ 3 ] ) { return 0; }

char *mw_date_time_get( uint32_t dt_bin[ 2 ] ) { return 0; }

enum mw_err mw_flash_id_get( uint8_t *man_id, uint16_t *dev_id ) { return 0; }

enum mw_err mw_flash_sector_erase( uint16_t sect ) { return 0; }

enum mw_err mw_flash_write( uint32_t addr, uint8_t *data, uint16_t data_len ) { return 0; }

uint8_t *mw_flash_read( uint32_t addr, uint16_t data_len ) { return 0; }

enum mw_err mw_gamertag_set( uint8_t slot, const struct mw_gamertag *gamertag ) { return 0; }

struct mw_gamertag *mw_gamertag_get( uint8_t slot ) { return 0; }

enum mw_err mw_log( const char *msg ) { return 0; }

enum mw_err mw_factory_settings( void ) { return 0; }

void mw_power_off( void ) {}

void mw_sleep( int16_t frames ) {}

enum mw_err mw_http_url_set( const char *url ) { return 0; }

enum mw_err mw_http_method_set( enum mw_http_method method ) { return 0; }

enum mw_err mw_http_header_add( const char *key, const char *value ) { return 0; }

enum mw_err mw_http_header_del( const char *key ) { return 0; }

enum mw_err mw_http_open( uint32_t content_len ) { return 0; }

int16_t mw_http_finish( uint32_t *content_len, int16_t tout_frames ) { return 0; }

uint32_t mw_http_cert_query( void ) { return 0; }

enum mw_err mw_http_cert_set( uint32_t cert_hash, const char *cert, uint16_t cert_len ) { return 0; }

int16_t mw_http_cleanup( void ) { return 0; }

char *mw_def_server_get( void ) { return 0; }

enum mw_err mw_def_server_set( const char *server_url ) { return 0; }

uint8_t *mw_hrng_get( uint16_t rnd_len ) { return 0; }

enum mw_err mw_ga_endpoint_set( const char *endpoint, const char *priv_key ) { return 0; }

enum mw_err mw_ga_key_value_add( const char **key, const char **value, uint16_t num_pairs ) { return 0; }

int16_t mw_ga_request( enum mw_http_method method, const char **path, uint8_t num_paths, const char **key, const char **value, uint8_t num_kv_pairs, uint32_t *content_len, int16_t tout_frames ) { return 0; }

enum mw_err mw_fw_list_upgrades( uint8_t page, uint8_t size, uint8_t offset, char **listUpgrades, uint8_t *len, uint8_t *total ) { return 0; }

enum mw_err mw_fw_upgrade( const char *name ) { return 0; }

struct mw_ping_response *mw_ping( const char* domain, u8 retries ) { return 0; }

