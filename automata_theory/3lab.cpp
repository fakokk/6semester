#include <iostream>
#include <string>
using namespace std;

//анализатор
bool analiz(string input) 
{
    //состояния автомата
    enum State { ENTRY, ZERO, ONE, ENDL, EXIT };

    //количество единиц
    int oneNumber = 0;
    //счетчик
    int count = 0;

    //результат равен 1
    bool result = true;

    //текущее состояние
    State state = ENTRY;

    //до тех пор пока состояние не равно выходу
    while (state != EXIT) 
    {
        switch (state) 
        {
        //начальное состояние
        case ENTRY:
            //если вышли за пределы строки
            if (count >= input.length()) 
            {
                //конец работы автомата
                state = ENDL;
            }
            //если обозреваем ноль
            else if (input[count] == '0') 
            {
                //состояние 0
                state = ZERO;
                count++;
            }
            //если обозреваем 1
            else if (input[count] == '1') 
            {
                //состояние 1
                state = ONE;
                oneNumber++;
                count++;
            }
            //иначе выход
            else 
            {
                result = false;
                state = EXIT;
            }
            break;
        case ZERO:
            //если вышли за пределы строки
            if (count >= input.length()) 
            {
                state = ENDL;
            }
            //если обозреваем 0
            else if (input[count] == '0') 
            {
                //состояние 0
                state = ZERO;
                count++;
            }
            //если обозреваем 1
            else if (input[count] == '1') 
            {
                //состояние 1
                state = ONE;
                //кол-во единиц ++
                oneNumber++;
                count++;
            }
            //иначе выход
            else 
            {
                result = false;
                state = EXIT;
            }
            break;
        case ONE:
            //если вышли за пределы строки
            if (count >= input.length()) 
            {
                state = ENDL;
            }
            //если обозреваем 0
            else if (input[count] == '0') 
            {
                //состояние 0
                state = ZERO;
                count++;
            }
            //иначе выход
            else 
            {
                result = false;
                state = EXIT;
            }
            break;
        case ENDL:
            //если количество единиц не четное
            if (oneNumber % 2 == 1) 
            {
                result = false;
            }
            state = EXIT;
            break;
        }
    }
    return result;
}

int main() 
{
    string input;

    cout << "Input string";

    cin >> input;

    //если анализатор ок то true 
    //если не ок то false
    if (analiz(input) == true)
        cout << "OK\n";
    else
        cout << "NOT OK\n";
    return 0;
}