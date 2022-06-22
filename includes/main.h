#ifndef MAIN_H
# define MAIN_H
# include "SDLX/SDLX.h"

# define WINDOW_NAME "Edge detection"
# define WINDOW_X SDL_WINDOWPOS_CENTERED
# define WINDOW_Y SDL_WINDOWPOS_CENTERED
# define WINDOW_H 500
# define WINDOW_W 500

# define DRAWSPACE_W WINDOW_W
# define DRAWSPACE_H WINDOW_H
// # define HOUGHSPACE_W 180
// # define HOUGHSPACE_H WINDOW_H
# define HOUGHSPACE_W 360
# define HOUGHSPACE_H WINDOW_H

# define DIVIDE_X 6
# define DIVIDE_Y 6
# define SEARCHRANGE 30

# define MAXTHRESHOLD 10
typedef struct s_transform
{
    int stage;
    int mode;
    int drawSpace[DRAWSPACE_W * DRAWSPACE_H];
    int houghSpace[HOUGHSPACE_W * HOUGHSPACE_H];
    int maximums[100];
    int maxIndex;
}               t_transform;

int draw(t_transform *transform);
int     divideNconquer(int w, int h, int *arr);
int     computeHough( int x, int y, int *arr, int w, int h);
int     visualizer(t_transform *transform);
int     compute(t_transform *transform);

int     renderHoughSpace(t_transform *transform);
int     renderDrawSpace(t_transform *transform);

#endif
