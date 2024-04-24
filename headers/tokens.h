#include "minishell.h"

typedef enum s_type
{
	WORD = 1,
	PIPE,
	NUMBER,
	RE_IN,
	RE_OUT,
	HERE_DOC,
	APPEND,
}			t_type;