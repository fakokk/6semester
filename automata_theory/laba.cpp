#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");

	cout << endl;

	cout << " <---q---Q---v---> +---+---+---+---+---+---+---+---+---+" << endl;
	cout << " | | | | Q | W | V | S | D | F | E | G |" << endl;
	cout << " | | +---+---+---+---+---+---+---+---+---+" << endl;
	cout << " <--W<--q— —q-->V--> | Q | | q | v | | | | | |" << endl;
	cout << " | | | | | | +---+---+---+---+---+---+---+---+---+" << endl;
	cout << " | v —--|-— v | | W | | | | v | | z | | |" << endl;
	cout << " | | | | | | +---+---+---+---+---+---+---+---+---+" << endl;
	cout << " | S | | D | | V | | | | | v | | z | |" << endl;
	cout << " z | | | | z +---+---+---+---+---+---+---+---+---+" << endl;
	cout << " | —-------— —— | | S | | | q | | | | | |" << endl;
	cout << " | | +---+---+---+---+---+---+---+---+---+" << endl;
	cout << " | | | D | | q | | | | | | |" << endl;
	cout << " <---------n--------— +---+---+---+---+---+---+---+---+---+" << endl;
	cout << " F E | F | | | | | | | n | |" << endl;
	cout << " —--------n---------> +---+---+---+---+---+---+---+---+---+" << endl;
	cout << " | | | E | | | | | | n | | |" << endl;
	cout << " <----q-----G-----v----> +---+---+---+---+---+---+---+---+---+" << endl;
	cout << " | G | | | | | | q | v | |" << endl;
	cout << " +---+---+---+---+---+---+---+---+---+" << endl << endl;

	cout << "Минимизация:" << endl << endl;

	cout << " <---q---Q---v---> +---+---+---+---+---+---" << endl;
	cout << " | | | | Q | W | V | F | E |" << endl;
	cout << " <------v-----— +---+---+---+---+---+---+" << endl;
	cout << " <--W V--> | Q | | q | v | | |" << endl;
	cout << " | —-----v------> | +---+---+---+---+---+---+" << endl;
	cout << " z z | W | | | v | z | |" << endl;
	cout << " | | +---+---+---+---+---+---+" << endl;
	cout << " F E | V | | v | | | z |" << endl;
	cout << " +---+---+---+---+---+---+" << endl;
	cout << " | F | | | | | |" << endl;
	cout << " +---+---+---+---+---+---+" << endl;
	cout << " | E | | | | | |" << endl;
	cout << " +---+---+---+---+---+---+" << endl << endl;

	cout << "Анализатор:" << endl << endl;

	cout << "Введите цепочку: ";
	string s = "";
	cin >> s;
	if (s[0] == 'q' && s.length() == 1)
		cout << "Выход W" << endl;
	else if (s[0] == 'v' && s.length() == 1)
		cout << "Выход V" << endl;

	else if (s[0] == 'q' && s.length() == 2)
	{
		if (s[1] == 'v' && s.length() == 2)
			cout << "Выход V" << endl;
		else if (s[1] == 'z' && s.length() == 2)
			cout << "Выход F" << endl;
		else
			cout << "Выход Error" << endl;
	}
	else if (s[0] == 'v' && s.length() == 2)
	{
		if (s[1] == 'v' && s.length() == 2)
			cout << "Выход W" << endl;
		else if (s[1] == 'z' && s.length() == 2)
			cout << "Выход E" << endl;
		else
			cout << "Выход Error" << endl;
	}

	else if (s[0] == 'q' && s[1] == 'v' && s.length() == 3)
	{
		if (s[2] == 'v' && s.length() == 3)
			cout << "Выход W" << endl;
		else if (s[2] == 'z' && s.length() == 3)
			cout << "Выход E" << endl;
		else
			cout << "Выход Error" << endl;
	}
	else if (s[0] == 'v' && s[1] == 'v' && s.length() == 3)
	{
		if (s[2] == 'v' && s.length() == 3)
			cout << "Выход V" << endl;
		else if (s[2] == 'z' && s.length() == 3)
			cout << "Выход F" << endl;
		else
			cout << "Выход Error" << endl;
	}
	else
		cout << "Выход Error" << endl;
}