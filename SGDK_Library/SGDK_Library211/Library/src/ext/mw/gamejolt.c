#include "_genesis.h"
#include "gamejolt.h"

bool gj_init(const char *endpoint, const char *game_id, const char *private_key, const char *username, const char *user_token, char *reply_buf, uint16_t buf_len, uint16_t tout_frames) { return 0; }

enum gj_error gj_get_error(void) { return 0; }

char *gj_trophies_fetch(bool achieved, const char *trophy_id) { return 0; }

char *gj_trophy_get_next(char *pos, struct gj_trophy *trophy) { return 0; }

bool gj_trophy_add_achieved(const char *trophy_id) { return 0; }

bool gj_trophy_remove_achieved(const char *trophy_id) { return 0; }

const char *gj_trophy_difficulty_str(enum gj_trophy_difficulty difficulty) { return 0; }

bool gj_time(struct gj_time *time) { return 0; }

char *gj_scores_fetch(const char *limit, const char *table_id, const char *guest, const char *better_than, const char *worse_than, bool only_user) { return 0; }

char *gj_score_get_next(char *pos, struct gj_score *score) { return 0; }

char *gj_scores_tables_fetch(void) { return 0; }

char *gj_score_table_get_next(char *pos, struct gj_score_table *score_table) { return 0; }

char *gj_scores_get_rank(const char *sort, const char *table_id) { return 0; }

bool gj_scores_add(const char *score, const char *sort, const char *table_id, const char *guest, const char *extra_data) { return 0; }

bool gj_data_store_set(const char *key, const char *data, bool user_store) { return 0; }

char *gj_data_store_keys_fetch(const char *pattern, bool user_store) { return 0; }

char *gj_data_store_key_next(char *pos, char **key) { return 0; }

char *data_store_fetch(const char *key, bool user_store) { return 0; }

char *gj_data_store_update(const char *key, enum gj_data_store_update_operation operation, const char *value, bool user_store) { return 0; }

bool gj_data_store_remove(const char *key, bool user_store) { return 0; }

bool gj_sessions_open(void) { return 0; }

bool gj_sessions_ping(bool active) { return 0; }

bool gj_sessions_check(const char *username, const char *user_token) { return 0; }

bool gj_sessions_close(void) { return 0; }

char *gj_users_fetch(const char *username, const char *user_id) { return 0; }

char *gj_user_get_next(char *pos, struct gj_user *user) { return 0; }

bool gj_users_auth(void) { return 0; }

char *gj_friends_fetch(void) { return 0; }

char *gj_friend_get_next(char *pos, char **user_id) { return 0; }

char *gj_request(const char **path, uint8_t num_paths, const char **key, const char **value, uint8_t num_kv_pairs, uint32_t *out_len) { return 0; }

