#ifndef OVERALL_H
# define OVERALL_H
# include "cub3d.h"

typedef struct		s_overall
{
	float			scale;
	t_conf			*conf;
	t_map			*map;
	t_img			*img;
	t_img			*m_img;
	void			*mlx;
	void			*win;
	size_t			pxy;
	size_t			pxx;
}					t_overall;

#endif
