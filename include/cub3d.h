#ifndef CUB3D_H 
# define CUB3D_H
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <math.h>
#include <mlx.h>
#include "libft.h"
#include "conf.h"

#define PI 3.1415926535
#define N PI/2
#define S 3*PI/2 
#define W PI 
#define E 0

# ifdef __linux__
#  include "linux_key.h"
# elif __APPLE__
#  include "macos_key.h"
# endif 

typedef	struct		s_map
{
	char			**matrix;
	size_t			x;
	size_t			y;
	float			hero_x;
	float			hero_y;
	float			hero_a;
	float 			hero_dx;
	float			hero_dy;
	float			plane_x;
	float			plane_y;
}					t_map;

typedef struct		s_img
{
	void 			*img;	
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
}					t_img;

typedef struct		s_px
{
	short int		cur_x;
	short int		cur_y;
}					t_px;

typedef struct		s_overall
{
	float			scale;
	t_px			px;
	t_conf			*conf;
	t_map			*map;
	t_img			*img;
	void			*mlx;
	void			*win;
}					t_overall;


/*
**============================================================
**						exit.c
*/

void				exit_error(char *str, t_conf *conf, int ret);

/*
**============================================================
**		 				init.c
*/

void				init(int ac, char **av);
void				init_conf(t_conf **conf);
void				init_resolution(t_overall *x);
void				init_hook(t_overall *x);
t_img				*init_image(t_overall *x);

/*
**============================================================
**						parse_cub.c
*/

void				parse_cub(char *line, t_conf *conf);
void				parse_resolution(char *line, t_conf *conf);
void				parse_rgb(char *line, t_conf *conf);
char				parse_color(char **line, t_conf *conf, int i);
void				parse_path(char *line, t_conf *conf);

/*
**============================================================
**						parse_map.c
*/

void				get_map(t_maphead *maphead, t_conf *conf);
void				fill_map(t_conf *conf);
int					get_sizes_map(t_maplst *lst, size_t *x, size_t *y);
int					map_matrix(char **matrix, t_maplst *head, size_t x, size_t y);
void				remove_empty_tails(t_maphead *mhead);

/*
**============================================================
**						read_cub.c
*/

t_conf				*read_cub(int ac, char **av);
void				read_map(int fd, t_conf *conf);
int					append_maplst(char *line, size_t len, t_maphead *h);
void				set_texture_flag(char *path, t_conf *conf);

/*
**============================================================
**						validate_cub.c
*/

void				handle_args(int ac, char **av);
int					validate_line(char **matrix, size_t y, t_conf *conf);
int					validate_first_last_line(t_map *map);
int					validate_updown(t_map *map, size_t x, size_t y);
void 				validate_path(char *line, t_conf *conf);

/*
**============================================================
**						memclr.c
*/
int					lst_clear(t_maplst *head, int ret);
int					matrix_clear(char **matrix, size_t i);

/*
**============================================================
**						graphix.c
*/
int					do_graphic_shit(t_overall *x);
void				put_pixel(t_img *data, int pos_x, int pos_y, int rgb);
void				fill_row(t_overall *x, int pos_y, int rgb);
void				fill_img(t_overall *x, int rgb);
void				draw_rectangle(t_overall *x, int sizex, int sizey, int rgb);

/*
**============================================================
**						minimap.c
*/
void				print_minimap(t_overall *x);
void				mm_ray(t_overall *x);
void				mm_dir(t_overall *x);
void				print_map_square(t_overall *x, int rgb);
void				print_hero(t_overall *x);

/*
**============================================================
**						hooks.c
*/
int					close_x(int keycode, t_overall *x);
int					key_handler(int keycode, t_overall *x);

/*
**============================================================
**						move/
*/

void				move_forward(t_overall *x);
void				move_backward(t_overall *x);
void				rot_l(t_overall *x);
void				rot_r(t_overall *x);
int					check_pos(t_overall *x, float offset_x, float offset_y);

#endif
