#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <list>

using namespace std;

//правила языка
class Rule
{
public:
	//порождающая цепочка языка
	string key;

	//порождаемая цепочка языка
	string value;

	//зацикливание
	bool IsLooped;

	Rule(string k, string v, bool l = false)
	{
		key = k;
		value = v;
		IsLooped = l;
	};

	Rule()
	{
		key = "S";
		value = "1";
		IsLooped = false;
	}
};

//печать правил на экран 
//на вход подается лист из всех правил языка
void print_rules(Rule *arr, int n)
{
	cout << "Правила языка: " << endl;
	for (int i= 0; i < n; i++)
	{
		cout << arr[i].key << " --> " << arr[i].value << endl;
	}
};

//множество состояний
enum State {H, C, D, S, N, P, B, A, ER};

//чтобы выбрать рандомно из двух вариантов состояний
State random(State a, State b)
{
	srand(time(NULL));

	int r = rand() % 2;

	if (r == 0)
		return a;
	else
		return b;
}

inline const char* ToString(State CS)
{
	switch (CS)
	{
		//enum State {H, C, D, S, N, P, B, A, ER};
		case H: return "H";
		case C: return "C";
		case D: return "D";
		case S: return "S";
		case N: return "N";
		case P: return "P";
		case B: return "B";
		case A: return "A";

		case ER: return "ER";
		default: return "[unknown type]";
	}
}

//анализатор 2 лаба общая №1
string Analizator1(string text)
{
	State CS = N;

	//счетчик = 0
	int count = 0;
	int txtsize = text.length();

	//строка результата
	string res = "";
	do
	{
		if (count < txtsize)
		{
			//сам анализатор
			if (CS == N)
			{
				if ((text[count] == '1') or (text[count] == '0'))
				{
					CS = N;
				}
				else
					if (text[count] == '.')
					{
						CS = P;
					}
					else CS = ER;
			}
			else
				if (CS == P)
				{
					if ((text[count] == '1') or (text[count] == '0'))
					{
						CS = S;
					}
					else CS = ER;
				}
				else
					if (CS == S) //конечное состояние автомата
					{
						if ((text[count] == '1') or (text[count] == '0'))
						{
							CS = S;
						}
						else CS = ER;
					}
					else
					{
						CS = ER;
						break;
					};

			res += ToString(CS);
			res += " ";
			count++;
		}
		else break;
	}
	//до тех пор пока не ошибка
	//или автмат не придет к конечному состоянию
	while (CS != ER && CS != S);

	return res;
}

//анализатор 2 лаба общая №2
string Analizator2(string text)
{
	State CS = H;

	//счетчик = 0
	int count = 0;
	int txtsize = text.length();

	//строка результата
	string res = "";
	do
	{
		if (count < txtsize)
		{
			//сам анализатор
			if (CS == H)
			{
				if ((text[count] == '1')or (text[count] == '0')) CS = A;
			}
			else
				if (CS == A)
				{
					if ((text[count] == '1') or (text[count] == '0')) CS = A;
					if (text[count] == '9') CS = S;
					if ((text[count] == '+') or (text[count] == '-')) CS = B;
				}
				else
					if (CS == S) //конечное состояние автомата
					{
						CS = ER;
						break;
					}
					else
						if (CS == B)
						{
							if ((text[count] == '1') or (text[count] == '0')) CS = A;
						}
						else
						{
							CS = ER;
							break;
						};

			res += ToString(CS);
			res += " ";
			count++;
		}
		else break;
	}
	//до тех пор пока не ошибка
	//или автмат не придет к конечному состоянию
	while (CS != ER && CS != S);

	return res;
}



/*
//функция анализатор
string Analizator(string text)
{
	//начальное состояние - H
	State CS = S;

	//счетчик = 0
	int count = 0;

	//строка результата
	string res = "";
	do
	{
		if (count < text.size())
		{
			switch (CS)
			{
			//состояние H
			case H:
				{
					CS = S;
				}
				//lse CS = ER;
				//break;
			//состояние S
			case S:
				if (text[count] == '1')
				{
					CS = D;
				}
				if (text[count] == '0')
				{
					CS = C;
				}
				else CS = ER;
				break;
				//состояние В
			case D:
				if (text[count] == '0')
				{
					CS = random(S, C);
				}
				else CS = ER;
				break;
				//состояние С
			case C:
				if (text[count] == '1')
				{
					CS = random(S, D);
				}
				else CS = ER;
				break;
			default:
				break;
			}

			res += CS;
			res += " ";
			//Console.WriteLine(now);
			count++;
		}
		else break;
	} 
	while (CS != ER);

	if (CS == ER)
	{
		return "error";
	}
	else
	{
		return res;
	}
		
}
*/

//анализатор для задания по вариантам
string Analizator3(string text)
{
	State CS = H;

	//счетчик = 0
	int count = 0;
	int txtsize = text.length();

	//строка результата
	string res = "";
	do
	{
		//если строка еще не закончилась
		if (count < txtsize)
		{
			//сам анализатор
			//если текущее состояние начальное - переходим в S
			if (CS == H)
			{
				CS = S;
			}
			else
				//если текущее состояние S - переходим в 
				if (CS == S)
				{
					if (text[count] == '0') CS = B;
				}
				else
					if (CS == B)
					{
						if (text[count] == '0')
						{
							CS = B;
						}
						else
						if (text[count] == '1') CS = C;
					}
					else
						if (CS == C)
						{
							if (text[count] == '0') CS = B;
						}
						else
						{
							CS = ER;
							break;
						};

			res += ToString(CS);
			res += " ";
			//Console.WriteLine(now);
			count++;
		}
		else break;
	}
	while (CS != ER);

	return res;
}

//печать диаграммы состояний на экран
void print_diagram(string a[3][4])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << "|" << setw(5) << a[i][j];
			if (j == 3)
				cout << "|";
		}

		cout << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	cout << "Лабораторная работа №2. Общее задание №1." << endl;

	cout << "Грамматика языка: G = ({0, 1, .}, {N, P, S}, P, N)" << endl;
	
	//количество элементов в массиве
	int n = 9;

	Rule* rule1 = new Rule[n];

	rule1[0] = Rule("S", "S0");
	rule1[1] = Rule("S", "S1");
	rule1[2] = Rule("S", "P0");
	rule1[3] = Rule("S", "P1");

	rule1[4] = Rule("P", "N.");

	rule1[5] = Rule("N", "0");
	rule1[6] = Rule("N", "1");
	rule1[7] = Rule("N", "N0");
	rule1[8] = Rule("N", "N1");

	print_rules(rule1, n);

	cout << "Анализатор: " << Analizator1("11.010") << endl;
	cout << "Анализатор: " << Analizator1("0.1") << endl;
	cout << "Анализатор: " << Analizator1("01.") << endl;
	cout << "Анализатор: " << Analizator1("100") << endl << endl;

	///////////////////////////////////////////////////
	cout << "Лабораторная работа №2. Общее задание №2." << endl << endl;

	cout << "Грамматика языка: G = ({0, 1, 9, +, -}, {H, A, B, S}, P, H)" << endl;

	cout << "Анализатор: " <<  Analizator2("10119") << endl;
	cout << "Анализатор: " <<  Analizator2("10+0119") << endl;
	cout << "Анализатор: " <<  Analizator2("0-101+19") << endl << endl;

	//анализатор 

	cout << "Лабораторная работа №2. Задание по вариантам. Вариант 12." << endl;

	//правила языка///////////////////////////////////////////////////////////////////////

	n = 8;

	Rule* rules = new Rule[n];

	rules[0] = Rule("S", "B0");
	rules[1] = Rule("S", "0");

	rules[2] = Rule("B", "B0");
	rules[3] = Rule("B", "C1");
	rules[4] = Rule("B", "1");
	rules[5] = Rule("B", "0");

	rules[6] = Rule("C", "B0");

	print_rules(rules, n);

	//анализатор/////////////////////////////////////////////////////////////////////////////

	string analiz_str;

	cout << "Строка для анализа: " << endl;

	cin >> analiz_str;

	cout << "Анализатор: " << Analizator3(analiz_str) << endl;

	cout << "Диаграмма переходов: " << endl;

	//переписать под 13 вариант
	string diagr[3][4] =
	{
		{" ", "C", "D", "S"},
		{"0", " ", "C,D", "C"},
		{"1", "S,D", " ", "D"}
	};

	print_diagram(diagr);

	return 0;
}