#include "stdafx.h"
#include "BaseObject.h"

BaseObject::BaseObject()
{
    rect_ = new SDL_Rect;
	rect_->x = 0;
	rect_->y = 0;
	p_object_ = NULL;
}


BaseObject::~BaseObject()
{
	Free();
}

bool BaseObject::LoadImg(std::string path, SDL_Renderer* screen)
{
	SDL_Surface* load_surface = IMG_Load(path.c_str());
	SDL_Texture* new_texture = NULL;
	if (load_surface != NULL)
	{
		new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
		if (new_texture != NULL)
		{
			rect_->h = load_surface->h;
			rect_->w = load_surface->w;
		}
		SDL_FreeSurface(load_surface);
	}
	p_object_ = new_texture;
	return p_object_ != NULL;

}

void BaseObject::Free()
{
	if (p_object_ != NULL)
	{
		SDL_DestroyTexture(p_object_);
		p_object_ = NULL;
		rect_->w = 0;
		rect_->h = 0;
	}
}

void BaseObject::Render(SDL_Renderer* des)
{
    //std::cout << rect_->y << std::endl;
	SDL_Rect renderquad = {rect_->x, rect_->y, rect_->w, rect_->h};
	SDL_RenderCopy(des, p_object_, 0, &renderquad);
}

