/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:13:51 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/05/05 18:16:36 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_sem.h"
#include "philo.h"
#include "libft.h"
#include <fcntl.h>
#include <sys/stat.h>

_Bool	my_sem_init(sem_t **sem, int value)
{
	*sem = 0;
	*sem = sem_open("/philo-sem.temp.1", O_CREAT | O_EXCL, 07700, value);
	if (*sem == SEM_FAILED)
		return (1);
	sem_unlink("/philo-sem.temp.1");
	return (0);
}

void	my_sem_close(sem_t *sem)
{
	if (sem == NULL || sem == SEM_FAILED)
		return ;
	sem_close(sem);
}

void	destroy_sems(t_semaphores *sems)
{
	my_sem_close(sems->queue_sem);
	my_sem_close(sems->stop_sem);
	my_sem_close(sems->forks);
}
