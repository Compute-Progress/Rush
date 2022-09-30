#include "../../includes/main.h"


void computeHough( int x, int y, int *arr, int w, int h)
{
    int angle = 0;
    double theta;
    int d = 0;

    // Formula: x cos(theta) + y sin(theta) = d
    while (angle < w)
    {
        theta = (angle * M_PI) / 180;
        d = x * cos(theta) + y * sin(theta);
        if ((d * w + angle) >= 0 && (d * w + angle) < (h * w))
        {
            arr[(d * w + angle)] += 1;
        }
        angle++;
    }
}

int getVal(int *houghSpace, int pos)
{
	if (pos >= 0 && pos < HOUGHSPACE_W * HOUGHSPACE_H)
		return houghSpace[pos];

	return -1;
}

int getMax_inRange(int *houghSpace, int pos)
{
    int row;
    int col;
    int maxPos;
    int tryPos;

    maxPos = pos;
    col = 0;
    while (col < SEARCHRANGE)
    {
        row = 0;
        while (row < SEARCHRANGE)
        {
            tryPos = pos + ((row * HOUGHSPACE_W) + col);

			if (getVal(houghSpace, pos + ((row * HOUGHSPACE_W) + col)) > houghSpace[maxPos])
						  maxPos = pos + ((row * HOUGHSPACE_W) + col);

			if (getVal(houghSpace, pos - ((row * HOUGHSPACE_W) + col)) > houghSpace[maxPos])
						  maxPos = pos - ((row * HOUGHSPACE_W) + col);

			if (getVal(houghSpace, pos + ((row * HOUGHSPACE_W) - col)) > houghSpace[maxPos])
						  maxPos = pos + ((row * HOUGHSPACE_W) - col);

			if (getVal(houghSpace, pos - ((row * HOUGHSPACE_W) - col)) > houghSpace[maxPos])
						  maxPos = pos - ((row * HOUGHSPACE_W) - col);

            row++;
        }
        col++;
    }
    return maxPos;
}

void getLocalMax(t_transform *transform, int start)
{
    int prevIndex;
    int nextIndex;

    if (start >= HOUGHSPACE_W * HOUGHSPACE_H || start < 0)
        return ;

    prevIndex = start;
    while (1)
    {
        nextIndex = getMax_inRange(transform->houghSpace, prevIndex);
        if (nextIndex == prevIndex)
        {
            if (transform->maxIndex < 100 && (transform->houghSpace[nextIndex]) >= transform->treshold)
            {
                transform->maximums[transform->maxIndex] = nextIndex;
                transform->maxIndex++;
            }
            break ;
        }

        prevIndex = nextIndex;
	}
}

void divideNconquer(t_transform *transform)
{
    int stepX;
    int stepY;
    int currX;
    int currY;

    stepX = HOUGHSPACE_W / DIVIDE_X;
    stepY = HOUGHSPACE_H / DIVIDE_Y;
    currX = 0;
    while (currX < HOUGHSPACE_W)
    {
        currY = 0;
        while (currY < HOUGHSPACE_H)
        {
            getLocalMax(transform,
                (currY * HOUGHSPACE_W) + currX);
            currY += stepY;
        }
        currX += stepX;
    }

}

void compute(t_transform *transform)
{
    renderDrawSpace(transform);

    if (transform->canDraw)
        draw(transform);
    else
    {
        renderLinesUnbound(transform);
        SDL_RenderCopy(SDLX_Display_Get()->renderer, transform->lines, NULL, NULL);
    }
}
