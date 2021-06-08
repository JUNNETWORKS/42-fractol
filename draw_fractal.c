#include "fractol.h"

static uint32_t	get_pixel_color(double zx, double zy, double cx, double cy)
{
	double	iteration;
	int		color;
	double	tmp_x;

	iteration = 0;
	while (zx * zx + zy * zy < 4 && iteration < MAX_ITERATION)
	{
		tmp_x = zx * zx - zy * zy + cx;
		zy = 2 * zx * zy + cy;
		zx = tmp_x;
		iteration++;
	}

	if (iteration == MAX_ITERATION)
		color = rgb2hex(0, 0, 0);
	else
		color = hsv2hex(180, (iteration / MAX_ITERATION), (iteration / MAX_ITERATION));
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
		cy = (((double)y / (double)(canvas->screen_height - 1)) * 2 - 1) * R / canvas->zoom;
		x = 0;
		while (x < canvas->screen_width)
		{
			cx = (((double)x / (double)(canvas->screen_width - 1)) * 2 - 1) * R / canvas->zoom;
			zx = 0;
			zy = 0;
			my_mlx_pixel_put(&canvas->img, x, y,
				get_pixel_color(zx, zy, cx, cy));
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
	double	zx;
	// zy represents the imaginary part of z.  (scale to be between -R and R)
	double	zy;
	// C is complex parameter
	// xz represents the real part of constant C
	double	cx;
	// xz represents the imaginary part of constant C
	double	cy;

	y = 0;
	cx = 0.4;
	cy = -0.325;
	// 1ピクセルで複素数平面上でどれだけ進むか
	double delta_re = (canvas->max_r - canvas->min_r) / (WIDTH - 1);
	double delta_im = (canvas->max_i - canvas->min_i) / (HEIGHT - 1);
	while (y < canvas->screen_height)
	{
		zy = y * delta_im;
		// zy = (((double)y / (double)(canvas->screen_height - 1)) * 2) * THRESHOLD / canvas->zoom + canvas->top;
		x = 0;
		while (x < canvas->screen_width)
		{
			zx = x * delta_re;
			// zx = (((double)x / (double)(canvas->screen_width - 1)) * 2) * THRESHOLD / canvas->zoom + canvas->left;
			my_mlx_pixel_put(&canvas->img, x, y,
				get_pixel_color(zx, zy, cx, cy));
			x++;
		}
		y++;
	}
	printf("zx: %f, zy: %f\n", zx, zy);
	return (0);
}
