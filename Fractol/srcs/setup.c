/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 04:20:46 by saneveu           #+#    #+#             */
/*   Updated: 2019/05/01 00:13:08 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void    setup(t_env *e)
{
    e->mlx_ptr = mlx_init();
    e->win_ptr = mlx_new_window(e->mlx_ptr, WIDTH, HEIGHT, "Fractol");
    e->img_ptr = mlx_new_image(e->mlx_ptr, WIDTH, HEIGHT);
    e->img = (int *)mlx_get_data_addr(e->img_ptr, &e->bpp, &e->s_l, &e->endian);
    e->usr_color = 0;
    /*->x_left = -2.1;
    e->x_right = 0.6;
    e->y_floor = -1.2;
    e->y_top = 1.2;*/
    e->zoom = 300;
    e->offset = (t_index) {.x = 0, .y = 0};
    e->rng = 0;
    e->motion = 0;
    e->minx = ((e->x_right - e->x_left) * e->zoom);
    e->miny = ((e->y_top - e->y_floor) * e->zoom);
    e->julia = (t_rng) {.real = -0.506667, .imag = 0.520000};;
    init_fractal(e);
}

void        julias_changes(t_env *e)
{
	if (!e->rng)
		e->julia = (t_rng) {.real = -0.506667, .imag = 0.520000 };
	else if (e->rng == 1)
		e->julia = (t_rng) {.real = 0.403333, .imag = 0.273333 };
	else if (e->rng == 2)
		e->julia = (t_rng) {.real = 0.386667, .imag = 0.103333 };
	else if (e->rng == 3)
		e->julia = (t_rng) {.real = -0.203333, .imag = -0.696667 };
	else if (e->rng == 4)
		e->julia = (t_rng) {.real = 0.18, .imag = -0.566667 };
	else if (e->rng == 5)
		e->julia = (t_rng) {.real = 0.371504, .imag = -0.153893 };
}

void        init_fractal(t_env *e)
{
    if (e->choix == 0)
    {
        //e->zoom = 200;
        e->max_iter = 100;
    }
    if (e->choix == 1)
    {
        e->max_iter = 300;
        julias_changes(e);
    }
}

void        whatfractal(t_env *e, char *name, int ac)
{
    if (ac >= 2)
    {
        if (!ft_strcmp(name, "Mandelbrot") || ac == 1)
            e->choix = 0;
        else if (!ft_strcmp(name, "Julia"))
            e->choix = 1;
        else
        {
            ft_putendl("Not valids arguments.\n[Mandelbrot - Julia]fractal [1 - 3]colors");
            exit(EXIT_FAILURE);
        }
    }
}

void        whatcolor(t_env *e, char *name, int ac)
{
    if (ac == 3)
    {
        if (ft_atoi(name) == 1)
        {
            e->usr_color = 0;
            colorset0(e);
        }
        else if (ft_atoi(name) == 2)
        {
            e->usr_color = 1;
            colorset1(e);
        }
        else if (ft_atoi(name) == 3)
        {
            e->usr_color = 2;
            colorset2(e);
        }
        else
        {
            ft_putendl("5 colors set available");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        e->usr_color = 0;
        colorset0(e); 
    }
    
}