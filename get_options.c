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

uint32_t		get_options(int argc, char *argv[])
{
	uint32_t options;

	(void) argc;
	options = 0;
	options = ft_strequ(*argv, "md5") ? MD5 : options;
	options = ft_strequ(*argv, "sha256") ? SHA256 : options;
	if (options == 0)
		x(-1, USAGE);
	while (*++argv && **argv == '-')
		options |= check_options((*argv) + 1);
	return (options);
}
