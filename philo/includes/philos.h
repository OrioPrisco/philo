/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:53:34 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/05/11 16:48:48 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include <pthread.h>
# include <stddef.h>
# include "philo_time.h"

typedef struct s_params			t_params;
typedef struct s_shared_data	t_shared_data;

typedef struct s_fork
{
	pthread_mutex_t	*mutex;
	_Bool			held;
}	t_fork;
//shared data lock also acts as a print lock
typedef struct s_philo_data
{
	const t_params	*params;
	size_t			philo_id;
	t_fork			left_fork;
	t_fork			right_fork;
}	t_philo_data;

typedef struct s_philo
{
	t_philo_data	data;
	pthread_t		thread;
}	t_philo;

typedef enum e_action
{
	TAKE_FORK,
	SLEEP,
	EAT,
	THINK,
	DIE,
	ERROR,
}	t_action;

//init
_Bool	populate_philos(t_philo *philos, pthread_mutex_t *mutexes,
			const t_params *params);
_Bool	launch_philos(t_philo *philos, size_t philo_num, t_shared_data *shared);
void	join_philos(t_philo *philos, size_t to_join, t_shared_data *shared);
//utils
_Bool	philo_say(const t_philo_data *philo, t_action action);
void	take_fork(t_fork *fork);
void	lay_fork(t_fork *fork);
//actions
_Bool	philo_eat(t_philo_data *philo);
_Bool	philo_sleep(t_philo_data *philo);
_Bool	philo_think(const t_philo_data *philo);
void	*philo_main(void *data);
#endif
