#pragma once
#include <string>

class OpenGLTexture3D
{
public: // Methods
    OpenGLTexture3D();
    void Create(int width, int height, int depth);
	void Bind(unsigned int slot);
	unsigned int GetID();
	unsigned int GetWidth();
	unsigned int GetHeight();
	unsigned int GetDepth();

private:
	unsigned int _ID = 0;
	unsigned char* _data = nullptr;
	int _NumOfChannels = 0;
	int _width = 0;
	int _height = 0;
	int _depth = 0; 
};
