#include "Student.h"
// Конструктор по умолчанию
Student::Student() :  vKurs(1), ThePersonWhoLearns() {}

// Конструктор с параметрами 
Student::Student(sg Lastname, sg Name, sg Patronymic, size_t Kurs) :  vKurs(1),ThePersonWhoLearns(Lastname, Name, Patronymic)
{
    this->Set(valS::kur, Kurs);
}

Student::Student(Student& other) :  vKurs(other.vKurs),ThePersonWhoLearns(other) {}

// Student ---------------------------------------------- Student
sg Student::Get(namS chose)
{
    if (chose== namS::Name)
    {
        return this->vName;
    }
    else if (chose == namS::Last)
    {
        return this->vLastname;
    }
    else if (chose == namS::Patr)
    {
        return this->vPatronymic;
    }
    else
    {
        return "<Metod Get>: Empty";
    }
}

size_t Student::Get(valS chose)
{
    if (chose == valS::id)
    {
        return this->vId;
    }
    else if (chose == valS::kur)
    {
        return this->vKurs;
    }
    else if (chose == valS::rat)
    {
        return this->vRating;
    }
    else
    {
       throw std::exception( "<Metod Get>: Empty");
       return 0;
    }
}

void Student::Set(namS chose, sg SetValue)
{
    if (chose == namS::Name)
    {
       this->vName = SetValue;
    }
    else if (chose == namS::Last)
    {
        this->vLastname = SetValue;
    }
    else if (chose == namS::Patr)
    {
        this->vPatronymic = SetValue;
    }
    else
    {
        throw  std::exception("<Metod Set>: Empty");
        return;
    }
}

void Student::Set(valS chose, size_t SetValue)
{
    if (chose == valS::id)
    {
        this->vId = SetValue;
    }
    else if (chose == valS::kur)
    {
        if (SetValue < 1)
            this->vKurs = 1;
        else if (SetValue > 5)
            this->vKurs = 5;
        else
            this->vKurs = SetValue;
    }
    else if (chose == valS::rat)
    {
        if (SetValue >100)
        {
            this->vRating = 100;
            return;
        }
        this->vRating = SetValue;
    }
    else
    {
        throw std::exception("<Metod Set>: Empty");
    }
}

sg Student::toString()
{
    return sg("Lastname: ") + vLastname + '\n'
        + "Name: " + vName + '\n'
        + "Patronymic: " + vPatronymic + '\n'
        + "Kurs: " + std::to_string(vKurs) + '\n'
        + "Id: " + std::to_string(vId) + '\n'
        + "Rating: " + std::to_string(vRating);
}

bool Student::toScanFile(std::fstream& file)
{
    int fail = 0;
    try
    {
        char ch;
        std::getline(file, vLastname, ' ');
        if (file.eof())
        {
            return false;
        }
        std::getline(file, vLastname, ',');
        std::getline(file, vName, ',');
        std::getline(file, vPatronymic, ',');
        file >> vKurs >> ch;
        this->Set(valS::kur, vKurs);
        file >> vId >> ch;
        file >> vRating >> ch;
        this->Set(valS::rat, vRating);
        do
        {
            file.get(ch);
           ++fail;
        } while (ch!=';' && fail<200);
        file.get(ch);
        return true;
    }
    catch (const std::fstream::failure & cat)
    {
        std::cout << cat.code() << std::endl;
        vLastname = cat.what();
        vName = cat.what();
        vPatronymic = cat.what();
        vKurs = ++IdGlobal;
        this->Set(valS::kur, vKurs);
        vId = IdGlobal;
        vRating = IdGlobal;
        this->Set(valS::rat, vRating);
        return false;
    }
   
}

bool Student::toPutFile(std::fstream& file)
{
    try
    {
        file <<"Student: "<< vLastname << "," << vName << ","
              << vPatronymic << "," << vKurs << ","
              << vId << "," << vRating << ";\n";
        return true;
    }
    catch (const std::exception& cat)
    {
        std::cout << cat.what() << std::endl;
        return false;
    }
}

Student& Student::operator=(const Student& student)
{
    this->vLastname = student.vLastname;
    this->vName = student.vName;
    this->vPatronymic = student.vPatronymic;
    this->vKurs = student.vKurs;
    this->vId = student.vId;
    this->vRating = student.vRating;
    return *this;
}

Student& Student::operator++()
{
    if (this->vKurs == 5)
    {
        return *this;
    }
    ++this->vKurs;
    return *this;
}

Student& Student::operator++(int)
{
    if (this->vKurs == 1)
    {
        return *this;
    }
    --this->vKurs;
    return *this;
}

Student& Student::operator--()
{
    if (vRating==100)
    {
        return *this;
    }
    ++this->vRating;
    return *this;
}

Student& Student::operator--(int)
{
    if (vRating == 1)
    {
        return *this;
    }
    --this->vRating;
    return *this;
}
Student::~Student(){}

std::ostream& operator<<(std::ostream& out, Student& d)
{
    out << "Lastname   - " << d.vLastname << "\n"
        << "Name       - " << d.vName << "\n"
        << "Patronymic - " << d.vPatronymic << "\n"
        << "Kurs       - " << d.vKurs << "\n"
        << "Id         - " << d.vId << '\n'
        << "Rating     - " << d.vRating << std::endl;
    return out;
}

std::istream& operator>>(std::istream& in, Student& d)
{
    std::cout << "Lastname  :\t"; std::getline(in, d.vLastname, '\n');
    std::cout << "Name      :\t"; std::getline(in, d.vName, '\n');
    std::cout << "Patronymic:\t"; std::getline(in, d.vPatronymic, '\n');
    std::cout << "Kurs      :\t"; std::cin >> d.vKurs;
    std::cout << "Id        :\t"; std::cin >> d.vId;
    std::cout << "Rating    :\t"; std::cin >> d.vRating;
    return in;
}
