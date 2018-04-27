/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_p.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 22:26:16 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/27 13:54:27 by knzeng-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

void        show_cam_mode(t_cam_mode cam_mode)
{
    if (cam_mode == MONO)
        ft_putstr("MONO VIEW\n");
    if (cam_mode == STEREO)
        ft_putstr("STEREO VIEW\n");
}

void		move_camera(t_rt *rt, SDL_Event ev)
{
	if (ev.type == SDL_MOUSEWHEEL)
		rt->cam->pos.z += ev.wheel.y;
	else if (ev.type == SDL_MOUSEMOTION)
	{
		rt->cam->rot.y += -(float)ev.motion.xrel / 20;
		rt->cam->rot.x += -(float)ev.motion.yrel / 20;
		rt->cam->right_cam->rot.y += -(float)ev.motion.xrel / 20;
		rt->cam->left_cam->rot.x += -(float)ev.motion.yrel / 20;
	}
	ft_raytracing(rt);
}

t_cam		*ini_cam(void)
{
	t_cam		*cam;

	if (!(cam = (t_cam*)malloc(sizeof(t_cam))))
		ft_malloc_error();
	cam->pos = ft_new_vect(0, 0, 0);
	cam->rot = ft_new_vect(0, 0, 0);
    cam->mode = MONO;
	if (!(cam->left_cam = (t_cam*)malloc(sizeof(t_cam))))
		ft_malloc_error();
	if (!(cam->right_cam = (t_cam*)malloc(sizeof(t_cam))))
		ft_malloc_error();
	cam->right_cam->pos = ft_new_vect(-3, 0, 0);
	cam->left_cam->pos = ft_new_vect(3, 0, 0);
	return (cam);
}

int			cam_lst(t_rt *rt, t_cam *cam)
{
	rt->cam = cam;
	return (1);
}

int			ft_add_cam(int fd, t_rt *rt)
{
	int			ret;
	char		*line;
	char		**datas;
	t_cam		*cam;

	cam = ini_cam();
	rt->switch_cam_mode = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		datas = ft_strsplit(line, ' ');
		if (datas[0] == 0)
			ret++;
		else if (ft_strcmp(datas[0], "coo:") == 0)
			cam->pos = get_coo(datas, ERREUR_COOR);
		else if (ft_strcmp(datas[0], "rot:") == 0)
			cam->rot = get_coo(datas, ERREUR_ROTA);
		else if (ft_strcmp(datas[0], "view:") == 0)
        {
            cam->mode = get_view_mode(datas, ERREUR_MODE);
            ft_putstr("\nCAMERA MODE ===> ");
            show_cam_mode(cam->mode);
        }
		else if (datas[1] == NULL && ft_check_obj(datas[0], fd, rt) == 1)
			ret++;
		else
			ft_bad_arg(5);
		ft_freetab(datas);
		free(line);
	}
	return (cam_lst(rt, cam));
}
