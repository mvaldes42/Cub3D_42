/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 17:53:19 by mvaldes           #+#    #+#             */
/*   Updated: 2020/07/08 15:43:06 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		cvt_screen_res(t_scene *scn_p, char *f_line)
{
	char		**str_array;

	str_array = (char **)malloc(sizeof(char *) * 3 + 1);
	str_array = ft_split(f_line, ' ');
	scn_p->screen.x = ft_atoi(str_array[1]);
	scn_p->screen.y = ft_atoi(str_array[2]);
	free(str_array);
}

static int		word_count(const char *s, char c)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static void			cvt_rgb(t_rgb *rgb, char *f_line)
{
	char	**str_array;
	int		b;
	int		g;
	int		r;

	ft_bzero(rgb, sizeof(&rgb));
	str_array = (char **)malloc(sizeof(char *) * word_count(f_line, ',') + 1);
	ft_memmove(f_line, f_line + 2, ft_strlen(f_line) - 2 + 1);
	str_array = ft_split(f_line, ',');
	b = ft_atoi(str_array[1]);
	g = ft_atoi(str_array[2]);
	r = ft_atoi(str_array[3]);
	if ((!((b <= 255 && b >= 0) && (g <= 255 && b >= 0) &&
	(r <= 255 && b >= 0))) || (word_count(f_line, ',') != 3))
	{
		g_error = 5;
		exit_message_failure();
	}
	rgb->b = b;
	rgb->g = g;
	rgb->r = r;
	free(str_array);
}

static void cvt_text_path(char **text_path, char *f_line)
{

	if (!(*text_path = ft_strchr(f_line, '.'))
	|| ft_strnstr(*text_path, "xpm", ft_strlen(*text_path)) == '\0')
	{
		g_error = 4;
		exit_message_failure();
	}
}

void			parse_env_params(char *f_line, t_scene *scn)
{
	if (f_line[0] == 'R')
		cvt_screen_res(scn, f_line);
	else if (f_line[0] == 'N' && f_line[1] == 'O')
		cvt_text_path(&(scn->n_tex), f_line);
	else if (f_line[0] == 'S' && f_line[1] == 'O')
		cvt_text_path(&(scn->s_tex), f_line);
	else if (f_line[0] == 'E' && f_line[1] == 'A')
		cvt_text_path(&(scn->e_tex), f_line);
	else if (f_line[0] == 'W' && f_line[1] == 'E')
		cvt_text_path(&(scn->w_tex), f_line);
	else if (f_line[0] == 'S' && f_line[1] == ' ')
		cvt_text_path(&(scn->sprt_tex), f_line);
	else if (f_line[0] == 'F')
		cvt_rgb(&(scn->flr_clr), f_line);
	else if (f_line[0] == 'C')
		cvt_rgb(&(scn->cei_clr), f_line);
}
