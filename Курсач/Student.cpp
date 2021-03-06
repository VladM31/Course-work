#include "Student.h"
// ??????????? ?? ?????????
Student::Student() :  vKurs(1), ThePersonWhoLearns() {}

// ??????????? ? ??????????? 
Student::Student(sg Lastname, sg Name, sg Patronymic, size_t Kurs) :  vKurs(1),ThePersonWhoLearns(Lastname, Name, Patronymic)
{
    this->Set(valS::kur, Kurs);
}

Student::Student(const Student& other) :  vKurs(other.vKurs),ThePersonWhoLearns(other) {}

// Student ---------------------------------------------- Student


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

void Student::Set(namA chose, sg SetValue)
{
    if (chose == namA::Name)
    {
       this->vName = SetValue;
    }
    else if (chose == namA::Last)
    {
        this->vLastname = SetValue;
    }
    else if (chose == namA::Patr)
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
            std::cout << "??????? ?? ???????? ????????" << std::endl;
            return;
        }
        else
        {
            this->vRating = SetValue;
        }
        
    }
    else
    {
        throw std::exception("<Metod Set>: Empty");
    }
}

void Student::SetConsole()
{
    ThePersonWhoLearns::SetConsole();
    std::string tempBuf;
    std::cout << "[/++][/--]??????? >> "; std::cin >> tempBuf;
    
    if (FindCommandSkip(tempBuf, "/++"))
    {
        --(*this);
    }
    else if (FindCommandSkip(tempBuf, "/--"))
    {
        (*this)--;
    }
    else if (!FindCommandSkip(tempBuf))
    {
        this->Set(valS::rat, static_cast<size_t>(atoi(tempBuf.c_str())));
    }
    std::cout << "[/++][/--]???? >> "; std::cin >> tempBuf;
    
    if (FindCommandSkip(tempBuf,"/++"))
    {
        ++(*this);
    }
    else if (FindCommandSkip(tempBuf, "/--"))
    {
        (*this)++;
    }
    else if (!FindCommandSkip(tempBuf))
     {
         this->Set(valS::kur, static_cast<size_t>(atoi(tempBuf.c_str())));
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

bool Student::toScanFile(std::fstream& file){
    int fail = 0;
    try{
        char ch;
        if (file.eof()) {
            throw std::fstream::failure("??????? ??? ??????????");
        }
        std::getline(file, vLastname, ',');
        std::getline(file, vName, ',');
        std::getline(file, vPatronymic, ',');
        file >> vKurs >> ch;
        this->Set(valS::kur, vKurs);
        if (file.eof()) {
            throw std::fstream::failure("??????? ??? ??????????");
        }
        file >> vId >> ch;
        file >> vRating >> ch;
        this->Set(valS::rat, vRating);
        do{
            file.get(ch);
           ++fail;
        } while (ch!=';' && fail<200);
        file.get(ch);
        return true;
    }
    catch (const std::fstream::failure & cat) {
        std::cout << cat.code() << std::endl;
        std::cout << cat.what() << std::endl;
        vLastname = cat.what();
        vName = cat.what();
        vPatronymic = cat.what();
        vKurs = ++IdGlobal;
        this->Set(valS::kur, vKurs);
        vId = IdGlobal;
        vRating = IdGlobal;
        this->Set(valS::rat, vRating);
        system("pause");
        return false;}
}

bool Student::toPutFile(std::fstream& file)
{
    try
    {
        if (!file.is_open())
        {
            throw std::exception("???? ?? ?????????, ????????? ????!");
        }
        file << vLastname << "," 
             << vName << ","
             << vPatronymic << "," 
             << vKurs << ","
             << vId << "," 
             << vRating << ";\n";
        return true;
    }
    catch (const std::exception& cat)
    {
        std::cout << cat.what() << std::endl;
        system("pause");
        return false;
    }
}

Student& Student::operator=(const Student& student)
{
    if (this==&student)
    {
        return *this;
    }
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
        std::cout << "???? ??? ??????????? ???????, ????? ?? ????" << std::endl;
        return *this;
    }
    ++this->vKurs;
    return *this;
}

Student& Student::operator++(int)
{
    if (this->vKurs == 1)
    {
        std::cout << "???? ??? ?????????? ???????, ????? ?? ????" << std::endl;
        return *this;
    }
    --this->vKurs;
    return *this;
}

Student& Student::operator--()
{
    if (vRating==100)
    {
        std::cout << "??????? ??? ??????????? ???????, ????? ?? ????" << std::endl;
        return *this;
    }
    ++this->vRating;
    return *this;
}

Student& Student::operator--(int)
{
    if (vRating == 1)
    {
        std::cout << "??????? ??? ?????????? ???????, ????? ?? ????" << std::endl;
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
    std::cout << "Kurs      :\t"; std::cin >> d.vKurs; std::cin.ignore();
    d.Set(valS::kur, d.vKurs);
    std::cout << "Lastname  :\t"; std::getline(in, d.vLastname, '\n');
    std::cout << "Name      :\t"; std::getline(in, d.vName, '\n');
    std::cout << "Patronymic:\t"; std::getline(in, d.vPatronymic, '\n');
    std::cout << "Id        :\t"; std::cin >> d.vId;
    std::cout << "Rating    :\t"; std::cin >> d.vRating;
    d.Set(valS::rat, d.vRating);
    d.Set(valS::kur, d.vKurs);
    return in;
}
