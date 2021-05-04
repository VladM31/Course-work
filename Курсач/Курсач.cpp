#include "MyFunk.h"

using namespace std;
 

int main() {
    Ukr;
    // Variables to use
    string temp;
    bool WorkСycle = true;
    auto ConsoleOperation = new MyMenu(new Grup<Grup<ThePersonWhoLearns*>*>, new Grup<string>(MyMenu::FindFileGrup()));
    //*****************************



    // =======================================================
    while (WorkСycle)
    {
        switch (ConsoleOperation->MainMenu())
        {
        case 1:
            FirstMenuPrint(FirstMenu(ConsoleOperation->GetNameGrup()->GetSize()), ConsoleOperation);
            Pause_Use;
            ConsoleClear;
            break;
        case 2:
            SecondMenu(ConsoleOperation);
            break;
        case 3:
            MyMenu::TheThirdMenu(ConsoleOperation);
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        default:
            WorkСycle = EndMenuProgram();
            break;
        }
    }

    Pause_Use; 
    // Очищаю динамическую память 
    delete ConsoleOperation;

}
