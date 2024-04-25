#include "../headers/minishell.h"

int	read_input(void)
{
	t_lexer	lex;
	char	*input;
	
	lex.token_list = NULL;
	lex.input = NULL;
	lex.input = readline("./minishell ");
	if (input == NULL)
		return (1);
	lex.i = 0;
	lex_input(&lex);
	ft_putlst_fd(lex.token_list, 1);
	return (0);
}

void	lex_input(t_lexer *lex)
{
	t_list	*new_token;

	while (lex->input[lex->i] != '\0')
	{
		while (ft_isspace(lex->input[lex->i]) == true)
			lex->i++;
		//if (lex->input[lex->i] == '|')			//PIPE_TOKEN		
			//get_pipe_token(lex);	//new_token = ft_lstnew("PIPE", 6);
		if (lex->input[lex->i] == '<' || lex->input[lex->i] == '>')		
			new_token = get_redir_token(lex);	//RE_DIR_TOKENS
		else
			new_token = get_word_token(lex);	//WORD_TOKEN

		if (new_token == NULL)
		{
			if (lex->token_list != NULL)
				ft_lstclear(lex->token_list);
			return (NULL);
		}
		ft_lstadd_back(lex->token_list, new_token);
	}
}

t_list	*get_word_token(t_lexer *lex)
{
	t_list	*new_token;
	char	*attr;
	int		j;

	attr = NULL;
	
}

t_list	*get_redir_token(t_lexer *lex)
{
	t_list	*new_token;
	char	*attr;
	t_type	type;
	int		j;

	attr = NULL;
	if (lex->input[lex->i] == '<')
		type = 1; //GREAT == INFILE
	if (lex->input[lex->i] == '>')
		type = 2; //LESSER == OUTFILE
	lex->i++;
	if (lex->input[lex->i] == '<' && lex->input[lex->i - 1] == '<')
		type = 3; //LESSERLESSER == HERE_DOC
	if (lex->input[lex->i] == '>' && lex->input[lex->i - 1] == '>')
		type = 4; //GREATGREAT == APPEND
	while (ft_isspace(lex->input[lex->i]) == true)
		lex->i++;
	if (lex->input[lex->i] == '\0')
		type = 5; //NULL
	j = 0;
	while (lex->input[lex->i] != '\0')
	{
		if (ft_isspace(lex->input[lex->i]) == true)
			break ;
		lex->i++;
		j++;
	}
	attr = (char *)malloc((j + 1) * sizeof(char));
	ft_strlcpy(attr, lex->input + (lex->i - j), j);
	printf("%s\n", attr);
	printf("%c\n", lex->input[lex->i]);
	new_token = ft_lstnew(attr, type);
}