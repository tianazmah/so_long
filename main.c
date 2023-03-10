#include "so_long.h"

char **clone_map(char **map, int y)
{
    char **clone;
    int i;

    i = 0;
    clone = (char **) malloc (sizeof(char*) * y);
    while (i < y)
    {
        clone[i] = ft_strdup(map[i]);
        i++;
    }
    return (clone);
}

int main(int argc, char **argv)
{
    int fd;
    char *line;
    char **map;
    char **path;
    size_t x;
    int y;
    int i = 0;

    if (argc != 2)
    {
        printf("you need to provide a map file\n");
        exit(0);
    }
    if (ft_strncmp(ft_strrchr(argv[1], '.'), ".ber", 4) != 0)
    {
        printf("you should provide a '.ber' file\n");
        exit(0);
    }
    
    x = 0;
    y = 0;
    map = NULL;
    fd = open(argv[1], O_RDONLY);
    while (1)
    {
        line = ft_strtrim(get_next_line(fd),"\n");
        if (!line)
            break;
        if (x == 0)
        {
            x = ft_strlen(line);
            check_horzontal_wall(line);
        }
        if (ft_strlen(line) != x)
        {
            printf("problem in line length\n");
            exit(0);
        }
        y++;
        map = add_line_map(map, line, y);
    }
    check_horzontal_wall(map[y - 1]);
    path = clone_map(map, y);
    check_path(path, y);
    check_collectables(path, y);
    while (i < y)
    {
        ft_printf("%s", path[i]);
        i++;
    }
    init_window(map, y);
}
