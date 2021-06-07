#include "fractol.h"

/*
 * マンデルブロ集合を描画する.
 * マンデルブロ集合とは z_n = z_(n-1) + C とした時に発散しない集合のこと.
 * Cは描画するピクセルの位置(縦横のピクセル数の相対)
 *
 * 発散した時は黒色で塗りつぶす
 */
int	draw_mandelbrot(t_canvas *canvas)
{
	int	x;
	int	y;
	// choose R > 0 such that R**2 - R >= sqrt(cx**2 + cy**2)
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

	R = 2;
	y = 0;
	while (y < canvas->screen_height)
	{
		cy = (((double)y / (double)(canvas->screen_height - 1)) * 2 - 1) * R;
		x = 0;
		while (x < canvas->screen_width)
		{
			cx = (((double)x / (double)(canvas->screen_width - 1)) * 2 - 1) * R;
			// printf("Z=%+f%+fi\n", cy, cx);

			iteration = 0;
			zx = 0;
			zy = 0;
			while (zx * zx + zy * zy < (R * R) && iteration < MAX_ITERATION)
			{
				// printf("%d: (%f,%f)\n", iteration, zx, zy);
				// Z_(n+1) = Z_n ^ 2 + C    (Zは複素数の式)
				// (a + bj)^2 = a^2 + 2abj - b^2
				double xtemp = zx * zx - zy * zy + cx;
				zy = 2 * zx * zy + cy;
				zx = xtemp;
				iteration++;
			}

			int	color;
			if (iteration == MAX_ITERATION)
				color = rgb2hex(0, 0, 0);
			else
				// color = (int)(0xffffff * ((double)iteration / (double)MAX_ITERATION));
				color = hsv2hex(180, ((double)iteration / (double)MAX_ITERATION), ((double)iteration / (double)MAX_ITERATION));
			my_mlx_pixel_put(&canvas->img, x, y, color);
			x++;
		}
		y++;
	}
	printf("DONE RENDERING\n");
	return (0);
}
