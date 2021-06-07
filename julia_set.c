#include "fractol.h"

/*
 * ジュリア集合を描画する.
 * ジュリア集合とは z_n = z_(n-1) + C とした時に発散しない集合のこと.
 *
 * 発散した時は黒色で塗りつぶす
 */
int	draw_julia(t_canvas *canvas)
{
	int	x;
	int	y;
	double	R;
	// zx represents the real part of z.  (scale to be between -R and R)
	double	zx;
	// zy represents the imaginary part of z.  (scale to be between -R and R)
	double	zy;
	// C is complex parameter
	// xz represents the real part of constant C
	double	cx;
	// xz represents the imaginary part of constant C
	double	cy;
	int	iteration;

	R = M_PI;
	y = 0;
	// TODO: 適当
	cx = 0;
	cy = 0;
	while (y < canvas->screen_height)
	{
		zy = (((double)y / (double)(canvas->screen_height - 1)) - 1) * R;
		x = 0;
		while (x < canvas->screen_width)
		{
			zx = (((double)x / (double)(canvas->screen_width - 1)) - 1) * R;

			iteration = 0;

			while (zx * zx + zy * zy < (R * R) && iteration < MAX_ITERATION)
			{
				double xtemp = zx * zx - zy * zy;
				zy = 2 * zx * zy + cy;
				zx = xtemp + cx;
				iteration++;
			}

			if (iteration == MAX_ITERATION)
				// TODO: draw black...
			else:
				// TODO: draw white or beautiful color...
		}
	}
}
