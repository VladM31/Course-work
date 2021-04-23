#include "ThePersonWhoLearns.h"

size_t ThePersonWhoLearns::IdGlobal = 1;

ThePersonWhoLearns::ThePersonWhoLearns() :vLastname("No Name"), vName("No Name"),
vPatronymic("No Name"), vId(IdGlobal++), vRating(1) {}

ThePersonWhoLearns::ThePersonWhoLearns(sg Lastname, sg Name, sg Patronymic)    : vLastname(Lastname), vName(Name),
vPatronymic(Patronymic), vId(IdGlobal++), vRating(1){}

ThePersonWhoLearns::ThePersonWhoLearns(const ThePersonWhoLearns& other) : vLastname(other.vLastname), vName(other.vName),
vPatronymic(other.vPatronymic), vId(other.vId), vRating(other.vRating) {}
