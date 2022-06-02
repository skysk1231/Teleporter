#pragma once
#include <iostream>

using namespace std;


namespace TGame_Engine
{
	
	class Player
	{
	public:
		float playerX;
		float playerY;

		Player() {
			playerX = 0;
			playerY = 0;
		};
		~Player() {};

		void UP()
		{
			playerY += 0.1;
		}
	};

	class TCommand
	{
	public:
		
		TCommand() {}
		virtual ~TCommand() {}

		virtual void Execute(Player* p) {}
	};

	class UPCommand :public TCommand
	{
	public:
		void Execute(Player* p)
		{
			if (p->playerY > 1)
			{
				p->playerY = 1;
			}
			p->playerY += 0.01f;
			
		}
	};
	class LEFTCommand :public TCommand
	{
	public:
		void Execute(Player* p)
		{
			if (p->playerX < -1)
			{
				p->playerX = -1;
			}
			p->playerX -= 0.01f;
			
		}
	};
	class RIGHTCommand :public TCommand
	{
	public:
		void Execute(Player* p)
		{
			if (p->playerX > 1)
			{
				p->playerX = 1;
			}
			p->playerX += 0.01f;
			
		}
	};
	class DOWNCommand : public TCommand
	{
	public:
		void Execute(Player* p)
		{
			if (p->playerY < -1)
			{
				p->playerY = -1;
			}
			p->playerY -= 0.01f;
			
		}
	};
}