#ifndef FRACTOL_H
# define FRACTOL_H

# include "./minilibx-linux/mlx.h"
# include "./libft/libft.h"
# include <X11/X.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
# include <errno.h>
# include <string.h>

# define KEY_Q 113
# define KEY_ESC 65307
# define MAX_ITERATION 10

# define ABS(x) ((x) < 0 ? -1 * (x) : (x))

typedef struct	s_img {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct	s_canvas {
	void		*mlx;
	void		*win;
	t_img		img;
	int			screen_width;
	int			screen_height;
}				t_canvas;

// MLX
int			exit_canvas(t_canvas *canvas);
void		initialize_canvas(t_canvas *canvas);
uint32_t	get_color(t_img img, int x, int y);
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
uint32_t	rgb2hex(int r, int g, int b);
uint32_t	get_hsv_hex(double h, double s, double v);

// fracal
int	draw_julia(t_canvas *canvas);
int	draw_mandelbrot(t_canvas *canvas);

#endif
