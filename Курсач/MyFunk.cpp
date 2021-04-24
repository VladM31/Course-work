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
		system("cls");// ������� ������� 
		return TempGrupS;
}

int MainMenu()
{
	int ChoseUser = 0;
	std::cout << " 1.�������� �� �����;" << std::endl;
	std::cout << " 2.�������� �����;" << std::endl;
	std::cout << " 3.�������� �����;" << std::endl;
	std::cout << " 4.�������� � ���� ����������;" << std::endl;
	std::cout << " 5.������ ����������;";
	std::cout << " ������ �������: "; std::cin >> ChoseUser;
	Pause_Use;
	return ChoseUser;
}


