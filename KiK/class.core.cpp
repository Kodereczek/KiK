// Filename: class.core.cpp
// Author:   Patryk Połeć

#include "engine.h"

////////////////////////////////////////////////////////////////////////////////////////////////// Constructor and destructor
C_Core::C_Core(Uint32 _flagsWindow)
{
	// Public fields
	stateInit = 0;

	stateMainLoop = RUN;

	mousePosition[1] = 0;
	mousePosition[2] = 0;

	// Private fields
	handleWindow = NULL;
	handleEvent  = NULL;
	handleOpenGL = NULL;

	keyPressed = NULL;

	windowCaption = "Application";

	windowWidth   = 800;
	windowHeight  = 600;

	timeDelayMainLoop = 1;

	texturesAmount = 20;
	for(int l = 0; l <= texturesAmount; l++) textures[l] = NULL;
	
	fontsAmount = 20;
	for(int l = 0; l <= fontsAmount; l++) fonts[l] = NULL;

	timeCountFps = 0;
	fps          = 0;

	timeMainLoop          = 0.0f;
	timeLastStartMainLoop = 0.0f;

	// Initialization
	if((
		SDL_Init(SDL_INIT_EVERYTHING) + 
		IMG_Init(IMG_INIT_JPG |IMG_INIT_PNG) + 
		TTF_Init() 
	< 0)) 
							  stateInit = 1;

	handleWindow = SDL_CreateWindow(windowCaption.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, _flagsWindow);
	if(handleWindow == NULL)  stateInit = 2;

	handleEvent = new SDL_Event;
	if(handleEvent == NULL)   stateInit = 3;

	handleOpenGL = SDL_GL_CreateContext(handleWindow);
	if(handleOpenGL == NULL)  stateInit = 4;

	if(glewInit() != GLEW_OK) stateInit = 5;

	keyPressed = const_cast <Uint8*>(SDL_GetKeyboardState(NULL));

	SetAttribute();
}

C_Core::~C_Core()
{
	for(int l = 0; l <= fontsAmount; l++) if(fonts[l]) TTF_CloseFont(fonts[l]);

	for(int l = 0; l <= texturesAmount; l++) if(textures[l]) glDeleteTextures(1, &textures[l]);

	SDL_GL_DeleteContext(handleOpenGL);
	delete handleEvent;
	SDL_DestroyWindow(handleWindow);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

////////////////////////////////////////////////////////////////////////////////////////////////// Public methods
void C_Core::ConfigurationWindow(int _windowWidth, int _windowHeight, string _windowCaption)
{	
	windowCaption = _windowCaption;
	windowWidth   = _windowWidth;
	windowHeight  = _windowHeight;

	SDL_SetWindowTitle(handleWindow, windowCaption.c_str());
	SDL_SetWindowSize(handleWindow, windowWidth, windowHeight);	
}

SDL_Window* C_Core::GetHandleWindow()
{
	return handleWindow;
}

SDL_Event* C_Core::GetHandleEvent()
{
	return handleEvent;
}

SDL_GLContext C_Core::GetHandleOpenGL()
{
	return handleOpenGL;
}

string C_Core::GetWindowCaption()
{
	return windowCaption;
}

int C_Core::GetWindowSize(int _param)
{
	if(_param == 3) return windowWidth;
	else            return windowHeight;
}

int C_Core::CheckEvent()
{
	SDL_GetMouseState(&mousePosition[1], &mousePosition[2]);

	return SDL_PollEvent(handleEvent);
}

bool C_Core::CheckEventWindow(int _eventType)
{
	if(handleEvent->type == SDL_WINDOWEVENT && handleEvent->window.event == _eventType) return true;
	
	return false;
}

bool C_Core::CheckEventKeyboard(int _eventType, int _keyName)
{
	if(handleEvent->type == _eventType && handleEvent->key.keysym.sym == _keyName) return true;

	return false;
}

int C_Core::CheckKeyPressed(int _keyName)
{
	return keyPressed[_keyName];
}

bool C_Core::CheckEventMouse(int _eventType, int _buttonName)
{
	if(handleEvent->type == _eventType && handleEvent->button.button == _buttonName) return true;

	return false;
}

bool C_Core::LoadTexture(string _texturePath, int _textureNumber)
{
	SDL_Surface *surfaceTexture = NULL;

	surfaceTexture = IMG_Load(_texturePath.c_str());
	if(!surfaceTexture) return false;

	GLenum 
		formatInternal,
		format;

	if(surfaceTexture->format->BytesPerPixel == 3)
	{
		formatInternal = GL_RGB;

		if(surfaceTexture->format->Rmask == 0xff) format = GL_RGB;
		else									  format = GL_BGR;
	}
	else
	{   
		formatInternal = GL_RGBA;

		if(surfaceTexture->format->Rmask == 0xff) format = GL_RGBA;
		else									  format = GL_BGRA;
	}

	DestroyTexture(_textureNumber);

	glGenTextures(1, &textures[_textureNumber]);
	glBindTexture(GL_TEXTURE_2D, textures[_textureNumber]);

	glTexImage2D(GL_TEXTURE_2D, 0, formatInternal, surfaceTexture->w, surfaceTexture->h, 0, format, GL_UNSIGNED_BYTE, surfaceTexture->pixels);
  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	SDL_FreeSurface(surfaceTexture);

	if(!textures[_textureNumber]) return false;

	return true;
}

GLuint C_Core::GetTexture(int _textureNumber)
{
	return textures[_textureNumber];
}

void C_Core::BindTexture(int _textureNumber)
{
	(_textureNumber) ? glBindTexture(GL_TEXTURE_2D, textures[_textureNumber]) : glBindTexture(GL_TEXTURE_2D, NULL);
}

void C_Core::DestroyTexture(int _textureNumber)
{
	if(textures[_textureNumber]) glDeleteTextures(1, &textures[_textureNumber]);

	textures[_textureNumber] = NULL;
}

bool C_Core::LoadFont(string _fontPath, int _fontSize, int _fontNumber)
{
	DestroyFont(_fontNumber);

	fonts[_fontNumber] = TTF_OpenFont(_fontPath.c_str(), _fontSize);
	if(!fonts[_fontNumber]) return false;

	return true;
}

void C_Core::DrawText(string _text, int _fontNumber, float _positionX, float _positionY,  Uint8 _R, Uint8 _G, Uint8 _B)
{
	SDL_Surface* textSurface = NULL;

	SDL_Color textColor = {_R, _G, _B};

	textSurface = TTF_RenderUTF8_Blended(fonts[_fontNumber], _text.c_str(), textColor);
	
	GLuint textTexture;
	glGenTextures(1, &textTexture);
    glBindTexture(GL_TEXTURE_2D, textTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textSurface->w, textSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, textSurface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glPushMatrix();
	glTranslatef((GLfloat)_positionX, (GLfloat)_positionY, 0.0f);
	glBindTexture(GL_TEXTURE_2D, textTexture);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex2f( 0.0f                  , 0.0f);
        glTexCoord2f(1, 0); glVertex2f((GLfloat)textSurface->w, 0.0f);
        glTexCoord2f(1, 1); glVertex2f((GLfloat)textSurface->w, (GLfloat)textSurface->h);
        glTexCoord2f(0, 1); glVertex2f( 0.0f                  , (GLfloat)textSurface->h);
    glEnd();
	glPopMatrix();
	
	SDL_FreeSurface(textSurface);
	glDeleteTextures(1, &textTexture);
}

void C_Core::DestroyFont(int _fontNumber)
{
	if(fonts[_fontNumber]) TTF_CloseFont(fonts[_fontNumber]);

	fonts[_fontNumber] = NULL;
}

void C_Core::SetTimeDelayMainLoop(int _time)
{
	(_time >= 0) ? timeDelayMainLoop = _time : timeDelayMainLoop = 0;
}

int C_Core::GetTimeDelayMainLoop()
{
	return timeDelayMainLoop;
}

int C_Core::GetTime()
{
	return SDL_GetTicks();
}

float C_Core::GetTimeInSec()
{
	return SDL_GetTicks() / 1000.0f;
}

float C_Core::GetTimeMainLoop()
{
	return timeMainLoop;
}

int C_Core::GetFps()
{
	return fps;
}

int C_Core::Random(int _number1, int _number2)
{
	if(_number1 == _number2) return _number1;

	srand(GetTime());

	return (rand() % (_number2 - _number1 + 1)) + _number1;
}

void C_Core::PrepareScene2D()
{
	glViewport(0, 0, windowWidth, windowHeight);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, windowWidth, windowHeight, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void C_Core::EndScene()
{
	SDL_GL_SwapWindow(handleWindow);

	SDL_Delay(timeDelayMainLoop);

	timeMainLoop          = GetTimeInSec() - timeLastStartMainLoop;
	timeLastStartMainLoop = GetTimeInSec();
	
	fps          = (int)(1/timeMainLoop);
	timeCountFps = GetTime();
}

////////////////////////////////////////////////////////////////////////////////////////////////// Private methods
void C_Core::SetAttribute()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
          
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,     8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,    8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,   8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,   8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,   32);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,  32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetSwapInterval(0);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GEQUAL, 0.1f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS);

	glEnable(GL_TEXTURE_2D);							
	glEnable(GL_BLEND);								
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
}