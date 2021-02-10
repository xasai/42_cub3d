#ifndef CUB3D_H
# define CUB3D_H
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "libft.h"

typedef struct		s_config
{
	int				res_x;
	int				res_y;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	unsigned char	*sprite;
	unsigned char	floor[3];
	unsigned char	ceiling[3];
}					t_config;

typedef	struct		s_flags
{
	unsigned int	line;
	unsigned char	res:1;
	unsigned char	no:1;
	unsigned char	so:1;
	unsigned char	we:1;
	unsigned char	ea:1;
	unsigned char	sprite:1;
	unsigned char	floor:1;
	unsigned char	ceiling:1;	
	t_config		values;
}					t_flags;

/*
**					main.c
*/
void				exit_error(char *str, int ret);
void				handle_args(int ac, char **av);

/*
**	 				conf_cub.c
*/
void				config_init(t_flags **conf);

/*
**					parse_cub.c
*/
void				parse_cub(char *line, t_flags *config);
void				parse_resolution(char *line, t_flags *config);
void				parse_rgb(char *line, t_flags *config);
unsigned char 		parse_color(char **line, int i);
void				parse_path(char *line, t_flags *config);

/*
**					read_cub.c
*/
void				read_cub(int ac, char **av);

/*
**					validate_cub.c
*/

void				validate_path(char *path);
#endif
