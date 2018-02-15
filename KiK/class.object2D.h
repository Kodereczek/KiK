// Filename: class.object2D.h
// Author:   Patryk Połeć

#pragma once 

class C_Object2D
{
	// Constructor and destructor
	public:
		C_Object2D(float _positionX = 0.0f, float _positionY = 0.0f, float _width = 0.0f, float _height = 0.0f, int _texturesAmount = 1);
		~C_Object2D();

	// Public methods
	public:
		void SetParameters(float _positionX, float _positionY, float _width, float _height, float _visible);
		void SetParameter(int _type, float _value);
	   float GetParameter(int _type);

	    bool CheckFocus(int _mousePosition[]);

		bool LoadTexture(string _texturePath, int _textureNumber = 1, int _positionX = -1, int _positionY = -1, int _width = -1, int _height = -1);
		bool CheckLoadTexture(int _textureNumber = 1);
		void DestroyTexture(int _textureNumber);

		void Draw(int _textureNumber = 0, float _visible = 1.0f);

	// Private methods
	private:

	// Public fields
	public:
		int currentTexture;

	// Private fields
	private:
		GLuint 
			*textures;

		int 
			texturesAmount;

		float
			positionX,
			positionY,

			width,
			height,
			
			visible;
};