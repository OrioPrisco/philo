/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:30:26 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/04/25 15:47:25 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TIME_H
# define PHILO_TIME_H

typedef unsigned long long	t_ms;

t_ms	get_ms_since(t_ms time);
t_ms	get_ms(void);
void	wait_ms(t_ms ms);

#endif
