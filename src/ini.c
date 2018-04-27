/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 01:04:42 by kboucaud          #+#    #+#             */
/*   Updated: 2017/10/21 01:09:54 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

void	ft_ini_viewplane(t_rt *rt)
{
	t_coo	cam_pos;
	t_coo	cam_forw;
	t_coo	cam_up;
	t_coo	cam_right;

	cam_pos = ((rt->cam->mode == MONO) ? rt->cam->pos : rt->cam->right_cam->pos);
	cam_forw = ((rt->cam->mode == MONO) ? rt->cam->forw : rt->cam->right_cam->forw);
	cam_up = ((rt->cam->mode == MONO) ? rt->cam->up : rt->cam->right_cam->up);
	cam_right = ((rt->cam->mode == MONO) ? rt->cam->right : rt->cam->right_cam->right);
	if (!(rt->view = (t_view*)malloc(sizeof(t_view))))
		ft_malloc_error();
	rt->view->height = 35;
	rt->view->length = 50;
	rt->view->up_left = ft_add_vect(cam_up,
	ft_add_vect(ft_mult_vect(PLN_DST, cam_forw), ft_sub_vect(ft_mult_vect(
	rt->view->height / 2, cam_up), ft_mult_vect(rt->view->length / 2,
	cam_right))));
}

void	ft_ini_cam(t_rt *rt)
{
	rt->cam->forw = ft_new_vect(0, 0, 1);
	rt->cam->up = ft_new_vect(0, 1, 0);
	rt->cam->right = ft_new_vect(1, 0, 0);

	rt->cam->left_cam->forw = ft_new_vect(0, 0, 1);
	rt->cam->left_cam->up = ft_new_vect(0, 1, 0);
	rt->cam->left_cam->right = ft_new_vect(1, 0, 0);
	
	rt->cam->right_cam->forw = ft_new_vect(0, 0, 1);
	rt->cam->right_cam->up = ft_new_vect(0, -1, 0);
	rt->cam->right_cam->right = ft_new_vect(1, 0, 0);
	ft_ini_viewplane(rt);
}

void	ft_malloc_ini(t_rt *rt)
{
	ft_create(rt);
	if (!(rt->inter = (t_inter*)malloc(sizeof(t_inter))))
		ft_malloc_error();
	if (!(rt->ray = (t_ray*)malloc(sizeof(t_ray))))
		ft_malloc_error();
	if (!(rt->light_ray = (t_ray*)malloc(sizeof(t_ray))))
		ft_malloc_error();
	if (!(rt->inter->angle = (t_ray*)malloc(sizeof(t_ray))))
		ft_malloc_error();
	if (!(rt->inter->mat = (t_material*)malloc(sizeof(t_material))))
		ft_malloc_error();
	if (!(rt->inter->col = (t_material*)malloc(sizeof(t_material))))
		ft_malloc_error();
	if (!(rt->inter->kdif = (t_material*)malloc(sizeof(t_material))))
		ft_malloc_error();
	if (!(rt->inter->kspe = (t_material*)malloc(sizeof(t_material))))
		ft_malloc_error();
	if (!(rt->op = (t_options*)malloc(sizeof(t_options))))
		ft_malloc_error();
}

void	ft_reset(t_rt *rt)
{
	rt->ray->o = rt->cam->pos;
	rt->inter->obj = -1;
}

void	ft_ini(t_rt *rt)
{
	ft_malloc_ini(rt);
	ft_ini_cam(rt);
	ft_reset(rt);
	make_rot(rt);
	rt->op->sepia = 0;
	rt->op->blwh = 0;
	rt->op->maintain = 0;
	rt->op->aa = 1;
}
