/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:47:22 by teando            #+#    #+#             */
/*   Updated: 2025/03/14 15:48:23 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ENV_H
#define MS_ENV_H

#include "libft.h"
#include <limits.h>

/*
** 環境変数構造体
*/
typedef struct s_env_var
{
	char *key;
	char *value;
} t_env_var;

/*
** 環境変数操作関数
*/
void free_env_var(void *env_var);

#endif
