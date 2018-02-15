// Filename: class.core.h
// Author:   Patryk Połeć

#pragma once

class C_Core
{
	// Constructor and destructor
	public:
		C_Core(Uint32 _flagsWindow);
		~C_Core();

	// Public methods
	public:
	         void ConfigurationWindow(int _windowWidth, int _windowHeight, string _windowCaption);

	  SDL_Window* GetHandleWindow();
       SDL_Event* GetHandleEvent();
	SDL_GLContext GetHandleOpenGL();
			
	       string GetWindowCaption();
			  int GetWindowSize(int _param);

		      int CheckEvent();
		     bool CheckEventWindow(int _eventType);
		     bool CheckEventKeyboard(int _eventType, int _keyName);
		      int CheckKeyPressed(int _keyName);
		     bool CheckEventMouse(int _eventType, int _buttonName);

             bool LoadTexture(string _texturePath, int _textureNumber);
		   GLuint GetTexture(int _textureNumber);
             void BindTexture(int _textureNumber);
             void DestroyTexture(int _textureNumber);

		     bool LoadFont(string _fontPath, int _fontSize, int _fontNumber);
		     void DrawText(string _text, int _fontNumber, float _positionX, float _positionY,  Uint8 _R = 0, Uint8 _G = 0, Uint8 _B = 0);
		     void DestroyFont(int _fontNumber);
	
			 void SetTimeDelayMainLoop(int _time);
			  int GetTimeDelayMainLoop();

		      int GetTime();
		    float GetTimeInSec();
	        float GetTimeMainLoop();
	          int GetFps();

		      int Random(int _number1, int _number2);

		     void PrepareScene2D();
		     void EndScene();

	// Private methods
	private:
		     void SetAttribute();

	// Public fields
	public:
		int
			stateInit,

			stateMainLoop,

			mousePosition[3];

	// Private fields
	private:
		SDL_Window    *handleWindow;
		SDL_Event     *handleEvent;
		SDL_GLContext  handleOpenGL;

		Uint8 
			*keyPressed;

		GLuint 
			textures[21];

		TTF_Font
			*fonts[21];

		string 
			windowCaption;
		
		int
			windowWidth,
			windowHeight,

			texturesAmount,
			fontsAmount,

			timeDelayMainLoop,

			timeCountFps,
			fps;

		float
			timeMainLoop,
			timeLastStartMainLoop;
};