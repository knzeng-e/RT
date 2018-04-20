/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knzeng-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 08:04:38 by knzeng-e          #+#    #+#             */
/*   Updated: 2018/04/20 21:42:47 by knzeng-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"


int     thread_render_1(void * rt)
{
    int i;
    int j;

    i = 0;
    while (i < WIN_LEN / 2)
    {
        j = 0;
        while (j < WIN_HEIGHT / 2)
        {
			ft_ini_ray(rt, i, j);
			ft_ray(rt, i, j, 1);
            j++;
        }
        i++;
    }
    return (0);
}

int     thread_render_2(void *rt)
{
    int k;
    int l;

    k = WIN_LEN / 2;
    while (k < WIN_LEN)
    {
        l = 0;
        while (l < WIN_HEIGHT / 2)
        {
			ft_ini_ray(rt, k, l);
			ft_ray(rt, k, l, 1);
            l++;
        }
        k++;
    }
    return (0);
}

int     thread_render_3(void * rt)
{
    int i;
    int j;

    i = 0;
    while (i < WIN_LEN / 2)
    {
        j = WIN_HEIGHT / 2;
        while (j < WIN_HEIGHT)
        {
			ft_ini_ray(rt, i, j);
			ft_ray(rt, i, j, 1);
            j++;
        }
        i++;
    }
    return (0);
}

int     thread_render_4(void * rt)
{
    int i;
    int j;

    i = WIN_LEN / 2;
    while (i < WIN_LEN)
    {
        j = WIN_HEIGHT / 2;
        while (j < WIN_HEIGHT)
        {
			ft_ini_ray(rt, i, j);
			ft_ray(rt, i, j, 1);
            j++;
        }
        i++;
    }
    return (0);
}
