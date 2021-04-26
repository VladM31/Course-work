#include "ThePersonWhoLearns.h"

size_t ThePersonWhoLearns::IdGlobal = 1;

ThePersonWhoLearns::ThePersonWhoLearns() :vLastname("No Name"), vName("No Name"),
vPatronymic("No Name"), vId(IdGlobal++), vRating(1) {}

ThePersonWhoLearns::ThePersonWhoLearns(sg Lastname, sg Name, sg Patronymic)    : vLastname(Lastname), vName(Name),
vPatronymic(Patronymic), vId(IdGlobal++), vRating(1){}

ThePersonWhoLearns::ThePersonWhoLearns(const ThePersonWhoLearns& other) : vLastname(other.vLastname), vName(other.vName),
vPatronymic(other.vPatronymic), vId(other.vId), vRating(other.vRating) {}

void ThePersonWhoLearns::Set(valA chose, size_t SetValue)
{
	if (valA::id==chose)
	{
		this->vId = SetValue;
	}
	else if(chose == valA::rat)
	{
		this->vRating = SetValue;
	}
}

sg ThePersonWhoLearns::Get(namA chose)
{
    if (chose == namA::Name)
    {
        return this->vName;
    }
    else if (chose == namA::Last)
    {
        return this->vLastname;
    }
    else if (chose == namA::Patr)
    {
        return this->vPatronymic;
    }
    else
    {
        return "<Metod Get>: Empty";
    }
}

size_t ThePersonWhoLearns::Get(valA chose)
{
    if (valA::id== chose)
    {
        return this->vId;
    }
    else if (valA::rat == chose)
    {
        return this->vRating;
    }
}

void ThePersonWhoLearns::SetConsole()
{
	std::cout << "Input data\n";
	std::cout << "Last name >> "; std::getline(std::cin, vLastname, '\n');
	std::cout << "Name >> "; std::getline(std::cin, vName, '\n');
	std::cout << "Patronymic >> "; std::getline(std::cin, vPatronymic, '\n');
	std::cout << "Id >> "; std::cin >> vId;
	std::cout << "Rating >> "; std::cin >> vRating;
}
