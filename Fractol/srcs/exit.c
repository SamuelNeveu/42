/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 23:02:21 by saneveu           #+#    #+#             */
/*   Updated: 2019/04/30 23:33:03 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void    error();

int     ft_exit(t_env *e)
{
    mlx_destroy_image(e->mlx_ptr, e->img_ptr);
    mlx_destroy_window(e->mlx_ptr, e->win_ptr);
    //free(e->color);
    free(e);
    exit(EXIT_SUCCESS);
    return (0);
}

void		ft_clear_img(t_env *e)
{
	int i;

	i = 0;
	while (i < WIDTH * HEIGHT)
	{
		if (e->img[i] != 0)
			e->img[i] = 0;
		i++;
	}
}
