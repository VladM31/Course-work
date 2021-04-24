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
		// ������ ���������� � ��������� ����� 
		std::cout << (*glist)[j]->toString() << std::endl << std::endl;
	}
	std::cout << std::endl;
}

Grup<Student*>* FillGrup(Grup<std::string>* NameFile, size_t index)
{

	Grup<Student*>* TempGrupS = new Grup<Student*>;
	std::string temp;
	std::fstream OpenFile;//������ object ��� �������� ������
	OpenFile.open((*NameFile)[index].c_str(), std::ios::in);// �������� ���� �����
	// ������ �� �������� ����� .txt
	for (size_t i = 0; i < 4; i++)
	{
		(*NameFile)[index].pop_back();
	}
	// ������� ����� ����������� ��� ���
	std::cout << "����� " << (*NameFile)[index] << " ����������?" << std::endl
		<< "������ true or false : "; std::cin >> temp;
	for (size_t j = 0; !OpenFile.eof(); j++)
	{
		if (!OpenFile.is_open())
		{
			break;
		}
		// ����������
		if (temp == "true")
			TempGrupS->push_back(new GraduateSD);
		// ������ �������� 
		else
			TempGrupS->push_back(new Student);
		// �������� ���� ������ �� ����� 
		(*TempGrupS)[j]->toScanFile(OpenFile);
		// ���� ����� ����� �� ������� ������ ������ �����
		if (OpenFile.eof()) {
			TempGrupS->pop_back();
		}

	}
	
	OpenFile.close();// �������� ���� 
	ConsoleClear;// ������� ������� 
	return TempGrupS;
}

int MainMenu()
{
	int ChoseUser = 0;
	std::cout << " 1.�������� �����;" << std::endl;
	std::cout << " 2.�������� �����;" << std::endl;
	std::cout << " 3.�������� �����;" << std::endl;
	std::cout << " 4.�������� � ���� ����������;" << std::endl;
	std::cout << " 5.������ ����������;\n";
	std::cout << " 6.������� ��������;\n";
	std::cout << " 7.�������� ��������;\n";
	std::cout << " 8.�������� ��������;\n";
	std::cout << " 9.�������� ����� ����;\n";
	std::cout << " ������ �������: "; std::cin >> ChoseUser;
	ConsoleClear;
	return ChoseUser;
}

bool EndMenuProgram()
{
	int Back;
	HANDLE Color_END = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout << "��������� � ������� ����?" << std::endl;
	SetConsoleTextAttribute(Color_END, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	std::cout << "��������� 1 , ��� ��������� � ������� ����" << std::endl;
	SetConsoleTextAttribute(Color_END, FOREGROUND_INTENSITY | FOREGROUND_RED);
	std::cout << "��������� 2 , ��� ��������� ��������" << std::endl;
	SetConsoleTextAttribute(Color_END,FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
	std::cout << "������ ������� >> "; std::cin >> Back;
	ConsoleClear;
	return Back-2;
}

Grup<std::string>* FirstMenu(size_t SizeGrup)
{
	using std::cout;
	using std::string;
	string AnswerGrup;
	int AnswerChoose;
	Grup<std::string>* TempGrupS = new Grup<std::string>;
	cout << " 1.������� �� �����;\n";
	cout << " 2.������� ������� ����;\n";
	cout << " 3.������� ���� �����;\n";
	cout << " ������ ���� ������� >> "; std::cin >> AnswerChoose; std::cin.ignore();
	ConsoleClear;
	if (AnswerChoose == 2)
	{
		for (size_t i = 0; i < SizeGrup; i++)
		{
			cout << "������ /skip , ��� �������� �������� ����\n";
			cout << "������ ����� >> "; std::getline(std::cin, AnswerGrup, '\n');
			ConsoleClear;
			if (AnswerGrup.find("/skip")+1)
				return (TempGrupS->GetSize())?TempGrupS:nullptr;
			else
				TempGrupS->push_back(AnswerGrup);
		}
		return TempGrupS;
	}
	else if (AnswerChoose == 3)
	{
		cout << "������ ����� >> "; std::getline(std::cin, AnswerGrup, '\n');
		ConsoleClear;
		TempGrupS->push_back(AnswerGrup);
		return TempGrupS;
	}
	else
		return nullptr;
}

void FirstMenuPrint(Grup<std::string>* FindName, Grup<std::string>* AllName, Grup<Grup<Student*>*> &GrupStudent)
{
	Grup<std::string>::iterator_g<std::string> AllNameIter(*AllName);
	Grup<Grup<Student*>*>::iterator_g<Grup<Student*>*> GroupList(GrupStudent);
	if (!FindName)//FindName == nullptr
	{
		for (auto i : GroupList)
		{
			std::cout << *AllNameIter << std::endl;
			PrintGrupStudent(i);
			++AllNameIter;
		}
		return;
	}
	Grup<std::string>::iterator_g<std::string> FindNameIter(*FindName);
	
	for (auto i: AllNameIter)
	{
		for (auto j: FindNameIter)
		{
			if (i==j)
			{
				std::cout << i << std::endl;
				PrintGrupStudent(*GroupList);
				continue;
			}
		}
		++GroupList;
	}
	delete FindName;
}


