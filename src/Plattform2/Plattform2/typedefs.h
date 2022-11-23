#pragma once
template<class T>
class Vector3;
struct FontResource;


typedef Vector3<unsigned char> Color;

template<class T>
class SharedResouce;
typedef SharedResource<TextureResource> Texture;

template<class T>
class SharedResouce;
typedef SharedResource<FontResource> Font;