// Filename: engine.cpp
// Author:   Patryk Połeć

#include "engine.h"

int main(int argc, char *args[])
{
	C_Core        *objCore        = new C_Core(SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	C_Log         *objLog         = new C_Log(PATH_FILE_ERROR_LOG);
	C_Config      *objConfig      = new C_Config(PATH_FILE_CONFIG_INI);
	C_Converter   *objConverter   = new C_Converter;
	C_Application *objApplication = new C_Application(objCore, objLog, objConfig, objConverter);

	if(objCore->stateInit)
	{
			 if(objCore->stateInit == 1) objLog->AddError("Initialization error", "SDL",       objCore->stateMainLoop);
		else if(objCore->stateInit == 2) objLog->AddError("Initialization error", "Window",    objCore->stateMainLoop);
		else if(objCore->stateInit == 3) objLog->AddError("Initialization error", "Event",     objCore->stateMainLoop);
		else if(objCore->stateInit == 4) objLog->AddError("Initialization error", "ContextGL", objCore->stateMainLoop);
		else if(objCore->stateInit == 5) objLog->AddError("Initialization error", "OpenGL",    objCore->stateMainLoop);
	}

	while(objCore->stateMainLoop == RUN)
    {
		objApplication->Events();
		objApplication->Physics();
		objApplication->Render();
    }

	delete objApplication;
	delete objConverter;
	delete objConfig;
	delete objLog;
	delete objCore;

    return 0;
}