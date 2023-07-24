/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejinkim <sejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 21:50:47 by sejinkim          #+#    #+#             */
/*   Updated: 2023/07/24 21:30:41 by sejinkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	redir_in(t_node *node, t_exec_info *info)
{
	info->fd_in = open(node->cmd_args[0], O_RDONLY);
	if (info->fd_in < 0)
		return (0);
	return (1);
}

int	redir_out(t_node *node)
{
	int	fd;

	fd = open(node->cmd_args[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (0);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (0);
	return (1);
}

int	redir_append(t_node *node)
{
	int	fd;

	fd = open(node->cmd_args[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (0);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (0);
	return (1);
}

void	redirection(t_node *node, t_exec_info *info)
{
	t_bool	success;

	success = TRUE;
	if (node->type == AST_REDIR_IN)
		success = redir_in(node, info);
	else if (node->type == AST_REDIR_OUT)
		success = redir_out(node);
	else if (node->type == AST_REDIR_APPEND)
		success = redir_append(node);
	else if (node->type == AST_HEREDOC)
		success = heredoc(node, info);
	if (!success)
		exit(err("error"));
}
