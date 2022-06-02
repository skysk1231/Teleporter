#pragma once

#include <iostream>
#include<chrono>
#include<thread>
#include <conio.h>
#include <GLFW/glfw3.h>
#include <Windows.h>

#include "TWindowManager.hpp"
#include "TEnemy.hpp"
#include "TPlayer.hpp"

using namespace std;

namespace TGame_Engine
{
	TCommand* Key[4];

	class TGameLoop
	{
	private:

	public:
		TGameLoop() { IsGameRunning = false; }
		~TGameLoop() {}
		bool IsGameRunning;
		bool GamePlaying;
		bool StartScreen;
		bool GameOverScreen;
		WindowManager Window;
		Enemy e;
		Player p;
		int LoadingScreenNum;
		

		void Run()
		{
			IsGameRunning = true;
			
			Initialize();
			GameStartRender();
			
			while (IsGameRunning)
			{
				if (GamePlaying == false && StartScreen == true)
				{ 
					GameStartInput();
				}
				else if (GamePlaying == true && StartScreen == false) 
				{
					Input();
					Update();
					Render();
					if (LoadingScreenNum > 30)
					{
						ColliderCheck();
					}
				}
				else if(GamePlaying == false && StartScreen == false)
				{
					GameOverInput();
					if (!GameOverScreen)
					{
						GameOverRender();
						GameOverScreen = true;
					}
				}
			}

			Release();
		}

	private:
		void Initialize()
		{
			GamePlaying = false;
			StartScreen = true;
			GameOverScreen = false;
			LoadingScreenNum = 0;
			Window.Initialize();
			Key[0] = new UPCommand();
			Key[1] = new LEFTCommand();
			Key[2] = new RIGHTCommand();
			Key[3] = new DOWNCommand();
			e.Initialize();
		}
		void Release()
		{
			Window.Release();

			for (size_t i = 0; i < 4; i++)
			{
				delete(Key[i]);
			}

			Window.ExitWindow();

		}
		void Input()
		{
			if (GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState(VK_UP) & 0x8001)
			{
				Key[0]->Execute(&p);
			}
			if (GetAsyncKeyState(VK_LEFT) & 0x8000 || GetAsyncKeyState(VK_LEFT) & 0x8001)
			{
				Key[1]->Execute(&p);
			}
			if (GetAsyncKeyState(VK_RIGHT) & 0x8000 || GetAsyncKeyState(VK_RIGHT) & 0x8001)
			{
				Key[2]->Execute(&p);
			}
			if (GetAsyncKeyState(VK_DOWN) & 0x8000 || GetAsyncKeyState(VK_DOWN) & 0x8001)
			{
				Key[3]->Execute(&p);
			}
			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000 || GetAsyncKeyState(VK_ESCAPE) & 0x8001)
			{
				ExitAll();
			}
			
		}
		void Update()
		{
			e.MoveEnemy();
			LoadingScreenNum++;
		
		}
		void Render()
		{
			Window.RenderStart();
			Window.RenderPlayer(p.playerX,p.playerY);
			for (int i = 0; i < 10; i++)
			{
				Window.RenderEnemy(e.EnemyX[i],e.EnemyY[i]);
			}
			Window.RenderEnd();
		}

		void GameOverRender()
		{
			Window.RenderStart();
			Window.EndScreen();
			Window.RenderEnd();
		}

		void GameStartRender()
		{
			Window.RenderStart();
			Window.StartScreen();
			Window.RenderEnd();
		}

		void ColliderCheck()
		{
			for (int i = 0; i < 10; i++) {

				if (((p.playerX - 0.05) < (e.EnemyX[i] + 0.05)) && ((p.playerX + 0.05) > (e.EnemyX[i] - 0.05)))
				{
					if (((p.playerY - 0.05) < (e.EnemyY[i] + 0.05)) && ((p.playerY + 0.05) > (e.EnemyY[i] - 0.05)))
						GamePlaying = false;
					GameOverScreen = false;
				}
			}
		}

		void GameOverInput()
		{
			if (GetAsyncKeyState(VK_LSHIFT) & 0x8000 || GetAsyncKeyState(VK_LSHIFT) & 0x8001)
			{
				ExitAll();
			}
			if (GetAsyncKeyState(VK_LCONTROL) & 0x8000 || GetAsyncKeyState(VK_LCONTROL) & 0x8001)
			{
				ReStart();
			}
			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000 || GetAsyncKeyState(VK_ESCAPE) & 0x8001)
			{
				ExitAll();
			}
		}

		void GameStartInput()
		{
			if (GetAsyncKeyState(VK_SPACE) & 0x8000 || GetAsyncKeyState(VK_SPACE) & 0x8001)
			{
				GamePlaying = true;
				StartScreen = false;
			}
			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000 || GetAsyncKeyState(VK_ESCAPE) & 0x8001)
			{
				ExitAll();
			}
		}

		void ExitAll()
		{
			IsGameRunning = false;
		}

		void ReStart()
		{
			GamePlaying = true;
			for (int i = 0; i < 10; i++) {
				e.EnemyY[i] = 1;
			}
			p.playerX = 0;
			p.playerY = 0;
		}
	};
}