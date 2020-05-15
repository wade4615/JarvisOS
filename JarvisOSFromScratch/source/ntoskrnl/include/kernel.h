/*
 * kernel.h
 *
 *  Created on: May 15, 2020
 *      Author: wade4
 */

#ifndef SOURCE_NTOSKRNL_INCLUDE_KERNEL_H_
#define SOURCE_NTOSKRNL_INCLUDE_KERNEL_H_

void port_out_b(unsigned short int port,char value);
void port_out_w(unsigned short int port,char value);
void port_out_d(unsigned short int port,char value);
void clear_cursor(void);
void draw_cursor(void);
void text_clear(void);
void init_vga_textmode(void);
void text_clear(void);
void text_clear_no_move(void);
void text_set_text_palette(uint8_t c);
uint8_t text_get_text_palette(void);
void sgr(void);
void scroll(void);
void text_clear(void);
int text_get_cursor_pos_x(void);
int text_get_cursor_pos_y(void);
void text_get_cursor_pos(int *x, int *y);
void text_set_cursor_pos(int x, int y);
void escape_parse(char c);
void text_write(const char *buf, size_t count);
void text_putchar(char c);
void prn_i(char *print_buf, size_t *print_buf_i, int64_t x);
void prn_ui(char *print_buf, size_t *print_buf_i, uint64_t x);
void prn_x(char *print_buf, size_t *print_buf_i, uint64_t x);
void prn_nstr(char *print_buf, size_t *print_buf_i, const char *string, size_t len);
void prn_str(char *print_buf, size_t *print_buf_i, const char *string);
void prn_char(char *print_buf, size_t *print_buf_i, char c);
void print(const char *fmt, ...);
void kernel_entry(unsigned long magic, unsigned long addr);
void kernel_exit();


#endif /* SOURCE_NTOSKRNL_INCLUDE_KERNEL_H_ */
