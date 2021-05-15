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
	// Меню первого пункта
	static Grup<std::string>* FirstMenu(MyMenu * menu);
	// Ввивод данных первого пункта
	static void FirstMenuPrint(Grup<std::string>* FindName, MyMenu* MyMenuGrup);
	// Меню второго пункта
	static void SecondMenu(MyMenu* MyMenuGrup);
	// Третий пункт меню
	static void TheThirdMenu(MyMenu * MyMenuGrup);
	// Меню виходу 
	static bool EndMenuProgram();
	// Создаю групу и заполняю её
	static Grup<ThePersonWhoLearns*>* FillGrup(Grup<std::string>* NameFile, size_t index, int &ChooseUser);
	// Сохранить в файл (меню четыре)
	static void SaveFile(MyMenu* MyMenuGrup);
	// Meny five
	static void TheFifthMenu(MyMenu* MyMenuGrup);
	// Пункт меню номер 9
	static void NinthItem(MyMenu* MyMenuGrup);
	// Пункт меню номер 10
	static void TenthMenu(MyMenu* MyMenuGrup);
};


