/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 05:34:34 by saneveu           #+#    #+#             */
/*   Updated: 2019/05/27 23:03:34 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int        deal_key(int key, t_env *e)
{
    ft_putnbr(key);
    ft_putendl("");
    key == 104 ? help_event(e) : 0;
    key == 65307/*53*/ ? ft_exit(e) : 0;
    key == 99/*8*/ ? switch_color(e) : 0; 
    key == 106/*38*/ ? change_julia_set(e) : 0;
    key == 65436/*83*/ ? switch_fractal(e, 0) : 0;
    key == 65433/*84*/ ? switch_fractal(e, 1) : 0;
    key == 65435/*85*/ ? switch_fractal(e, 2) : 0;
    key == 65430/*86*/ ? switch_fractal(e, 3) : 0;
    key == 65437/*87*/ ? switch_fractal(e, 4) : 0;
    key == 65432/*88*/ ? switch_fractal(e, 5) : 0;
    key == 65429/*89*/ ? switch_fractal(e, 6) : 0;
    key == 65431/*91*/ ? switch_fractal(e, 7) : 0;
    //key == 32/*49*/ ? allow_motion_julia(e) : 0;
    key == 100/*15*/ ? reset_default(e) : 0;
    if(key == 32)
    {
        e->smooth == 0 ? e->smooth += 1 : (e->smooth = 0); 
        do_fractol(e);
    }
    if(key == 108)
        e->linear == 0 ? e->linear += 1 : (e->linear = 0);
    //do_fractol(e);
    return (0); 
}

int         press_event(int key, t_env *e)
{
    key == 65451/*69*/ || key == 65453/*78*/ ? cycle_usr(key, e) : 0;
    key == 114/*15*/ ? rgb_usr(e, 'r') : 0;
    key == 103/*5*/ ? rgb_usr(e, 'g') : 0;
    key == 98/*11*/ ? rgb_usr(e, 'b') : 0;
    key == 65361/*123*/ ? move(e, 'x', 0.05) : 0;
    key == 65363/*124*/ ? move(e, 'x', -0.05) : 0;
    key == 65361/*126*/ ? move(e, 'y', 0.05) : 0;
    key == 65364/*125*/ ? move(e, 'y', -0.05) : 0;
    if (key == 65365 || key == 65366)
    {
        key == 65365 ? e->max_iter += 20 : (e->max_iter -= 20);
        do_fractol(e);
    }    
    return (0);
}

void        cycle_usr(int k, t_env *e)
{
    if (k == 65453)
        e->cycle <= 0 ? e->cycle = 1 : (e->cycle -= 5);
    else if (k == 65451)
        e->cycle > 300 ? e->cycle = 0 : (e->cycle += 5);
    //e->cycle < 0 ? e->cycle = 1 : 0;
    ft_putnbr(e->cycle);
    ft_putendl("");
    do_fractol(e);
}
void        switch_fractal(t_env *e, int c)
{
    if (c == 0)
        e->choix = 0;
    else if (c == 1)
        e->choix = 1;
    else if (c == 2)
        e->choix = 2;
    else if (c == 3)
        e->choix = 3;
    else if (c == 4)
    {
        e->choix = 4;
        //e->offset = (t_index) {.x = 500, .y = 1000};
    }
    else if (c == 5)
        e->choix = 5;
    else if (c == 6)
        e->choix = 6;
    else if (c == 7)
        e->choix = 7;
    init_fractal(e);
    do_fractol(e);
}

void        switch_color(t_env *e)
{
    e->usr_color == 6 ? e->usr_color = 0 :
        e->usr_color++;
    if (e->usr_color == 0)
        colorset0(e);
    else if (e->usr_color == 1)
        colorset1(e);
    else if (e->usr_color == 2)
        colorset2(e);
    else if (e->usr_color == 3)
        colorset3(e);
    else if (e->usr_color == 4)
        colorset4(e);
    else if (e->usr_color == 5)
        colorset5(e);
    else if (e->usr_color == 6)
    {
        !e->r ? e->r = 1 : 0;
        !e->g ? e->g = 1 : 0;
        !e->b ? e->b = 1 : 0;
    }
    do_fractol(e);
}

int        motion_mouse(int x, int y, t_env *e)
{
    if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT && e->motion)
	{
		e->julia.real = (x + e->offset.x) / (double)e->zoom + e->minx;
		e->julia.imag = (y + e->offset.y) / (double)e->zoom + e->miny;
		do_fractol(e);
	}
    return (1);
}

void        rgb_usr(t_env *e, char c)
{
    if (c == 'r')
        e->r < 40 ? e->r += 1 : (e->r = 0);
    else if (c == 'g')
        e->g < 40 ? e->g += 1 : (e->g = 0);
    else if (c == 'b')
        e->g < 40 ? e->g += 1 : (e->g = 0);
    do_fractol(e);
}

int			mouse_zoom(int k, int x, int y, t_env *e)
{
    ft_putnbr(k);
	if ((k == 1 || k == 3 || k == 4 || k == 5) &&
	(x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT))
	{
		if (k == 3)
        {
            e->x1 =  (x / e->zoom + e->x1) - (x / (e->zoom / 1.25));
			e->y1 = (y / e->zoom + e->y1) - (y / (e->zoom / 1.25));
            e->max_iter -= 3;
        }
        k == 3 || k == 5 ? e->zoom /= 1.25 : 0;
        if (k == 1)
		{
			e->x1 =  (x / e->zoom + e->x1) - (x / (e->zoom * 1.25));
			e->y1 = (y / e->zoom + e->y1) - (y / (e->zoom * 1.25));
            e->max_iter += 3;
        }
        k == 1 || k == 4 ? e->zoom *= 1.25 : 0;
        do_fractol(e);
	}
	return (1);
}