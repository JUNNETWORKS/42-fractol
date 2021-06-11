#include "fractol.h"

void	move_arrow_key(int keycode, t_canvas *canvas)
{
	if (keycode == KEY_UP_ARROW)
	{
		canvas->min_im += (canvas->max_im - canvas->min_im) * MOVE_RATIO;
		canvas->max_im += (canvas->max_im - canvas->min_im) * MOVE_RATIO;
	}
	if (keycode == KEY_DW_ARROW)
	{
		canvas->min_im -= (canvas->max_im - canvas->min_im) * MOVE_RATIO;
		canvas->max_im -= (canvas->max_im - canvas->min_im) * MOVE_RATIO;
	}
	if (keycode == KEY_R_ARROW)
	{
		canvas->min_re += (canvas->max_re - canvas->min_re) * MOVE_RATIO;
		canvas->max_re += (canvas->max_re - canvas->min_re) * MOVE_RATIO;
	}
	if (keycode == KEY_L_ARROW)
	{
		canvas->min_re -= (canvas->max_re - canvas->min_re) * MOVE_RATIO;
		canvas->max_re -= (canvas->max_re - canvas->min_re) * MOVE_RATIO;
	}
}

int	key_press_hook(int keycode, t_canvas *canvas)
{
	if (keycode == KEY_ESC)
		exit_canvas(canvas);
	if (keycode == KEY_SHIFT)
		canvas->is_pressed_shift = true;
	if (keycode == KEY_UP_ARROW || keycode == KEY_DW_ARROW
		|| keycode == KEY_L_ARROW || keycode == KEY_R_ARROW)
		move_arrow_key(keycode, canvas);
	return (0);
}

int		key_release_hook(int keycode, t_canvas *canvas)
{
	if (keycode == KEY_SHIFT)
		canvas->is_pressed_shift = false;
	return (0);
}

static double	interpolate(double start, double end, double interpolation)
{
	return (start + ((end - start) * interpolation));
}

int	mouse_hook(int button, int x, int y, t_canvas *canvas)
{
	double	mouse_re;
	double	mouse_im;
	double	interpolation;

	if (button != SCROLL_UP && button != SCROLL_DOWN)
		return (0);
	mouse_re = (double)x
		/ (WIDTH / (canvas->max_re - canvas->min_re)) + canvas->min_re;
	mouse_im = (double)y
		/ (HEIGHT / (canvas->max_im - canvas->min_im)) * -1 + canvas->max_im;
	if (button == SCROLL_UP)
	{
		if (canvas->max_iter > 4)
			canvas->max_iter -= 4;
		interpolation = 1.0 / 0.8;
	}
	else if (button == SCROLL_DOWN)
	{
		canvas->max_iter += 4;
		interpolation = 1.0 / 1.2;
	}
	canvas->min_re = interpolate(mouse_re, canvas->min_re, interpolation);
	canvas->min_im = interpolate(mouse_im, canvas->min_im, interpolation);
	canvas->max_re = interpolate(mouse_re, canvas->max_re, interpolation);
	canvas->max_im = interpolate(mouse_im, canvas->max_im, interpolation);
	return (0);
}
