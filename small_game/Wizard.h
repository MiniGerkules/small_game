#pragma once
#include "Player.h"

class Wizard : public Player
{
private:
	unsigned short mana;

	void Output() override
	{
		if (mana <= 5)
			mana = 0;
		else
			mana -= 5;
	}

	virtual void VictoryCry(const std::string& otherName) override
	{
		std::cout << "My name is " << name << " and I have defeated the " << otherName << "!" << std::endl;
		std::cout << "My magic is getting stronger!" << std::endl;
		attackPower += 2;
	}

	virtual bool CanAttack(int enemyX, int enemyY) const override { return true; }

	virtual void DeathScream() override
	{
		std::cout << "My magic has run dry..." << std::endl;
		
		throw HeroDied(name + " died...");
	}

public:
	Wizard(std::string name_, int coordinateX_, int coordinateY_)
		: Player(name_, coordinateX_, coordinateY_)
	{
		// ѕочему-то списки инициализации не прокатили
		health = 100;
		stamina = 100;
		mana = 100;
		attackPower = 8;
		attackCost = 6;
		moveCost = 4;
	}

	virtual void Relax() override
	{
		if (stamina >= 95)
			stamina = 100;
		else
			stamina += 5;

		if (mana >= 95)
			mana = 100;
		else
			mana += 5;

		std::cout << "Even harsh wizards need rest at times." << std::endl;
	}

	virtual void PrintOtherParameters() override
	{
		std::cout << name << " has " << stamina << " points of stamina and " << mana 
			<< " points of mana." << std::endl;
	}
};