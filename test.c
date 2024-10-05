/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:52:33 by babonnet          #+#    #+#             */
/*   Updated: 2024/10/04 18:19:56 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_pthread.h"
#include "includes/syscall.h"
#include <stdio.h>

/* void *thread_routine(void *data) */
/* { */
/* 	printf("%d\n", *(int *)data); */
/* 	return (NULL); */
/* } */

int main()
{
	ft_syscall(SYS_WRITE, 1, "yoo\n", 4);
	/* t_pthread yes[100]; */
	/*  */
	/* for (int i = 0; i <= 10; i++) */
	/* 	ft_pthread_create(&yes[i], NULL, thread_routine, &i); */
}
