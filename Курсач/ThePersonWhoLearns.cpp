#include "ThePersonWhoLearns.h"

size_t ThePersonWhoLearns::IdGlobal = 1;

ThePersonWhoLearns::ThePersonWhoLearns() :vLastname("No Name"), vName("No Name"),
vPatronymic("No Name"), vId(IdGlobal++), vRating(1) {}

ThePersonWhoLearns::ThePersonWhoLearns(sg Lastname, sg Name, sg Patronymic)    : vLastname(Lastname), vName(Name),
vPatronymic(Patronymic), vId(IdGlobal++), vRating(1){}

ThePersonWhoLearns::ThePersonWhoLearns(const ThePersonWhoLearns& other) : vLastname(other.vLastname), vName(other.vName),
vPatronymic(other.vPatronymic), vId(other.vId), vRating(other.vRating) {}

void ThePersonWhoLearns::SetConsole()
{
	std::cout << "Input data\n";
	std::cout << "Last name >> "; std::getline(std::cin, vLastname, '\n');
	std::cout << "Name >> "; std::getline(std::cin, vName, '\n');
	std::cout << "Patronymic >> "; std::getline(std::cin, vPatronymic, '\n');
	std::cout << "Id >> "; std::cin >> vId;
	std::cout << "Rating >> "; std::cin >> vRating;
}
