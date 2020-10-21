#include "audio_manager.h"

// Global variables.
struct_enemy_object global_enemy_object;

void engine_audio_manager_init()
{
	struct_enemy_object *eo = &global_enemy_object;
	eo->data = 14;
}

int engine_audio_manager_test()
{
	struct_enemy_object *eo = &global_enemy_object;
	return eo->data;
}