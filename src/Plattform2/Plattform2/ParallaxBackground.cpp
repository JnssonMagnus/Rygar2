#include "stdafx.h"
#include "ParallaxBackground.h"

void ParallaxBackground::Render(const Vector2f& aCameraPosition)
{
	for (int layerIndex = 0; layerIndex < myLayers.Size(); layerIndex++)
	{
		myLayers[layerIndex].Render(aCameraPosition);
	}
}

void ParallaxBackground::AddLayer(const std::string_view aFilename, const Vector2f& aMovePercent)
{
	ParallaxLayer newLayer;
	newLayer.Init(aFilename.data(), aMovePercent);
	myLayers.Add(newLayer);
}
