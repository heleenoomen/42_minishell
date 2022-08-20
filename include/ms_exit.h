/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:46:13 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/20 16:06:23 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_EXIT_H
# define MS_EXIT_H

/*malloc failed, no memory available*/
# define NO_MEM		1	

/*environment variable not set*/
# define NO_ENV		2

/*file not found*/
# define NO_FILE	3

/*file error flags for panic_file function*/
/*file type is executable*/
# define ISEXEC		0b10

/*file exists*/
# define EXIST		0b100

/*path variable not set*/
# define NOPA		0b1000

#endif
