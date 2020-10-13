#ifndef _INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_

// Public method.
void engine_input_manager_update();

// Public methods HOLD.
unsigned char engine_input_manager_hold_up();
unsigned char engine_input_manager_hold_down();
unsigned char engine_input_manager_hold_left();
unsigned char engine_input_manager_hold_right();
unsigned char engine_input_manager_hold_buttonA();
unsigned char engine_input_manager_hold_buttonB();
unsigned char engine_input_manager_hold_buttonC();
unsigned char engine_input_manager_hold_buttonStart();

// Public methods MOVE.
unsigned char engine_input_manager_move_up();
unsigned char engine_input_manager_move_down();
unsigned char engine_input_manager_move_left();
unsigned char engine_input_manager_move_right();
unsigned char engine_input_manager_move_buttonA();
unsigned char engine_input_manager_move_buttonB();
unsigned char engine_input_manager_move_buttonC();
unsigned char engine_input_manager_move_buttonStart();

#endif//_INPUT_MANAGER_H_