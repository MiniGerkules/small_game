#pragma once
#include "Exeptions.h"
#include <iostream>
#include <cmath>

class Player
{
	friend class Master;

protected:
	std::string name;
	unsigned short health;
	unsigned short stamina;
	unsigned short attackPower;
	unsigned short attackCost;
	unsigned short moveCost;
	int coordinateX;
	int coordinateY;
	bool isAlive;

	virtual void Output() = 0;

	virtual void VictoryCry(const std::string& otherName) = 0;

	virtual bool CanAttack(const int enemyX, const int enemyY) const = 0;

	virtual void DeathScream() = 0;

public:
	Player(std::string name_, int coordinateX_, int coordinateY_)
		: name(std::move(name_)), coordinateX(coordinateX_), coordinateY(coordinateY_), isAlive(true)
	{
	}

	const std::string& Name() const { return name; }

	int* Position() const
	{
		int position[] = { coordinateX, coordinateY };

		return position;
	}

	unsigned short Health() const { return health; }

	bool IsAlive() const { return isAlive; }

	void Attack(Player& other)
	{
		if (CanAttack(other.coordinateX, other.coordinateY))
		{
			if (stamina > 0)
			{
				if (attackPower >= other.health)
				{
					other.health = 0;
					VictoryCry(other.name);
					std::cout << std::endl;
					other.DeathScream();
				}
				else
					other.health -= attackPower;

				std::cout << "Oh yeah! He got it right! " << other.name << " has " << other.health << " hp left!" << std::endl;
				Output();
			}
			else
				throw AnotherMove("I am so tired! I cannot do anything!");
		}
		else
			throw AnotherMove("I won't get it... We must try something different.");
	}

	void Move(const int newX, const int newY)
	{
		if (stamina > 0)
		{
			unsigned int distance = sqrt(pow(newX - coordinateX, 2) + pow(newY - coordinateY, 2));
			unsigned long energy = moveCost * distance;

			if (energy >= stamina)
				stamina = 0;
			else
				stamina -= energy;

			coordinateX = newX;
			coordinateY = newY;

			std::cout << "Walking again? Let's fight already!" << std::endl;
		}
		else
			throw AnotherMove("I am so tired! I cannot do anything!");
	}

	virtual void Relax() = 0;

	virtual void PrintOtherParameters() = 0;
};
