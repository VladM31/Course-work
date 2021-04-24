#include "MyFunk.h"

Grup<std::string> FindFileGrup()
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

void PrintGrupStudent(Grup<Student*>* glist)
{
	for (size_t j = 0; j < glist->GetSize(); j++)
	{
		// Вивожу информацию о студентах групи 
		std::cout << (*glist)[j]->toString() << std::endl << std::endl;
	}
	std::cout << std::endl;
}

Grup<Student*>* FillGrup(Grup<std::string>* NameFile, size_t index)
{

	Grup<Student*>* TempGrupS = new Grup<Student*>;
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
		// Дипломники
		if (temp == "true")
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
		system("cls");// Очистка консоли 
		return TempGrupS;
}

int MainMenu()
{
	int ChoseUser = 0;
	std::cout << " 1.Ввивести всі групи;" << std::endl;
	std::cout << " 2.Створити групу;" << std::endl;
	std::cout << " 3.Видалити групу;" << std::endl;
	std::cout << " 4.Зберегти в файл інформацію;" << std::endl;
	std::cout << " 5.Змінити інформацію;";
	std::cout << " Введіть відповідь: "; std::cin >> ChoseUser;
	Pause_Use;
	return ChoseUser;
}


