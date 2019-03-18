#include "ft_ssl.h"

static uint32_t	check_options(char *opstr)
{
	int options;

	options = 0;
	while (*opstr)
	{
		*opstr == 'p' ? options |= P_OP : 0;
		*opstr == 'q' ? options |= Q_OP : 0;
		*opstr == 'r' ? options |= R_OP : 0;
		*opstr == 's' ? options |= S_OP : 0;
		if (ft_strchr("pqrs", *opstr) == NULL)
			x(-1, USAGE);
		opstr++;
	}
	return (options);
}

uint32_t		get_options(char *argv[])
{
	uint32_t options;

	options = 0;
	while (*++argv && **argv == '-')
		options |= check_options((*argv) + 1);
	if (*argv)
		options |= ARGS;
	return (options);
}
