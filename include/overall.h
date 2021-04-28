#ifndef OVERALL_H
# define OVERALL_H
# include "cub3d.h"

typedef struct		s_overall
{
	float			scale;
	t_conf			*conf;
	t_map			*map;
	t_img			*img;
	t_img			*nswe_img[4];
	void			*mlx;
	void			*win;
	size_t			pxy;
	size_t			pxx;
	size_t			hero_x;
	size_t			hero_y;
	size_t			dir_x;
	size_t			dir_y;
	double			plane_x;
	double			plane_y;
}					t_overall;

#endif
