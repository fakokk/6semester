#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <list>
#include <vector>

using namespace std;

//R, L - конечные
enum State { S, D, F, A, G, H, R, J, L, M };


//char State[10] = { 'S', 'D', 'F', 'A', 'G', 'H', 'R', 'J', 'L', 'M'};
char symbol[6] = { '@', 'e', '$', 'n', 'c', '!' };

class Automate
{
    //пишем класс 
    //состояния, переходы, таблица
    //можно использовать анализатор
    //ищем с его помощью экв и недостиж состояния
public:
    State state_0; //текущее
    State state_1; //следующее
    string value;   //обозреваемый символ

    //проверка достижимости состояния
    bool StateUnreach(State state, State* Automate)
    {
        for (int i = 0; i < sizeof(Automate); i++)
        {
            if ((state == R) or (state == L))
                break;
            if (state != Automate[i] && state.state_0 == Automate[i].state_1 ||
                state == Automate[i] && state.state_0 == state.state_1)
                return false;
        }
        return true;
    }
    //удаление недостижимых состояний
    State* DeleteUnreachableStates(State* Automate)
    {
        //автомат после преобраз-й
        State* states = new State[16];
        //добавляем туда первое состояние автомата
        states[0] = Automate[0];

        //от начала до конца автомата
        for (int i = 1; i < sizeof(Automate); i++)
        {
            //если состoяние уже есть в списке гипотез
            if (ItemInsideList(states, Automate[i]))
            {
                continue;

            }
            //если состояние недостижимо
            if (StateUnreachable(Automate, Automate[i]))
                continue;

            states[i] = Automate[i];

        }

        return states;
    }

    //анализатор недостижимых состояний
    string Analizator_Unreachable(Automate aititi)
    {
        
    }

    //анализатор эквивалетных состояний
    string Analizator_Equals(string text)
    {

    }

};




class ybvhckudbbdvbjhdbvjdv
{
public: States state_0; //текущее
	    States state_1; //следующее
		string value;   //обозреваемый символ

		//
		State()
		{
			state_0 = States::S;
            state_1 = States::S;
			value = "";
		}

		//
		State(States s0, string vl, States s1)
		{
			state_0 = s0;
			value = vl;
			state_1 = s1;
		}

		//конструктор копирования
		State(const State &copyState)
		{
			state_0 = copyState.state_0;
			state_1 = copyState.state_1;
			value = copyState.value;
		}

		//возвращает 1 если состояния эквивалентны
        friend bool operator==(const State& s1, const State& s2)
		{
			return s1.value == s2.value &&
				s1.state_0 == s2.state_0 &&
				s1.state_1 == s2.state_1;
		}

		//возвращает 1 если состояния НЕ! эквивалентны
		friend bool operator != (State &s1, State &s2)
		{
			return s1.value != s2.value ||
				s1.state_0 != s2.state_0 ||
				s1.state_1 != s2.state_1;
		}
};


//для корректного отображения в консоли
inline const char* StrState(States CS)
{
	switch (CS)
	{
	//enum State States { K, S, D, F, G, A, J, H, R, M, L, E };
	case K: return "K";
    case S: return "S";
    case D: return "D";
    case F: return "F";
    case G: return "G";
    case A: return "A";
    case J: return "J";
    case H: return "H";
    case R: return "R";
    case M: return "M";
    case E: return "E";
    case L: return "L";

	default: return "[unknown type]";
	}
}


// true - state есть в гипотезах
// fasle - его там нет
bool ItemInsideList(State *statesList, State &state)
{
    for (int i = 0; i < sizeof(statesList); i++)
        if (state == statesList[i])
            return true;
    return false;
}

// true - состояние недостижимо
// fasle - состояние достижимо
bool StateUnreachable(State* Automate, State& state)
{
    for (int i = 0; i < sizeof(Automate); i++)
    {
        if (state != Automate[i] && state.state_0 == Automate[i].state_1 ||
            state == Automate[i] && state.state_0 == state.state_1)
            return false;
    }
    return true;
}


//удаление недостижимых состояний
State* DeleteUnreachableStates(State* Automate)
{
    //автомат после преобраз-й
    State* states = new State[16];
    //добавляем туда первое состояние автомата
    states[0] = Automate[0];

    //от начала до конца автомата
    for (int i = 1; i < sizeof(Automate); i++)
    {
        //если сост уже есть в списке гипотез
        if (ItemInsideList(states, Automate[i]))
        {
            continue;

        }
        //если состояние недостижимо
        if (StateUnreachable(Automate, Automate[i]))
            continue;

        states[i] = Automate[i];

    }

    return states;
}

//удаление эквивалентных состояний
State* DeleteExualStates(State *Automate)
{
    //новый массив
    State* states = new State[16];
    //добавляем туда первое состояние автомата
    states[0] = Automate[0];

    for (int i = 1; i < sizeof(Automate); i++)
    {
        //если начало или конец автомата
        if (Automate[i].state_0 == States::K && Automate[i].state_1 == States::E)
            continue;
        if (ItemInsideList(states, Automate[i]))
            continue;
        if (StateUnreachable(Automate, Automate[i]))
            continue;
        states[i] = Automate[i];
    }
    return states;
}


//есть ли состояние в таблице
bool StateInTable(string **table, string state, int n, int m)
{
    //проходимся по столбцу таблицы где записаны состояния автомата
    for (int i = 0; i < n; i++)
    {
        if (table[i][0] == state)
            return true;
    }

    return false;
}

//есть ли терминал в таблице
bool TerminalInTable(string** table, string terminal, int n, int m)
{
    for (int i = 0; i < m; i++)
    {
        if (table[0][i] == terminal)
            return true;
    }

    return false;
}

//количество строк
int GetNumberRow(string** table, string state, int n, int m)
{
    for (int i = 0; i < n; i++)
        if (table[i][0] == state)
            return i;

    return -1;
}

//колво столбцов
int GetNumberCol(string** table, string terminal, int n, int m)
{
    for (int i = 0; i < m; i++)
        if (table[0][i] == terminal)
            return i;

    return -1;
}


int main()
{
	setlocale(LC_ALL, "Russian");

	cout << "Лабораторная работа №4. Минимизация конечного автомата." << endl;

	//динамический массив с достижимыми символами
	//char *Enumbers;

    State* Automate = new State[16];

    Automate[0] = State(States::E, "!", States::H);
    Automate[1] = State(States::E, "!", States::F);

    Automate[2] = State(States::H, "c", States::L);
    Automate[3] = State(States::H, "b", States::G);

    Automate[4] = State(States::L, "c", States::H);
    Automate[5] = State(States::L, "b", States::M);

    Automate[6] = State(States::M, "b", States::H);
    Automate[7] = State(States::M, "a", States::K);
    Automate[8] = State(States::M, "1", States::M);
    Automate[9] = State(States::M, "0", States::M);
    Automate[10] = State(States::M, "!", States::S);

    Automate[11] = State(States::S, "!", States::G);

    Automate[12] = State(States::G, "a", States::F);
    Automate[13] = State(States::G, "0", States::G);
    Automate[14] = State(States::G, "1", States::G);

    Automate[15] = State(States::K, "-", States::E);

    cout << "Изначальный автомат: " << endl;
    cout << " _s0____v____s1_" << endl;

    for (int i = 0; i < 16; i++)
    {
        cout << StrState(Automate[i].state_0) << " --> " << Automate[i].value << " " << StrState(Automate[i].state_1) << endl;
    }


    Automate = DeleteUnreachableStates(Automate);

    cout << "Автомат после удаления недостижимых состояний: ";
    for (int i = 0; i < 16; i++)
    {
        cout << StrState(Automate[i].state_0) << " --> " << Automate[i].value << " " << StrState(Automate[i].state_1) << endl;
    }

    Automate = DeleteExualStates(Automate);
    cout << "Автомат после удаления эквивалентных состояний: ";
    for (int i = 0; i < 16; i++)
    {
        cout << StrState(Automate[i].state_0) << " --> " << Automate[i].value << " " << StrState(Automate[i].state_1) << endl;
    }

    //строки, столбцы
    int n = 10, m = 10;

    //таблица переходов
    string** table = new string*[n];

    for (int i = 0; i < n; i++) table[i] = new string[m];

    //создание классов эквивалентности
    int k = 1;
    //n]Q - число состояний автомата, сост 1 - начальное
    for (int i = 0; i < sizeof(Automate); i++)
    {
        string state = StrState(Automate[i].state_0);
        if (!StateInTable(table, state, n, m))
        {
            table[i][k] = StrState(Automate[i].state_0);
            k++;
        }

        if (!TerminalInTable(table, Automate[i].value, n, m))
            table[i][0] =  Automate[i].value;

    }
    //Алгоритм заканчивается, когда (n+1)-эквивалентные состояния совпадают с n-эквивалентными.


    int row = 0, col = 0;
    for (int i = 0; i < sizeof(Automate); i++)
    {
        row = GetNumberRow(table, StrState(Automate[i].state_0), n, m );
        col = GetNumberCol(table, Automate[i].value, n, m);
        table[row][col] = StrState(Automate[i].state_1);
    }

    cout << "Конечный минимизированный автомат: " << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << " " << table[i][j] << " |";
        }
        cout << endl;
    }

}