#pragma once
#include "SharedResource.h"
#include <Vector2.h>

typedef struct _TTF_Font TTF_Font;

struct FontResource
{
	TTF_Font* myFont;	
};

typedef SharedResource<FontResource> Font;
