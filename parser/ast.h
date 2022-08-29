/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 07:51:15 by ktashbae          #+#    #+#             */
/*   Updated: 2022/08/26 14:54:27 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include "minishell.h"
# include "libft/libft.h"
# define EOL -1
# define SUCCESS 0
# define ERROR 1
# define CHAR_ERR 2
# define TOKENS 14
# define NONTERM 20

typedef enum e_grammar
{
	NT_START,
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
	NT_PREFIX,
	NT_PREFIX1,
	NT_SUFFIX,
	NT_SUFFIX1,
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
	int		line_len;
	char	*line;
	void	(***table)(t_list **, t_grammar);
	t_list	*env;
	t_list	*value;
}	t_minishell;

void	init_minishell(t_minishell *shell);
void	copy_input_line(t_prompt *line, char *readline);

/* LEXER and support functions*/
t_list	*lexer(t_prompt *line);
t_lexer	*init_lexer(void);
t_list	*get_token_list(t_lexer *lex, t_prompt *line);
void	type_checker(t_token *tok, int *is_balanced, int *cmd_flag);
int		quote_checker(char *line);
void	flag_exists(int flag);
void	delete_token(void *token);
char	get_charbychar(t_prompt *line);
char	set_peek(t_prompt *line);
void	update_char(t_prompt *line);
void	skip_whitespace(t_prompt *line);
void	save_to_lexer(t_lexer *lex, char c);
int		update_lexer(t_lexer *lex, t_prompt *line, char c);
char	*increase_buffer(void *temp1, int current_size, int update_size);
void	init_buffer(t_lexer *lexer);
void	lexer_get_value(t_lexer *lex, t_prompt *line);

/* TOKENIZER and support functions*/
t_token	*tokenizer(t_lexer *lex, t_prompt *line);
t_token	*create_token(t_token *token, t_prompt *line, char *value);
void	token_operator(t_lexer *lex, t_prompt *line, char c);
void	set_token_type(t_token *token, char *lex);
void	token_operator(t_lexer *lex, t_prompt *line, char c);
int		check_value_assign(char *str);
t_token	*init_token(void);

/* PARSER and AST building */
t_ast	*ast_builder(char *input, void (***table)(t_list **, t_grammar));
void	init_content(t_prompt *content, char *input);
t_ast	*check_syntax(t_list *token_list, void (***table)(t_list **, \
		t_grammar));
int		scan_nodes_parser(t_list *token_list, t_parser *node_p, \
		t_list **cmds, void (***table)(t_list **, t_grammar));
void	add_nodes_parser(t_list **tokens, t_parser *node_p, t_list **cmd);
void	*create_new_node(t_grammar tok_type);
void	free_ast_tree(t_ast **ast);
void	free_ast_commands(t_cmd_def **cmds);
void	remove_ast_node(t_ast **node);
void	init_parse(t_list **cmds_list, t_ast **node);
t_ast	*init_new_node(t_node_type n_type);
void	free_token(void *token);
t_ast	*add_child(t_ast *top, t_ast *child);
void	free_node(t_ast *node);
void	init_parser(t_list **cmds_list, t_ast **node);
void	*create_node(t_grammar tok_type);

/* Parse TRAVERSER */
void	run_start(t_list **stack_table, t_grammar type);
void	run_and_or(t_list **stack_table, t_grammar type);
void	run_and_or1(t_list **stack_table, t_grammar type);
void	set_epsilon(t_list **stack_table, t_grammar type);
void	run_pipe(t_list **stack_table, t_grammar type);
void	run_pipe1(t_list **stack_table, t_grammar type);
void	run_subshell(t_list **stack_table, t_grammar type);
void	run_prefix_with_cmd(t_list **stack_table, t_grammar type);
void	run_prefix_with_cmd1(t_list **stack_table, t_grammar type);
void	run_cmd_suffix(t_list **stack_table, t_grammar type);
void	run_cmd_suffix1(t_list **stack_table, t_grammar type);
void	redirect_to_file(t_list **stack_table, t_grammar type);
void	run_redirections(t_list **stack_table, t_grammar type);
void	run_redirections1(t_list **stack_table, t_grammar type);
void	run_io_file(t_list **stack_table, t_grammar type);
void	run_io_here(t_list **stack_table, t_grammar type);
void	run_commandset(t_list **stack_table, t_grammar type);
void	run_commandset1(t_list **stack_table, t_grammar type);
void	run_command(t_list **stack_table, t_grammar type);
void	run_command1(t_list **stack_table, t_grammar type);
void	run_command2(t_list **stack_table, t_grammar type);

/* Traversing utils */
void	branch_node(t_parser **new_node, t_parser *old_node, int node_type);
void	branch_child_node(t_parser **new_node, t_parser *prev_node, int type);
void	*create_new_node(t_grammar tok_type);
void	*lst_get_content(t_list **lst);
void	*lst_get_cmd(t_list *cmd);

/* LL1 main table */
void	start_and_or(void (***table)(t_list **, t_grammar ));
void	pipe_and_subshell(void (***table)(t_list **, t_grammar));
void	split_to_prefix(void (***table)(t_list **, t_grammar));
void	run_redirections_grand(void (***table)(t_list **, t_grammar));
void	commandset_and_io_here_file(void (***table)(t_list **, t_grammar));
void	get_suffix_cmd(void (***table)(t_list **, t_grammar));
void	child_commands(void (***table)(t_list **, t_grammar));

#endif
