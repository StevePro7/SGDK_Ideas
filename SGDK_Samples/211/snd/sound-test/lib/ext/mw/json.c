#include "json.h"

int json_null_terminate(char *json_str, const jsmntok_t *obj_tok, int num_tok) { return 0; }

bool json_is_key(const jsmntok_t *json_tok, int obj_idx, int num_tok) { return 0; }

int json_object_next(const jsmntok_t *obj_tok, int obj_idx, int parent_idx, int num_tok) { return 0; }

int json_key_next(const jsmntok_t *json_tok, int obj_idx, int parent_idx, int num_tok) { return 0; }

int json_key_search(const char *key, const char *json_str, const jsmntok_t *json_tok, int obj_idx, int parent_idx, int num_tok) { return 0; }

int json_bool_get(const char *json_str, const jsmntok_t *json_tok, int obj_idx) { return 0; }

