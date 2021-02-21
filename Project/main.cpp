#include <Windows.h>
#include <iostream>
using namespace std;

#include "GL/glut.h"

#include "Raymarch/Shading.hpp"

//////////////////////////////////////////////////////////// 
// Definitions /////////////////////////////////////////////
////////////////////////////////////////////////////////////

#define WINDOW_WIDTH  (800)
#define WINDOW_HEIGHT (400)
#define WINDOW_TITLE  ("RayTracing")

//////////////////////////////////////////////////////////// 
// Global Variables ////////////////////////////////////////
////////////////////////////////////////////////////////////

int _gScreenWidth;
int _gScreenHeight;
Texture2D _gBackBufferTexture;
RaymarchShading _gRaymarchShading;

GLubyte* _gBackBufferPixels = nullptr;

////////////////////////////////////////////////////////////
// Framework Callback Functions ////////////////////////////
////////////////////////////////////////////////////////////

void OnInitialize(void)
{
	_gRaymarchShading.Initialize(_gBackBufferTexture);
	_gRaymarchShading.Draw(_gBackBufferTexture);
}

void OnRelease(void)
{
	_gRaymarchShading.Release();
}

void OnUpdate(void)
{
	// DO NOTHING
}

////////////////////////////////////////////////////////////
// GLUT Callback Functions /////////////////////////////////
////////////////////////////////////////////////////////////

void OnWindowRepaint(void)
{
	// Framework Callback Function - OnUpdate
	OnUpdate();

	// Update GLUT Backbuffer
	int pixelCount = WINDOW_WIDTH * WINDOW_HEIGHT;
	for (int i = 0; i < pixelCount; ++i)
	{
		Color3f& color = _gBackBufferTexture.Pixel(i);
		_gBackBufferPixels[i * 3 + 0] = (GLubyte)(color.r * 255.0f + 0.5f);
		_gBackBufferPixels[i * 3 + 1] = (GLubyte)(color.g * 255.0f + 0.5f);
		_gBackBufferPixels[i * 3 + 2] = (GLubyte)(color.b * 255.0f + 0.5f);
	}

	// Draw Backbuffer Color
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, _gBackBufferPixels);
	glutSwapBuffers();
}

////////////////////////////////////////////////////////////
// Main ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
	// Initialize Screen Size And Backbuffer
	_gScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	_gScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	_gBackBufferTexture.Initialize(WINDOW_WIDTH, WINDOW_HEIGHT);
	_gBackBufferPixels = new GLubyte[WINDOW_WIDTH * WINDOW_HEIGHT * 3];

	// Framework Callback Function - OnInitialize
	OnInitialize();

	// Create GL Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition((_gScreenWidth - WINDOW_WIDTH) / 2, (_gScreenHeight - WINDOW_HEIGHT) / 2);
	glutCreateWindow(WINDOW_TITLE);
	glutDisplayFunc(&OnWindowRepaint);
	glutMainLoop();

	// Framework Callback Function - OnRelease
	OnRelease();

	// Release Backbuffer data
	if (_gBackBufferPixels != nullptr)
	{
		delete[] _gBackBufferPixels;
		_gBackBufferPixels = nullptr;
	}

	return 0;
}