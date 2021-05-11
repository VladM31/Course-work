#include "MyFunk.h"
#include <typeinfo>
using namespace std;
 
void Test(ThePersonWhoLearns * asd)
{
    if (atof(asd->Get(namA::any).c_str())>80)
    {
        cout << asd->Get(namA::Name) << " " << asd->Get(namA::any) <<endl;
    }
}
int main() {
    Ukr;
    // Variables to use
    string temp;
    bool WorkСycle = true;
    auto ConsoleOperation = new MyMenu(new Grup<Grup<ThePersonWhoLearns*>*>, new Grup<string>(MyMenu::FindFileGrup()));
    //*****************************
    for (auto i : ConsoleOperation->GetListGrup()->operator[](0)->begin())
    {
        if (string("class GraduateSD")== typeid(*i).name())
        {
            Test(i);
        }
    }


    // =======================================================
    while (WorkСycle)
    {
        switch (ConsoleOperation->MainMenu())
        {
        case 1:
            MyMenu::FirstMenuPrint(MyMenu::FirstMenu(ConsoleOperation->GetNameGrup()->GetSize()), ConsoleOperation);
            Pause_Use;
            ConsoleClear;
            break;
        case 2:
            MyMenu::SecondMenu(ConsoleOperation);
            break;
        case 3:
            MyMenu::TheThirdMenu(ConsoleOperation);
            break;
        case 4:
            MyMenu::SaveFile(ConsoleOperation);
            break;
        case 5:
            MyMenu::TheFifthMenu(ConsoleOperation);
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        default:

            WorkСycle = MyMenu::EndMenuProgram();
            break;
        }
    }

    // Очищаю динамическую память 
    delete ConsoleOperation;

}
