#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>

// Если в строке есть "/skip" , то вернет истину 
bool FindCommandSkip(std::string check, const char* findCommand = "/skip");
typedef std::string sg;
enum class namA
{
    Last, Name, Patr, any
};
enum class valA {
   id, rat
};
class ThePersonWhoLearns
{
protected:
    sg vLastname;//Прізвищ
    sg vName;//Іменя
    sg vPatronymic;//По батькові
    size_t vId;//Індефікаційний номер 
    size_t vRating;//Рейтинг
    static size_t IdGlobal;//Статична зммінна , щоб у об'єктів класа ,які були створені конструктором за умовчення , айді 
public:
    ThePersonWhoLearns();
    ThePersonWhoLearns(sg Lastname, sg Name, sg Patronymic);
    ThePersonWhoLearns(const ThePersonWhoLearns & Second);
    // Set 
    virtual void Set(namA chose, sg SetValue)=0;
    virtual void Set(valA chose, size_t SetValue);
    // Get
    virtual sg Get(namA chose);
    virtual size_t Get(valA chose);
    //
    virtual void SetConsole();
    virtual sg toString()=0;
    virtual bool toScanFile(std::fstream& file) = 0;
    virtual bool toPutFile(std::fstream& file)=0;
    virtual ~ThePersonWhoLearns() {}

};



