#include "fractol.h"

static uint32_t	get_pixel_color(t_canvas *canvas, double z_re, double z_im, double c_re, double c_im)
{
	double	iteration;
	int		color;
	double	tmp_x;

	iteration = 0;
	while (z_re * z_re + z_im * z_im < 4 && iteration < canvas->max_iter)
	{
		tmp_x = z_re * z_re - z_im * z_im + c_re;
		z_im = 2 * z_re * z_im + c_im;
		z_re = tmp_x;
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

	R = 2;
	y = 0;
	while (y < canvas->screen_height)
	{
		cy = (((double)y / (double)(canvas->screen_height - 1)) * 2 - 1) * R;
		x = 0;
		while (x < canvas->screen_width)
		{
			cx = (((double)x / (double)(canvas->screen_width - 1)) * 2 - 1) * R;
			zx = 0;
			zy = 0;
			my_mlx_pixel_put(&canvas->img, x, y,
				get_pixel_color(canvas, zx, zy, cx, cy));
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
	// zx represents the real part of z.  (scale to be between -R and R)
	double	z_re;
	// zy represents the imaginary part of z.  (scale to be between -R and R)
	double	z_im;
	// C is complex parameter
	// xz represents the real part of constant C
	double	c_re;
	// xz represents the imaginary part of constant C
	double	c_im;

	y = 0;
	c_re = 0.4;
	c_im = -0.325;
	// 1ピクセルで複素数平面上でどれだけ進むか
	double delta_re = (canvas->max_re - canvas->min_re) / (WIDTH - 1);
	double delta_im = (canvas->max_im - canvas->min_im) / (HEIGHT - 1);
	while (y < canvas->screen_height)
	{
		z_im = canvas->max_im - y * delta_im;
		x = 0;
		while (x < canvas->screen_width)
		{
			z_re = canvas->min_re + x * delta_re;
			my_mlx_pixel_put(&canvas->img, x, y,
				get_pixel_color(canvas, z_re, z_im, c_re, c_im));
			x++;
		}
		y++;
	}
	// printf("zx: %f, zy: %f\n", zx, zy);
	return (0);
}
