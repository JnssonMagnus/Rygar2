#pragma once
#include "Font.h"

class Renderer;

class Text
{
public:
	void				Init(const char* aFontName);
	void				Draw();
	void				SetText(const std::string& aText);
	void				SetPosition(const Vector2<int>& aPosition);

	const Vector2<int>& GetPosition() const;

	static void			SetRenderer(Renderer* aRenderer);

private:
	std::string			myText;
	Font				myFont;
	Vector2<int>		myPosition;

	static Renderer*	ourRenderer;
};

