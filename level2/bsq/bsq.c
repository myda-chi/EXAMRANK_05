#include "bsq.h"

static int	min3(int a, int b, int c)
{
	if (b < a) a = b;
	if (c < a) a = c;
	return (a);
}

static int	parse_map(FILE *fp, int *rows, int *cols,
		char *empty, char *obstacle, char *full, char ***grid)
{
	char	*line = NULL;
	size_t	len = 0;
	int		i, j;

	if (getline(&line, &len, fp) <= 0)
		return (free(line), -1);
	if (sscanf(line, "%d %c %c %c", rows, empty, obstacle, full) != 4
		|| *rows <= 0 || *empty == *obstacle
		|| *empty == *full || *obstacle == *full)
		return (free(line), -1);
	free(line);
	*grid = (char **)malloc(sizeof(char *) * (*rows));
	if (!*grid)
		return (-1);
	*cols = -1;
	for (i = 0; i < *rows; i++)
	{
		(*grid)[i] = NULL;
		line = NULL;
		len = 0;
		if (getline(&line, &len, fp) <= 0)
			return (free(line), -1);
		j = strlen(line);
		if (j > 0 && line[j - 1] == '\n')
			line[--j] = '\0';
		if (j <= 0)
			return (free(line), -1);
		if (*cols == -1)
			*cols = j;
		else if (*cols != j)
			return (free(line), -1);
		for (j = 0; j < *cols; j++)
			if (line[j] != *empty && line[j] != *obstacle)
				return (free(line), -1);
		(*grid)[i] = line;
	}
	return (0);
}

static void	find_and_fill(char **grid, int rows, int cols,
		char obstacle, char full)
{
	int	i, j, best = 0, br = 0, bc = 0;
	int	*dp = (int *)calloc(rows * cols, sizeof(int));

	for (i = 0; i < rows; i++)
		for (j = 0; j < cols; j++)
		{
			if (grid[i][j] == obstacle)
				dp[i * cols + j] = 0;
			else if (i == 0 || j == 0)
				dp[i * cols + j] = 1;
			else
				dp[i * cols + j] = min3(dp[(i - 1) * cols + j],
					dp[i * cols + j - 1], dp[(i - 1) * cols + j - 1]) + 1;
			if (dp[i * cols + j] > best)
			{
				best = dp[i * cols + j];
				br = i;
				bc = j;
			}
		}
	for (i = br - best + 1; i <= br; i++)
		for (j = bc - best + 1; j <= bc; j++)
			grid[i][j] = full;
	free(dp);
}

static int	solve(FILE *fp)
{
	char	empty, obstacle, full, **grid;
	int		rows, cols, i;

	if (parse_map(fp, &rows, &cols, &empty, &obstacle, &full, &grid) < 0)
		return (-1);
	find_and_fill(grid, rows, cols, obstacle, full);
	for (i = 0; i < rows; i++)
	{
		fputs(grid[i], stdout);
		fputs("\n", stdout);
		free(grid[i]);
	}
	free(grid);
	return (0);
}

int	main(int argc, char **argv)
{
	FILE	*fp;
	int		i;

	if (argc == 1)
	{
		if (solve(stdin) < 0)
			fprintf(stderr, "map error\n");
		return (0);
	}
	for (i = 1; i < argc; i++)
	{
		fp = fopen(argv[i], "r");
		if (!fp || solve(fp) < 0)
			fprintf(stderr, "map error\n");
		if (fp)
			fclose(fp);
		if (i < argc - 1)
			fputs("\n", stdout);
	}
	return (0);
}
