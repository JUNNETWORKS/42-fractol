#include "fractol.h"

int	key_press_hook(int keycode, t_canvas *canvas)
{
	if (keycode == KEY_ESC)
		exit_canvas(canvas);
	return (0);
}

int	mouse_hook(int button, int x, int y, void *canvas)
{
	(void)canvas;
	printf("button: %x, x: %d, y: %d\n", button, x, y);
	// if (button == SCROLL_UP)
	// 	;  // TODO: zoom in...
	// else if (button == SCROLL_DOWN)
	// 	;  // TODO: zoom out...
	return (0);
}
