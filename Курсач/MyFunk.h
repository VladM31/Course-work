#pragma once
#include "iterator.h"

class MyMenu
{
	int ChooseUser;
	Grup<Grup<ThePersonWhoLearns*>*>* MyListGrup;
	Grup<std::string>* MyNameGrup;
public:
	MyMenu(Grup<Grup<ThePersonWhoLearns*>*>* SetMyListGrup, Grup<std::string>* MyNameGrup);

	~MyMenu();
	// ==== Метод Класа ====
	// Главное меню
	int MainMenu();
	// Get
	// Повертає ліст стрингов
	Grup<std::string>* GetNameGrup();
	// Повертає групу 
	Grup<Grup<ThePersonWhoLearns*>*>* GetListGrup();
	 
	// ---- Static ----
	// Узнае сколько груп через файл Start
	static Grup<std::string> FindFileGrup(const char* nameFile = "Start.txt");
	// Ввиводит на консоль студентов групи 
	static void PrintGrupStudent(Grup<ThePersonWhoLearns*>* glist);
	// Третий пункт меню
	static void TheThirdMenu(MyMenu * MyMenuGrup);
};

// Создаю групу и заполняю её
Grup<ThePersonWhoLearns*>* FillGrup(Grup<std::string>* NameFile, size_t index);
// Меню виходу 
bool EndMenuProgram();
// Меню первого пункта
Grup<std::string>* FirstMenu(size_t SizeGrup);
// Ввивод данных первого пункта
void FirstMenuPrint(Grup<std::string>* FindName, MyMenu* MyMenuGrup);
// Меню второго пункта
void SecondMenu(MyMenu* MyMenuGrup);