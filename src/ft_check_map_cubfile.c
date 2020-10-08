/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_cubfile.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 18:34:40 by wbertoni          #+#    #+#             */
/*   Updated: 2020/10/08 15:43:08 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubfile.h"

static int		ft_check_map_cubfile_symbol(t_map *map)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < map->num_row)
	{
		while (j < map->num_col && map->map[i][j] != '\0')
		{
			if (
				map->map[i][j] != ' ' && map->map[i][j] != '0'
				&& map->map[i][j] != '1' && map->map[i][j] != '2'
				&& map->map[i][j] != 'N' && map->map[i][j] != 'S'
				&& map->map[i][j] != 'E' && map->map[i][j] != 'W')
				return (FALSE);
			j++;
		}
		j = 0;
		i++;
	}
	return (TRUE);
}

/**
 * cr = current_row
 * cc = current_col
 * dir = direction
**/

static int		ft_has_wall_row_column(t_map *map, const int cr,
								const int cc, t_face dir)
{
	int i;
	int pos;

	if (dir == left || dir == up)
	{
		i = (dir == left ? cc : cr);
		while (i >= 0)
		{
			if (ft_is_w_or_s(pos = dir == left ? map->map[cr][i]
							: map->map[i][cc]))
				return (pos == '1' ? TRUE : FALSE);
			i--;
		}
	}
	else
	{
		i = (dir == right ? cc : cr);
		while (i < map->num_col)
		{
			if (ft_is_w_or_s(pos = dir == right ? map->map[cr][i]
							: map->map[i][cc]))
				return (pos == '1' ? TRUE : FALSE);
			i++;
		}
	}
	return (FALSE);
}

static int		ft_check_map_cubfile_border(t_map *map)
{
	int		i;
	int		j;
	t_face	direction;

	direction = up;
	i = 0;
	j = 0;
	while (map->map[i] != '\0')
	{
		while (map->map[i][j] != '\0')
		{
			if (map->map[i][j] != '1' && map->map[i][j] != ' ')
			{
				while (direction <= right)
				{
					if (!ft_has_wall_row_column(map, i, j, direction++))
						return (FALSE);
				}
			}
			direction = up;
			j++;
		}
		j = 0;
		i++;
	}
	return (TRUE);
}

t_error_file	ft_check_map_cubfile(t_map *map)
{
	if (ft_check_map_cubfile_has_empty_line(map->map))
		return (eempty);
	if (!ft_check_map_cubfile_symbol(map))
		return (eallow);
	if (!ft_check_map_cubfile_border(map))
		return (ewall);
	return (noerror);
}
