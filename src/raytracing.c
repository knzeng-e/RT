/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 20:11:06 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/24 19:57:30 by knzeng-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

void		ft_convert(t_rt *rt)
{
	if (rt->inter->mat->r > 1.0)
		rt->inter->mat->r = 1.0;
	if (rt->inter->mat->g > 1.0)
		rt->inter->mat->g = 1.0;
	if (rt->inter->mat->b > 1.0)
		rt->inter->mat->b = 1.0;
	rt->inter->mat->r = (int)(rt->inter->mat->r * 255);
	rt->inter->mat->g = (int)(rt->inter->mat->g * 255);
	rt->inter->mat->b = (int)(rt->inter->mat->b * 255);
}

void		ft_ray(t_rt *rt, int x, int y, int type)
{
	ft_check_object(rt);
	ft_convert(rt);
	if (type == 2)
		return ;
	put_pxl(rt->data, x, y, rt->inter->mat);
	put_pxl_base(rt->data, x, y, rt->inter->mat);
}

void		ft_ini_ray(t_rt *rt, double x, double y)
{
	rt->ray->dir = ft_sub_vect(ft_add_vect(rt->view->up_left,
	ft_mult_vect(rt->view->length * x / WIN_LEN, rt->cam->right)),
	ft_mult_vect(rt->view->height * y / WIN_HEIGHT, rt->cam->up));
	rt->ray->dir = ft_rotation(rt->ray->dir, rt->cam->rot);
	rt->ray->dir = ft_normalize(rt->ray->dir);
}


void		ft_raytracing(t_rt *rt)
{
    SDL_Thread  *thread_1 = SDL_CreateThread(thread_render_1, "Thread 1", rt);
    SDL_WaitThread(thread_1, NULL);
    SDL_Thread  *thread_2 = SDL_CreateThread(thread_render_2, "Thread 2", rt);
    SDL_WaitThread(thread_2, NULL);
    SDL_Thread  *thread_3 = SDL_CreateThread(thread_render_3, "Thread 3", rt);
    SDL_WaitThread(thread_3, NULL);
    SDL_Thread  *thread_4 = SDL_CreateThread(thread_render_4, "Thread 4", rt);
    SDL_WaitThread(thread_4, NULL);
}
