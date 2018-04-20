/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knzeng-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 22:38:25 by knzeng-e          #+#    #+#             */
/*   Updated: 2018/04/20 23:05:53 by knzeng-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opencl.h"

/* Find a GPU or CPU associated with the first available platform */
cl_device_id    create_device() 
{

    cl_platform_id platform;
    cl_device_id dev;
    int err;

    /* Identify a platform */
    err = clGetPlatformIDs(1, &platform, NULL);
    if (err < 0) 
    {
         ft_putstr("\nCouldn't identify a platform");
        exit(1);
    }
    /* Access a device */
    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &dev, NULL);
    if (err == CL_DEVICE_NOT_FOUND) 
    {
        err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &dev, NULL);
    }
    if (err < 0)
    {
        ft_putstr("\nCouldn't access any devices");
        exit(1);   
    }
    return (dev);
}
