#pragma once

#include "Color3f.hpp"

class Texture2D
{
public:

	Texture2D() : _width(0), _height(0), _data(nullptr)
	{
		// DO NOTHING
	}

	Texture2D(int width, int height) : _width(width), _height(height)
	{
		_data = new Color3f[width * height];
	}

	~Texture2D()
	{
		if (_data != nullptr)
			delete[] _data;
	}

public:

	void Clear(const Color3f& color)
	{
		int pixelCount = _width * _height;
		for (int i = 0; i < pixelCount; ++i)
			_data[i] = color;
	}

	inline Color3f& Pixel(int i)
	{
		return _data[i];
	}

	inline Color3f& Pixel(int x, int y)
	{
		return _data[y * _width + x];
	}

	inline Color3f& Pixel(float u, float v)
	{
		int x = (int)(u * (float)(_width - 1));
		int y = (int)(v * (float)(_height - 1));
		return _data[y * _width + x];
	}

	void Initialize(int width, int height)
	{
		if (_data != nullptr)
			delete[] _data;

		_width = width;
		_height = height;
		_data = new Color3f[width * height];
	}

	void Release()
	{
		if (_data != nullptr)
		{
			delete[] _data;
			_data = nullptr;
		}

		_width = 0;
		_height = 0;
	}

	int GetWidth() const
	{
		return _width;
	}

	int GetHeight() const
	{
		return _height;
	}

private:

	int _width;
	int _height;
	Color3f* _data;

};