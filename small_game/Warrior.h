#pragma once
#include "Player.h"

class Warrior : public Player
{
private:
	void Output() override
	{
		if (stamina <= 5)
			stamina = 0;
		else
			stamina -= 5;
	}


	virtual void VictoryCry(const std::string& otherName) override
	{
		std::cout << "My name is " << name << " and I have defeated the " << otherName << "!" << std::endl;
		std::cout << "As my grandfather used to say: \"The ax is your best friend\"!" << std::endl;
		attackPower += 3;
	}

	virtual bool CanAttack(const int enemyX, const int enemyY) const override
	{
		unsigned int distance = sqrt(pow(enemyX - coordinateX, 2) + pow(enemyY - coordinateY, 2));

		if (distance <= 3)
			return true;
		else
			return false;
	}

	virtual void DeathScream() override
	{
		std::cout << "My ax got so heavy..." << std::endl;

		throw HeroDied(name + " died...");
	}

public:
	Warrior(std::string name_, int coordinateX_, int coordinateY_)
		: Player(name_, coordinateX_, coordinateY_)
	{
		// ѕочему-то списки инициализации не прокатили
		health = 100;
		stamina = 100;
		attackPower = 10;
		attackCost = 5;
		moveCost = 2;
	}

	virtual void Relax() override
	{
		if (stamina >= 90)
			stamina = 100;
		else
			stamina += 10;

		std::cout << "Now I'm ready to fight again!" << std::endl;
	}

	virtual void PrintOtherParameters() override
	{
		std::cout << name << " has " << stamina << " points of stamina." << std::endl;
	}
};