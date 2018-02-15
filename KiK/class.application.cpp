// Filename: class.application.cpp
// Author:   Patryk Połeć

#include "engine.h"

////////////////////////////////////////////////////////////////////////////////////////////////// Constructor and destructor
C_Application::C_Application(C_Core *_objCore, C_Log *_objLog, C_Config *_objConfig, C_Converter *_objConverter): objCore(_objCore), objLog(_objLog), objConfig(_objConfig), objConverter(_objConverter)
{
	// Private fields
	objMenu[1] = new C_Object2D(0.0f, 0.0f, 800.0f, 3000.0f);
	objMenuButton[1][1] = new C_Object2D(287.0f, 140.0f, 226.0f, 34.0f);
	objMenuButton[1][2] = new C_Object2D(276.0f, 200.0f, 250.0f, 34.0f);
	objMenuButton[1][3] = new C_Object2D(305.0f, 260.0f, 191.0f, 34.0f);
	objMenuButton[1][4] = new C_Object2D(328.0f, 320.0f, 142.0f, 34.0f);

	objMenu[2] = new C_Object2D(0.0f, 0.0f, 800.0f, 1200.0f);
	objMenuButton[2][1] = new C_Object2D(440.0f, 144.0f, 100.0f, 40.0f, 3);
	objMenuButton[2][2] = new C_Object2D(440.0f, 204.0f, 100.0f, 40.0f, 3);
	objMenuButton[2][3] = new C_Object2D(333.0f, 471.0f, 134.0f, 34.0f);

	objMap = new C_Object2D(0.0f, 0.0f, 800.0f, 600.0f);
	objMapField[1] = new C_Object2D(270.0f, 170.0f, 60.0f, 60.0f, 2);
	objMapField[2] = new C_Object2D(370.0f, 170.0f, 60.0f, 60.0f, 2);
	objMapField[3] = new C_Object2D(470.0f, 170.0f, 60.0f, 60.0f, 2);
	objMapField[4] = new C_Object2D(270.0f, 270.0f, 60.0f, 60.0f, 2);
	objMapField[5] = new C_Object2D(370.0f, 270.0f, 60.0f, 60.0f, 2);
	objMapField[6] = new C_Object2D(470.0f, 270.0f, 60.0f, 60.0f, 2);
	objMapField[7] = new C_Object2D(270.0f, 370.0f, 60.0f, 60.0f, 2);
	objMapField[8] = new C_Object2D(370.0f, 370.0f, 60.0f, 60.0f, 2);
	objMapField[9] = new C_Object2D(470.0f, 370.0f, 60.0f, 60.0f, 2);

	objMovePlayer = new C_Object2D(240.0f, 10.0f, 320.0f, 120.0f,2);

	objWin = new C_Object2D(240.0f, 10.0f, 320.0f, 120.0f, 3);

	objAgain = new C_Object2D(0.0f, 600.0f, 800.0f, 120.0f);
	objAgainButton[1] = new C_Object2D(270.0f, 545.0f,  70.0f, 30.0f);
	objAgainButton[2] = new C_Object2D(350.0f, 545.0f, 100.0f, 30.0f);
	objAgainButton[3] = new C_Object2D(460.0f, 545.0f,  70.0f, 30.0f);

	objSystemHUD = new C_Object2D(0.0f, 0.0f, 220.0f, 90.0f);

	statusSettings  = true;
	statusSystemHUD = false;

	stateMenu    = MENU_I;
	stateNewGame = NEW_GAME_OFF;
	stateGame    = GAME_OFF;
	stateMove    = MOVE_OFF;
	stateWin     = WIN_OFF;

	levelOfDifficulty = 0;

	numberOfMaps = 0;
	currentMap   = 0;

	currentPlayer = PLAYER_OFF;

	timeCountMoveAi = 0;
	intervalAi      = 0;

	timeCountSystemHUD = 0;
	intervalSystemHUD  = 0;
			
	fpsBuffer = 0;

	clickedField = 0;

	speedObjectMove    = 0.0f;
	speedObjectVisible = 0.0f;
	
	timeMainLoopBuffer = 0.0f;

	// Configuration
	objCore->ConfigurationWindow(800, 600, "KiK");

	objCore->SetTimeDelayMainLoop(objConfig->GetValueI("timeDelayMainLoop"));

	levelOfDifficulty  = objConfig->GetValueI("levelOfDifficulty");
	numberOfMaps       = objConfig->GetValueI("numberOfMaps");
	intervalAi         = objConfig->GetValueI("intervalAi");
	intervalSystemHUD  = objConfig->GetValueI("intervalSystemHUD");
	speedObjectMove    = objConfig->GetValueF("speedObjectMove");
	speedObjectVisible = objConfig->GetValueF("speedObjectVisible");
	
	// Load files
	if(!objCore->LoadFont("Fonts/font.ttf",  22, 1)) objLog->AddError("Couldn't open font", "Fonts/font.ttf", objCore->stateMainLoop);
	if(!objCore->LoadFont("Fonts/tnri.ttf" , 16, 2)) objLog->AddError("Couldn't open font", "Fonts/tnri.ttf", objCore->stateMainLoop);

	if(!objMenu[1]->LoadTexture("Data/menu1")) objLog->AddError("Couldn't open texture", "Data/menu1", objCore->stateMainLoop);

	if(!objMenu[2]->LoadTexture("Data/menu2")) objLog->AddError("Couldn't open texture", "Data/menu2", objCore->stateMainLoop);
	if(!objMenuButton[2][1]->LoadTexture("Data/levels", 1, 0,  0, 100, 40)) objLog->AddError("Couldn't open texture", "Data/levels", objCore->stateMainLoop);
	if(!objMenuButton[2][1]->LoadTexture("Data/levels", 2, 0, 40, 100, 40)) objLog->AddError("Couldn't open texture", "Data/levels", objCore->stateMainLoop);
	if(!objMenuButton[2][1]->LoadTexture("Data/levels", 3, 0, 80, 100, 40)) objLog->AddError("Couldn't open texture", "Data/levels", objCore->stateMainLoop);
	if(!objMenuButton[2][2]->LoadTexture("Data/levels", 1, 0,  0, 100, 40)) objLog->AddError("Couldn't open texture", "Data/levels", objCore->stateMainLoop);
	if(!objMenuButton[2][2]->LoadTexture("Data/levels", 2, 0, 40, 100, 40)) objLog->AddError("Couldn't open texture", "Data/levels", objCore->stateMainLoop);
	if(!objMenuButton[2][2]->LoadTexture("Data/levels", 3, 0, 80, 100, 40)) objLog->AddError("Couldn't open texture", "Data/levels", objCore->stateMainLoop);

	for(int l = 1; l <= 9; l++) 
	{
		if(!objMapField[l]->LoadTexture("Data/ox", 1, 0,  0, 60, 60)) objLog->AddError("Couldn't open texture", "Data/ox", objCore->stateMainLoop);
		if(!objMapField[l]->LoadTexture("Data/ox", 2, 0, 60, 60, 60)) objLog->AddError("Couldn't open texture", "Data/ox", objCore->stateMainLoop);
	}

	if(!objMovePlayer->LoadTexture("Data/moveplayers", 1, 0,   0, 320, 120)) objLog->AddError("Couldn't open texture", "Data/moveplayers", objCore->stateMainLoop);
	if(!objMovePlayer->LoadTexture("Data/moveplayers", 2, 0, 120, 320, 120)) objLog->AddError("Couldn't open texture", "Data/moveplayers", objCore->stateMainLoop);
	
	if(!objWin->LoadTexture("Data/win", 1, 0,   0, 320, 120)) objLog->AddError("Couldn't open texture", "Data/win", objCore->stateMainLoop);
	if(!objWin->LoadTexture("Data/win", 2, 0, 120, 320, 120)) objLog->AddError("Couldn't open texture", "Data/win", objCore->stateMainLoop);
	if(!objWin->LoadTexture("Data/win", 3, 0, 240, 320, 120)) objLog->AddError("Couldn't open texture", "Data/win", objCore->stateMainLoop);

	if(!objAgain->LoadTexture("Data/again")) objLog->AddError("Couldn't open texture", "Data/again", objCore->stateMainLoop);
}

C_Application::~C_Application()
{
	objConfig->SetValue("timeDelayMainLoop", objConverter->ToS(objCore->GetTimeDelayMainLoop()));
	objConfig->SetValue("levelOfDifficulty", objConverter->ToS(levelOfDifficulty));

	delete objSystemHUD;

	delete objAgainButton[3];
	delete objAgainButton[2];
	delete objAgainButton[1];
	delete objAgain;

	delete objWin;

	delete objMovePlayer;

	delete objMapField[9];
	delete objMapField[8];
	delete objMapField[7];
	delete objMapField[6];
	delete objMapField[5];
	delete objMapField[4];
	delete objMapField[3];
	delete objMapField[2];
	delete objMapField[1];
	delete objMap;

	delete objMenuButton[2][3];
	delete objMenuButton[2][2];
	delete objMenuButton[2][1];
	delete objMenu[2];

	delete objMenuButton[1][4];
	delete objMenuButton[1][3];
	delete objMenuButton[1][2];
	delete objMenuButton[1][1];
	delete objMenu[1];
}

////////////////////////////////////////////////////////////////////////////////////////////////// Public methods
void C_Application::Events()
{
	while(objCore->CheckEvent()) 
	{
		EventsWindow();
		EventsKeyboard();
		EventsMause();
	}
}

void C_Application::Physics()
{
	PhysicsSettings();
	PhysicsNewGame();
	PhysicsMovesPlayers();
	PhysicsAnimation();
}

void C_Application::Render()
{
	objCore->PrepareScene2D();

		RenderMenu();
		RenderGame();
		RenderSystemHUD();

	objCore->EndScene();
}

////////////////////////////////////////////////////////////////////////////////////////////////// Private methods
void C_Application::EventsWindow()
{
	if(objCore->CheckEventWindow(SDL_WINDOWEVENT_CLOSE)) objCore->stateMainLoop = STOP;
}

void C_Application::EventsKeyboard()
{
	if(objCore->CheckEventKeyboard(SDL_KEYDOWN, SDLK_ESCAPE))
	{
		     if(stateMenu == MENU_I   && stateGame == GAME_OFF) objCore->stateMainLoop = STOP;
		else if(stateMenu == MENU_I   && stateGame != GAME_OFF) stateMenu = MENU_OFF;
		else if(stateMenu == MENU_II                          ) stateMenu = MENU_I;
		else if(stateMenu == MENU_OFF && stateGame != GAME_OFF) stateMenu = MENU_I;
	}

	if(objCore->CheckEventKeyboard(SDL_KEYDOWN, SDLK_F1)) (statusSystemHUD == false) ? statusSystemHUD = true : statusSystemHUD = false;

	if(objCore->CheckEventKeyboard(SDL_KEYDOWN, SDLK_F5)) stateNewGame = NEW_GAME_ON;
}

void C_Application::EventsMause()
{
	if(stateMenu == MENU_I)
	{
			 if(objMenuButton[1][1]->CheckFocus(objCore->mousePosition)) objMenu[1]->SetParameter(Y, -600.0f);
		else if(objMenuButton[1][2]->CheckFocus(objCore->mousePosition)) objMenu[1]->SetParameter(Y, -1200.0f);
		else if(objMenuButton[1][3]->CheckFocus(objCore->mousePosition)) objMenu[1]->SetParameter(Y, -1800.0f);
		else if(objMenuButton[1][4]->CheckFocus(objCore->mousePosition)) objMenu[1]->SetParameter(Y, -2400.0f);
		else                                                             objMenu[1]->SetParameter(Y, 0.0f);
	}
	else if(stateMenu == MENU_II)
	{
		if(objMenuButton[2][3]->CheckFocus(objCore->mousePosition)) objMenu[2]->SetParameter(Y, -600.0f);
		else                                                        objMenu[2]->SetParameter(Y, 0.0f);
	}

	if(objCore->CheckEventMouse(SDL_MOUSEBUTTONDOWN, SDL_BUTTON_LEFT))
	{
		if(stateMenu == MENU_OFF && stateMove == MOVE_HUMAN && stateWin == WIN_OFF)
		{
			for(int l = 1; l <= 9; l++) if(objMapField[l]->CheckFocus(objCore->mousePosition) && objMapField[l]->currentTexture == NULL) clickedField = l;
		}
		else if(stateMenu == MENU_I)
		{
			     if(objMenuButton[1][1]->CheckFocus(objCore->mousePosition)) {stateMenu = MENU_OFF; stateNewGame = NEW_GAME_ON; stateGame = GAME_ONE_PLAYER;}
			else if(objMenuButton[1][2]->CheckFocus(objCore->mousePosition)) {stateMenu = MENU_OFF; stateNewGame = NEW_GAME_ON; stateGame = GAME_TWO_PLAYER;}
			else if(objMenuButton[1][3]->CheckFocus(objCore->mousePosition))  stateMenu = MENU_II;
			else if(objMenuButton[1][4]->CheckFocus(objCore->mousePosition))  objCore->stateMainLoop = STOP;
		}
		else if(stateMenu == MENU_II)
		{
			if(objMenuButton[2][1]->CheckFocus(objCore->mousePosition)) 
			{
					 if(objMenuButton[2][1]->currentTexture == 1) levelOfDifficulty = 2;
				else if(objMenuButton[2][1]->currentTexture == 2) levelOfDifficulty = 3;
				else if(objMenuButton[2][1]->currentTexture == 3) levelOfDifficulty = 1;

				statusSettings = true;
			}
			else if(objMenuButton[2][2]->CheckFocus(objCore->mousePosition))
			{
					 if(objMenuButton[2][2]->currentTexture == 1) objCore->SetTimeDelayMainLoop(3);
				else if(objMenuButton[2][2]->currentTexture == 2) objCore->SetTimeDelayMainLoop(1);
				else if(objMenuButton[2][2]->currentTexture == 3) objCore->SetTimeDelayMainLoop(6);

				statusSettings = true;
			}
			else if(objMenuButton[2][3]->CheckFocus(objCore->mousePosition)) stateMenu = MENU_I;
		}
		else if(stateMenu == MENU_OFF && stateWin != WIN_OFF)
		{
			     if(objAgainButton[1]->CheckFocus(objCore->mousePosition)) stateNewGame = NEW_GAME_ON;
			else if(objAgainButton[2]->CheckFocus(objCore->mousePosition)) objCore->stateMainLoop = STOP;
			else if(objAgainButton[3]->CheckFocus(objCore->mousePosition)) stateMenu = MENU_I;
		}
	}
}

void C_Application::PhysicsSettings()
{
	if(statusSettings)
	{
		objMenuButton[2][1]->currentTexture = levelOfDifficulty;

			 if(objCore->GetTimeDelayMainLoop() == 1) objMenuButton[2][2]->currentTexture = 3;
		else if(objCore->GetTimeDelayMainLoop() == 3) objMenuButton[2][2]->currentTexture = 2;
		else if(objCore->GetTimeDelayMainLoop() == 6) objMenuButton[2][2]->currentTexture = 1;

		statusSettings = false;
	}
}

void C_Application::PhysicsNewGame()
{
	if(stateNewGame == NEW_GAME_ON)
	{
		LoadRandomMap();
				
		for(int l = 1; l <= 9; l++)
		{
			objMapField[l]->currentTexture = NULL;
		}

		if(stateGame == GAME_ONE_PLAYER) 
		{
			stateMove = objCore->Random(1, 2);
			timeCountMoveAi = objCore->GetTime();
		}
		else if(stateGame == GAME_TWO_PLAYER) 
		{
			stateMove = MOVE_HUMAN;
		}

		currentPlayer = objCore->Random(1, 2);

		objMovePlayer->SetParameter(VISIBLE, 1.0f);
		objWin->SetParameter(VISIBLE, 0.0f);
		objAgain->SetParameter(Y, 600.0f);

		stateWin = WIN_OFF;

		stateNewGame = NEW_GAME_OFF;
	}
}

void C_Application::PhysicsMovesPlayers()
{
	if(stateMove == MOVE_HUMAN && stateWin == WIN_OFF && clickedField != 0) 
	{
		objMapField[clickedField]->currentTexture = currentPlayer;
		clickedField = 0;

		CheckWin();
		TogglePlayer();
			
		if(stateGame == GAME_ONE_PLAYER)
		{
			timeCountMoveAi = objCore->GetTime();
			stateMove = MOVE_AI;
		}
	}
	else if(stateMove == MOVE_AI && stateWin == WIN_OFF && (objCore->GetTime() - timeCountMoveAi) > intervalAi)
	{
		int result = 0;

		     if(levelOfDifficulty == 1) result = objCore->Random(1, 3);
		else if(levelOfDifficulty == 2) result = objCore->Random(1, 2);
		else if(levelOfDifficulty == 3) result = 1;

		if(result == 1)
		{
			int enemy = 0;

				 if(currentPlayer == PLAYER_O) enemy = PLAYER_X;
			else if(currentPlayer == PLAYER_X) enemy = PLAYER_O;

				 if(objMapField[1]->currentTexture == currentPlayer && objMapField[2]->currentTexture == currentPlayer && objMapField[3]->currentTexture == NULL) objMapField[3]->currentTexture = currentPlayer;
			else if(objMapField[1]->currentTexture == currentPlayer && objMapField[5]->currentTexture == currentPlayer && objMapField[9]->currentTexture == NULL) objMapField[9]->currentTexture = currentPlayer;
			else if(objMapField[1]->currentTexture == currentPlayer && objMapField[4]->currentTexture == currentPlayer && objMapField[7]->currentTexture == NULL) objMapField[7]->currentTexture = currentPlayer;
			else if(objMapField[2]->currentTexture == currentPlayer && objMapField[5]->currentTexture == currentPlayer && objMapField[8]->currentTexture == NULL) objMapField[8]->currentTexture = currentPlayer;
			else if(objMapField[3]->currentTexture == currentPlayer && objMapField[2]->currentTexture == currentPlayer && objMapField[1]->currentTexture == NULL) objMapField[1]->currentTexture = currentPlayer;
			else if(objMapField[3]->currentTexture == currentPlayer && objMapField[5]->currentTexture == currentPlayer && objMapField[7]->currentTexture == NULL) objMapField[7]->currentTexture = currentPlayer;
			else if(objMapField[3]->currentTexture == currentPlayer && objMapField[6]->currentTexture == currentPlayer && objMapField[9]->currentTexture == NULL) objMapField[9]->currentTexture = currentPlayer;
			else if(objMapField[4]->currentTexture == currentPlayer && objMapField[5]->currentTexture == currentPlayer && objMapField[6]->currentTexture == NULL) objMapField[6]->currentTexture = currentPlayer;
			else if(objMapField[6]->currentTexture == currentPlayer && objMapField[5]->currentTexture == currentPlayer && objMapField[4]->currentTexture == NULL) objMapField[4]->currentTexture = currentPlayer;
			else if(objMapField[7]->currentTexture == currentPlayer && objMapField[8]->currentTexture == currentPlayer && objMapField[9]->currentTexture == NULL) objMapField[9]->currentTexture = currentPlayer;
			else if(objMapField[7]->currentTexture == currentPlayer && objMapField[5]->currentTexture == currentPlayer && objMapField[3]->currentTexture == NULL) objMapField[3]->currentTexture = currentPlayer;
			else if(objMapField[7]->currentTexture == currentPlayer && objMapField[4]->currentTexture == currentPlayer && objMapField[1]->currentTexture == NULL) objMapField[1]->currentTexture = currentPlayer;
			else if(objMapField[8]->currentTexture == currentPlayer && objMapField[5]->currentTexture == currentPlayer && objMapField[2]->currentTexture == NULL) objMapField[2]->currentTexture = currentPlayer;
			else if(objMapField[9]->currentTexture == currentPlayer && objMapField[8]->currentTexture == currentPlayer && objMapField[7]->currentTexture == NULL) objMapField[7]->currentTexture = currentPlayer;
			else if(objMapField[9]->currentTexture == currentPlayer && objMapField[5]->currentTexture == currentPlayer && objMapField[1]->currentTexture == NULL) objMapField[1]->currentTexture = currentPlayer;
			else if(objMapField[9]->currentTexture == currentPlayer && objMapField[6]->currentTexture == currentPlayer && objMapField[3]->currentTexture == NULL) objMapField[3]->currentTexture = currentPlayer;
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			else if(objMapField[1]->currentTexture == currentPlayer && objMapField[3]->currentTexture == currentPlayer && objMapField[2]->currentTexture == NULL) objMapField[2]->currentTexture = currentPlayer;
			else if(objMapField[1]->currentTexture == currentPlayer && objMapField[9]->currentTexture == currentPlayer && objMapField[5]->currentTexture == NULL) objMapField[5]->currentTexture = currentPlayer;
			else if(objMapField[1]->currentTexture == currentPlayer && objMapField[7]->currentTexture == currentPlayer && objMapField[4]->currentTexture == NULL) objMapField[4]->currentTexture = currentPlayer;
			else if(objMapField[2]->currentTexture == currentPlayer && objMapField[8]->currentTexture == currentPlayer && objMapField[5]->currentTexture == NULL) objMapField[5]->currentTexture = currentPlayer;
			else if(objMapField[3]->currentTexture == currentPlayer && objMapField[1]->currentTexture == currentPlayer && objMapField[2]->currentTexture == NULL) objMapField[2]->currentTexture = currentPlayer;
			else if(objMapField[3]->currentTexture == currentPlayer && objMapField[7]->currentTexture == currentPlayer && objMapField[5]->currentTexture == NULL) objMapField[5]->currentTexture = currentPlayer;
			else if(objMapField[3]->currentTexture == currentPlayer && objMapField[9]->currentTexture == currentPlayer && objMapField[6]->currentTexture == NULL) objMapField[6]->currentTexture = currentPlayer;
			else if(objMapField[4]->currentTexture == currentPlayer && objMapField[6]->currentTexture == currentPlayer && objMapField[5]->currentTexture == NULL) objMapField[5]->currentTexture = currentPlayer;
			else if(objMapField[6]->currentTexture == currentPlayer && objMapField[4]->currentTexture == currentPlayer && objMapField[5]->currentTexture == NULL) objMapField[5]->currentTexture = currentPlayer;
			else if(objMapField[7]->currentTexture == currentPlayer && objMapField[9]->currentTexture == currentPlayer && objMapField[8]->currentTexture == NULL) objMapField[8]->currentTexture = currentPlayer;
			else if(objMapField[7]->currentTexture == currentPlayer && objMapField[3]->currentTexture == currentPlayer && objMapField[5]->currentTexture == NULL) objMapField[5]->currentTexture = currentPlayer;
			else if(objMapField[7]->currentTexture == currentPlayer && objMapField[1]->currentTexture == currentPlayer && objMapField[4]->currentTexture == NULL) objMapField[4]->currentTexture = currentPlayer;
			else if(objMapField[8]->currentTexture == currentPlayer && objMapField[2]->currentTexture == currentPlayer && objMapField[5]->currentTexture == NULL) objMapField[5]->currentTexture = currentPlayer;
			else if(objMapField[9]->currentTexture == currentPlayer && objMapField[7]->currentTexture == currentPlayer && objMapField[8]->currentTexture == NULL) objMapField[8]->currentTexture = currentPlayer;
			else if(objMapField[9]->currentTexture == currentPlayer && objMapField[1]->currentTexture == currentPlayer && objMapField[5]->currentTexture == NULL) objMapField[5]->currentTexture = currentPlayer;
			else if(objMapField[9]->currentTexture == currentPlayer && objMapField[3]->currentTexture == currentPlayer && objMapField[6]->currentTexture == NULL) objMapField[6]->currentTexture = currentPlayer;
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
			else if(objMapField[1]->currentTexture == enemy && objMapField[2]->currentTexture == enemy && objMapField[3]->currentTexture == NULL) objMapField[3]->currentTexture = currentPlayer;
			else if(objMapField[1]->currentTexture == enemy && objMapField[5]->currentTexture == enemy && objMapField[9]->currentTexture == NULL) objMapField[9]->currentTexture = currentPlayer;
			else if(objMapField[1]->currentTexture == enemy && objMapField[4]->currentTexture == enemy && objMapField[7]->currentTexture == NULL) objMapField[7]->currentTexture = currentPlayer;
			else if(objMapField[2]->currentTexture == enemy && objMapField[5]->currentTexture == enemy && objMapField[8]->currentTexture == NULL) objMapField[8]->currentTexture = currentPlayer;
			else if(objMapField[3]->currentTexture == enemy && objMapField[2]->currentTexture == enemy && objMapField[1]->currentTexture == NULL) objMapField[1]->currentTexture = currentPlayer;
			else if(objMapField[3]->currentTexture == enemy && objMapField[5]->currentTexture == enemy && objMapField[7]->currentTexture == NULL) objMapField[7]->currentTexture = currentPlayer;
			else if(objMapField[3]->currentTexture == enemy && objMapField[6]->currentTexture == enemy && objMapField[9]->currentTexture == NULL) objMapField[9]->currentTexture = currentPlayer;
			else if(objMapField[4]->currentTexture == enemy && objMapField[5]->currentTexture == enemy && objMapField[6]->currentTexture == NULL) objMapField[6]->currentTexture = currentPlayer;
			else if(objMapField[6]->currentTexture == enemy && objMapField[5]->currentTexture == enemy && objMapField[4]->currentTexture == NULL) objMapField[4]->currentTexture = currentPlayer;
			else if(objMapField[7]->currentTexture == enemy && objMapField[8]->currentTexture == enemy && objMapField[9]->currentTexture == NULL) objMapField[9]->currentTexture = currentPlayer;
			else if(objMapField[7]->currentTexture == enemy && objMapField[5]->currentTexture == enemy && objMapField[3]->currentTexture == NULL) objMapField[3]->currentTexture = currentPlayer;
			else if(objMapField[7]->currentTexture == enemy && objMapField[4]->currentTexture == enemy && objMapField[1]->currentTexture == NULL) objMapField[1]->currentTexture = currentPlayer;
			else if(objMapField[8]->currentTexture == enemy && objMapField[5]->currentTexture == enemy && objMapField[2]->currentTexture == NULL) objMapField[2]->currentTexture = currentPlayer;
			else if(objMapField[9]->currentTexture == enemy && objMapField[8]->currentTexture == enemy && objMapField[7]->currentTexture == NULL) objMapField[7]->currentTexture = currentPlayer;
			else if(objMapField[9]->currentTexture == enemy && objMapField[5]->currentTexture == enemy && objMapField[1]->currentTexture == NULL) objMapField[1]->currentTexture = currentPlayer;
			else if(objMapField[9]->currentTexture == enemy && objMapField[6]->currentTexture == enemy && objMapField[3]->currentTexture == NULL) objMapField[3]->currentTexture = currentPlayer;
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			else if(objMapField[1]->currentTexture == enemy && objMapField[3]->currentTexture == enemy && objMapField[2]->currentTexture == NULL) objMapField[2]->currentTexture = currentPlayer;
			else if(objMapField[1]->currentTexture == enemy && objMapField[9]->currentTexture == enemy && objMapField[5]->currentTexture == NULL) objMapField[5]->currentTexture = currentPlayer;
			else if(objMapField[1]->currentTexture == enemy && objMapField[7]->currentTexture == enemy && objMapField[4]->currentTexture == NULL) objMapField[4]->currentTexture = currentPlayer;
			else if(objMapField[2]->currentTexture == enemy && objMapField[8]->currentTexture == enemy && objMapField[5]->currentTexture == NULL) objMapField[5]->currentTexture = currentPlayer;
			else if(objMapField[3]->currentTexture == enemy && objMapField[1]->currentTexture == enemy && objMapField[2]->currentTexture == NULL) objMapField[2]->currentTexture = currentPlayer;
			else if(objMapField[3]->currentTexture == enemy && objMapField[7]->currentTexture == enemy && objMapField[5]->currentTexture == NULL) objMapField[5]->currentTexture = currentPlayer;
			else if(objMapField[3]->currentTexture == enemy && objMapField[9]->currentTexture == enemy && objMapField[6]->currentTexture == NULL) objMapField[6]->currentTexture = currentPlayer;
			else if(objMapField[4]->currentTexture == enemy && objMapField[6]->currentTexture == enemy && objMapField[5]->currentTexture == NULL) objMapField[5]->currentTexture = currentPlayer;
			else if(objMapField[6]->currentTexture == enemy && objMapField[4]->currentTexture == enemy && objMapField[5]->currentTexture == NULL) objMapField[5]->currentTexture = currentPlayer;
			else if(objMapField[7]->currentTexture == enemy && objMapField[9]->currentTexture == enemy && objMapField[8]->currentTexture == NULL) objMapField[8]->currentTexture = currentPlayer;
			else if(objMapField[7]->currentTexture == enemy && objMapField[3]->currentTexture == enemy && objMapField[5]->currentTexture == NULL) objMapField[5]->currentTexture = currentPlayer;
			else if(objMapField[7]->currentTexture == enemy && objMapField[1]->currentTexture == enemy && objMapField[4]->currentTexture == NULL) objMapField[4]->currentTexture = currentPlayer;
			else if(objMapField[8]->currentTexture == enemy && objMapField[2]->currentTexture == enemy && objMapField[5]->currentTexture == NULL) objMapField[5]->currentTexture = currentPlayer;
			else if(objMapField[9]->currentTexture == enemy && objMapField[7]->currentTexture == enemy && objMapField[8]->currentTexture == NULL) objMapField[8]->currentTexture = currentPlayer;
			else if(objMapField[9]->currentTexture == enemy && objMapField[1]->currentTexture == enemy && objMapField[5]->currentTexture == NULL) objMapField[5]->currentTexture = currentPlayer;
			else if(objMapField[9]->currentTexture == enemy && objMapField[3]->currentTexture == enemy && objMapField[6]->currentTexture == NULL) objMapField[6]->currentTexture = currentPlayer;
			else MoveRandomAI();
		}
		else MoveRandomAI();

		CheckWin();
		TogglePlayer();

		stateMove = MOVE_HUMAN;
	}
}

void C_Application::PhysicsAnimation()
{
	if(stateMenu == MENU_OFF && stateWin != WIN_OFF)
	{
		if(objMovePlayer->GetParameter(VISIBLE) > 0.0f) 
		{
			if(objMovePlayer->GetParameter(VISIBLE) < 0.7f && stateWin == WIN_PLAYER_REMIS) objMovePlayer->SetParameter(VISIBLE, 0.0f);
			objMovePlayer->SetParameter(VISIBLE, objMovePlayer->GetParameter(VISIBLE) - speedObjectVisible * objCore->GetTimeMainLoop());
		}
		if(objWin->GetParameter(VISIBLE) < 1.0f)        objWin->SetParameter(VISIBLE, objWin->GetParameter(VISIBLE) + speedObjectVisible * objCore->GetTimeMainLoop());
			
		if(objAgain->GetParameter(Y) > 482.0f) objAgain->SetParameter(Y, objAgain->GetParameter(Y) - speedObjectMove * objCore->GetTimeMainLoop());
		if(objAgain->GetParameter(Y) < 482.0f) objAgain->SetParameter(Y, 482.0f);
	}
}

void C_Application::RenderMenu()
{
	     if(stateMenu == MENU_I ) objMenu[1]->Draw();
	else if(stateMenu == MENU_II) 
	{
		objMenu[2]->Draw();
		objMenuButton[2][1]->Draw();
		objMenuButton[2][2]->Draw();
	}
}

void C_Application::RenderGame()
{
	if(stateMenu == MENU_OFF) 
	{
		objMap->Draw();
		for(int l = 1; l <= 9; l++) if(objMapField[l]->currentTexture != NULL) objMapField[l]->Draw();

		objMovePlayer->Draw(currentPlayer);

		if(stateWin != WIN_OFF)
		{
			objWin->Draw(stateWin);
			objAgain->Draw();
		}
	}
}

void C_Application::RenderSystemHUD()
{
	if(statusSystemHUD)
	{
		objSystemHUD->Draw();

		if((objCore->GetTime() - timeCountSystemHUD) > intervalSystemHUD)
		{
			fpsBuffer = objCore->GetFps();
			timeMainLoopBuffer = objCore->GetTimeMainLoop();

			timeCountSystemHUD = objCore->GetTime();
		}

		objCore->DrawText("FPS: " + objConverter->ToS(fpsBuffer), 1, 10.0f, 10.0f);
		objCore->DrawText("TRA: " + objConverter->ToS(objCore->GetTimeInSec()), 1, 10.0f, 30.0f);
		objCore->DrawText("TML: " + objConverter->ToS(timeMainLoopBuffer), 1, 10.0f, 50.0f);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////// Other
void C_Application::LoadRandomMap()
{
	currentMap = objCore->Random(1, numberOfMaps);

	stringstream buffer;
	buffer.str("");
	buffer << "Maps/map" << currentMap;
	if(!objMap->LoadTexture(buffer.str())) objLog->AddError("Couldn't open map", buffer.str(), objCore->stateMainLoop);
}

void C_Application::MoveRandomAI()
{
	bool statusLoop = true;
	while(statusLoop)
	{
		int result = objCore->Random(1, 9);
		if(objMapField[result]->currentTexture == NULL) {objMapField[result]->currentTexture = currentPlayer; statusLoop = false;}
	}
}

void C_Application::CheckWin()
{
	int amountChecked = 0;
	for(int l = 1; l <= 9; l++) if(objMapField[l]->currentTexture != NULL) amountChecked++;
		
	if((objMapField[1]->currentTexture == currentPlayer && objMapField[2]->currentTexture == currentPlayer && objMapField[3]->currentTexture == currentPlayer) ||
	   (objMapField[4]->currentTexture == currentPlayer && objMapField[5]->currentTexture == currentPlayer && objMapField[6]->currentTexture == currentPlayer) ||
	   (objMapField[7]->currentTexture == currentPlayer && objMapField[8]->currentTexture == currentPlayer && objMapField[9]->currentTexture == currentPlayer) ||
	  
       (objMapField[1]->currentTexture == currentPlayer && objMapField[4]->currentTexture == currentPlayer && objMapField[7]->currentTexture == currentPlayer) ||
	   (objMapField[2]->currentTexture == currentPlayer && objMapField[5]->currentTexture == currentPlayer && objMapField[8]->currentTexture == currentPlayer) ||
	   (objMapField[3]->currentTexture == currentPlayer && objMapField[6]->currentTexture == currentPlayer && objMapField[9]->currentTexture == currentPlayer) ||
		   
	   (objMapField[1]->currentTexture == currentPlayer && objMapField[5]->currentTexture == currentPlayer && objMapField[9]->currentTexture == currentPlayer) ||
	   (objMapField[3]->currentTexture == currentPlayer && objMapField[5]->currentTexture == currentPlayer && objMapField[7]->currentTexture == currentPlayer)) 
		   
			                    stateWin = currentPlayer;

	else if(amountChecked == 9) stateWin = WIN_PLAYER_REMIS;
}

void C_Application::TogglePlayer()
{
	if(stateWin == WIN_OFF)
	{
		     if(currentPlayer == PLAYER_O) currentPlayer = PLAYER_X;
		else if(currentPlayer == PLAYER_X) currentPlayer = PLAYER_O;
	}
}