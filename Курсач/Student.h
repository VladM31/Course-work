#pragma once
#include "ThePersonWhoLearns.h"
typedef std::string sg;
enum class valS {
   kur, id, rat
};
class Student : public ThePersonWhoLearns {
protected:

    size_t vKurs;//Курс
public:
    // По умолчанию
    Student();
    // С параметрами
    Student(sg Lastname, sg Name, sg Patronymic, size_t Kurs);
    // Копирования
    Student(const Student& Second);
    //Get
    size_t Get(valS chose);
    // Set
    // Устанавливаю данные строк
    virtual void Set(namA chose,sg SetValue) override;
    // Устанавливаю данные чисел
    virtual void Set(valS chose, size_t SetValue);

    void SetConsole() override;
    // Metod
    // Перевожу все данные полей класса в строку
    virtual sg toString()override;
    // Считываю данные с файла 
    bool toScanFile(std::fstream& file)override;
    // Закидиваю данные в файл
    bool toPutFile(std::fstream& file)override;
    // Operator
    Student& operator =(const Student& student);
    // Увеличиваю курс на 1
    Student& operator ++();
    // Уменьшаю курс на 1
    Student& operator++(int);
    // Увеличиваю рейтинг на 1
    Student& operator--();
    // Уменьшаю  рейтинг на 1
    Student& operator--(int);

    friend std::ostream& operator << (std::ostream& out, Student& d);
    friend std::istream& operator >> (std::istream& in, Student& d);
    virtual ~Student();
};

// ==================================================
