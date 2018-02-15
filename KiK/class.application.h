// Filename: class.application.h
// Author:   Patryk Połeć

#pragma once

class C_Application
{
	// Constructor and destructor
	public:
		C_Application(C_Core *_objCore, C_Log *_objLog, C_Config *_objConfig, C_Converter *_objConverter);
		~C_Application();

	// Public methods
	public:
		void Events();
		void Physics();
		void Render();

	// Private methods
	private:
		void EventsWindow();
		void EventsKeyboard();
		void EventsMause();

		void PhysicsSettings();
		void PhysicsNewGame();
		void PhysicsMovesPlayers();
		void PhysicsAnimation();

		void RenderMenu();
		void RenderGame();
		void RenderSystemHUD();

		/////////////////////
		void LoadRandomMap();
		void MoveRandomAI();
		void CheckWin();
		void TogglePlayer();

	// Public fields
	public:

	// Private fields
	private:
		C_Core      *objCore;
		C_Log       *objLog;
		C_Config    *objConfig;
		C_Converter *objConverter;

		C_Object2D 
			*objMenu[3],
			*objMenuButton[3][5],
			*objMap,
			*objMapField[10],
			*objMovePlayer,
			*objWin,
			*objAgain,
			*objAgainButton[4],
			*objSystemHUD;

		bool
			statusSettings,
			statusSystemHUD;

		int
			stateMenu,
			stateNewGame,
			stateGame,
			stateMove,
			stateWin,

			levelOfDifficulty,

			numberOfMaps,
			currentMap,

			currentPlayer,
			
			timeCountMoveAi,
			intervalAi,
			
			timeCountSystemHUD,
			intervalSystemHUD,
			
			fpsBuffer,

			clickedField;
		
		float
			speedObjectMove,
			speedObjectVisible,
			
			timeMainLoopBuffer;
};