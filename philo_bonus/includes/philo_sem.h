/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sem.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:04:01 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/05/01 16:20:07 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_SEM_H
# define PHILO_SEM_H

# include <semaphore.h>

_Bool	my_sem_init(sem_t **sem, int value);
void	my_sem_close(sem_t *sem);

#endif
