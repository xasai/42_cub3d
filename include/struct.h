#ifndef STRUCT_H 
# define STRUCT_H 
# include "cub3d.h"

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
	uint16_t		res_x;
	uint16_t		res_y;
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


typedef struct		s_img
{
	void 			*img;	
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	size_t			size;
	size_t			size_x;
	size_t			size_y;
}					t_img;

typedef struct s_ray
{
    float angle;
    float distance;
    float cx;
    float cy;
}               t_ray;

#endif
