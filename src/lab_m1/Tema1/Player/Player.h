#pragma once

#include "lab_m1/Tema1/GameObject.h"

namespace p1
{
	class Player : public GameObject
	{
	public:
		Player(Tema1* scene);

		void Awake();
		void Start();
		void Update(float deltaTime);

	public:
		static Player* Instance;
		int health = 3;
		int bullets = 3;
		int score = 0;

	private:
		void DrawHealth();
		void DrawBullets();
		void DrawScore();
	};
}