#include <assert.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <termbox.h>
#include "test.h"

#define draw_screen() draw_test()
//#define draw_screen() draw_keyboard()

void print_tb(const char *str, int x, int y, uint16_t fg, uint16_t bg)
{
	while (*str) {
		uint32_t uni;
		str += tb_utf8_char_to_unicode(&uni, str);
		tb_change_cell(x, y, uni, fg, bg);
		x++;
	}
}

void printf_tb(int x, int y, uint16_t fg, uint16_t bg, const char *fmt, ...)
{
	char buf[4096];
	va_list vl;
	va_start(vl, fmt);
	vsnprintf(buf, sizeof(buf), fmt, vl);
	va_end(vl);
	print_tb(buf, x, y, fg, bg);
}

void draw_key(struct key *k, uint16_t fg, uint16_t bg)
{
	while (k->x) {
		tb_change_cell(k->x+2, k->y+4, k->ch, fg, bg);
		k++;
	}
}

int new_frame(int x, int y, int width, int heigth)
{
    int i;

	tb_change_cell(x + 0    , y + 0,        0x250C, TB_WHITE, TB_DEFAULT);
	tb_change_cell(x + width, y,            0x2510, TB_WHITE, TB_DEFAULT);
	tb_change_cell(x,         y + heigth,   0x2514, TB_WHITE, TB_DEFAULT);
	tb_change_cell(x + width, y + heigth,   0x2518, TB_WHITE, TB_DEFAULT);

	for (i = x+1; i < x + width; ++i) {
		tb_change_cell(i, y+0, 0x2500, TB_WHITE, TB_DEFAULT);
		tb_change_cell(i, y+heigth, 0x2500, TB_WHITE, TB_DEFAULT);
	}
	for (i = y+1; i < y + heigth; ++i) {
		tb_change_cell(x+0, i, 0x2502, TB_WHITE, TB_DEFAULT);
		tb_change_cell(x+width, i, 0x2502, TB_WHITE, TB_DEFAULT);
	}
}

void draw_test()
{
	int i;
    new_frame(0, 0, 80, 12);
    new_frame(0, 12, 80, 5);
//	tb_change_cell(0, 0, 0x250C, TB_WHITE, TB_DEFAULT);
//	tb_change_cell(79, 0, 0x2510, TB_WHITE, TB_DEFAULT);
//	tb_change_cell(0, 23, 0x2514, TB_WHITE, TB_DEFAULT);
//	tb_change_cell(79, 23, 0x2518, TB_WHITE, TB_DEFAULT);

//	for (i = 1; i < 79; ++i) {
//		tb_change_cell(i, 0, 0x2500, TB_WHITE, TB_DEFAULT);
//		tb_change_cell(i, 23, 0x2500, TB_WHITE, TB_DEFAULT);
//		tb_change_cell(i, 17, 0x2500, TB_WHITE, TB_DEFAULT);
//		tb_change_cell(i, 4, 0x2500, TB_WHITE, TB_DEFAULT);
//	}
//	for (i = 1; i < 23; ++i) {
//		tb_change_cell(0, i, 0x2502, TB_WHITE, TB_DEFAULT);
//		tb_change_cell(79, i, 0x2502, TB_WHITE, TB_DEFAULT);
//	}
//	tb_change_cell(0, 17, 0x251C, TB_WHITE, TB_DEFAULT);
//	tb_change_cell(79, 17, 0x2524, TB_WHITE, TB_DEFAULT);
//	tb_change_cell(0, 4, 0x251C, TB_WHITE, TB_DEFAULT);
//	tb_change_cell(79, 4, 0x2524, TB_WHITE, TB_DEFAULT);
//	for (i = 5; i < 17; ++i) {
//		tb_change_cell(1, i, 0x2588, TB_YELLOW, TB_YELLOW);
//		tb_change_cell(78, i, 0x2588, TB_YELLOW, TB_YELLOW);
//	}
//
//	draw_key(K_ESC, TB_WHITE, TB_BLUE);
//	draw_key(K_K_PERIOD, TB_WHITE, TB_BLUE);
//
//	printf_tb(33, 1, TB_MAGENTA | TB_BOLD, TB_DEFAULT, "Test demo!");
//	printf_tb(21, 2, TB_MAGENTA, TB_DEFAULT, "(press CTRL+X and then CTRL+Q to exit)");
//	printf_tb(15, 38, TB_MAGENTA, TB_DEFAULT, "(press CTRL+X and then CTRL+C to change input mode)");
//
//	int inputmode = tb_select_input_mode(0);
//	char inputmode_str[64];
//
//	if (inputmode & TB_INPUT_ESC)
//		sprintf(inputmode_str, "TB_INPUT_ESC");
//	if (inputmode & TB_INPUT_ALT)
//		sprintf(inputmode_str, "TB_INPUT_ALT");
//
//	if (inputmode & TB_INPUT_MOUSE)
//		sprintf(inputmode_str, "%s | TB_INPUT_MOUSE", inputmode_str);
//
//	printf_tb(3, 18, TB_WHITE, TB_DEFAULT, "Input mode: %s", inputmode_str);
}

const char *funckeymap(int k)
{
	static const char *fcmap[] = {
		"CTRL+2, CTRL+~",
		"CTRL+A",
		"CTRL+B",
		"CTRL+C",
		"CTRL+D",
		"CTRL+E",
		"CTRL+F",
		"CTRL+G",
		"CTRL+H, BACKSPACE",
		"CTRL+I, TAB",
		"CTRL+J",
		"CTRL+K",
		"CTRL+L",
		"CTRL+M, ENTER",
		"CTRL+N",
		"CTRL+O",
		"CTRL+P",
		"CTRL+Q",
		"CTRL+R",
		"CTRL+S",
		"CTRL+T",
		"CTRL+U",
		"CTRL+V",
		"CTRL+W",
		"CTRL+X",
		"CTRL+Y",
		"CTRL+Z",
		"CTRL+3, ESC, CTRL+[",
		"CTRL+4, CTRL+\\",
		"CTRL+5, CTRL+]",
		"CTRL+6",
		"CTRL+7, CTRL+/, CTRL+_",
		"SPACE"
	};
	static const char *fkmap[] = {
		"F1",
		"F2",
		"F3",
		"F4",
		"F5",
		"F6",
		"F7",
		"F8",
		"F9",
		"F10",
		"F11",
		"F12",
		"INSERT",
		"DELETE",
		"HOME",
		"END",
		"PGUP",
		"PGDN",
		"ARROW UP",
		"ARROW DOWN",
		"ARROW LEFT",
		"ARROW RIGHT"
	};

	if (k == TB_KEY_CTRL_8)
		return "CTRL+8, BACKSPACE 2"; /* 0x7F */
	else if (k >= TB_KEY_ARROW_RIGHT && k <= 0xFFFF)
		return fkmap[0xFFFF-k];
	else if (k <= TB_KEY_SPACE)
		return fcmap[k];
	return "UNKNOWN";
}

void pretty_print_press(struct tb_event *ev)
{
	char buf[7];
	buf[tb_utf8_unicode_to_char(buf, ev->ch)] = '\0';
	printf_tb(3, 19, TB_WHITE , TB_DEFAULT, "Key: ");
	printf_tb(8, 19, TB_YELLOW, TB_DEFAULT, "decimal: %d", ev->key);
	printf_tb(8, 20, TB_GREEN , TB_DEFAULT, "hex:     0x%X", ev->key);
	printf_tb(8, 21, TB_CYAN  , TB_DEFAULT, "octal:   0%o", ev->key);
	printf_tb(8, 22, TB_RED   , TB_DEFAULT, "string:  %s", funckeymap(ev->key));

	printf_tb(54, 19, TB_WHITE , TB_DEFAULT, "Char: ");
	printf_tb(60, 19, TB_YELLOW, TB_DEFAULT, "decimal: %d", ev->ch);
	printf_tb(60, 20, TB_GREEN , TB_DEFAULT, "hex:     0x%X", ev->ch);
	printf_tb(60, 21, TB_CYAN  , TB_DEFAULT, "octal:   0%o", ev->ch);
	printf_tb(60, 22, TB_RED   , TB_DEFAULT, "string:  %s", buf);

	printf_tb(54, 18, TB_WHITE, TB_DEFAULT, "Modifier: %s",
			(ev->mod) ? "TB_MOD_ALT" : "none");

}

void pretty_print_resize(struct tb_event *ev)
{
	printf_tb(3, 19, TB_WHITE, TB_DEFAULT, "Resize event: %d x %d", ev->w, ev->h);
}

int counter = 0;

void  pretty_print_mouse(struct tb_event *ev) {
	printf_tb(3, 19, TB_WHITE, TB_DEFAULT, "Mouse event: %d x %d", ev->x, ev->y);
	char *btn = "";
	switch (ev->key) {
	case TB_KEY_MOUSE_LEFT:
		btn = "MouseLeft: %d";
		break;
	case TB_KEY_MOUSE_MIDDLE:
		btn = "MouseMiddle: %d";
		break;
	case TB_KEY_MOUSE_RIGHT:
		btn = "MouseRight: %d";
		break;
	case TB_KEY_MOUSE_WHEEL_UP:
		btn = "MouseWheelUp: %d";
		break;
	case TB_KEY_MOUSE_WHEEL_DOWN:
		btn = "MouseWheelDown: %d";
		break;
	case TB_KEY_MOUSE_RELEASE:
		btn = "MouseRelease: %d";
	}
	counter++;
	printf_tb(43, 19, TB_WHITE, TB_DEFAULT, "Key: ");
	printf_tb(48, 19, TB_YELLOW, TB_DEFAULT, btn, counter);
}

void dispatch_press(struct tb_event *ev)
{
	if (ev->mod & TB_MOD_ALT) {
		draw_key(K_LALT, TB_WHITE, TB_RED);
		draw_key(K_RALT, TB_WHITE, TB_RED);
	}

	struct combo *k = 0;
	if (ev->key >= TB_KEY_ARROW_RIGHT)
		k = &func_combos[0xFFFF-ev->key];
	else if (ev->ch < 128) {
		if (ev->ch == 0 && ev->key < 128)
			k = &combos[ev->key];
		else
			k = &combos[ev->ch];
	}
	if (!k)
		return;

	struct key **keys = k->keys;
	while (*keys) {
		draw_key(*keys, TB_WHITE, TB_RED);
		keys++;
	}
}

int main(int argc, char **argv)
{
	(void) argc; (void) argv;
	int ret;

	ret = tb_init();
	if (ret) {
		fprintf(stderr, "tb_init() failed with error code %d\n", ret);
		return 1;
	}

	tb_select_input_mode(TB_INPUT_ESC | TB_INPUT_MOUSE);
	struct tb_event ev;

	tb_clear();
	draw_screen();
	tb_present();
	int inputmode = 0;
	int ctrlxpressed = 0;

	while (tb_poll_event(&ev)) {
		switch (ev.type) {
		case TB_EVENT_KEY:
			if (ev.key == TB_KEY_CTRL_Q && ctrlxpressed) {
				tb_shutdown();
				return 0;
			}
			if (ev.key == TB_KEY_CTRL_C && ctrlxpressed) {
				static int chmap[] = {
					TB_INPUT_ESC | TB_INPUT_MOUSE, /* 101 */
					TB_INPUT_ALT | TB_INPUT_MOUSE, /* 110 */
					TB_INPUT_ESC,                  /* 001 */
					TB_INPUT_ALT,                  /* 010 */
				};
				inputmode++;
				if (inputmode >= 4) {
					inputmode = 0;
				}
				tb_select_input_mode(chmap[inputmode]);
			}
			if (ev.key == TB_KEY_CTRL_X)
				ctrlxpressed = 1;
			else
				ctrlxpressed = 0;

			tb_clear();
			draw_screen();
			dispatch_press(&ev);
			pretty_print_press(&ev);
			tb_present();
			break;
		case TB_EVENT_RESIZE:
			tb_clear();
			draw_screen();
			pretty_print_mouse(&ev);
			tb_present();
			break;
		default:
			break;
		}
	}
	tb_shutdown();
	return 0;
}
