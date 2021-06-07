#include "fractol.h"

int	key_press_hook(int keycode, t_canvas *canvas)
{
	if (keycode == KEY_ESC)
		exit_canvas(canvas);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_canvas *canvas)
{
	printf("button: %x, x: %d, y: %d\n", button, x, y);
	if (button == SCROLL_UP && canvas->zoom < 1000)
		canvas->zoom += 0.1;
	else if (button == SCROLL_DOWN && canvas->zoom > 0.2)
		canvas->zoom -= 0.1;
	canvas->mouse_x = x;
	canvas->mouse_y = y;
	printf("canvas->zoom: %f\n", canvas->zoom);
	return (0);
}
