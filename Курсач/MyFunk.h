#pragma once
#include "iterator.h"

class MyMenu
{
	int ChooseUser;
	Grup<Grup<ThePersonWhoLearns*>*>* MyListGrup;
public:
	MyMenu(Grup<Grup<ThePersonWhoLearns*>*>* SetMyListGrup, Grup<std::string>* MyNameGrup);

	~MyMenu();
	// ==== Метод Класа ====
	// Главное меню
	int MainMenu();
	// Get
	// Повертає групу 
	Grup<Grup<ThePersonWhoLearns*>*>* GetListGrup();
	 
	// ---- Static ----
	// Узнае сколько груп через файл Start
	static Grup<std::string> FindFileGrup(const char* nameFile = "Start.txt");
	// Ввиводит на консоль студентов групи (Повну інформацію)
	static void PrintGrupStudent(Grup<ThePersonWhoLearns*>* glist);
	// Ввиводит на консоль студентов групи (Прізвище, ім'я,по батькові)
	static void PrintGrupStudentItem_namA(Grup<ThePersonWhoLearns*>* glist,namA ValurC);
	// Ввиводит на консоль студентов групи (Рейтинг ,айди )
	static void PrintGrupStudentItem_valA(Grup<ThePersonWhoLearns*>* glist, valA ValurC);

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
	// 5.Змінити інформацію одного студетна
	static void TheFifthMenu(MyMenu* MyMenuGrup);
	// 6.Вивести одного студетна
	static void TheSixthMenu(MyMenu* MyMenuGrup);
	// 7.Добавити студента
	static void TheSeventhMenu(MyMenu* MyMenuGrup);
	// 8.Видалити студента
	static void TheEighthMenu(MyMenu* MyMenuGrup);
	// 9.Змінити назву групи
	static void NinthItem(MyMenu* MyMenuGrup);
	// 10.Ввивести студентів групи, у яких диплом виконаний понад 80%
	static void TenthMenu(MyMenu* MyMenuGrup);
	// 11.Сортувати студентів
	static void EleventhMenu(MyMenu* MyMenuGrup);
};


