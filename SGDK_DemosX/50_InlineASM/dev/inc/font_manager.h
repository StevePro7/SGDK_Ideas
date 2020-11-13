#ifndef _FONT_MANAGER_H_
#define _FONT_MANAGER_H_

void engine_font_manager_clear( unsigned short x, unsigned short y, unsigned short w );
void engine_font_manager_data( unsigned short value, unsigned short x, unsigned short y );
void engine_font_manager_char( const char ch, unsigned short x, unsigned short y );
void engine_font_manager_text( const char *str, unsigned short x, unsigned short y );

#endif//_FONT_MANAGER_H_