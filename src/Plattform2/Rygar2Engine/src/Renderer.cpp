#include "stdafx.h"
#include "Renderer.h"
#include "Sprite.h"
#include "Text.h"
#include "texture.h"
#include "camera.h"
#include "particle.h"
#include "ParticleEmitter.h"
#include "DebugDrawer.h"
#include <SDL.h>
#include <SDL_TTF.h>

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Init()
{
	mySDL_Pointers = SDL::Init(WINDOW_WIDTH, WINDOW_HEIGHT);
	myRenderTarget = SDL_CreateTexture(mySDL_Pointers.myRenderer, SDL_PIXELFORMAT_RGBA8888, 
		SDL_TextureAccess::SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderTarget(mySDL_Pointers.myRenderer, myRenderTarget);
	Sprite::SetRenderer(this);
	Text::SetRenderer(this);
	DebugDrawer::SetRenderer(*this);
	PostMaster::GetInstance()->Register(this, eMessageTypes::ePushCamera);
	PostMaster::GetInstance()->Register(this, eMessageTypes::ePopCamera);
}

void Renderer::AddTextRenderCommand(const Vector2<int>& aPosition, const std::string& aText, Font aFont, const Color& aColor)
{
	myTextRenderCommands[1].Add({ aColor, aPosition, aText, aFont });
}

void Renderer::AddGUIRenderCommand(const Vector2f& aDstPos, const Vector2<int>& aDstSize, const Vector2<int>& aSrcPos, const Vector2<int>& aSrcSize, const Color& aColor, Texture aTexture)
{
	myGUIRenderCommands[1].Add({ aColor, aDstPos, aDstSize, {0, 0}, aDstSize, {0, 0}, aTexture });
}

void Renderer::AddPSRenderCommand(const PSRenderCommand& aPSRenderCommand)
{
	myPSRenderCommands[1].Add(aPSRenderCommand);
}

void Renderer::AddDebugLine(const Vector2<int>& aStart, const Vector2<int>& aEnd)
{
	LineRenderCommand debugLineCommand;
	debugLineCommand.myStart = aStart;
	debugLineCommand.myEnd = aEnd;
	debugLineCommand.myColor = { 255, 255, 255 };
	myDebugLines[1].Add(debugLineCommand);
}

void Renderer::AddRenderCommand(RenderCommand& aRenderCommand)
{
	myRenderCommands[1].Add(aRenderCommand);
}

void Renderer::AddRenderCommand(const Vector2f& aDstPos, const Vector2<int>& aDstSize, const Vector2<int>& aPivot, Texture aTexture, const float aAngle, const bool aNoZoom)
{
	myRenderCommands[1].Add({ { 255_uc, 255_uc, 255_uc }, aDstPos, aDstSize, {0, 0}, aDstSize, aPivot, aTexture, aAngle, 255_uc, static_cast<unsigned char>(static_cast<unsigned char>(aNoZoom) * RenderCommand::eRenderOptions::eNoZoom) });
}

void Renderer::AddRenderCommand(const Vector2f& aDstPos, const Vector2<int>& aDstSize, const Vector2<int>& aSrcPos, const Vector2<int>& aSrcSize, Texture aTexture, const float aAngle, const unsigned char aAlpha)
{
	myRenderCommands[1].Add({ { 255_uc, 255_uc, 255_uc }, aDstPos, aDstSize, aSrcPos, aSrcSize,  {0, 0}, aTexture, aAngle, aAlpha });
}

void Renderer::Draw()
{
	SDL_RenderClear(mySDL_Pointers.myRenderer);

	CopyCurrentCameraData();
	DrawSprites();
	DrawParticleSystems();
	DrawDebugLines();
	DrawGUISprites();
	DrawText();

	SDL_SetRenderTarget(mySDL_Pointers.myRenderer, nullptr);
	SDL_RenderCopy(mySDL_Pointers.myRenderer, myRenderTarget, nullptr, nullptr);

	SDL_RenderPresent(mySDL_Pointers.myRenderer);

	SDL_SetRenderTarget(mySDL_Pointers.myRenderer, myRenderTarget);
}

void Renderer::SwapRenderBuffer()
{
	myRenderCommands[0].Clear();
	myTextRenderCommands[0].Clear();
	myGUIRenderCommands[0].Clear();
	myPSRenderCommands[0].Clear();
	myDebugLines[0].Clear();

	std::swap(myRenderCommands[0], myRenderCommands[1]);
	std::swap(myTextRenderCommands[0], myTextRenderCommands[1]);
	std::swap(myGUIRenderCommands[0], myGUIRenderCommands[1]);
	std::swap(myPSRenderCommands[0], myPSRenderCommands[1]);
	std::swap(myDebugLines[0], myDebugLines[1]);
}

void Renderer::UpdateCamera()
{
	if (myCameraStack.Empty() == false)
	{
		myCameraStack.Top()->Update();
		Message msg;
		msg.myMessageType = eMessageTypes::eCameraMoved;
		msg.myPosition = myCameraStack.Top()->GetPosition();
		PostMaster::GetInstance()->SendMessage(msg);
	}
}

void Renderer::RecieveMessage(const Message& aMessage)
{
	switch (aMessage.myMessageType)
	{
	case eMessageTypes::ePushCamera:
		PushCamera(static_cast<Camera*>(aMessage.myVoidPointer));
		break;
	case eMessageTypes::ePopCamera:
		PopCamera();
		break;
	}	
}

SDL_Renderer* Renderer::GetSDL_Renderer()
{
	return mySDL_Pointers.myRenderer;
}

void Renderer::PushCamera(Camera* aCamera)
{
	DL_ASSERT(aCamera != nullptr && "tried to push a nullptr camera");
	myCameraStack.Push(aCamera);
}

void Renderer::PopCamera()
{
	DL_ASSERT(myCameraStack.Empty() == false && "Can't pop empty camera stack!");
	myCameraStack.Pop();
}

void Renderer::DrawParticleSystems()
{
	SDL_Rect dst;
	SDL_Rect src;
	src.x = src.y = 0;
	src.w = src.h = 64;

	for (int renderCommandIndex = 0; renderCommandIndex < myPSRenderCommands[0].Size(); renderCommandIndex++)
	{
		PSRenderCommand& renderCommand = myPSRenderCommands[0][renderCommandIndex];
		SDL_Texture* texture = renderCommand.myTexture.GetResource()->myTexture;
		SDL_SetTextureBlendMode(texture, static_cast<SDL_BlendMode>(renderCommand.myBlendMode));

		for (int particleIndex = 0; particleIndex < renderCommand.myParticles->Size(); particleIndex++)
		{
			const Particle& particle = (*renderCommand.myParticles)[particleIndex];
			dst.x = static_cast<int>(particle.myPosition.myX) - particle.mySize.myX / 2;
			dst.y = static_cast<int>(particle.myPosition.myY) - particle.mySize.myY / 2;
			dst.w = particle.mySize.myX;
			dst.h = particle.mySize.myY;
			WorldPosToCameraSpace(dst, true);

			SDL_SetTextureAlphaMod(texture, particle.myColor.myA * 255);
			SDL_SetTextureColorMod(texture, particle.myColor.myR * 255, particle.myColor.myG * 255, particle.myColor.myB * 255);
			SDL_RenderCopy(mySDL_Pointers.myRenderer, texture, nullptr, &dst);
		}
	}
}

void Renderer::DrawDebugLines()
{
	for (int renderCommandIndex = 0; renderCommandIndex < myDebugLines[0].Size(); renderCommandIndex++)
	{
		LineRenderCommand& renderCommand = myDebugLines[0][renderCommandIndex];
		SDL_SetRenderDrawColor(mySDL_Pointers.myRenderer, renderCommand.myColor.r, renderCommand.myColor.g, renderCommand.myColor.b, renderCommand.myAlpha);
		SDL_Rect start = { renderCommand.myStart.x, renderCommand.myStart.y, 0.f, 0.f };
		SDL_Rect end = { renderCommand.myEnd.x, renderCommand.myEnd.y, 0.f, 0.f };
		WorldPosToCameraSpace(start, true);
		WorldPosToCameraSpace(end, true);
		SDL_RenderDrawLine(mySDL_Pointers.myRenderer, start.x, start.y, end.x, end.y);
	}
}

void Renderer::CopyCurrentCameraData()
{
	myCopiedCameraData.myPosition = myCameraStack.Top()->GetPosition();
	myCopiedCameraData.myZoom = myCameraStack.Top()->GetZoom();

}

void Renderer::WorldPosToCameraSpace(SDL_Rect& aWorldPos, const bool aUseZoom)
{
	const float cameraZoom = aUseZoom ? myCopiedCameraData.myZoom : 1.f;
	float fx, fy, fw, fh;
	aWorldPos.x = fx = ((aWorldPos.x - myCopiedCameraData.myPosition.myX) * cameraZoom) + 0.5f + (SCREEN_WIDTH / 2.f + 0.5f);
	aWorldPos.y = fy = ((aWorldPos.y - myCopiedCameraData.myPosition.myY) * cameraZoom) + 0.5f + (SCREEN_HEIGHT / 2.f + 0.5f);
	aWorldPos.w = fw = (aWorldPos.w * cameraZoom) + 0.5f;
	aWorldPos.h = fh = (aWorldPos.h * cameraZoom) + 0.5f;

	float errorX = fx + fw - aWorldPos.x - aWorldPos.w;
	float errorY = fy + fh - aWorldPos.y - aWorldPos.h;

	aWorldPos.w += static_cast<int>(errorX > 0.5f);
	aWorldPos.h += static_cast<int>(errorY > 0.5f);
}

void Renderer::DrawSprites()
{
	SDL_Rect dstRect;
	SDL_Rect srcRect;
	SDL_Point pivot;

	for (int renderCommandIndex = 0; renderCommandIndex < myRenderCommands[0].Size(); renderCommandIndex++)
	{
		const RenderCommand& renderCommand = myRenderCommands[0][renderCommandIndex];
		
		dstRect.x = static_cast<int>(renderCommand.myDstPos.myX) - renderCommand.myPivot.myX;
		dstRect.y = static_cast<int>(renderCommand.myDstPos.myY) - renderCommand.myPivot.myY;
		dstRect.w = renderCommand.myDstSize.myX;
		dstRect.h = renderCommand.myDstSize.myY;

		srcRect.x = renderCommand.mySrcPos.myX;
		srcRect.y = renderCommand.mySrcPos.myY;
		srcRect.w = renderCommand.mySrcSize.myX;
		srcRect.h = renderCommand.mySrcSize.myY;

		pivot.x = renderCommand.myPivot.myX;
		pivot.y = renderCommand.myPivot.myY;

		SDL_Texture* texture = renderCommand.myTexture.GetResource()->myTexture;

		SDL_SetTextureAlphaMod(texture, renderCommand.myAlpha);
		SDL_SetTextureColorMod(texture, renderCommand.myColor.r, renderCommand.myColor.g, renderCommand.myColor.b);

		WorldPosToCameraSpace(dstRect, !(renderCommand.myOptions & RenderCommand::eRenderOptions::eNoZoom));

		SDL_RenderCopyEx(mySDL_Pointers.myRenderer, texture, &srcRect, &dstRect, 
			(renderCommand.myAngle / (PI * 2.0) * 360.0), &pivot, static_cast<SDL_RendererFlip>(renderCommand.myOptions & RenderCommand::eRenderOptions::eFlipped));
	}
}

void Renderer::DrawText()
{
	SDL_Color color;
	SDL_Surface* text_surface;
	SDL_Rect dest;

	for (int renderCommandIndex = 0; renderCommandIndex < myTextRenderCommands[0].Size(); renderCommandIndex++)
	{
		TTF_Font* font = myTextRenderCommands[0][renderCommandIndex].myFont.GetResource()->myFont;
		const std::string& text = myTextRenderCommands[0][renderCommandIndex].myText;
		dest.x = myTextRenderCommands[0][renderCommandIndex].myPosition.myX;
		dest.y = myTextRenderCommands[0][renderCommandIndex].myPosition.myY;

		color.r = myTextRenderCommands[0][renderCommandIndex].myColor.r;
		color.g = myTextRenderCommands[0][renderCommandIndex].myColor.g;
		color.b = myTextRenderCommands[0][renderCommandIndex].myColor.b;
		color.a = 255;

		text_surface = TTF_RenderText_Solid(font, text.c_str(), color);
		DL_ASSERT(text_surface != nullptr && "Failed to print text!");

		SDL_Texture* sdl_texture = SDL_CreateTextureFromSurface(mySDL_Pointers.myRenderer, text_surface);

		dest.w = text_surface->w;
		dest.h = text_surface->h;
		
		SDL_RenderCopy(mySDL_Pointers.myRenderer, sdl_texture, nullptr, &dest);
		
		SDL_FreeSurface(text_surface);
		SDL_DestroyTexture(sdl_texture);
	}
}

void Renderer::DrawGUISprites()
{
	SDL_Rect dstRect;
	SDL_Rect srcRect;
	SDL_Texture* texture;

	for (int renderCommandIndex = 0; renderCommandIndex < myGUIRenderCommands[0].Size(); renderCommandIndex++)
	{
		texture = myGUIRenderCommands[0][renderCommandIndex].myTexture.GetResource()->myTexture;

		const RenderCommand& renderCommand = myGUIRenderCommands[0][renderCommandIndex];

		dstRect.x = static_cast<int>(renderCommand.myDstPos.myX);
		dstRect.y = static_cast<int>(renderCommand.myDstPos.myY);
		dstRect.w = renderCommand.myDstSize.myX;
		dstRect.h = renderCommand.myDstSize.myY;

		srcRect.x = renderCommand.mySrcPos.myX;
		srcRect.y = renderCommand.mySrcPos.myY;
		srcRect.w = renderCommand.mySrcSize.myY;
		srcRect.h = renderCommand.mySrcSize.myY;

		SDL_SetTextureColorMod(texture, renderCommand.myColor.r, renderCommand.myColor.g, renderCommand.myColor.b);
		SDL_SetTextureAlphaMod(texture, renderCommand.myAlpha);

		SDL_RenderCopy(mySDL_Pointers.myRenderer, texture, &srcRect, &dstRect);
	}
}
