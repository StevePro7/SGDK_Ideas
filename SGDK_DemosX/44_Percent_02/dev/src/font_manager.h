#ifndef __FONT_MANAGER_H__
#define __FONT_MANAGER_H__

void engine_font_manager_clear( unsigned short x, unsigned short y, unsigned short w );
void engine_font_manager_data( unsigned short value, unsigned short x, unsigned short y );
void engine_font_manager_zero( unsigned short value, unsigned short x, unsigned short y );
void engine_font_manager_char( const char ch, unsigned short x, unsigned short y );
void engine_font_manager_text( const char *str, unsigned short x, unsigned short y );

#endif//__FONT_MANAGER_H__