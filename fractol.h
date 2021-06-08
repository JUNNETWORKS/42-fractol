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
# define SCROLL_UP 5
# define SCROLL_DOWN 4
# define MOUSE_RIGHT 1
# define MOUSE_CENTER 2
# define MOUSE_LEFT 3
# define ZOOM_STEP 0.5
# define THRESHOLD 2

# define WIDTH 800
# define HEIGHT 800
# define MAX_ITERATION 100

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

enum e_fractal_type {
	FRACTAL_JULIA,
	FRACTAL_MANDELBROT,
};

typedef struct	s_canvas {
	void				*mlx;
	void				*win;
	t_img				img;
	int					screen_width;
	int					screen_height;
	// mouse position
	int					mouse_x;
	int					mouse_y;
	// zoom ratio  default: 1
	double				zoom;
	// 左上の座標
	// マウスの座標に向かってズームする時に必要
	double				min_re;
	double				min_im;
	double				max_re;
	double				max_im;
	enum e_fractal_type	fractal_type;
}				t_canvas;

// MLX
int			exit_canvas(t_canvas *canvas);
void		initialize_canvas(t_canvas *canvas);
uint32_t	get_color(t_img img, int x, int y);
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
int			key_press_hook(int keycode, t_canvas *canvas);
int			mouse_hook(int button, int x, int y, t_canvas *canvas);

// fracal
int	draw_julia(t_canvas *canvas);
int	draw_mandelbrot(t_canvas *canvas);

// color utils
uint32_t	rgb2hex(int r, int g, int b);
uint32_t	hsv2hex(double h, double s, double v);

#endif
