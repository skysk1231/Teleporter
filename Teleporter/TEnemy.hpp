#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

namespace TGame_Engine
{
	class Enemy
	{
	public :
		float FixedX = -0.8;
		float EnemyX[5];
		float EnemyY[5];
		float Speed[5];

		Enemy()
		{
			for (int i = 0; i < 5; i++)
			{
				EnemyX[i] = FixedX;
				EnemyY[i] = 1;
				FixedX += 0.4f;
	
				Speed[i] = rand() % 10 / static_cast<float>(500);

			}
		}
		~Enemy(){}

		void MoveEnemy()
		{
			for (int i = 0; i < 5; i++)
			{
			if (EnemyY[i] <= -1)
				{
					EnemyY[i] = 1;
					Speed[i] = rand() % 5 / static_cast<float>(500) + 0.005f;
				}
				else
				{
				EnemyY[i] -= Speed[i];
				}
			}
		}

	};
}