#include "rush.h"

int isHoverDraw(SDLX_GUIElem *elem)
{
	SDLX_Input input;

	input = SDLX_InputGet();

	if (SDLX_PointInCircle(input.mouse,
	 (SDLX_Circle){elem->sprite->dst->x + 2, elem->sprite->dst->y + 5, 8}))
	{
		if (input.mouse_click == SDL_MOUSEBUTTONDOWN)
			elem->triggered = SDLX_TRUE;
		return SDLX_TRUE;
	}
	return SDLX_FALSE;
}

int DrawButtonHover(SDLX_GUIElem *elem)
{
	Context *ctx;
	SDLX_Animator *anim;
	Button *button;

	ctx = getCtx();
	button = elem->data;

	if (ctx->level.drawing == SDLX_TRUE && button->isTrigger == SDLX_FALSE)
	{

		// Fix by changing w to distance between them
		// to be correct but can't be done without extra sqrt
		// & will be a little off anyways
		// AVoid for now
		// }
		button->anim.active = SDLX_TRUE;
		button->isTrigger = SDLX_TRUE;
	}
	return 0;
}

int DrawButtonTrigger(SDLX_GUIElem *elem)
{
	Context *ctx;
	SDLX_Animator *anim;
	Button		*button;

	ctx = getCtx();

	button = elem->data;
	ctx->level.drawing = SDLX_TRUE;
	button->anim.active = SDLX_TRUE;
	button->isTrigger = SDLX_TRUE;

	return 0;
}
