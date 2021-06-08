#include "fractol.h"

int	key_press_hook(int keycode, t_canvas *canvas)
{
	if (keycode == KEY_ESC)
		exit_canvas(canvas);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_canvas *canvas)
{
	double	new_zoom;
	double	adjustment;

	printf("button: %x, x: %d, y: %d\n", button, x, y);
	if (button == SCROLL_UP && canvas->zoom < 10000)
		new_zoom = canvas->zoom + ZOOM_STEP;
	else if (button == SCROLL_DOWN && canvas->zoom >= 1 + ZOOM_STEP)
		new_zoom = canvas->zoom - ZOOM_STEP;
	adjustment = new_zoom / canvas->zoom;
	if (button == SCROLL_UP || button == SCROLL_DOWN)
	{
		canvas->zoom = new_zoom;
		canvas->top = (canvas->top / (adjustment / 2) - ((double)y / (double)canvas->screen_height));
		canvas->left = (canvas->left / (adjustment / 2) + ((double)x / (double)canvas->screen_width));
		printf("top: %f, left: %f\n", canvas->top, canvas->left);
		canvas->mouse_x = x;
		canvas->mouse_y = y;
	}
	printf("canvas->zoom: %f\n", canvas->zoom);
	return (0);
}
