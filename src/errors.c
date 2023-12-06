#include "cub3D.h"
#include <string.h>

void error_msg(t_game *game, int i)
{
	ft_printf("Error\n");
	ft_printf("%s\n", game->errors[i]);
}

void showError(int i, t_game *game)
{
	printf("Error\n");
	printf("%s", game->errors[i]);
	exit(0);
}

char* copyString(char s[])
{
    char* s2;
	int size;

	size = ft_strlen(s);
    s2 = (char*)malloc(size);
 
    strcpy(s2, s);
    return (char*)s2;
}

void	load_errors(t_game *game)
{
	game->errors = malloc(sizeof(char *) * 18);
	game->errors[VALID] = copyString("VALIDO\n");
	game->errors[INVALID_MAP] = copyString("Invalid Map\n");
	game->errors[INVALID_ARGS] = copyString("Arguments invalids try: 'cub3d maps/teste.cub'\n");
	game->errors[INVALID_EXTENSION] = copyString("The file is not valid, the '.cub' extension is required.\n");
	game->errors[FILE_NOT_FOUNDED] = copyString("File not founded\n");
	game->errors[INVALID_TEXTURE] = copyString("Is necessary texture to all directions - NO - SO - EA - WE\n");
	game->errors[INVALID_COLORS] = copyString("RGB Values invalids\n");
	game->errors[CARDINAL_POINTS] = copyString("NO - SO - EA - WE\n");
	game->errors[INVALID_TEXTURE_EA] = copyString("Texture EA - Invalid.\n");
	game->errors[INVALID_TEXTURE_WE] = copyString("Texture WE - Invalid.\n");
	game->errors[INVALID_TEXTURE_SO] = copyString("Texture SO - Invalid.\n");
	game->errors[INVALID_TEXTURE_NO] = copyString("Texture NO - Invalid.\n");
}