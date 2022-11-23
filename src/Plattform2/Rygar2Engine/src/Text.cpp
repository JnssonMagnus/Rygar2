#include "stdafx.h"
#include "Text.h"
#include "Renderer.h"

Renderer* Text::ourRenderer = nullptr;

void Text::Init(const char* aFontName)
{
	myFont = ResourceManager::GetInstance()->GetFont(aFontName);
}

void Text::Draw()
{
	DL_ASSERT(ourRenderer != nullptr && "Text isn't initiated with renderer yet!");
	ourRenderer->AddTextRenderCommand(myPosition, myText, myFont, { 255, 255, 255 });
}

void Text::SetText(const std::string& aText)
{
	myText = aText;
}

void Text::SetPosition(const Vector2<int>& aPosition)
{
	myPosition = aPosition;
}

const Vector2<int>& Text::GetPosition() const
{
	return myPosition;
}

void Text::SetRenderer(Renderer* aRenderer)
{
	DL_ASSERT(aRenderer != nullptr && "Renderer is nullptr!");
	ourRenderer = aRenderer;
}
