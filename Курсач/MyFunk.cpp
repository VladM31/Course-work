#include "MyFunk.h"

Grup<ThePersonWhoLearns*>* MyMenu::FillGrup(Grup<std::string>* NameFile, size_t index, int &ChooseUser)
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
	// Закидиваю в групу ее название
	TempGrupS->SetNameGroop((*NameFile)[index]);
	if (ChooseUser)
	{
		for (size_t j = 0; !OpenFile.eof(); j++)
		{
			if (!OpenFile.is_open())
			{
				break;
			}
			// Дипломники
			if (ChooseUser==1)
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
	// Вибираю групу дипломников или без
	std::cout << "Група " << (*NameFile)[index] << " Дипломники?" << std::endl
		<< "Введіть true or false : "; std::cin >> temp;
	if (FindCommandSkip(temp,"/all(1)"))//Всі інші будуть вибиратися як дипломники
	{
		ChooseUser = 1;
	}
	if (FindCommandSkip(temp, "/all(0)"))//Всі інші будуть вибиратися як студенти
	{
		ChooseUser = 2;
	}
	//Пока файл не закочится ,считиваем людей
	for (size_t j = 0; !OpenFile.eof(); j++)
	{
		//Проверка на откритие файла
		if (!OpenFile.is_open())
		{
			break;
		}
		// Дипломники
		if (temp == "true" || temp == "1" || ChooseUser == 1)
		{
			TempGrupS->push_back(new GraduateSD);
		}
		else	// Просто студенти 
		{
			TempGrupS->push_back(new Student);
		}
			
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

bool MyMenu::EndMenuProgram()
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

Grup<std::string>* MyMenu::FirstMenu(MyMenu* menu)
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
	if (menu->MyListGrup->GetSize() ==1)
	{
		return nullptr;
	}
	if (AnswerChoose == 2)
	{
		for (int i = 0; i < menu->MyListGrup->GetSize(); i++)
		{
			cout << "Введіть /skip , щоб закінчити введення груп\n";
			cout << " Групи :\n";
			for (auto k: menu->MyListGrup->begin())
			{
				cout << " " << k->GetNameGroop() << std::endl;
			}
			cout << "[/skip] Введіть групу >> "; std::getline(std::cin, AnswerGrup, '\n');
			ConsoleClear;
			if (FindCommandSkip(AnswerGrup))
				return (TempGrupS->GetSize()/*Если есть хотяби один елемент*/)?TempGrupS:nullptr;
			else
			{
				bool find = false, Check_for_identity = false;
				//TempGrupS->push_back(AnswerGrup);
				// Проверяю есть ли такая група
				for (auto it: menu->MyListGrup->begin())
				{
					if (it->GetNameGroop() == AnswerGrup)
					{
						find = true;
						break;
					}
					else {

						find = false;
					}
				}

				if (!i && find)// Если первий проход по циклу и такая групу есть то добавлю групу
				{
					TempGrupS->push_back(AnswerGrup);
				}
				else if (find)// Если не первий проход по циклу и такая групу есть 
				{
					// Проверяю на идентичность
					for (size_t v = 0; v < i; v++)
					{
						if (TempGrupS->operator[](v) == AnswerGrup)
						{
							Check_for_identity = true;
							// Если не идентична  , то виходжу з циклу
							break;
						}
						else
						{
							Check_for_identity = false;
						}
					}

					if (Check_for_identity)
					{
						std::cout << "Група " << AnswerGrup <<" була вже введена !!" << std::endl;
						i--;
					}
					else
					{
						TempGrupS->push_back(AnswerGrup);
					}
				}
				else
				{
					std::cout << "Група " << AnswerGrup << " не э в програмі !!" << std::endl;
					i--;
				}
			}
				
		}
		return TempGrupS;
	}
	else if (AnswerChoose == 3)
	{
		cout << " Групи :\n";
		for (auto k : menu->MyListGrup->begin())
		{
			cout <<" "<< k->GetNameGroop() << std::endl;
		}
		cout << "Введіть групу >> "; std::getline(std::cin, AnswerGrup, '\n');
		ConsoleClear;
		TempGrupS->push_back(AnswerGrup);
		return TempGrupS;
	}
	else
		return nullptr;
}

void  MyMenu::FirstMenuPrint(Grup<std::string>* FindName, MyMenu* MyMenuGrup)
{
	if (MyMenuGrup->GetListGrup()->empty())// == 0
	{
		std::cout << "Груп немає !!" << std::endl;
		Pause_Use;
		delete FindName;
		ConsoleClear;
	}
	//auto AllNameIter = MyMenuGrup->GetNameGrup()->begin();

	size_t ChoosePrint;
	using std::cout, std::endl, std::cin;
	cout << "1.Вивести всю інформацію" << endl;
	cout << "2.Вивести тільки прізвище" << endl;
	cout << "3.Вивести прізвище і ім'я" << endl;
	cout << "4.Вивести прізвище і по батькові" << endl;
	cout << "5.Вивести прізвище і ID" << endl;
	cout << "6.Вивести прізвище і рейтинг" << endl;
	cout << "7.Вивести назви груп" << endl;
	cout << "[Input] >> "; cin >> ChoosePrint;
	ConsoleClear;


	auto GroupList= MyMenuGrup->GetListGrup()->begin();
	if (!FindName)//FindName == nullptr
	{
		for (auto &i : GroupList)
		{
			std::cout << "***=======================================***" << std::endl;
			std::cout << "\t\t"<<i->GetNameGroop() << std::endl;
			std::cout << "***=======================================***" << std::endl;
			if (ChoosePrint >= 2 && ChoosePrint < 5)
			{
				//ChoosePrint-=2;
				MyMenu::PrintGrupStudentItem_namA(i, (namA)(ChoosePrint-2));
			}
			else if (ChoosePrint == 5 || ChoosePrint == 6)
			{
				//ChoosePrint -= 5;
				MyMenu::PrintGrupStudentItem_valA(i, (valA)(ChoosePrint-5));
			}
			else if (ChoosePrint==7)
			{
				std::cout << std::endl;
			}
			else
			{
				MyMenu::PrintGrupStudent(i);
			}
			
		}
		return;
	}
	auto FindNameIter = FindName->begin();
	
	for (auto i: MyMenuGrup->GetListGrup()->begin())
	{
		for (auto j: FindNameIter)
		{
			if (i->GetNameGroop()==j)
			{
				std::cout << "***=======================================***" << std::endl;
				std::cout << "\t\t" << i->GetNameGroop() << std::endl;
				std::cout << "***=======================================***" << std::endl;
				if (ChoosePrint >= 2 && ChoosePrint < 5)
				{
					//ChoosePrint -= 2;
					MyMenu::PrintGrupStudentItem_namA(*GroupList, (namA)(ChoosePrint-2));
				}
				else if (ChoosePrint == 5 || ChoosePrint == 6)
				{
					//ChoosePrint -= 5;
					MyMenu::PrintGrupStudentItem_valA(*GroupList, (valA)(ChoosePrint - 2));
				}
				else if (ChoosePrint == 7)
				{
					std::cout << std::endl;
				}
				else
				{
					MyMenu::PrintGrupStudent(*GroupList);
				}
				//MyMenu::PrintGrupStudent(*GroupList);
				continue;
			}
		}
		++GroupList;
	}
	delete FindName;
}

void MyMenu::SecondMenu(MyMenu* MyMenuGrup)
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
		
		MyMenuGrup->MyListGrup->push_back(new Grup<ThePersonWhoLearns*>);// Добавляю новую групу
		///***Delete***/MyMenuGrup->GetNameGrup()->push_back(temp);// Добавляю название новой групи
		MyMenuGrup->MyListGrup->operator[](MyMenuGrup->MyListGrup->GetSize())->SetNameGroop(temp);// Добавляю название новой групи
		--SizeNewGrup;
	}

}

Grup<std::string> MyMenu::FindFileGrup(const char * nameFile)
// Считивает файл на наличие файлов груп
{
	std::ifstream read(nameFile);
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

void MyMenu::TheThirdMenu(MyMenu* MyMenuGrup)
{
	using std::cout; using  std::endl; using  std::cin;
	size_t indexRemove = 0;// індекс для видалення 
	size_t numberGrupDelete;// Кількість груп для видалення
	std::string InPutUser;
	cout << "Введіть кількість груп для видалення "; cin >> InPutUser; cin.ignore();
	ConsoleClear;
	if (MyMenuGrup->MyListGrup->empty() | FindCommandSkip(InPutUser)/*Если ли скип*/ |
		((numberGrupDelete = atoi(InPutUser.c_str())/* Присвоюю значення кількость груп для видалення*/) > 
			MyMenuGrup->MyListGrup->GetSize(/*Если число груп для удаления больше чем груп*/)
		|| !numberGrupDelete/* == 0*/))
	{
		return;
	}

	while (numberGrupDelete)
	{
		cout << "Список груп: " << endl;
		for (auto i : MyMenuGrup->MyListGrup->begin())
		{
			cout << i->GetNameGroop() << endl;
		}
		cout << "Введіть групу для видалення >> ";
		std::getline(cin, InPutUser,'\n');
		// є скіп , то кінець функції
		if (FindCommandSkip(InPutUser))
		{
			return;
		}
		for (auto i : MyMenuGrup->MyListGrup->begin())
		{
			// Порівнює групи для видалення з тими ,якими є
			if (i->GetNameGroop() == InPutUser)
			{
				MyMenuGrup->MyListGrup->removeAt(indexRemove);
				///***Delete***/MyMenuGrup->MyNameGrup->removeAt(indexRemove);
				indexRemove = 0;
				break;
			}
			++indexRemove;
		}
		ConsoleClear;
		// Якщо більше нема , то на консоль виводится повідомлення
		if (MyMenuGrup->MyListGrup->empty())
		{
			cout << "Більше груп нема!!!!" << endl;
			Pause_Use;
			ConsoleClear;
			break;
		}
		// Якщо при провірці не було видалено групи , то виводить повідомлення ,
		// що група буда не знайдена
		else if (indexRemove == MyMenuGrup->MyListGrup->GetSize())
		{
			cout << "Група " << InPutUser << " НЕ ЗНАЙДЕНА!!!!" << endl;
			++numberGrupDelete;
		}
		// Якщо була видаленна гру то виведе повідомлення про це
		else
		{
			cout << "Група " << InPutUser << " видалена!" << endl;
		}
		Pause_Use;
		ConsoleClear;
		--numberGrupDelete;
	}



}

void MyMenu::PrintGrupStudent(Grup<ThePersonWhoLearns*>* g_list)
///Виводит на консоль дание групи 
{
	for (size_t j = 0; j < g_list->GetSize(); j++)
	{
		// Вивожу информацию о студентах групи 
		std::cout << (*g_list)[j]->toString() << std::endl << std::endl;
	}
	std::cout << std::endl;
}

void MyMenu::PrintGrupStudentItem_valA(Grup<ThePersonWhoLearns*>* g_list, valA ValurC)
///Виводит на консоль дание групи 
{
	for (auto i : g_list->begin())
	{
		switch (ValurC)
		{
		case valA::id:
			std::cout << i->Get(namA::Last);// Виводжу  прізвище
			for (size_t j = 0; j < 39 - i->Get(namA::Last).length(); j++)// Роблю інтервал
			{
				std::cout << ' ';
			}
			std::cout << " " << i->Get(valA::id) << std::endl;//Виводжу id
			break;
		case valA::rat:
			std::cout << i->Get(namA::Last);// Виводжу  прізвище
			for (size_t j = 0; j < 39 - i->Get(namA::Last).length(); j++)// Роблю інтервал
			{
				std::cout << ' ';
			}
			std::cout << " " << i->Get(valA::rat) << std::endl;//Виводжу rat
			break;
		default:
			break;
		}
	}
	std::cout << std::endl;
}

void MyMenu::PrintGrupStudentItem_namA(Grup<ThePersonWhoLearns*>* g_list, namA ValurC)
///Виводит на консоль дание групи 
{
	for (auto i: g_list->begin())
	{
		switch (ValurC)
		{
		case namA::Last:
			// Виводжу тільки прізвище
			std::cout << i->Get(namA::Last) << std::endl;
			break;
		case namA::Name:
			std::cout << i->Get(namA::Last);// Виводжу  прізвище
			for (size_t j = 0; j < 39- i->Get(namA::Last).length(); j++)// Роблю інтервал
			{
				std::cout << ' ';
			}
			std::cout << " " << i->Get(namA::Name) << std::endl;//Виводжу ім'я
			break;
		case namA::Patr:
			std::cout << i->Get(namA::Last);// Виводжу  прізвище
			for (size_t j = 0; j < 39 - i->Get(namA::Last).length(); j++)// Роблю інтервал
			{
				std::cout << ' ';
			}
			std::cout << " " << i->Get(namA::Patr) << std::endl;// Виводжу по бітькові
			break;
		case namA::any:
			break;
		default:
			break;
		}
	}
	std::cout << std::endl;
	
}

int MyMenu::MainMenu()
{
	std::string CheckChoose;// Змінна для запам'ятовування відповіді 
	std::cout << " 1.Ввивести групу;" << std::endl;
	std::cout << " 2.Створити групу;" << std::endl;
	std::cout << " 3.Видалити групу;" << std::endl;
	std::cout << " 4.Зберегти в файл інформацію;" << std::endl;
	std::cout << " 5.Змінити інформацію одного студетна;\n";
	std::cout << " 6.Вивести одного студетна ;\n";
	std::cout << " 7.Добавити студента;\n";
	std::cout << " 8.Видалити студента;\n";
	std::cout << " 9.Змінити назву групи;\n";
	std::cout << " 10.Ввивести студентів групи, у яких диплом виконаний понад 80%;\n";
	std::cout << " 11.Сортувати студентів ;\n";
	std::cout << " [/skip][/end]Введіть відповідь: "; std::cin >> CheckChoose;
	ConsoleClear;
	if (FindCommandSkip(CheckChoose))
	{
		return this->ChooseUser;
	}
	else if (FindCommandSkip(CheckChoose,"/end"))
	{
		return this->ChooseUser=111;
	}
	this->ChooseUser = atoi(CheckChoose.c_str());
	return this->ChooseUser;
}

MyMenu::MyMenu(Grup<Grup<ThePersonWhoLearns*>*>* SetMyListGrup, Grup<std::string>* SetMyNameGrup) : ChooseUser(0),MyListGrup(SetMyListGrup)
{
	for (size_t i = 0; i < SetMyNameGrup->GetSize(); i++)
	{
		MyListGrup->push_back(FillGrup(SetMyNameGrup, i,this->ChooseUser));// Создаю Групу студентов 
	}
	/* очистить тут потом память надо будет Grup<std::string>* SetMyNameGrup*/
	delete SetMyNameGrup;
}

Grup<Grup<ThePersonWhoLearns*>*>* MyMenu::GetListGrup()
{
	return this->MyListGrup;
}

MyMenu::~MyMenu()
{
	for (size_t i = 0; i < MyListGrup->GetSize(); i++)
	{
		while (0 < (*MyListGrup)[i]->GetSize())
		{
			delete (*((*MyListGrup)[i]))[0];
			(*MyListGrup)[i]->pop_front();
		}
	}
	delete MyListGrup;
}

void MyMenu::SaveFile(MyMenu* MyMenuGrup)
{
	if (!MyMenuGrup->MyListGrup->GetSize())
	{
		std::cout << "Нема , що зберігти" << std::endl;
		Pause_Use;
		ConsoleClear;
		return;
	}
	std::cout << "Назва груп " << std::endl;
	for (auto NameGrup: MyMenuGrup->MyListGrup->begin())
	{
		std::cout << NameGrup->GetNameGroop() << std::endl;
	}

	std::cout << "Введіть назви груп для збереження!" << std::endl;
	/// 
	Grup<std::string> NameFileSave;
	std::string temp;
	bool allSave = false;
	auto NameGrupCkl = MyMenuGrup->MyListGrup->begin();
	std::fstream FilePut;
	/// 
	while (NameFileSave.GetSize() <= MyMenuGrup->MyListGrup->GetSize())
	{
		std::cout << "[/skip][/all][Input] >> "; std::cin >> temp;
		if (FindCommandSkip(temp))
		{
			break;
		}
		if (FindCommandSkip(temp,"/all"))
		{
			allSave = true;
			break;
		}
		for (auto NameGrup : MyMenuGrup->MyListGrup->begin())
		{
			if (temp == NameGrup->GetNameGroop())
			{
				NameFileSave.push_back(temp);
				break;
			}
		}
	}
	ConsoleClear;
	if (allSave)
	{
		for (auto Grup : MyMenuGrup->MyListGrup->begin())
		{
			temp = (*NameGrupCkl)->GetNameGroop() + "_Save.txt";
			FilePut.open(temp, std::ios::out);
			for (auto StudentGrup : Grup->begin())
			{
				StudentGrup->toPutFile(FilePut);
			}
			FilePut.close();
			NameGrupCkl++;
	
		}
		return;
	}
	else
	{
		if (!NameFileSave.GetSize())
		{
			return;
		}
		auto Grupp = MyMenuGrup->MyListGrup->begin();
		for (auto findName: NameFileSave.begin())
		{
			if ((*NameGrupCkl)->GetNameGroop() == (findName))
			{
				NameGrupCkl = NameGrupCkl.begin();
				FilePut.open(findName + "_Save.txt");
				for (auto StudentGrup : (*Grupp)->begin())
				{
					StudentGrup->toPutFile(FilePut);
				}

			}
		}

	}
}

void MyMenu::TheFifthMenu(MyMenu* MyMenuGrup)
{
	//----------------//
	std::string tempUse;
	size_t indexs=0,number=1;
	bool Exit = false;
	//----------------//
	if (MyMenuGrup->MyListGrup->empty())
	{
		std::cout << "Нема , що змінити!" << std::endl;
		Pause_Use;
		ConsoleClear;
		return;
	}
	while (true)
	{
		std::cout << "Назва груп " << std::endl;
		// Виводжу на консоль назви груп
		for (auto NameGrup : MyMenuGrup->MyListGrup->begin())
		{
			std::cout << NameGrup->GetNameGroop() << std::endl;
		}
		std::cout << "Введіть групу >> "; std::cin >> tempUse;
		// Перевірка на команду /скіп
		if (FindCommandSkip(tempUse))
		{
			ConsoleClear;
			std::cout << "Повернення у головне меню" << std::endl;
			Pause_Use;
			ConsoleClear; return;
		}
		// Перевірка на існування введеної групи
		for (auto i: MyMenuGrup->MyListGrup->begin())
		{
			if (tempUse==i->GetNameGroop())
			{
				//якщо група була знайдена , то флаг міняє своє значення на істину
				Exit = true;
				break;
			}
			++indexs;
		}
		ConsoleClear;
		// 
		if (Exit)
		{
			break;
		}
		else
		{
			std::cout << "Група " << tempUse << " не знайдена !!!" << std::endl;
			indexs = 0;
			Pause_Use;
			ConsoleClear;
		}
	}
	using std::cout, std::endl,std::cin;
	while (true)
	{
		cout << "Виберіть студента (введіть цифру)" << endl;
		for (auto i : MyMenuGrup->MyListGrup->operator[](indexs)->begin())
		{
			cout << number++ <<")"<< i->Get(namA::Last) << " " << i->Get(namA::Name).at(0) << "." << i->Get(namA::Patr).at(0) << ".\n";
		}
		cout << "Введіть вибір >> "; std::cin >> tempUse;
		if (FindCommandSkip(tempUse))
		{
			ConsoleClear;
			std::cout << "Повернення у головне меню" << std::endl;
			Pause_Use;
			ConsoleClear; return;
		}
		number = static_cast<size_t>(atoi(tempUse.c_str()));
		if (number<1 || number>MyMenuGrup->MyListGrup->operator[](indexs)->GetSize())
		{
			cout << "Не та цифра!!!Введіть нову" << endl;
			Pause_Use;
			ConsoleClear;
		}
		else
		{
			break;
		}
	}
	ConsoleClear;
	auto ChangesInTheStudent = MyMenuGrup->MyListGrup->operator[](indexs)->operator[](number - 1);
	while (true)
	{
		cout << "1.Змінити рейтинг" << endl;
		cout << "2.Змінити Id" << endl;
		cout << "3.Зміните Прізвище" << endl;
		cout << "4.Змінити Ім'я" << endl;
		cout << "5.Змінити По батькові" << endl;
		cout << "6.Змінити все інше" << endl;
		cout << "Imput chose >> "; std::cin >> tempUse; std::cin.ignore();
		ConsoleClear;
		if (FindCommandSkip(tempUse))
		{
			return;
		}
		switch (atoi(tempUse.c_str()))
		{
		case 1:
			cout << "Введіть рейтин" << endl;
			std::getline(cin, tempUse, '\n');
			if (FindCommandSkip(tempUse))
			{
				return;
			}
			ChangesInTheStudent->Set(valA::rat, atoi(tempUse.c_str()));
			break;
		case 2:
			cout << "Введіть Id" << endl;
			std::getline(cin, tempUse, '\n');
			if (FindCommandSkip(tempUse))
			{
				return;
			}
			ChangesInTheStudent->Set(valA::id, atoi(tempUse.c_str()));
			break;
		case 3:
			cout << "Введіть Прізвище" << endl;
			std::getline(cin, tempUse, '\n');
			if (FindCommandSkip(tempUse))
			{
				return;
			}
			ChangesInTheStudent->Set(namA::Last, tempUse);
			break;
		case 4:
			cout << "Введіть Ім'я" << endl;
			std::getline(cin, tempUse, '\n');
			if (FindCommandSkip(tempUse))
			{
				return;
			}
			ChangesInTheStudent->Set(namA::Name, tempUse);
			break;
		case 5:
			cout << "Введіть По батькові" << endl;
			std::getline(cin, tempUse, '\n');
			if (FindCommandSkip(tempUse))
			{
				return;
			}
			ChangesInTheStudent->Set(namA::Patr, tempUse);
			break;
		default:
			ChangesInTheStudent->SetConsole();
			break;
		}
		ConsoleClear;
	}

}

void MyMenu::TheSixthMenu(MyMenu* MyMenuGrup)
{
	if (MyMenuGrup->MyListGrup->empty())
	{
		std::cout << "Груп нема" << std::endl;
		Pause_Use;
		ConsoleClear;
	}
	using std::cin, std::cout, std::endl; cin.ignore();
	std::string value;
	bool find = true;
	size_t indexGrup = 0;// Індекс групи шуканого студента
	size_t indexStudent = 0;
	//**********************
	// ---------------- Перевірка є ли така група в програмі ----------------
	do
	{
		cout << " Перелічення груп:" << endl;
		// Виводжу на консоль всі групи
		for (auto i : MyMenuGrup->MyListGrup->begin())
		{
			cout << "- " << i->GetNameGroop() << endl;
		}
		cout << "[/skip] Введіть відповідь >> "; std::getline(cin, value, '\n');
		if (FindCommandSkip(value))
		{
			ConsoleClear;
			cout << "Повернення у головне меню" << endl;
			Pause_Use;
			ConsoleClear; return;
		}
		ConsoleClear;
		for (auto i : MyMenuGrup->MyListGrup->begin())
		{
			
			if (i->GetNameGroop() == value)
			{
				find = false;
				break;
			}
			++indexGrup;
		}
		if (find)
		{
			cout << "Групa " << value << " нема в базі" << endl;
			indexGrup = 0;
		}
	} while (find);
	// ---------------- Перевірка є ли така група в програмі ----------------


	// ================ Перевірка є ли таке айді в програмі
	find = true;
	do
	{
		for (auto i : (*MyMenuGrup->MyListGrup)[indexGrup]->begin())
		{
			cout << i->Get(namA::Last) << " " << i->Get(namA::Name)[0] << "." << i->Get(namA::Patr)[0] << ".";
			for (size_t j = 0; j < 33 - i->Get(namA::Last).length(); j++)
			{
				cout << " ";
			}
			cout << "Id: " << i->Get(valA::id) << endl;
		}
		cout << "[/skip][ Id ] >> "; std::getline(cin, value, '\n');

		if (FindCommandSkip(value))
		{
			ConsoleClear;
			cout << "Повернення у головне меню" << endl;
			Pause_Use;
			ConsoleClear; return;
		}
		ConsoleClear;
		for (auto i : (*MyMenuGrup->MyListGrup)[indexGrup]->begin())
		{
			if (i->Get(valA::id)== atoi(value.c_str()))
			{
				find = false;
				break;
			}
			++indexStudent;
			
		}

		if (find)
		{
			cout << "Id " << value << " нема в базі" << endl;
			indexStudent = 0;
		}

	} while (find);
	ConsoleClear;

	HANDLE Color_END = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(Color_END, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);

	cout << "==============================================\n";
	cout << "\t\t" << (*MyMenuGrup->MyListGrup)[indexGrup]->GetNameGroop() << endl;
	cout << "==============================================\n";
	// Встановлює жовтий колір
	SetConsoleTextAttribute(Color_END, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	cout << "Прізвище : " << (*MyMenuGrup->MyListGrup)[indexGrup]->operator[](indexStudent)->Get(namA::Last) << endl;
	cout << "Ім'я : " << (*MyMenuGrup->MyListGrup)[indexGrup]->operator[](indexStudent)->Get(namA::Name) << endl;
	cout << "По батькові : " << (*MyMenuGrup->MyListGrup)[indexGrup]->operator[](indexStudent)->Get(namA::Patr) << endl;
	// Встановлює нормальний колір
	SetConsoleTextAttribute(Color_END, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
	cout << "==============================================\n";
	if ((*MyMenuGrup->MyListGrup)[indexGrup]->operator[](indexStudent)->Get(valA::rat)<60)
	{
		// Встановлюю червоний колір ,якщо рейтинг менше 60
		SetConsoleTextAttribute(Color_END, FOREGROUND_INTENSITY | FOREGROUND_RED);
	}
	else
	{
		// Встановлюю зелений колір ,якщо рейтинг більше або дорівнює 60
		SetConsoleTextAttribute(Color_END, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	}
	cout << "Rating : " << (*MyMenuGrup->MyListGrup)[indexGrup]->operator[](indexStudent)->Get(valA::rat) << endl;
	// Встановлює нормальний колір
	SetConsoleTextAttribute(Color_END, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
	cout << "==============================================\n";
	cout<<"Id : "<< (*MyMenuGrup->MyListGrup)[indexGrup]->operator[](indexStudent)->Get(valA::id) << endl;
	cout << "==============================================\n";
	if (std::string("class GraduateSD") == typeid(*(*MyMenuGrup->MyListGrup)[indexGrup]->operator[](indexStudent)).name())
	{
		if (atoi((*MyMenuGrup->MyListGrup)[indexGrup]->operator[](indexStudent)->Get(namA::any).c_str()) < 80)
		{
			SetConsoleTextAttribute(Color_END, FOREGROUND_INTENSITY | FOREGROUND_RED);
		}
		else
		{
			SetConsoleTextAttribute(Color_END, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
		}
		cout << "Дипломна робота зроблена на : " << (*MyMenuGrup->MyListGrup)[indexGrup]->operator[](indexStudent)->Get(namA::any) << endl;
		SetConsoleTextAttribute(Color_END, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
		cout << "==============================================\n";
	}
	cout << "Повна інформація : " << endl;
	SetConsoleTextAttribute(Color_END, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	cout << (*MyMenuGrup->MyListGrup)[indexGrup]->operator[](indexStudent)->toString();
	SetConsoleTextAttribute(Color_END, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
	cout << "\n==============================================\n";
	Pause_Use; 
	ConsoleClear;
}

void MyMenu::TheSeventhMenu(MyMenu* MyMenuGrup)
{
	if (MyMenuGrup->MyListGrup->empty())
	{
		std::cout << "Груп нема" << std::endl;
		Pause_Use;
		ConsoleClear;
	}
	using std::cin, std::cout, std::endl; cin.ignore();
	std::string value;
	bool find = true;
	size_t indexGrup = 0;// Індекс групи шуканого студента
	//**********************
	// ---------------- Перевірка є ли така група в програмі ----------------
	do
	{
		cout << " Перелічення груп:" << endl;
		// Виводжу на консоль всі групи
		for (auto i : MyMenuGrup->MyListGrup->begin())
		{
			cout << "- " << i->GetNameGroop() << endl;
		}
		cout << "[/skip] Введіть відповідь >> "; std::getline(cin, value, '\n');
		if (FindCommandSkip(value))
		{
			ConsoleClear;
			cout << "Повернення у головне меню" << endl;
			Pause_Use;
			ConsoleClear; return;
		}
		ConsoleClear;
		for (auto i : MyMenuGrup->MyListGrup->begin())
		{

			if (i->GetNameGroop() == value)
			{
				find = false;
				break;
			}
			++indexGrup;
		}
		if (find)
		{
			cout << "Групa " << value << " нема в базі" << endl;
			indexGrup = 0;
		}
	} while (find);
	// ---------------- Перевірка є ли така група в програмі ----------------
	ConsoleClear;
	cout << "==============================================\n";
	cout << "\tГрупа " << (*MyMenuGrup->MyListGrup)[indexGrup]->GetNameGroop() << endl;
	cout << "==============================================\n";
	cout << "Добавити студента? Введіть true або false \n";
	cout << "[Input] >> "; std::getline(cin, value, '\n');

	if (!FindCommandSkip(value,"true") )
	{
		ConsoleClear;
		cout << "Повернення у головне меню" << endl;
		Pause_Use;
		ConsoleClear;
		return;
	}
	ConsoleClear;

	cout<<"Студент дипломник ? Введіть true або false \n";
	cout << "[Input] >> "; std::getline(cin, value, '\n');
	if (FindCommandSkip(value, "true") || FindCommandSkip(value, "1"))
	{
		(*MyMenuGrup->MyListGrup)[indexGrup]->push_back(new GraduateSD);
	}
	else
	{
		(*MyMenuGrup->MyListGrup)[indexGrup]->push_back(new Student);
	}
	ConsoleClear;

	cout << "Заповніть поля студента! Будь-ласка не використовуйте команду /skip!" << endl;
	(*MyMenuGrup->MyListGrup)[indexGrup]->operator[]((*MyMenuGrup->MyListGrup)[indexGrup]->GetSize() - 1)->SetConsole();
	Pause_Use;
	ConsoleClear;
}

void MyMenu::TheEighthMenu(MyMenu* MyMenuGrup)
{
	if (MyMenuGrup->MyListGrup->empty())
	{
		std::cout << "Груп нема" << std::endl;
		Pause_Use;
		ConsoleClear;
	}
	using std::cin, std::cout, std::endl; cin.ignore();
	std::string value;
	bool find = true;
	size_t indexGrup = 0;// Індекс групи шуканого студента
	size_t indexStudent = 0;// Індекс шуканого студента
	//**********************
	// ---------------- Перевірка є ли така група в програмі ----------------
	do
	{
		cout << " Перелічення груп:" << endl;
		// Виводжу на консоль всі групи
		for (auto i : MyMenuGrup->MyListGrup->begin())
		{
			cout << "- " << i->GetNameGroop() << endl;
		}
		cout << "[/skip] Введіть відповідь >> "; std::getline(cin, value, '\n');
		if (FindCommandSkip(value))
		{
			ConsoleClear;
			cout << "Повернення у головне меню" << endl;
			Pause_Use;
			ConsoleClear; return;
		}
		ConsoleClear;
		for (auto i : MyMenuGrup->MyListGrup->begin())
		{

			if (i->GetNameGroop() == value)
			{
				find = false;
				break;
			}
			++indexGrup;
		}
		if (find)
		{
			cout << "Групa " << value << " нема в базі" << endl;
			indexGrup = 0;
		}
	} while (find);
	// ---------------- Перевірка є ли така група в програмі ----------------


	// ================ Перевірка є ли таке айді в програмі =================
	find = true;
	do
	{
		for (auto i : (*MyMenuGrup->MyListGrup)[indexGrup]->begin())
		{
			cout << i->Get(namA::Last) << " " << i->Get(namA::Name)[0] << "." << i->Get(namA::Patr)[0] << ".";
			for (size_t j = 0; j < 33 - i->Get(namA::Last).length(); j++)
			{
				cout << " ";
			}
			cout << "Id: " << i->Get(valA::id) << endl;
		}
		cout << "[/skip][ Id ] >> "; std::getline(cin, value, '\n');

		if (FindCommandSkip(value))
		{
			ConsoleClear;
			cout << "Повернення у головне меню" << endl;
			Pause_Use;
			ConsoleClear; return;
		}
		ConsoleClear;
		for (auto i : (*MyMenuGrup->MyListGrup)[indexGrup]->begin())
		{
			if (i->Get(valA::id) == atoi(value.c_str()))
			{
				find = false;
				break;
			}
			++indexStudent;

		}

		if (find)
		{
			cout << "Id " << value << " нема в базі" << endl;
			indexStudent = 0;
		}

	} while (find);
	// ================ Перевірка є ли таке айді в програмі =================
	ConsoleClear;
	cout<<"Студент "<< (*(*MyMenuGrup->MyListGrup)[indexGrup])[indexStudent]->Get(namA::Last)
		<<" " << (*(*MyMenuGrup->MyListGrup)[indexGrup])[indexStudent]->Get(namA::Name)[0]
		<<"." << (*(*MyMenuGrup->MyListGrup)[indexGrup])[indexStudent]->Get(namA::Patr)[0]
		<< ". Id : " << (*(*MyMenuGrup->MyListGrup)[indexGrup])[indexStudent]->Get(valA::id)<< " був видалений" << endl;
	(*(*MyMenuGrup->MyListGrup)[indexGrup]).removeAt(indexStudent);
	Pause_Use;
	ConsoleClear;
}

void MyMenu::NinthItem(MyMenu* MyMenuGrup)
{
	if (MyMenuGrup->MyListGrup->empty())
	{
		std::cout << "Груп нема" << std::endl;
		Pause_Use;
		ConsoleClear;
	}
	std::cin.ignore();
	std::string value;
	bool Find = true;
	while (true)
	{
		Find = true;
		std::cout << "Групи :" << std::endl; 
		for (auto i : MyMenuGrup->MyListGrup->begin())
		{
			std::cout <<"- "<< i->GetNameGroop() << std::endl;
		}
		std::cout << " Дії :" << std::endl;
		std::cout << "1.Змінити назву групи" << std::endl;
		std::cout << "2.Поверутись  у головне меню" << std::endl;
		std::cout << "                                      <<\r"; std::cout << "Введіть >> ";
		std::getline(std::cin, value, '\n');
		ConsoleClear;
		if (FindCommandSkip(value,"1") || FindCommandSkip(value, "Змінити"))
		{
			std::cout << "Групи :" << std::endl;
			for (auto i : MyMenuGrup->MyListGrup->begin())
			{
				std::cout << i->GetNameGroop() << std::endl;
			}
			std::cout << "                                       <<\r"; 
			std::cout << "Введіть групу >> "; std::getline(std::cin, value, '\n');
			if (FindCommandSkip(value))
			{
				return;
			}
			ConsoleClear;
			for (auto &i : MyMenuGrup->MyListGrup->begin())
			{
				if (i->GetNameGroop() == value)
				{
					std::cout << "                                       <<\r";
					std::cout << "Введіть нову назву >> "; std::getline(std::cin, value, '\n');
					if (FindCommandSkip(value))
					{
						return;
					}
					ConsoleClear;
					std::cout << "Назву змінено з " << i->GetNameGroop() << " на "<< value << std::endl;
					i->SetNameGroop(value);
					Find = false;
				}
			}
			if (Find)
			{
				std::cout << "Групи " << value << " немає!!!" << std::endl;
			}
			Pause_Use;
			ConsoleClear;
		}
		else
		{
			ConsoleClear;
			return;
		}
	}
}

void PrintOfWork(Grup<ThePersonWhoLearns*>* i)
{
	const std::string checkThatTheStudentIsA_SD("class GraduateSD");
	for (auto j : i->begin())
	{
		// Переверія чи студент має диплом
		if (checkThatTheStudentIsA_SD == typeid(*j).name())
		{
			if (atof(j->Get(namA::any).c_str()) > 80)
			{
				std::cout << j->Get(namA::Name) << " " <<  j->Get(namA::any) << std::endl;
			}
		}
		// Якщо нкмає то виводжу про це повідомлення
		else
		{
			std::cout << "Студент " << j->Get(namA::Last)<<" "<<j->Get(namA::Name)<< " " << j->Get(namA::Patr)
				<<" не є дипломником" << std::endl;
		}
	}
}

void MyMenu::TenthMenu(MyMenu* MyMenuGrup)
{
	if (MyMenuGrup->MyListGrup->empty())
	{
		std::cout << "Груп нема" << std::endl;
		Pause_Use;
		ConsoleClear;
	}
	std::string value;
	bool Find=true;
	auto NameAllGrup = MyMenuGrup->MyListGrup->begin();
	//***************
	std::cout << "Групи :" << std::endl; std::cin.ignore();
	for (auto i : MyMenuGrup->MyListGrup->begin())
	{
		std::cout << i->GetNameGroop() << std::endl;
	}
	std::cout << "Введіть назву групи або введіть /all , щоб вивести всі групи " << std::endl;
	std::cout << "Ввод >> "; std::getline(std::cin, value, '\n');
	ConsoleClear;
	if (FindCommandSkip(value,"/all"))
	{
		for (auto i: MyMenuGrup->MyListGrup->begin())
		{
			std::cout << "Група "<< i->GetNameGroop() << std::endl;
			PrintOfWork(i);
			++NameAllGrup;
		}
	}
	else if (FindCommandSkip(value))
	{
		ConsoleClear;
		return;
	}
	else
	{
		for (size_t i = 0; i < MyMenuGrup->MyListGrup->GetSize(); i++,++NameAllGrup)
		{
			if (value == (*NameAllGrup)->GetNameGroop())
			{
				PrintOfWork(MyMenuGrup->MyListGrup->operator[](i));
				Find = false;
				break;
			}
		}
		if (Find)
		{
			std::cout << "Групи "<< value <<" немає!!!" << std::endl;
		}
	}
	Pause_Use;
	ConsoleClear;
	return;
}

void SortGrup(Grup<ThePersonWhoLearns*>* i,size_t index)
{
	bool Sort = true;
	iterator_g<ThePersonWhoLearns*> j = i->begin();
	iterator_g<ThePersonWhoLearns*> k = (++i->begin());
	while(Sort)
	{ 
		Sort = false;
		for (; k != k.end(); ++j, ++k)
		{
			switch (index)
			{
			case 1:
				if ((*j)->Get(namA::Last) > (*k)->Get(namA::Last))
				{
					std::swap(*j, *k); Sort = true;
				}
				break;
			case 2:
				if ((*j)->Get(namA::Name) > (*k)->Get(namA::Name))
				{
					std::swap(*j, *k); Sort = true;
				}
				break;
			case 3:
				if ((*j)->Get(namA::Patr) > (*k)->Get(namA::Patr))
				{
					std::swap(*j, *k); Sort = true;
				}
				break;
			case 4:
				if ((*j)->Get(valA::rat) > (*k)->Get(valA::rat))
				{
					std::swap(*j, *k); Sort = true;
				}
				break;
			case 5:
				if ((*j)->Get(valA::id) > (*k)->Get(valA::id))
				{
					std::swap(*j, *k); Sort = true;
				}
				break;
			default:
				std::cout << "!!!  Eror  !!!" << std::endl;
				break;
			}
		}
		j = i->begin();
		k = (++i->begin());
	}
}

void MyMenu::EleventhMenu(MyMenu* MyMenuGrup)
{
	using std::cout, std::endl, std::cin;
	std::cin.ignore();
	std::string value;
	bool flag = true;
	//*************************************************************************************//
	if (MyMenuGrup->MyListGrup->GetSize()>1)
	{
		std::cout << "1.Сортувати всі групи" << std::endl;
		std::cout << "2.Сортувати декілька груп" << std::endl;
		std::cout << "3.Сортувати одну" << std::endl;
		std::cout << "Введіть відповіть >> "; std::getline(std::cin, value, '\n');
		if (FindCommandSkip(value))
		{
			ConsoleClear;
			std::cout << "Повертаємось в головне меню \n";
			Pause_Use;
			ConsoleClear;
			return;
		}
		//Pause_Use;
		ConsoleClear;
	}
	//Якщо груп немає
	else if(MyMenuGrup->MyListGrup->empty())
	{
		ConsoleClear;
		std::cout << "Груп нема!!" << std::endl;
		Pause_Use;
		ConsoleClear;
		return;
	}
	// Якщо є тільки одна група
	else
	{
		std::cout << "Є тільки одна група " << MyMenuGrup->MyListGrup->operator[](0)->GetNameGroop() << std::endl;
		flag = false;
	}
	//*************************************************************************************//
	Grup<std::string> nameSort;
	std::string NameSortGroop;
	int temp = 0;
	bool flag2 = false;
	//=====================================================================================//
	if (value == "2" || value == "3")
	{
		flag = false;
		cout << "Перелік груп: " << endl;
		for (auto i : MyMenuGrup->MyListGrup->begin())
		{
			cout << i->GetNameGroop() << endl;
		}
		if (value == "2")
		{
			do
			{
				cout << "[/skip для виходу][Введіть групу] \n>> "; std::getline(std::cin, value, '\n');

				if (FindCommandSkip(value))
				{
					if (!temp)
					{
						ConsoleClear;
						cout << "Не було введено групи" << endl;
						Pause_Use;
						ConsoleClear;
					}
				}

				// Перевіряю є ця група серед представлених
				for (auto j : MyMenuGrup->MyListGrup->begin())
				{
					if (j->GetNameGroop() == value)
					{
						flag2 = true;
					}
				}
				if (!nameSort.empty())
				{
					//Перевіряю ,чи не повторюється введена група
					for (auto k : nameSort)
					{
						if (k == value)
						{
							flag2 = false;
						}
					}
				}
				else
				{
					nameSort.push_front(value);
					temp++;
				}
				if (flag2)
				{
					nameSort.push_front(value);
					temp++;
				}
				else
				{
					cout << value << " така група вже добавлена або її немає серед представлених\n";
				}
				flag2 = false;

			} while (nameSort.GetSize()>= MyMenuGrup->MyListGrup->GetSize());
		}
		else
		{
			do
			{
				cout << "[Введіть групу] >> "; std::getline(std::cin, NameSortGroop, '\n');

				// Перевіряю є ця група серед представлених
				for (auto j : MyMenuGrup->MyListGrup->begin())
				{
					if (j->GetNameGroop() == NameSortGroop)
					{
						flag2 = true;
					}
				}
				
				if (flag2)
				{
					break;

				}
				else
				{
					cout << NameSortGroop << " такої групи немає \n";
					flag2 = false;
				}

			} while (!flag2);
		}
	}
	else
	{
		flag = true;
	}
	//=====================================================================================//

	ConsoleClear;
	std::cout << "Сортувати студентів в групі за :" << std::endl;
	std::cout << "1.Сортувати за прізвищем" << std::endl;
	std::cout << "2.Сортувати за ім'ям" << std::endl;
	std::cout << "3.Сортувати за по батькові" << std::endl;
	std::cout << "4.Сортувати за рейтингом" << std::endl;
	std::cout << "5.Сортувати за Id" << std::endl;
	if (flag)
	{
		std::cout << "6.Сортувати всі групи за назвою" << std::endl;
	}
	cout << "[/skip][Введіть групу] \n>> "; std::getline(std::cin, value, '\n');
	if (FindCommandSkip(value))
	{
		ConsoleClear;
		cout << "Повертаємось на головне меню без сортування" << endl;
		Pause_Use;
		ConsoleClear;
	}
	temp = atoi(value.c_str());
	if (temp<1 || temp>6)
	{
		ConsoleClear;
		cout << "Повертаємось на головне меню без сортування, бо введено не те значення" << endl;
		Pause_Use;
		ConsoleClear;
	}
	
	if (flag)
	{
		auto j = MyMenuGrup->MyListGrup->begin();
		auto k = ++MyMenuGrup->MyListGrup->begin();
		bool Sortt = true;
		switch (temp)
		{
		case 6:
			
			while (Sortt)
			{
				Sortt = false;
				for ( ;k != k.end(); ++j, ++k)
				{
					if ((*j)->GetNameGroop() > (*k)->GetNameGroop())
					{
						std::swap(*j, *k); Sortt = true;
					}
				}
				j = MyMenuGrup->MyListGrup->begin();
				k = ++MyMenuGrup->MyListGrup->begin();
			}
			break;
		default:
			for (auto it : MyMenuGrup->MyListGrup->begin())
			{
				SortGrup(it, temp);
			}
			break;
		}
	
	}
	else if (!nameSort.empty())
	{
		auto j = nameSort.begin();
		for (auto i = MyMenuGrup->MyListGrup->begin(); i!= i.end();++i)
		{
			if ((*j)==(*i)->GetNameGroop())
			{
				SortGrup(*i, temp);
				++j; i = MyMenuGrup->MyListGrup->begin();
			}
		}
	}
	else if (!NameSortGroop.empty())
	{
		for (auto &i : MyMenuGrup->MyListGrup->begin())
		{
			if (NameSortGroop ==i->GetNameGroop() )
			{
				SortGrup(i, temp);
				break;
			}
		}
	}
	else
	{
		cout << "eror !!!" << endl;
		Pause_Use;
		ConsoleClear;
	}
	ConsoleClear;
	cout << "Сортування успішне !!!" << endl;
	Pause_Use;
	ConsoleClear;
}