#pragma once
#include "ParallaxLayer.h"
#include <GrowingArray.h>

class ParallaxBackground
{
public:
	void								Render(const Vector2f& aCameraPosition);
	void								AddLayer(const std::string_view aFilename, const Vector2f& aMovePercent);

private:
	CU::GrowingArray<ParallaxLayer>		myLayers;
};
