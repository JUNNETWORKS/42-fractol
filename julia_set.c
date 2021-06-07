#include "fractol.h"

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
	(void)canvas;
	return (0);
}
