#include "../../includes/main.h"


int drawAndShow(t_transform *transform, int x, int y)
{
    SDL_Rect dst = {
        .x = x,
        .y = y,
        .w = transform->canvW / 2,
        .h = transform->canvH / 2
        };

    draw(transform);
    renderDrawSpace_toDest(transform, dst);
    return 0;
}

void visualizer(t_transform *transform)
{
    SDL_Rect rect;

    rect.h = transform->canvH / 2;
    rect.w = transform->canvW / 2;
    rect.x = 0;
    rect.y = 0;

    drawAndShow(transform, rect.x, rect.y);

	rect.x += transform->canvW / 2;
	renderHoughSpace_AsPoints(transform, rect.x, rect.y);
    renderGridAt(rect.x, rect.y, rect.w, rect.h, 10);

	rect.x = 0;
    rect.y += transform->canvH / 2;
    renderGridAt(rect.x, rect.y, rect.w, rect.h, 10);

	renderHoughSpace_AsHeathMap(transform, rect.x, rect.y);
    renderMaximums(transform, rect.x, rect.y);

	rect.x += transform->canvW / 2;
    renderLinesUnbound(transform);

    SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer, 255, 255, 255, 255);

	SDL_RenderDrawLine(SDLX_Display_Get()->renderer, 0, transform->canvH / 2, transform->canvW, transform->canvH / 2);
    SDL_RenderDrawLine(SDLX_Display_Get()->renderer, transform->canvW / 2, 0, transform->canvW / 2, transform->canvW);

	SDL_SetRenderDrawColor(SDLX_Display_Get()->renderer, 0, 0, 0, 255);
    SDL_RenderCopy(SDLX_Display_Get()->renderer, transform->lines, NULL, &rect);
}
