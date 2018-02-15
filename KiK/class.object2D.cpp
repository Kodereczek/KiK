// Filename: class.object2D.cpp
// Author:   Patryk Połeć

#include "engine.h"

////////////////////////////////////////////////////////////////////////////////////////////////// Constructor and destructor
C_Object2D::C_Object2D(float _positionX, float _positionY, float _width, float _height, int _texturesAmount)
{
	// Public fields
	currentTexture = 0;

	// Private fields
	positionX = _positionX;
	positionY = _positionY;

	width  = _width;
	height = _height;

	visible = 1.0f;

	texturesAmount = _texturesAmount + 1;

	textures = new GLuint[texturesAmount]; 
	for(int l = 0; l < texturesAmount; l++) textures[l] = NULL;
}

C_Object2D::~C_Object2D()
{
	for(int l = 0; l < texturesAmount; l++) if(textures[l]) glDeleteTextures(1, &textures[l]);

	delete [] textures;
}

////////////////////////////////////////////////////////////////////////////////////////////////// Public methods
void C_Object2D::SetParameters(float _positionX, float _positionY, float _width, float _height, float _visible)
{
	positionX = _positionX;
	positionY = _positionY;

	width  = _width;
	height = _height;

	visible = _visible;
}

void C_Object2D::SetParameter(int _type, float _value)
{
	     if(_type == 1) positionX = _value;
	else if(_type == 2) positionY = _value;
	else if(_type == 3) width     = _value;
	else if(_type == 4) height    = _value;
	else if(_type == 5) visible   = _value;
}

float C_Object2D::GetParameter(int _type)
{
	     if(_type == 1) return positionX;
	else if(_type == 2) return positionY;
	else if(_type == 3) return width;
	else if(_type == 4) return height;
	else if(_type == 5) return visible;

	return 0.0f;
}

bool C_Object2D::CheckFocus(int _mousePosition[])
{
	if((float)_mousePosition[1] >= positionX && (float)_mousePosition[1] <= (positionX + width) && 
	   (float)_mousePosition[2] >= positionY && (float)_mousePosition[2] <= (positionY + height
	))
		return true;

	else
		return false;
}

bool C_Object2D::LoadTexture(string _texturePath, int _textureNumber, int _positionX, int _positionY, int _width, int _height)
{
	SDL_Surface *surfaceTexture = NULL;

	surfaceTexture = IMG_Load(_texturePath.c_str());
	if(!surfaceTexture) return false;

	int
		width  = surfaceTexture->w,
		height = surfaceTexture->h;

	if(_positionX >= 0 && _positionY >= 0 && _width <= width && _height <= height)
	{
		SDL_Rect rect;
		rect.x = _positionX;
		rect.y = _positionY;
		rect.w = _width;
		rect.h = _height;

		SDL_SetSurfaceBlendMode(surfaceTexture, SDL_BLENDMODE_NONE);
		SDL_BlitSurface(surfaceTexture, &rect, surfaceTexture, NULL);

		width  = _width;
		height = _height;
	}

	GLenum 
		formatInternal,
		format;

	if(surfaceTexture->format->BytesPerPixel == 3)
	{
		formatInternal = GL_RGB;

		(surfaceTexture->format->Rmask == 0xff) ? format = GL_RGB : format = GL_BGR;
	}
	else
	{   
		formatInternal = GL_RGBA;

		(surfaceTexture->format->Rmask == 0xff) ? format = GL_RGBA : format = GL_BGRA;
	}

	DestroyTexture(_textureNumber);

	glGenTextures(1, &textures[_textureNumber]);
	glBindTexture(GL_TEXTURE_2D, textures[_textureNumber]);

	glTexImage2D(GL_TEXTURE_2D, 0, formatInternal, width, height, 0, format, GL_UNSIGNED_BYTE, surfaceTexture->pixels);
  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	SDL_FreeSurface(surfaceTexture);

	if(!textures[_textureNumber]) return false;

	currentTexture = _textureNumber;

	return true;
}

bool C_Object2D::CheckLoadTexture(int _textureNumber)
{
	if(!textures[_textureNumber]) return false;

	return true;
}

void C_Object2D::DestroyTexture(int _textureNumber)
{
	if(textures[_textureNumber]) glDeleteTextures(1, &textures[_textureNumber]);

	if(currentTexture == _textureNumber) currentTexture = 0;

	textures[_textureNumber] = NULL;
}

void C_Object2D::Draw(int _textureNumber, float _visible)
{
	if(_textureNumber)   currentTexture = _textureNumber;
	if(_visible != 1.0f) visible        = _visible;

	glPushMatrix();
	glTranslatef(positionX, positionY, 0.0f);
	glBindTexture(GL_TEXTURE_2D, textures[currentTexture]);
	glColor4f(1.0f, 1.0f, 1.0f, visible);
	glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex2f( 0.0f, 0.0f);
        glTexCoord2f(1, 0); glVertex2f(width, 0.0f);
        glTexCoord2f(1, 1); glVertex2f(width, height);
        glTexCoord2f(0, 1); glVertex2f( 0.0f, height);
    glEnd();
	glPopMatrix();
}
