#pragma once
#include <iostream>

using namespace std;

namespace TGame_Engine
{
	class Player
	{
	public:
		float playerX =0;
		float playerY =0;
		Player() {
		};
		~Player() {};
	};

	class TCommand
	{
		
	public:
		Player p;
		TCommand() {}
		virtual ~TCommand() {}

		virtual void Execute() {}
	};

	class UPCommand :public TCommand
	{
	public:
		void Execute()
		{
			p.playerY += 0.1;
		}
	};
	class LEFTCommand :public TCommand
	{
	public:
		void Execute()
		{
			p.playerX -= 0.1f;
		}
	};
	class RIGHTCommand :public TCommand
	{
	public:
		void Execute()
		{
			p.playerX += 0.1;
			cout << p.playerX;
		}
	};
	class DOWNCommand : public TCommand
	{
	public:
		void Execute()
		{
			p.playerY -= 0.1;
		}
	};
}
