#ifndef CONF_H
# define CONF_H 
# include "cub3d.h"

typedef struct s_map t_map;
typedef struct		s_maphead
{
	struct s_maplst	*head;
	struct s_maplst	*tail;
	size_t			width;
}					t_maphead;

typedef struct		s_maplst
{
	struct s_maplst *next;
	char			*line;
	size_t			len;
}					t_maplst;

typedef struct		s_conf
{
	int				res_x;
	int				res_y;
	int				floor;
	int				ceiling;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*sprite;
	int				line_num;
	t_map			*map;
	unsigned char	flag;
	char			save_bmp;
}					t_conf;

#endif
