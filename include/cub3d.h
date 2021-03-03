#ifndef CUB3D_H
# define CUB3D_H
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "libft.h"

typedef	struct		s_map
{
	char			**map;
	int				x;
	int				y;
	int				player_x;
	int				player_y;
	char			player;
}					t_map;

typedef	struct		s_f
{
	unsigned short	flag;
	unsigned char	res:1;
	unsigned char	no:1;
	unsigned char	so:1;
	unsigned char	we:1;
	unsigned char	ea:1;
	unsigned char	sprite:1;
	unsigned char	floor:1;
	unsigned char	ceiling:1;	
	unsigned char	option:1;
}					t_f;

typedef struct		s_conf
{
	int				line_num;
	int				res_x;
	int				res_y;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*sprite;
	unsigned char	floor[3];
	unsigned char	ceiling[3];
	t_map			*map;
	t_f				f;	
}					t_conf;

/*
**============================================================
**						main.c
*/

void				handle_args(int ac, char **av);
void				exit_error(char *str, t_conf *conf, int ret);

/*
**============================================================
**		 				conf_cub.c
*/

void				config_init(t_conf **conf);

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
**						read_cub.c
*/

void				read_cub(int ac, char **av);
void				read_map(int fd, t_conf *conf);
void				append_lst(char *line, t_list **lst_head, t_conf *conf);
void				make_map(t_map *map_t, t_list **lst_head, t_conf *conf);

/*
**============================================================
**						validate_cub.c
*/

void 				validate_path(char *line, t_conf *conf);

/*
**============================================================
**						memclr.c
*/

void				lst_clear(t_list *lst);

#endif
