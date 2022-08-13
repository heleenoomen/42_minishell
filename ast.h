/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 07:51:15 by ktashbae          #+#    #+#             */
/*   Updated: 2022/08/13 18:05:51 by kanykei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "lists/list.h"
// # include <../libft/libft.h>

# define EOL -1
# define SUCCESS 0
# define ERROR 1
# define CHAR_ERR 2
# define TOKENS 14
# define NONTERM 20

typedef enum e_grammar
{
	NT_START,
	NT_PREFIX,
	NT_PREFIX1,
	NT_SUFFIX,
	NT_SUFFIX1,
	NT_AND_OR,
	NT_AND_OR1,
	NT_PIPESPLIT,
	NT_PIPESPLIT1,
	NT_COMMANDSET,
	NT_COMMANDSET1,
	NT_SUBSHELL,
	NT_CMD,
	NT_CMD1,
	NT_CMD2,
	NT_REDIR,
	NT_REDIR1,
	NT_IO_REDIR,
	NT_IO_FILE,
	NT_IO_HERE,
	T_PIPE,
	T_LBRACE,
	T_RBRACE,
	T_AND,
	T_OR,
	T_LESS,
	T_GREAT,
	T_DGREAT,
	T_LESSGREAT,
	T_DLESS,
	T_ASSIGN,
	T_STRING,
	T_EOF,
	T_UNKNOWN,
}	t_grammar;

typedef struct s_prompt
{
	char	*input;
	long	len;
	long	index;
}	t_prompt;

typedef struct s_token
{
	int			input_len;
	char		*input;
	t_grammar	type;
	t_prompt	*line;
}				t_token;

typedef struct s_lexer
{
	char	*tokens;
	int		len;
	int		index;
}			t_lexer;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef enum e_node_type
{
	N_CMD,
	N_PIPE,
	N_REDIR,
	N_AND_OR,
	N_OR,
	N_AND,
	N_SUB,
	N_ASSIGN,
	N_DUMM,
}	t_node_type;

typedef struct s_cmd_def
{
	t_list	*cmd;
	t_list	*redir;
	t_list	*assign;
}			t_cmd_def;

typedef struct s_ast
{
	int				node_id;
	int				nodes;
	t_node_type		type;
	t_cmd_def		*cmds;
	struct s_ast	*child;
	struct s_ast	*prev_sibling;
	struct s_ast	*next_sibling;
}					t_ast;

typedef struct s_parser
{
	t_grammar	token_type;
	t_node_type	node_type;
	t_ast		*node;
}	t_parser;

typedef struct s_minishell
{
	int		line;
	char	*line;
	void	(***table)(t_list **, t_grammar);
	t_list	*env;
	t_list	*value;
}	t_minishell;

/* LEXER and support functions*/
void	skip_whitespace(t_prompt *line);
void	update_char(t_prompt *line);
char	set_peek(t_prompt *line);
char	get_charbychar(t_prompt *line);
void	run_lexer(t_lexer *lex);
t_list	*get_token_list(t_lexer *lex, char *line);
void	type_checker(t_token *token, int *cmd, int *flag);
int		flag_checker(char *line);
t_list	*lexer(t_prompt *line);

/* TOKENIZER and support functions*/
t_token	*init_token(void);
t_token	*launch_tokens(t_token *token, t_prompt *line, char *lex);
void	parser(t_lexer *lex, t_prompt *line);
void	get_token_type(t_token *token, char *lex);
int		check_value_assign(char *str);
int		update_buffer(t_lexer *lex, t_prompt *line, char c);
void	token_operator(t_lexer *lex, t_prompt *line, char c);
void	save_buffer(t_lexer *lex, char c);
char	*increase_buffer(void *temp1, int current_size, int update_size);
void	init_buffer(t_lexer *lexer);
t_token	*tokenizer(t_lexer *lex, t_prompt *line);

/* PARSER and AST building */
void	*lst_get_cmd(t_list *cmd);
void	*lst_get_content(t_list **lst);
void	add_nodes_parser(t_list **tokens, t_parser *node_p, t_list **cmd);
int		scan_nodes_parser(t_list *token_list, t_parser *node_p, \
t_list **cmds, void (***table)(t_list **, t_grammar));
void	remove_ast_node(t_ast **node);
t_ast	*add_child(t_ast *top, t_ast *child);
t_ast	*init_new_node(t_node__type n_type);
void	*create_node(t_grammar tok_type);
void	init_parse(t_list **cmds_list, t_ast **node);
t_ast	*check_syntax(t_list *token_list, void (***table)(t_list **, t_grammar));
void	init_content(t_prompt *content, char *input);
t_ast	*ast_builder(char *input, void (***table)(t_list **, t_grammar));

/* LL1 grammar table */
void	run_redirections_grand(void (***table)(t_list **, t_grammar));
void	get_suffix_cmd(void (***table)(t_list **, t_grammar));
void	split_to_prefix(void (***table)(t_list **, t_grammar));
void	child_commands(void (***table)(t_list **, t_grammar));
void	commandset_and_io_here_file(void (***table)(t_list **, t_grammar));
void	pipe_and_subshell(void (***table)(t_list **, t_grammar));
void	start_and_or(void (***table)(t_list **, t_grammar));

void	run_start(t_list **stack_table, t_grammar type);
void	run_and_or(t_list **stack_table, t_grammar type);
void	run_and_or1(t_list **stack_table, t_grammar type);
void	set_epsilon(t_list **stack_table, t_grammar type);
void	run_pipe(t_list **stack_table, t_grammar type);
void	run_pipe1(t_list **stack_table, t_grammar type);
void	run_subshell(t_list **stack_table, t_grammar type);
void	run_commandset(t_list **stack_table, t_grammar type);
void	run_commandset1(t_list **stack_table, t_grammar type);
void	run_command(t_list **stack_table, t_grammar type);
void	run_command1(t_list **stack_table, t_grammar type);
void	run_command2(t_list **stack_table, enum e_symbol tok_type);



/* TRAVERSE AST */
void	branch_node(t_parser **new_node, t_parser *old_node, int node_type);
void	branch_child_node(t_parser **new_node, t_parser *prev_node, int type);
void	*create_new_node(t_grammar tok_type);
void	*lst_get_content(t_list **lst);
void	*lst_get_cmd(t_list *cmd);

#endif
