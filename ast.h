/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 07:51:15 by ktashbae          #+#    #+#             */
/*   Updated: 2022/08/09 16:18:40 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <../libft/libft.h>

# define EOL -1
# define SUCCESS 0
# define ERROR 1
# define CHAR_ERR 2
# define NONTERM 20
# define TOKENS 14

typedef enum e_grammar
{
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
	TK_START,
	TK_PREFIX,
	TK_PREFIX1,
	TK_SUFFIX,
	TK_SUFFIX1,
	TK_AND_OR,
	TK_AND_OR1,
	TK_PIPELINE,
	TK_PIPELINE1,
	TK_COMMAND,
	TK_COMMAND1,
	TK_SUBSHELL,
	TK_SIMPLE_CMD,
	TK_SIMPLE_CMD1,
	TK_SIMPLE_CMD2,
	TK_REDIR,
	TK_REDIR1,
	TK_IO_REDIRECT,
	TK_IO_FILE,
	TK_IO_HERE,
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

#endif
