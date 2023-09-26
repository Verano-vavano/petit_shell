#include "math.h"

bool is_math(const char *cmd)
{
	while(*cmd)
	{
		if (*cmd == '(' && *(cmd + 1) == '(')
		{
			cmd += 2;
			while(*cmd)
			{
				if (*cmd == ')' && *(cmd + 1) == ')')
					return (true);
				cmd++;
			}
		}
		else
			cmd++;
	}
	return (false);
}
