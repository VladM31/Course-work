#include "MyFunk.h"




Grup<ThePersonWhoLearns*>* MyMenu::FillGrup(Grup<std::string>* NameFile, size_t index, int &ChooseUser)
{

	Grup<ThePersonWhoLearns*>* TempGrupS = new Grup<ThePersonWhoLearns*>;
	std::string temp;
	std::fstream OpenFile;//������ object ��� �������� ������
	OpenFile.open((*NameFile)[index].c_str(), std::ios::in);// �������� ���� �����
	// ������ �� �������� ����� .txt
	for (size_t i = 0; i < 4; i++)
	{
		(*NameFile)[index].pop_back();
	}
	if (ChooseUser)
	{
		for (size_t j = 0; !OpenFile.eof(); j++)
		{
			if (!OpenFile.is_open())
			{
				break;
			}
			// ����������
			if (ChooseUser==1)
				TempGrupS->push_back(new GraduateSD);
			// ������ �������� 
			else if (ChooseUser==2)
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
	// ������� ����� ����������� ��� ���
	std::cout << "����� " << (*NameFile)[index] << " ����������?" << std::endl
		<< "������ true or false : "; std::cin >> temp;
	if (FindCommandSkip(temp,"/all(1)"))
	{
		ChooseUser = 1;
	}
	if (FindCommandSkip(temp, "/all(0)"))
	{
		ChooseUser = 2;
	}
	for (size_t j = 0; !OpenFile.eof(); j++)
	{
		if (!OpenFile.is_open())
		{
			break;
		}
		// ����������
		if (temp == "true" || temp == "1")
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

bool MyMenu::EndMenuProgram()
{
	int Back;
	HANDLE Color_END = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout << "��������� � ������� ����?" << std::endl;
	SetConsoleTextAttribute(Color_END, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	std::cout << "�������� 1 , ��� ��������� � ������� ����" << std::endl;
	SetConsoleTextAttribute(Color_END, FOREGROUND_INTENSITY | FOREGROUND_RED);
	std::cout << "�������� 2 , ��� ��������� ��������" << std::endl;
	SetConsoleTextAttribute(Color_END,FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
	std::cout << "������ ������� >> "; std::cin >> Back;
	ConsoleClear;
	return Back-2;
}


Grup<std::string>* MyMenu::FirstMenu(size_t SizeGrup)
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
			if (FindCommandSkip(AnswerGrup))
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

void  MyMenu::FirstMenuPrint(Grup<std::string>* FindName, MyMenu* MyMenuGrup)
{
	if (!MyMenuGrup->GetNameGrup()->GetSize())// == 0
	{
		std::cout << "���� ���� !!" << std::endl;
		Pause_Use;
		delete FindName;
		ConsoleClear;
	}
	auto AllNameIter = MyMenuGrup->GetNameGrup()->begin();
	auto GroupList= MyMenuGrup->GetListGrup()->begin();
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

void MyMenu::SecondMenu(MyMenu* MyMenuGrup)
{
	using std::cout;
	int SizeNewGrup;
	cout << "������ ������� ����� ���� >> "; std::cin >> SizeNewGrup; std::cin.ignore();
	ConsoleClear;
	if (SizeNewGrup < 1 || SizeNewGrup>25)
	{
		return;
	}
	std::string temp;
	while (SizeNewGrup)
	{
		cout << "������ /skip , ��� �������� ��������\n";
		cout << "������ ����� ����� >> "; std::getline(std::cin, temp, '\n');
		ConsoleClear;
		if (FindCommandSkip(temp))// �������� �� ����
		{
			return;
		}
		
		MyMenuGrup->GetListGrup()->push_back(new Grup<ThePersonWhoLearns*>);// �������� ����� �����
		MyMenuGrup->GetNameGrup()->push_back(temp);// �������� �������� ����� �����
		--SizeNewGrup;
	}

}

Grup<std::string> MyMenu::FindFileGrup(const char * nameFile)
// ��������� ���� �� ������� ������ ����
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
	using std::cout, std::endl, std::cin;
	size_t indexRemove = 0, numberGrupDelete;
	std::string InPutUser;
	cout << "������ ������� ���� ��� ��������� "; cin >> InPutUser; cin.ignore();
	ConsoleClear;
	if (!MyMenuGrup->MyListGrup->GetSize(/* == 0*/) | FindCommandSkip(InPutUser) |
		((numberGrupDelete = atoi(InPutUser.c_str())) > MyMenuGrup->MyListGrup->GetSize() || !numberGrupDelete/* == 0*/))
	{
		return;
	}

	while (numberGrupDelete)
	{
		cout << "������ ����: " << endl;
		for (auto i : MyMenuGrup->MyNameGrup->begin())
		{
			cout << i << endl;
		}
		cout << "������ ����� ��� ��������� >> ";
		std::getline(cin, InPutUser);
		if (FindCommandSkip(InPutUser))
		{
			return;
		}
		for (auto i : MyMenuGrup->MyNameGrup->begin())
		{
			if (i == InPutUser)
			{
				MyMenuGrup->MyListGrup->removeAt(indexRemove);
				MyMenuGrup->MyNameGrup->removeAt(indexRemove);
				indexRemove = 0;
				break;
			}
			++indexRemove;
		}
		ConsoleClear;
		if (!MyMenuGrup->MyNameGrup->GetSize()/* == 0*/)
		{
			cout << "������ ���� ����!!!!" << endl;
			Pause_Use;
			ConsoleClear;
			break;
		}
		else if (indexRemove == MyMenuGrup->MyNameGrup->GetSize())
		{
			cout << "����� " << InPutUser << " �� ��������!!!!" << endl;
			++numberGrupDelete;
		}
		else
		{
			cout << "����� " << InPutUser << " ��������!" << endl;
		}
		Pause_Use;
		ConsoleClear;
		--numberGrupDelete;
	}



}

void MyMenu::PrintGrupStudent(Grup<ThePersonWhoLearns*>* glist)
///������� �� ������� ����� ����� 
{
	for (size_t j = 0; j < glist->GetSize(); j++)
	{
		// ������ ���������� � ��������� ����� 
		std::cout << (*glist)[j]->toString() << std::endl << std::endl;
	}
	std::cout << std::endl;
}

int MyMenu::MainMenu()
{
	std::string CheckChoose;
	std::cout << " 1.�������� �����;" << std::endl;
	std::cout << " 2.�������� �����;" << std::endl;
	std::cout << " 3.�������� �����;" << std::endl;
	std::cout << " 4.�������� � ���� ����������;" << std::endl;
	std::cout << " 5.������ ����������;\n";
	std::cout << " 6.������� ��������;\n";
	std::cout << " 7.�������� ��������;\n";
	std::cout << " 8.�������� ��������;\n";
	std::cout << " 9.�������� ����� ����;\n";
	std::cout << " ������ �������: "; std::cin >> CheckChoose;
	ConsoleClear;
	if (FindCommandSkip(CheckChoose))
	{
		return this->ChooseUser;
	}
	else if (FindCommandSkip(CheckChoose,"/end"))
	{
		return this->ChooseUser=11;
	}
	this->ChooseUser = atoi(CheckChoose.c_str());
	return this->ChooseUser;
}




MyMenu::MyMenu(Grup<Grup<ThePersonWhoLearns*>*>* SetMyListGrup, Grup<std::string>* SetMyNameGrup) : ChooseUser(0), MyNameGrup(SetMyNameGrup),MyListGrup(SetMyListGrup)
{
	for (size_t i = 0; i < MyNameGrup->GetSize(); i++)
	{
		MyListGrup->push_back(FillGrup(MyNameGrup, i,this->ChooseUser));// ������ ����� ��������� 
	}
}

Grup<std::string>* MyMenu::GetNameGrup()
{
	return this->MyNameGrup;
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
	delete MyNameGrup, MyListGrup;
}


void MyMenu::SaveFile(MyMenu* MyMenuGrup)
{
	if (!MyMenuGrup->MyListGrup->GetSize())
	{
		std::cout << "���� , �� �������" << std::endl;
		Pause_Use;
		ConsoleClear;
		return;
	}
	std::cout << "����� ���� " << std::endl;
	for (auto NameGrup: MyMenuGrup->MyNameGrup->begin())
	{
		std::cout << NameGrup << std::endl;
	}
	std::cout << "������ ����� ���� ��� ����������!" << std::endl;
	/// 
	Grup<std::string> NameFileSave;
	std::string temp;
	bool allSave = false;
	auto NameGrupCkl = MyMenuGrup->MyNameGrup->begin();
	std::fstream FilePut;
	/// 
	while (NameFileSave.GetSize()!= MyMenuGrup->MyNameGrup->GetSize())
	{
		std::cin >> temp;
		if (FindCommandSkip(temp))
		{
			break;
		}
		if (FindCommandSkip(temp,"/all"))
		{
			allSave = true;
			break;
		}
		for (auto NameGrup : MyMenuGrup->MyNameGrup->begin())
		{
			if (temp == NameGrup)
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
			temp = *NameGrupCkl + "_Save.txt";
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
			if ((*NameGrupCkl) == (findName))
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
	if (!MyMenuGrup->MyListGrup->GetSize())
	{
		std::cout << "���� , �� ������!" << std::endl;
		Pause_Use;
		ConsoleClear;
		return;
	}
	while (true)
	{
		std::cout << "����� ���� " << std::endl;
		for (auto NameGrup : MyMenuGrup->MyNameGrup->begin())
		{
			std::cout << NameGrup << std::endl;
		}
		std::cout << "������ ����� >> "; std::cin >> tempUse;
		if (FindCommandSkip(tempUse))
		{
			return;
		}
		for (auto i: MyMenuGrup->MyNameGrup->begin())
		{
			if (tempUse==i)
			{
				Exit = true;
				break;
			}
			++indexs;
		}
		ConsoleClear;
		if (Exit)
		{
			break;
		}
		else
		{
			std::cout << "����� " << tempUse << " �� �������� !!!" << std::endl;
			indexs = 0;
			Pause_Use;
			ConsoleClear;
		}
	}
	using std::cout, std::endl,std::cin;
	while (true)
	{
		cout << "������� �������� (������ �����)" << endl;
		for (auto i : MyMenuGrup->MyListGrup->operator[](indexs)->begin())
		{
			cout << number++ <<")"<< i->Get(namA::Last) << " " << i->Get(namA::Name).at(0) << "." << i->Get(namA::Patr).at(0) << ".\n";
		}
		cout << "������ ���� >> "; std::cin >> tempUse;
		if (FindCommandSkip(tempUse))
		{
			return;
		}
		number = static_cast<size_t>(atoi(tempUse.c_str()));
		if (number<1 || number>MyMenuGrup->MyListGrup->operator[](indexs)->GetSize())
		{
			cout << "�� �� �����!!!������ ����" << endl;
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
		cout << "1.������ �������" << endl;
		cout << "2.������ Id" << endl;
		cout << "3.������ �������" << endl;
		cout << "4.������ ��'�" << endl;
		cout << "5.������ �� �������" << endl;
		cout << "6.������ ��� ����" << endl;
		cout << "Imput chose >> "; std::cin >> tempUse; std::cin.ignore();
		ConsoleClear;
		if (FindCommandSkip(tempUse))
		{
			return;
		}
		switch (atoi(tempUse.c_str()))
		{
		case 1:
			cout << "������ ������" << endl;
			std::getline(cin, tempUse, '\n');
			if (FindCommandSkip(tempUse))
			{
				return;
			}
			ChangesInTheStudent->Set(valA::rat, atoi(tempUse.c_str()));
			break;
		case 2:
			cout << "������ Id" << endl;
			std::getline(cin, tempUse, '\n');
			if (FindCommandSkip(tempUse))
			{
				return;
			}
			ChangesInTheStudent->Set(valA::id, atoi(tempUse.c_str()));
			break;
		case 3:
			cout << "������ �������" << endl;
			std::getline(cin, tempUse, '\n');
			if (FindCommandSkip(tempUse))
			{
				return;
			}
			ChangesInTheStudent->Set(namA::Last, tempUse);
			break;
		case 4:
			cout << "������ ��'�" << endl;
			std::getline(cin, tempUse, '\n');
			if (FindCommandSkip(tempUse))
			{
				return;
			}
			ChangesInTheStudent->Set(namA::Name, tempUse);
			break;
		case 5:
			cout << "������ �� �������" << endl;
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
