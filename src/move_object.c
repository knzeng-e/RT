/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knzeng-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 02:09:19 by knzeng-e          #+#    #+#             */
/*   Updated: 2018/04/27 13:02:38 by knzeng-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 13:40:59 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/24 02:09:04 by knzeng-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

void		move_sphere(t_rt *rt, SDL_Event ev)
{
	rt->sphere = rt->start->sph;
	while (rt->sphere->id != rt->op->id)
		rt->sphere = rt->sphere->next;
	if (ev.type == SDL_MOUSEMOTION)
	{
		rt->sphere->o.x += (float)ev.motion.xrel / 100;
		rt->sphere->o.y += -(float)ev.motion.yrel / 100;
	}
	else if (ev.type == SDL_MOUSEWHEEL)
		rt->sphere->o.z += (float)ev.wheel.y / 100;
	if (rt->sphere->pln != NULL)
	{
		if (ev.type == SDL_MOUSEMOTION)
		{
			rt->sphere->pln->o.x += (float)ev.motion.xrel / 100;
			rt->sphere->pln->o.y += -(float)ev.motion.yrel / 100;
		}
		else if (ev.type == SDL_MOUSEWHEEL)
			rt->sphere->pln->o.z += (float)ev.wheel.y / 100;
	}
}

void		move_plane(t_rt *rt, SDL_Event ev)
{
	rt->plane = rt->start->pln;
	while (rt->plane->id != rt->op->id)
		rt->plane = rt->plane->next;
	if (ev.type == SDL_MOUSEMOTION)
	{
		rt->plane->o.x += (float)ev.motion.xrel / 100;
		rt->plane->o.y += -(float)ev.motion.yrel / 100;
	}
	else if (ev.type == SDL_MOUSEWHEEL)
		rt->plane->o.z += (float)ev.wheel.y / 100;
}

void		move_cyl(t_rt *rt, SDL_Event ev)
{
	rt->cylinder = rt->start->cyl;
	while (rt->cylinder->id != rt->op->id)
		rt->cylinder = rt->cylinder->next;
	if (ev.type == SDL_MOUSEMOTION)
	{
		rt->cylinder->o.x += (float)ev.motion.xrel / 100;
		rt->cylinder->o.y += -(float)ev.motion.yrel / 100;
	}
	else if (ev.type == SDL_MOUSEWHEEL)
		rt->cylinder->o.z += (float)ev.wheel.y / 100;
	if (rt->cylinder->pln != NULL)
	{
		if (ev.type == SDL_MOUSEMOTION)
		{
			rt->cylinder->pln->o.x += (float)ev.motion.xrel / 100;
			rt->cylinder->pln->o.y += -(float)ev.motion.yrel / 100;
		}
		else if (ev.type == SDL_MOUSEWHEEL)
			rt->cylinder->pln->o.z += (float)ev.wheel.y / 100;
	}
}

void		move_cone(t_rt *rt, SDL_Event ev)
{
	rt->cone = rt->start->con;
	while (rt->cone->id != rt->op->id)
		rt->cone = rt->cone->next;
	if (ev.type == SDL_MOUSEMOTION)
	{
		rt->cone->o.x += (float)ev.motion.xrel / 100;
		rt->cone->o.y += -(float)ev.motion.yrel / 100;
	}
	else if (ev.type == SDL_MOUSEWHEEL)
		rt->cone->o.z += (float)ev.wheel.y / 100;
	if (rt->cone->pln != NULL)
	{
		if (ev.type == SDL_MOUSEMOTION)
		{
			rt->cone->pln->o.x += (float)ev.motion.xrel / 100;
			rt->cone->pln->o.y += -(float)ev.motion.yrel / 100;
		}
		else if (ev.type == SDL_MOUSEWHEEL)
			rt->cone->pln->o.z += (float)ev.wheel.y / 100;
	}
}

void		get_obj(t_rt *rt, int x, int y)
{
	rt->op->maintain = 1;
	ft_ini_ray(rt, x, y);
	rt->light = rt->start->lgh;
	rt->inter->obj = 0;
	rt->inter->dst = MAX;
	check_forms(rt, 0);
	rt->op->obj = rt->inter->obj;
	rt->op->id = rt->inter->num;
}

int        moving_sphere(void *rt)
{
    SDL_Event ev;
	if (((t_rt *)rt)->op->obj == SPH)
		move_sphere(rt, ev);
    return (0);
}

int        moving_plane(void *rt)
{
    SDL_Event ev;
	if (((t_rt *)rt)->op->obj == PLN)
		move_plane(rt, ev);
    return (0);
}

int        moving_cyl(void *rt)
{
    SDL_Event ev;
	if (((t_rt *)rt)->op->obj == CYL)
		move_cyl(rt, ev);
    return (0);
}

int        moving_cone(void *rt)
{
    SDL_Event ev;

    if (((t_rt *)rt)->op->obj == CON)
        move_cone(rt, ev);
    return (0);
}

void		move_object(t_rt *rt, SDL_Event ev)
{
    SDL_Thread  *move_sphere_thread;
    SDL_Thread  *move_plane_thread;
    SDL_Thread  *move_cyl_thread;
    SDL_Thread  *move_cone_thread;

    move_sphere_thread = SDL_CreateThread(moving_sphere, "sphere_move", rt);
    SDL_WaitThread(move_sphere_thread, NULL);
    move_plane_thread = SDL_CreateThread(moving_plane, "plane_move", rt);
    SDL_WaitThread(move_plane_thread, NULL);
    move_cyl_thread = SDL_CreateThread(moving_cyl, "cyl_move", rt);
    SDL_WaitThread(move_cyl_thread, NULL);
    move_cone_thread = SDL_CreateThread(moving_cone, "cone_move", rt);
    SDL_WaitThread(move_cone_thread, NULL);
    /*	else if (rt->op->obj == PLN)
        move_plane(rt, ev);
        else if (rt->op->obj == CYL)
        move_cyl(rt, ev);
        else if (rt->op->obj == CON)
        move_cone(rt, ev);*/
    ft_reset(rt);
    ft_raytracing(rt);
}
