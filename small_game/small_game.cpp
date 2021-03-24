#include "Player.h"
#include "Warrior.h"
#include "Wizard.h"
#include <vector>

void PrintAllPositions(const std::vector<Player*>& allHero);

void Check(std::vector<Player*>& allHero);

void DeleteAll(std::vector<Player*>& allHero);

int main()
{
	try
	{
		std::vector<Player*> game = std::vector<Player*>();
		Warrior* player1 = new Warrior((std::string)"Arthur", 0, 0);
		Wizard* player2 = new Wizard((std::string)"Gandalf", 5, 5);
		size_t choice;
		size_t turn = 0;

		game.push_back(player1);
		game.push_back(player2);

		try
		{
			while (true)
			{

				PrintAllPositions(game);

				std::cout << "\nNow it's " << game[turn]->Name() << "'s turn." << std::endl;
				std::cout << "\nYou can:" << std::endl;
				std::cout << "1 -- Attack!" << std::endl;
				std::cout << "2 -- MOOOOOOOOVE!" << std::endl;
				std::cout << "3 -- Relaaax~..." << std::endl;

				do
				{
					std::cout << "Your choice -- ";
					std::cin >> choice;

					if ((choice < 1) || (choice > 3))
						std::cout << "Hands are shaking. The choice is difficult. You missed the button!" << std::endl;

				} while ((choice < 1) || (choice > 3));

				std::cout << std::endl;

				switch (choice)
				{
				case(1):
					try
					{
						game[turn]->Attack(*game[(turn + 1) % 2]);
						turn = (turn + 1) % 2;
					}
					catch (AnotherMove error)
					{
						std::cerr << error.what() << std::endl;
					}
					break;

				case(2):
					int newX, newY;
					std::cout << "Enter new coordinates:" << std::endl;
					std::cout << "New X coordinate -- ";
					std::cin >> newX;
					std::cout << "New Y coordinate -- ";
					std::cin >> newY;

					try
					{
						game[turn]->Move(newX, newY);
						turn = (turn + 1) % 2;
					}
					catch (AnotherMove error)
					{
						std::cerr << error.what() << std::endl;
					}
					break;

				case(3):
					game[turn]->Relax();
					turn = (turn + 1) % 2;
					break;
				}

				system("pause");
				system("cls");
			}
		}
		catch (HeroDied error)
		{
			std::cerr << error.what() << std::endl;
		}

		DeleteAll(game);
		game.clear();
	}
	catch (std::bad_alloc error)
	{
		std::cerr << error.what() << std::endl;
	}

	return 0;
}

void PrintAllPositions(const std::vector<Player*>& allHero)
{
	for (auto it = allHero.begin(); it != allHero.end(); ++it)
	{
		int* position = (*it)->Position();
		std::cout << (*it)->Name() << " is position is " << position[0] << ", " << position[1] << std::endl;
		std::cout << "His health -- " << (*it)->Health() << std::endl;
		(*it)->PrintOtherParameters();
		std::cout << std::endl;
	}
}

void Check(std::vector<Player*>& allHero)
{
	for (size_t i = 0; i < allHero.size(); ++i)
		if (!allHero[i]->IsAlive())
		{
			delete allHero[i];
			allHero[i] = nullptr;
		}
}

void DeleteAll(std::vector<Player*>& allHero)
{
	for (size_t i = 0; i < allHero.size(); ++i)
		if (allHero[i] != nullptr)
		{
			delete allHero[i];
			allHero[i] = nullptr;
		}
}
