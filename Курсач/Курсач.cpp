#include "MyFunk.h"
#include <typeinfo>
using namespace std;
 

int main() {

    Ukr;
    // Variables to use
    string temp;
    bool WorkСycle = true;
    auto ConsoleOperation = new MyMenu(new Grup<Grup<ThePersonWhoLearns*>*>, new Grup<string>(MyMenu::FindFileGrup()));
    // =======================================================
  

    // =======================================================
    while (WorkСycle)
    {
        switch (ConsoleOperation->MainMenu())
        {
        case 1:
            MyMenu::FirstMenuPrint(MyMenu::FirstMenu(ConsoleOperation), ConsoleOperation);
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
            MyMenu::TheSixthMenu(ConsoleOperation);
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            MyMenu::NinthItem(ConsoleOperation);
            break;
        case 10:
            MyMenu::TenthMenu(ConsoleOperation);
            break;
        case 11:
            MyMenu::EleventhMenu(ConsoleOperation);
            break;
        default:

            WorkСycle = MyMenu::EndMenuProgram();
            break;
        }
    }

    // Очищаю динамическую память 
    delete ConsoleOperation;

}
