#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define ROWS 7
#define COLS 12
#define VISITED '1'

char * map[] = {
    "11111",
    "1W001",
    "11111",
};

char * visited[] = {
    "00000",
    "00000",
    "00000",
};

void	ft_flood(int y, int x, int height, char **map, char **visited)
{
	//printf("map height: %d\n", scene->map.height);
	if (y < 0 || x < 0 || y >= height || x >= (int)strlen(map[y])
		|| map[y][x] == '_'
		|| visited[y][x] == VISITED)
	{
		//printf("y: %d x: %d\n", y, x);
		return ;
	}
	//printf("map flood current line: %s\n", scene->map.flood[y]);
	visited[y][x] = VISITED;
	if ((map[y][x] == '0' || map[y][x] == '1'))
		map[y][x] = '2';
	//printf("flood start:\n");
	//printf("map flood current line: %s\n", scene->map.flood[y]);
	//map[y][x] += 2;
	//print_arr(map);
	ft_flood(y + 1, x, height, map, visited);
	ft_flood(y - 1, x, height, map, visited);
	ft_flood(y, x + 1, height, map, visited);
	ft_flood(y, x - 1, height, map, visited);
	ft_flood(y + 1, x + 1, height, map, visited);
	ft_flood(y + 1, x - 1, height, map, visited);
	ft_flood(y - 1, x + 1, height, map, visited);
	ft_flood(y - 1, x - 1, height, map, visited);
}

void printMap(char **arr) {
    for (int i = 0; i < 3; i++) {
        printf("%s\n", arr[i]);
    }
}

int main() {
    int i;
    char **flood = (char**)malloc(4*sizeof(char*));
    char **marked = (char**)malloc(4*sizeof(char*));
    for(i = 0; i < 3; i++){
        //printf("%d\n", i);
        flood[i] = strdup(map[i]);
        marked[i] = strdup(visited[i]);
    }

    printf("Original Map:\n");
    printMap(flood);
    printf("Original visited:\n");
    printMap(marked);

    int startX, startY;

    startX = 1;
    startY = 1;

    ft_flood(startY, startX, 3, flood, marked);

    printf("\nMap after Flood Fill:\n");
    printMap(flood);
    printf("\nMarked after Flood Fill:\n");
    printMap(marked);
    return 0;
}