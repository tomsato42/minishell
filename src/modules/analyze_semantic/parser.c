/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:45:42 by teando            #+#    #+#             */
/*   Updated: 2025/04/10 18:46:43 by teando           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "mod_sem.h"

t_status	parser(t_shell *shell)
{
	return (E_NONE);
}
int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	shell_init(&shell, env, 0);
	parser(shell);
	return (0);
}
