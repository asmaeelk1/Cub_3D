#include <stdio.h>
#include <stdlib.h>

// typedef struct s_textures
// {
// 	char    *north;
// 	char    *south;
// 	char    *west;
// 	char    *east;
// }    t_textures;

int main()
{
	// t_textures *data;
	// data = (t_textures *)malloc(sizeof(t_textures));
	// data->north = "north";
	// data->south = "south";
	// data->west = "west";
	// data->east = "east";
	// printf("Output of sizeof * data->north = %lu\n", sizeof * data->north);
	// printf("Output of sizeof(data->north) = %lu\n", sizeof(data->north));

	int *v = &64;
	printf("Output of *v = %d\n", *v);
}