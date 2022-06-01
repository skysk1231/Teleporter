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

	class MGameLoop
	{
	private:

	public:
		MGameLoop() { IsGameRunning = false; }
		~MGameLoop() {}
		bool IsGameRunning;
		WindowManager Window;
		Enemy e;
		Player p;

		void Run()
		{
			IsGameRunning = true;
			Initialize();
			while (IsGameRunning)
			{
				Input();
				Render();
				Update();
			}
			Release();
		}

	private:
		void Initialize()
		{
			Window.Initialize();
			Key[0] = new UPCommand();
			Key[1] = new LEFTCommand();
			Key[2] = new RIGHTCommand();
			Key[3] = new DOWNCommand();
		}
		void Release()
		{
			Window.Release();
			for (size_t i = 0; i < 4; i++)
			{
				delete(Key[i]);
			}
		}
		void Input()
		{
			if (GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState(VK_UP) & 0x8001)
			{
				Key[0]->Execute();
			}
			if (GetAsyncKeyState(VK_LEFT) & 0x8000 || GetAsyncKeyState(VK_LEFT) & 0x8001)
			{
				Key[1]->Execute();
			}
			if (GetAsyncKeyState(VK_RIGHT) & 0x8000 || GetAsyncKeyState(VK_RIGHT) & 0x8001)
			{
				Key[2]->Execute();
			}
			if (GetAsyncKeyState(VK_DOWN) & 0x8000 || GetAsyncKeyState(VK_DOWN) & 0x8001)
			{
				Key[3]->Execute();
			}

		}
		void Update()
		{
			e.MoveEnemy();
		
		}
		void Render()
		{
			Window.RenderStart();
			Window.RenderPlayer(p.playerX,p.playerY);
			for (int i = 0; i < 5; i++)
			{
				Window.RenderEnemy(e.EnemyX[i],e.EnemyY[i]);
			}
			Window.RenderEnd();
		}

	};
}