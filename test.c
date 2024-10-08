/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:52:33 by babonnet          #+#    #+#             */
/*   Updated: 2024/10/06 22:29:56 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_pthread.h"
#include <stdio.h>

void *thread_routine(void *data)
{
	printf("%d\n", *(int *)data);
	return (NULL);
}

int main()
{
    t_pthread yes[100];
    int thread_ids[100];

    for (int i = 0; i <= 10; i++) {
        thread_ids[i] = i;
        ft_pthread_create(&yes[i], NULL, thread_routine, &thread_ids[i]);
    }

    return 0;
}
