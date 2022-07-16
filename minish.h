#ifndef MINSH_H
# define MINSH_H

enum e_type{
	EXEC,
	REDER,	
	PIPE,
	LIST,
	BLOCK,
	BACK
}

typedef struct s_listcmd{
	int		type;
	void	*left;
	void	*right;
}			t_linecmd;

typedef struct s_pipecmd{
	int		type;
	void	*left;
	void	*right;
}			t_pipecmd;

typedef struct s_backmd{
 	int				type;
 	struct s_cmd	*cmd;
}

typedef struct s_execcmd{
	int			type;
	char		**argv;
	char		**argve;
}				t_execcmd;

typedef struct s_redircmd{
	int		type;
	char	*file;
	char	*efile;
	int		mode;
	int		fd;
	s_cmd	*cmd;
}			t_redircmd;


#endif
