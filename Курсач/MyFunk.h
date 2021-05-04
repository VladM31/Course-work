#pragma once
#include "iterator.h"

class MyMenu
{

	int ChooseUser;
public:
	MyMenu() : ChooseUser(0) {}

	// ==== ћетод  ласа ====
	// √лавное меню
	int MainMenu();

	// ---- Static ----
	// ”знае сколько груп через файл Start
	static Grup<std::string> FindFileGrup();
	// ¬виводит на консоль студентов групи 
	static void PrintGrupStudent(Grup<ThePersonWhoLearns*>* glist);
	// “ретий пункт меню
	static void TheThirdMenu(Grup<Grup<ThePersonWhoLearns*>*>& GrupStudent, Grup<std::string>* AllName);
};

// —оздаю групу и заполн€ю еЄ
Grup<ThePersonWhoLearns*>* FillGrup(Grup<std::string>* NameFile, size_t index);
// ћеню виходу 
bool EndMenuProgram();
// ћеню первого пункта
Grup<std::string>* FirstMenu(size_t SizeGrup);
// ¬вивод данных первого пункта
void FirstMenuPrint(Grup<std::string>* FindName, Grup<std::string>* AllName, Grup<Grup<ThePersonWhoLearns*>*> &GrupStudent);
// ћеню второго пункта
void SecondMenu(Grup<Grup<ThePersonWhoLearns*>*>& GrupStudent, Grup<std::string>* AllName);