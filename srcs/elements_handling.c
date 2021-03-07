/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mezz <ael-mezz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 14:33:48 by ael-mezz          #+#    #+#             */
/*   Updated: 2021/02/25 17:30:00 by ael-mezz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

char	**find_id(char	*id)
{
	char	**data;
	int		i;

	i = 0;
	while (file.elem[i])
	{
		data = ft_split(file.elem[i], ' ');
		if (ft_strcmp(data[0], id) == 0)
			return (data);
		i++;
	}
	return (NULL);
}

int		handle_r()
{
	char	**res;

	res = find_id("R");
	if (ft_strlen_2d(res) < 3)
		return (out("Error\nOne at least of resolution infotmations is missing!\n"));
	if (ft_strlen_2d(res) > 3)
		return (out("Error\nneed only 2 info's for rosulution!\n"));
	g_data.dimens.w = ft_atoi(res[2]);
	g_data.dimens.h = ft_atoi(res[1]);
	if (g_data.dimens.w  <= 0 || g_data.dimens.h <= 0)
		return (out("Error\nPlease provide a valid resolution!\n"));
	g_data.dimens.w  = g_data.dimens.w  > 2560 ? 2560 : g_data.dimens.w ;
	g_data.dimens.h = g_data.dimens.h > 1395 ? 1395 : g_data.dimens.h;
	free_2d(res);
	return (1);
}

int		handle_map()
{
	int	k;
	int j;

	if (g_data.rows < 3 || g_data.cols < 3)
		return (out("unvalid map/map unfound!\n"));
	k = g_data.rows;
	while (k--)
	{
		j = -1;
		while (g_data.world[k][++j])
		{
			if (!(ft_strnchar("NEWS120 ", g_data.world[k][j])))
				return (out("Fobidden character exist in map!\n"));
			else if ((ft_strnchar("NEWS20", g_data.world[k][j])) && !(map_parsing(k, j)))
				return (out("Map is not properly closed!\n"));
		}
	}
	return (1);
}

int		map_parsing(int k, int j)
{
	int x;
	int y;

	y = -2;
	x = -2;
	while (++y < 2)
	{
		if (k + y >= g_data.cols || k <= 0)
			return (0);
		if (g_data.world[k + y][j] == ' ' || g_data.world[k + y][j] == '\0')
			return (0);
	}
	while (++x < 2)
	{
		if ((j + x + 1 > ft_strlen(g_data.world[k]) || j <= 0))
			return (0);
		if (g_data.world[k][j + x] == ' ')
			return (0);
	}
	return (1);
}

int		texture_data()
{
	char	***id;
	int		i;

	i = -1;
	id = malloc(sizeof(char **) * 4);
	id[0] = find_id("NO");
	if (ft_strlen_2d(id[0]) > 2 || ft_strlen_2d(id[0]) < 2)
		return (out("Can't find the north texture!\n"));
	g_data.xpm_n = ft_strdup(id[0][1]);
	id[1] = find_id("SO");
	if (ft_strlen_2d(id[1]) > 2 || ft_strlen_2d(id[1]) < 2)
		return (out("Can't find the south texture!\n"));
	g_data.xpm_s = ft_strdup(id[1][1]);
	id[2] = find_id("WE");
	if (ft_strlen_2d(id[2]) > 2 || ft_strlen_2d(id[2]) < 2)
		return (out("Can't find the west texture!\n"));
	g_data.xpm_w = ft_strdup(id[2][1]);
	id[3] = find_id("EA");
	if (ft_strlen_2d(id[3]) > 2 || ft_strlen_2d(id[3]) < 2)
		return (out("Can't find the east texture!\n"));
	g_data.xpm_e = ft_strdup(id[3][1]);
	while (++i < 4)
		free_2d(id[i]);
	free(id);
	return (1);
}