#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static int g_width, g_heigth;

int count_neighbour(char *board, int x, int y)
{
	int dy, dx, nx, ny, count = 0;
	for(dy = -1; dy <= 1; dy++)
	{
		for(dx = -1; dx <=1; dx++)
		{
			if(!dy && !dx)
				continue;
			nx = x + dx;
			ny = y + dy;

			if(nx >= 0 && nx < g_width && ny >= 0 && ny < g_height && board[ny * g_width + nx])
				count++;
		}
	}
	return(count);
}

void step(char *board)
{
	int size = g_heigth * g_width, neighbour, i;
	char *next = calloc(size, 1);
	if(!next)
		return ;
	for(i = 0; i < size; i++)
	{
		neighbour = count_neighbour(board, i % g_width, i / g_heigth);
		next[i] = board[i] ? (neighbour == 2 || neighbour == 3) : (neighbour == 3);
	}
	for(i = 0; i < size; i++)
		board[i] = next[i];
	free(next);
}

int main(int ac, char **av)
{
	int pen_y = 0, pen_x = 0, drawning = 0, iteration, i;
	char *board, cmd;

	if(ac != 4)
		return(1);
	g_width = atoi(av[1]);
	g_heigth = atoi(av[2]);
	iteration = atoi(av[3]);
	if(g_heigth <= 0 || g_width <= 0 || iteration < 0)
		return(1);
	board = calloc(g_heigth * g_width, 1);
	if(!board)
		return(1);
	while(read(0, &cmd, 1) > 0)
	{
		switch(cmd)
		{
			case 'x' : drawning = !drawning; break;
			case 'w' : pen_y--; break;
			case 'a' : pen_x--; break;
			case 's' : pen_y++; break;
			case 'd' : pen_x++; break;
		}
		if(drawning && pen_x >=  0 && pen_x <g_width && pen_y >=0 && pen_y <g_heigth)
			board[pen_y * g_width + pen_x] = 1;
	}
	for(i = 0; i < iteration; i++)
		step(board);
	for(i = 0; i < g_heigth * g_width; i++)
	{
		putchar(board[i] ? 'O' : ' ');
		if((i + 1) % g_width == 0)
			putchar('\n');
	}
	free(board);
	return(0);
}