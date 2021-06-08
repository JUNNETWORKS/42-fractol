#include "fractol.h"

static uint32_t	get_color_in_fractal(t_canvas *canvas)
{
	double	iteration;
	int		color;
	double	tmp_x;

	iteration = 0;
	while (canvas->z_re * canvas->z_re + canvas->z_im * canvas->z_im < 4
		&& iteration < canvas->max_iter)
	{
		tmp_x = canvas->z_re * canvas->z_re
			- canvas->z_im * canvas->z_im + canvas->c_re;
		canvas->z_im = 2 * canvas->z_re * canvas->z_im + canvas->c_im;
		canvas->z_re = tmp_x;
		iteration++;
	}
	if (iteration == canvas->max_iter)
		color = rgb2hex(0, 0, 0);
	else
		color = hsv2hex(180, (iteration / canvas->max_iter), (iteration / canvas->max_iter));
	return (color);
}

/*
 * マンデルブロ集合を描画する.
 * マンデルブロ集合とは z_n = z_(n-1) + C とした時に発散しない集合のこと.
 * Cは描画するピクセルの位置(縦横のピクセル数の相対)
 * Z_0 は 0 にセットする
 *
 * 発散した時は黒色で塗りつぶす
 *
 * メモ
 * Z_(n+1) = Z_n ^ 2 + C    (Zは複素数の式)
 * (a + bj)^2 = a^2 + 2abj - b^2
 */
int	draw_mandelbrot(t_canvas *canvas)
{
	int	x;
	int	y;

	canvas->delta_re = (canvas->max_re - canvas->min_re) / (WIDTH - 1);
	canvas->delta_im = (canvas->max_im - canvas->min_im) / (HEIGHT - 1);
	y = 0;
	while (y < canvas->screen_height)
	{
		canvas->c_im = canvas->max_im - y * canvas->delta_im;
		x = 0;
		while (x < canvas->screen_width)
		{
			canvas->c_re = canvas->min_re + x * canvas->delta_re;
			canvas->z_re = 0;
			canvas->z_im = 0;
			my_mlx_pixel_put(&canvas->img, x, y,
				get_color_in_fractal(canvas));
			x++;
		}
		y++;
	}
	return (0);
}

/*
 * ジュリア集合を描画する.
 * ジュリア集合とは z_n = z_(n-1) + C とした時に発散しない集合のこと.
 * Cは複素数の定数(全てのピクセルにおいて同じ数字を使う)
 * Z_0 は描画するピクセルの位置(縦横のピクセル数の相対)
 *
 * 発散した時は黒色で塗りつぶす
 */
int	draw_julia(t_canvas *canvas)
{
	int	x;
	int	y;

	// TODO: C は自由に変えれるようにする
	canvas->c_re = 0.4;
	canvas->c_im = -0.325;
	canvas->delta_re = (canvas->max_re - canvas->min_re) / (WIDTH - 1);
	canvas->delta_im = (canvas->max_im - canvas->min_im) / (HEIGHT - 1);
	y = 0;
	while (y < canvas->screen_height)
	{
		canvas->z_im = canvas->max_im - y * canvas->delta_im;
		x = 0;
		while (x < canvas->screen_width)
		{
			canvas->z_re = canvas->min_re + x * canvas->delta_re;
			my_mlx_pixel_put(&canvas->img, x, y,
				get_color_in_fractal(canvas));
			x++;
		}
		y++;
	}
	return (0);
}
