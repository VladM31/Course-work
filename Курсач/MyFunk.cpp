#include "MyFunk.h"



Grup<ThePersonWhoLearns*>* FillGrup(Grup<std::string>* NameFile, size_t index)
{

	Grup<ThePersonWhoLearns*>* TempGrupS = new Grup<ThePersonWhoLearns*>;
	std::string temp;
	std::fstream OpenFile;//Создаю object для открития файлов
	OpenFile.open((*NameFile)[index].c_str(), std::ios::in);// Откриваю файл групи
	// Удаляю из названия групи .txt
	for (size_t i = 0; i < 4; i++)
	{
		(*NameFile)[index].pop_back();
	}
	// Вибираю групу дипломников или без
	std::cout << "Група " << (*NameFile)[index] << " Дипломники?" << std::endl
		<< "Введіть true or false : "; std::cin >> temp;
	for (size_t j = 0; !OpenFile.eof(); j++)
	{
		if (!OpenFile.is_open())
		{
			break;
		}
		// Дипломники
		if (temp == "true" || temp == "1")
			TempGrupS->push_back(new GraduateSD);
		// Просто студенти 
		else
			TempGrupS->push_back(new Student);
		// Заполняю клас даними из файла 
		(*TempGrupS)[j]->toScanFile(OpenFile);
		// Если конец файла то удаляем лишний объект класа
		if (OpenFile.eof()) {
			TempGrupS->pop_back();
		}

	}
	
	OpenFile.close();// Закриваю файл 
	ConsoleClear;// Очистка консоли 
	return TempGrupS;
}

bool EndMenuProgram()
{
	int Back;
	HANDLE Color_END = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout << "Вернутися в головне меню?" << std::endl;
	SetConsoleTextAttribute(Color_END, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	std::cout << "Натисніть 1 , щоб вернутися в головне меню" << std::endl;
	SetConsoleTextAttribute(Color_END, FOREGROUND_INTENSITY | FOREGROUND_RED);
	std::cout << "Натисніть 2 , щоб завершити програму" << std::endl;
	SetConsoleTextAttribute(Color_END,FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
	std::cout << "Введіть відповідь >> "; std::cin >> Back;
	ConsoleClear;
	return Back-2;
}
// Если в строке есть "/skip" , то вернет истину 
bool FindCommandSkip(std::string& check)
{
	return (check.find("/skip") + 1) ? true : false;
}

Grup<std::string>* FirstMenu(size_t SizeGrup)
{
	using std::cout;
	using std::string;
	string AnswerGrup;
	int AnswerChoose;
	Grup<std::string>* TempGrupS = new Grup<std::string>;
	cout << " 1.Вивести всі групи;\n";
	cout << " 2.Вивести декілька груп;\n";
	cout << " 3.Вивести одну групу;\n";
	cout << " Введіть свою відповідь >> "; std::cin >> AnswerChoose; std::cin.ignore();
	ConsoleClear;
	if (AnswerChoose == 2)
	{
		for (size_t i = 0; i < SizeGrup; i++)
		{
			cout << "Введіть /skip , щоб закінчити введення груп\n";
			cout << "Введіть групу >> "; std::getline(std::cin, AnswerGrup, '\n');
			ConsoleClear;
			if (FindCommandSkip(AnswerGrup))
				return (TempGrupS->GetSize())?TempGrupS:nullptr;
			else
				TempGrupS->push_back(AnswerGrup);
		}
		return TempGrupS;
	}
	else if (AnswerChoose == 3)
	{
		cout << "Введіть групу >> "; std::getline(std::cin, AnswerGrup, '\n');
		ConsoleClear;
		TempGrupS->push_back(AnswerGrup);
		return TempGrupS;
	}
	else
		return nullptr;
}

void FirstMenuPrint(Grup<std::string>* FindName, Grup<std::string>* AllName, Grup<Grup<ThePersonWhoLearns*>*> &GrupStudent)
{
	auto AllNameIter = AllName->begin();
	auto GroupList= GrupStudent.begin();
	if (!FindName)//FindName == nullptr
	{
		for (auto i : GroupList)
		{
			std::cout << *AllNameIter << std::endl;
			MyMenu::PrintGrupStudent(i);
			++AllNameIter;
		}
		return;
	}
	auto FindNameIter = FindName->begin();
	
	for (auto i: AllNameIter)
	{
		for (auto j: FindNameIter)
		{
			if (i==j)
			{
				std::cout << i << std::endl;
				MyMenu::PrintGrupStudent(*GroupList);
				continue;
			}
		}
		++GroupList;
	}
	delete FindName;
}

void SecondMenu(Grup<Grup<ThePersonWhoLearns*>*>& GrupStudent, Grup<std::string>* AllName)
{
	using std::cout;
	int SizeNewGrup;
	cout << "Введіть кількість нових груп >> "; std::cin >> SizeNewGrup; std::cin.ignore();
	ConsoleClear;
	if (SizeNewGrup < 1 || SizeNewGrup>25)
	{
		return;
	}
	std::string temp;
	while (SizeNewGrup)
	{
		cout << "Введіть /skip , щоб закінчити введення\n";
		cout << "Введіть назву групи >> "; std::getline(std::cin, temp, '\n');
		ConsoleClear;
		if (FindCommandSkip(temp))// Проверяю на скип
		{
			return;
		}
		GrupStudent.push_back(new Grup<ThePersonWhoLearns*>);// Добавляю новую групу
		AllName->push_back(temp);// Добавляю название новой групи
		--SizeNewGrup;
	}

}

Grup<std::string> MyMenu::FindFileGrup()
// Считивает файл на наличие файлов груп
{
	std::ifstream read("Start.txt");
	if (!read.is_open())
	{
		throw std::exception("File dont open!\n");
	}
	std::string temp;
	Grup<std::string> NameGrup;
	std::getline(read, temp, ':');
	std::getline(read, temp, '\n');
	for (size_t i = 0; !read.eof(); i++)
	{
		if (read.eof())
		{
			break;
		}
		std::getline(read, temp, '\n');
		temp = temp + ".txt";
		NameGrup.push_back(temp);
	}
	read.close();
	return  NameGrup;
}


void MyMenu::PrintGrupStudent(Grup<ThePersonWhoLearns*>* glist)
///Виводит на консоль дание групи 
{
	for (size_t j = 0; j < glist->GetSize(); j++)
	{
		// Вивожу информацию о студентах групи 
		std::cout << (*glist)[j]->toString() << std::endl << std::endl;
	}
	std::cout << std::endl;
}

int MyMenu::MainMenu()
{
	std::string CheckChoose;
	std::cout << " 1.Ввивести групу;" << std::endl;
	std::cout << " 2.Створити групу;" << std::endl;
	std::cout << " 3.Видалити групу;" << std::endl;
	std::cout << " 4.Зберегти в файл інформацію;" << std::endl;
	std::cout << " 5.Змінити інформацію;\n";
	std::cout << " 6.Вивести студента;\n";
	std::cout << " 7.Добавити студента;\n";
	std::cout << " 8.Видалити студента;\n";
	std::cout << " 9.Ввивести назви груп;\n";
	std::cout << " Введіть відповідь: "; std::cin >> CheckChoose;
	ConsoleClear;
	if (FindCommandSkip(CheckChoose))
	{
		return this->ChooseUser;
	}
	this->ChooseUser = atoi(CheckChoose.c_str());
	return this->ChooseUser;
}