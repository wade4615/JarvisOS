#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>
#include "kernel.h"

#define VD_COLS (80 * 2)
#define VD_ROWS 25
#define VIDEO_BOTTOM ((VD_ROWS * VD_COLS) - 1)
#define PRINT_BUF_MAX 512

static char *video_mem = (char *)0xb8000;
static size_t cursor_offset = 0;
static uint8_t text_palette = 0x07;
static uint8_t cursor_palette = 0x70;
static int cursor_status = 1;
static const char *base_digits = "0123456789abcdef";
static int escape = 0;
static int esc_value0 = 0;
static int esc_value1 = 0;
static int *esc_value = &esc_value0;
static int esc_default0 = 1;
static int esc_default1 = 1;
static int *esc_default = &esc_default0;
static uint8_t ansi_colours[] = { 0, 4, 2, 6, 1, 5, 3, 7 };

void port_out_b(unsigned short int port,char value){
   asm("outb %%al,%%dx;"
   : //no output data
   :"d"(port),"a"(value)
   );
}

void port_out_w(unsigned short int port,char value){
   asm("outw %%ax,%%dx;"
   : //no output data
   :"d"(port),"a"(value)
   );
}

void port_out_d(unsigned short int port,char value){
   asm("outl %%eax,%%dx;"
   : //no output data
   :"d"(port),"a"(value)
   );
}

void clear_cursor(void) {
    video_mem[cursor_offset + 1] = text_palette;
    return;
}

void draw_cursor(void) {
    if (cursor_status) {
        video_mem[cursor_offset + 1] = cursor_palette;
    }
    return;
}

void text_clear(void) {
    clear_cursor();
    for (size_t i = 0; i < VIDEO_BOTTOM; i += 2) {
        video_mem[i] = ' ';
        video_mem[i + 1] = text_palette;
    }
    cursor_offset = 0;
    draw_cursor();
    return;
}

void init_vga_textmode(void) {
    port_out_b(0x3d4, 0x0a);
    port_out_b(0x3d5, 0x20);
    text_clear();
}

void text_clear_no_move(void) {
    clear_cursor();
    for (size_t i = 0; i < VIDEO_BOTTOM; i += 2) {
        video_mem[i] = ' ';
        video_mem[i + 1] = text_palette;
    }
    draw_cursor();
    return;
}

void text_set_text_palette(uint8_t c) {
    text_palette = c;
    return;
}

uint8_t text_get_text_palette(void) {
    return text_palette;
}

void sgr(void) {
    if (esc_value0 >= 30 && esc_value0 <= 37) {
        uint8_t pal = text_get_text_palette();
        pal = (pal & 0xf0) + ansi_colours[esc_value0 - 30];
        text_set_text_palette(pal);
        return;
    }

    if (esc_value0 >= 40 && esc_value0 <= 47) {
        uint8_t pal = text_get_text_palette();
        pal = (pal & 0x0f) + ansi_colours[esc_value0 - 40] * 0x10;
        text_set_text_palette(pal);
        return;
    }

    return;
}

void scroll(void) {
    // move the text up by one row
    for (size_t i = 0; i <= VIDEO_BOTTOM - VD_COLS; i++)
        video_mem[i] = video_mem[i + VD_COLS];
    // clear the last line of the screen
    for (size_t i = VIDEO_BOTTOM; i > VIDEO_BOTTOM - VD_COLS; i -= 2) {
        video_mem[i] = text_palette;
        video_mem[i - 1] = ' ';
    }
    return;
}

int text_get_cursor_pos_x(void) {
    return (cursor_offset % VD_COLS) / 2;
}

int text_get_cursor_pos_y(void) {
    return cursor_offset / VD_COLS;
}

void text_get_cursor_pos(int *x, int *y) {
    *x = (cursor_offset % VD_COLS) / 2;
    *y = cursor_offset / VD_COLS;
}

void text_set_cursor_pos(int x, int y) {
    clear_cursor();
    cursor_offset = y * VD_COLS + x * 2;
    draw_cursor();
}

void escape_parse(char c) {
    if (c >= '0' && c <= '9') {
        *esc_value *= 10;
        *esc_value += c - '0';
        *esc_default = 0;
        return;
    }

    switch (c) {
        case '[':
            return;
        case ';':
            esc_value = &esc_value1;
            esc_default = &esc_default1;
            return;
        case 'A':
            if (esc_default0)
                esc_value0 = 1;
            if (esc_value0 > text_get_cursor_pos_y())
                esc_value0 = text_get_cursor_pos_y();
            text_set_cursor_pos(text_get_cursor_pos_x(),
                                text_get_cursor_pos_y() - esc_value0);
            break;
        case 'B':
            if (esc_default0)
                esc_value0 = 1;
            if ((text_get_cursor_pos_y() + esc_value0) > (VD_ROWS - 1))
                esc_value0 = (VD_ROWS - 1) - text_get_cursor_pos_y();
            text_set_cursor_pos(text_get_cursor_pos_x(),
                                text_get_cursor_pos_y() + esc_value0);
            break;
        case 'C':
            if (esc_default0)
                esc_value0 = 1;
            if ((text_get_cursor_pos_x() + esc_value0) > (VD_COLS / 2 - 1))
                esc_value0 = (VD_COLS / 2 - 1) - text_get_cursor_pos_x();
            text_set_cursor_pos(text_get_cursor_pos_x() + esc_value0,
                                text_get_cursor_pos_y());
            break;
        case 'D':
            if (esc_default0)
                esc_value0 = 1;
            if (esc_value0 > text_get_cursor_pos_x())
                esc_value0 = text_get_cursor_pos_x();
            text_set_cursor_pos(text_get_cursor_pos_x() - esc_value0,
                                text_get_cursor_pos_y());
            break;
        case 'H':
            esc_value0--;
            esc_value1--;
            if (esc_default0)
                esc_value0 = 0;
            if (esc_default1)
                esc_value1 = 0;
            if (esc_value1 >= (VD_COLS / 2))
                esc_value1 = (VD_COLS / 2) - 1;
            if (esc_value0 >= VD_ROWS)
                esc_value0 = VD_ROWS - 1;
            text_set_cursor_pos(esc_value1, esc_value0);
            break;
        case 'm':
            sgr();
            break;
        case 'J':
            switch (esc_value0) {
                case 2:
                    text_clear_no_move();
                    break;
                default:
                    break;
            }
            break;
        default:
            escape = 0;
            text_putchar('?');
            break;
    }

    esc_value = &esc_value0;
    esc_value0 = 0;
    esc_value1 = 0;
    esc_default = &esc_default0;
    esc_default0 = 1;
    esc_default1 = 1;
    escape = 0;

    return;
}

void text_write(const char *buf, size_t count) {
    for (size_t i = 0; i < count; i++)
        text_putchar(buf[i]);
}

void text_putchar(char c) {
    if (escape) {
        escape_parse(c);
        return;
    }
    switch (c) {
        case 0x00:
            break;
        case 0x1B:
            escape = 1;
            return;
        case '\n':
            if (text_get_cursor_pos_y() == (VD_ROWS - 1)) {
                clear_cursor();
                scroll();
                text_set_cursor_pos(0, (VD_ROWS - 1));
            } else {
                text_set_cursor_pos(0, (text_get_cursor_pos_y() + 1));
            }
            break;
        case '\r':
            text_set_cursor_pos(0, text_get_cursor_pos_y());
            break;
        case '\b':
            if (cursor_offset) {
                clear_cursor();
                cursor_offset -= 2;
                draw_cursor();
            }
            break;
        default:
            clear_cursor();
            video_mem[cursor_offset] = c;
            if (cursor_offset >= (VIDEO_BOTTOM - 1)) {
                scroll();
                cursor_offset = VIDEO_BOTTOM - (VD_COLS - 1);
            } else
                cursor_offset += 2;
            draw_cursor();
    }
    return;
}

void prn_i(char *print_buf, size_t *print_buf_i, int64_t x) {
    int i;
    char buf[20] = {0};

    if (!x) {
        prn_char(print_buf, print_buf_i, '0');
        return;
    }

    int sign = x < 0;
    if (sign) x = -x;

    for (i = 18; x; i--) {
        buf[i] = (x % 10) + 0x30;
        x = x / 10;
    }
    if (sign)
        buf[i] = '-';
    else
        i++;

    prn_str(print_buf, print_buf_i, buf + i);

    return;
}

void prn_ui(char *print_buf, size_t *print_buf_i, uint64_t x) {
    int i;
    char buf[21] = {0};

    if (!x) {
        prn_char(print_buf, print_buf_i, '0');
        return;
    }

    for (i = 19; x; i--) {
        buf[i] = (x % 10) + 0x30;
        x = x / 10;
    }

    i++;
    prn_str(print_buf, print_buf_i, buf + i);

    return;
}

void prn_x(char *print_buf, size_t *print_buf_i, uint64_t x) {
    int i;
    char buf[17] = {0};

    if (!x) {
        prn_str(print_buf, print_buf_i, "0x0");
        return;
    }

    for (i = 15; x; i--) {
        buf[i] = base_digits[(x % 16)];
        x = x / 16;
    }

    i++;
    prn_str(print_buf, print_buf_i, "0x");
    prn_str(print_buf, print_buf_i, buf + i);

    return;
}

void prn_nstr(char *print_buf, size_t *print_buf_i, const char *string, size_t len) {
    size_t i;

    for (i = 0; i < len; i++) {
        if (*print_buf_i == (PRINT_BUF_MAX - 1))
            break;
        print_buf[(*print_buf_i)++] = string[i];
    }

    print_buf[*print_buf_i] = 0;

    return;
}

void prn_str(char *print_buf, size_t *print_buf_i, const char *string) {
    size_t i;

    for (i = 0; string[i]; i++) {
        if (*print_buf_i == (PRINT_BUF_MAX - 1))
            break;
        print_buf[(*print_buf_i)++] = string[i];
    }

    print_buf[*print_buf_i] = 0;

    return;
}

void prn_char(char *print_buf, size_t *print_buf_i, char c) {
    if (*print_buf_i < (PRINT_BUF_MAX - 1)) {
        print_buf[(*print_buf_i)++] = c;
    }

    print_buf[*print_buf_i] = 0;

    return;
}

void print(const char *fmt, ...) {
    va_list args;

    va_start(args, fmt);

    char print_buf[PRINT_BUF_MAX];
    size_t print_buf_i = 0;

    for (;;) {
        while (*fmt && *fmt != '%')
            prn_char(print_buf, &print_buf_i, *fmt++);

        if (!*fmt++)
            goto out;

        switch (*fmt++) {
            case 's': {
                char *str = (char *)va_arg(args, const char *);
                if (!str)
                    prn_str(print_buf, &print_buf_i, "(null)");
                else
                    prn_str(print_buf, &print_buf_i, str); }
                break;
            case 'S': {
                char *str = (char *)va_arg(args, const char *);
                size_t str_len = va_arg(args, size_t);
                if (!str)
                    prn_str(print_buf, &print_buf_i, "(null)");
                else
                    prn_nstr(print_buf, &print_buf_i, str, str_len); }
                break;
            case 'd':
                prn_i(print_buf, &print_buf_i, (int64_t)va_arg(args, int32_t));
                break;
            case 'u':
                prn_ui(print_buf, &print_buf_i, (uint64_t)va_arg(args, uint32_t));
                break;
            case 'x':
                prn_x(print_buf, &print_buf_i, (uint64_t)va_arg(args, uint32_t));
                break;
            case 'D':
                prn_i(print_buf, &print_buf_i, va_arg(args, int64_t));
                break;
            case 'U':
                prn_ui(print_buf, &print_buf_i, va_arg(args, uint64_t));
                break;
            case 'X':
                prn_x(print_buf, &print_buf_i, va_arg(args, uint64_t));
                break;
            case 'c': {
                char c = (char)va_arg(args, int);
                prn_char(print_buf, &print_buf_i, c); }
                break;
            default:
                prn_char(print_buf, &print_buf_i, '?');
                break;
        }
    }

out:
    va_end(args);
    text_write(print_buf, print_buf_i);

#ifdef E9_OUTPUT
    for (size_t i = 0; i < print_buf_i; i++)
        port_out_b(0xe9, print_buf[i]);
#endif

    return;
}

void kernel_entry(unsigned long magic, unsigned long addr) {
	init_vga_textmode();
	print("Welcome to JarvisOS");
}

void kernel_exit() {
	//Clear hardware interrupts (to prevent the next instruction being interrupted) and then "hlt".
	__asm__ __volatile__("cli");
	__asm__ __volatile__("hlt");
	//If that fails, busy loop.
	LOOP: goto LOOP;
}
