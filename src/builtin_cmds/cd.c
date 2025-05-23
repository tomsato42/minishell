/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:59:45 by teando            #+#    #+#             */
/*   Updated: 2025/04/28 14:06:02 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cmds.h"

t_status	__cd_tilde(char path[], char *arg, t_shell *sh)
{
	char	*home;

	home = ms_getenv("HOME", sh);
	if (home[0] == '\0')
	{
		ft_dprintf(2, "cd: HOME not set\n");
		free(home);
		return (1);
	}
	free(home);
	if (arg == NULL)
		path_launcher(path, "~", F_OK, sh);
	else
		path_launcher(path, arg, F_OK, sh);
	return (E_NONE);
}

t_status	__cd_oldpwd(char path[], char *arg, t_shell *sh)
{
	char	*oldpwd;

	if (arg[1] != '\0')
		return (ft_dprintf(2, ES_INVALID_OPTION, arg), -2);
	oldpwd = ms_getenv("OLDPWD", sh);
	if (!oldpwd || !*oldpwd)
	{
		ft_dprintf(2, "cd: OLDPWD not set\n");
		if (oldpwd)
			xfree((void **)&oldpwd);
		return (1);
	}
	if (path_launcher(path, oldpwd, F_OK, sh) == -1)
		return (ft_dprintf(2, "minishell: cd: %s: %s\n", oldpwd,
				strerror(errno)), -1);
	printf("%s\n", oldpwd);
	xfree((void **)&oldpwd);
	return (E_NONE);
}

t_status	__cd(int argc, char **argv, t_shell *sh)
{
	char	mv_dir[PATH_MAX + 1];

	if (argc >= 3)
		return (ft_dprintf(2, ES_TOO_MANY_ARGS, argv[0]), 1);
	else if (argc == 1 || (argv[1][0] == '~' && argv[1][1] == '\0'))
	{
		if (__cd_tilde(mv_dir, argv[1], sh) != E_NONE)
			return (1);
	}
	else if (argc == 2 && ft_strcmp(argv[1], "-") == 0)
	{
		if (__cd_oldpwd(mv_dir, argv[1], sh) != E_NONE)
			return (2);
	}
	else if (argc == 2 && argv[1][0] == '-')
		return (ft_dprintf(2, ES_INVALID_OPTION, argv[1]), 2);
	else if (path_launcher(mv_dir, argv[1], F_OK, sh) == -1)
		return (ft_dprintf(2, ES_NO_SUCH_FOD, argv[1]), 1);
	if (chdir(mv_dir) == -1 || access(mv_dir, F_OK))
		return (ft_dprintf(2, "cd: %s: %s\n", mv_dir, strerror(errno)), 1);
	ms_setenv_item("OLDPWD", sh->cwd, sh);
	ms_path_cleancpy(sh->cwd, mv_dir, PATH_MAX + 1);
	ms_setenv_item("PWD", mv_dir, sh);
	return (E_NONE);
}
