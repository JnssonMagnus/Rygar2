#pragma once
template<class T>
class Vector3;

typedef Vector3<unsigned char> Color;

template<class T>
class SharedResouce;

struct TextureResource;
struct FontResource;

typedef SharedResource<TextureResource> Texture;
typedef SharedResource<FontResource> Font;