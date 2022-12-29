#pragma once
#include "typedefs.h"
#include <GrowingArray.h>
#include <Vector2.h>
#include <Vector3.h>
#include <string>

struct Particle;

struct TextRenderCommand
{
	Color					myColor;
	Vector2<int>			myPosition;
	std::string				myText;
	Font					myFont;
};

struct PSRenderCommand
{
	CU::GrowingArray<Particle>* myParticles;
	Texture						myTexture;
	int							myBlendMode = 1;
};

struct LineRenderCommand
{
	Vector2<int>			myStart;
	Vector2<int>			myEnd;
	Color					myColor;
	unsigned char			myAlpha = 255_uc;
};

struct RenderCommand
{
	enum eRenderOptions : unsigned char
	{
		eFlipped = 1,
		eNoZoom = 1 << 1
	};

	Color					myColor;
	Vector2f				myDstPos;
	Vector2<int>			myDstSize;
	Vector2<int>			mySrcPos;
	Vector2<int>			mySrcSize;
	Vector2<int>			myPivot;
	Texture					myTexture;
	float					myAngle;
	unsigned char			myAlpha = 255_uc;
	unsigned char			myOptions = 0;
};
