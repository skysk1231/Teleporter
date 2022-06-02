#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

namespace TGame_Engine
{
	class Enemy
	{

		int a = 0;
	public :
		float FixedX = -0.8;
		float EnemyX[10];
		float EnemyY[10];
		float Speed[10];

		Enemy()
		{
			
		
		}
		~Enemy(){}

		void MoveEnemy()
		{
			for (int i = 0; i < 10; i++)
			{
			if (EnemyY[i] <= -1)
				{
					EnemyY[i] = 1;
					Speed[i] = rand() % 4 / static_cast<float>(500) + 0.005f;

					if (EnemyX[i] > 0)
					{
						EnemyX[i] = (rand() % 11) / static_cast<float>(10);
					}
					else if (EnemyX[i] == 0)
					{
						if ((a % 2) == 0)
						{
							EnemyX[i] = (rand() % 11) / static_cast<float>(10);
						}
						else
						{
							EnemyX[i] = -((rand() % 11) / static_cast<float>(10));
						}
						a++;
					}
					else
					{
						EnemyX[i] = -((rand() % 11) / static_cast<float>(10));
					}
				}
				else
				{
				EnemyY[i] -= Speed[i];
				}
			
			}
		}

		void Initialize()
		{
			for (int i = 0; i < 10; i++)
			{
				EnemyY[i] = 1;
				if (i < 5)
				{
					EnemyX[i] = (rand() % 11) / static_cast<float>(100);
				}
				else
				{
					EnemyX[i] = -1;
				}
				EnemyY[i] = 1;
				FixedX += 0.4f;

				Speed[i] = 1;
			}
		}
	};
}