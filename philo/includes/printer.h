/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:57:21 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/05/02 17:00:27 by OrioPrisc        ###   ########.fr       */
/*   Updated: 2023/04/26 20:18:53 by orio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTER_H
# define PRINTER_H

# include <stddef.h>
# include "philo_time.h"
# include "philos.h"

typedef struct s_message
{
	t_ms		ms;
	size_t		id;
	t_action	action;
}	t_message;

void	*printer_main(void *foo);

//internals

typedef struct s_philo_monitor
{
	t_ms	last_eat;
	size_t	eats;
}	t_philo_monitor;

void	print_message(t_message *message);

//monitor functions
_Bool	check_death(const t_params *params, t_philo_monitor *philos, t_ms ms);
void	update_philo(const t_params *params, t_philo_monitor *philos,
			t_message *message);
void	kill_philo(size_t id, t_ms ms);
_Bool	check_end(const t_params *params, t_philo_monitor *philos);
#endif
