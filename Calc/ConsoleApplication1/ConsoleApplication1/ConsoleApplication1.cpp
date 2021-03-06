// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "string.h"
#include <stack>
#include <list>
#include <sstream>
#include <iomanip>
using namespace std;

//3-(2*5*(3-1))+9
//4*((2+1-2)+10)/7
//4*([2+1-2]+10)/2

//some answers might be wrong cause of division and an order of operations
//0 is the result of the division by 0

/*
string intToString(int value)
{
	string str;
	stringstream ss;
	ss << value;
	return ss.str();
}
*/

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Введите выражение\n";
	char str[80];
	cin >> str;
	char symbol = str[0];
	stack <char> ops;
	list<string> poliz;
	string tmp_str;
	int i = 0;
	int num = 0;
	bool lastNum = false;
	bool error = false;
	bool closingBracket = false;
	//making poliz (reverse Polish notation)
	while (!error)
	{
		symbol = str[i++];
		if (symbol >= '0' && symbol <= '9')	//is num
		{
			closingBracket = false;
			num = num * 10 + symbol - '0';
			lastNum = true;
		}
		else if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '(' || symbol == '[')	//is ops
		{
			if (lastNum)
			{
				poliz.push_back(to_string(num));
				num = 0;
				if (!ops.empty() && (ops.top() == '*' || ops.top() == '/') && (symbol == '+' || symbol == '-'))	//ops priority
				{
					closingBracket = false;
					tmp_str = ops.top();
					poliz.push_back(tmp_str);
					ops.pop();
				}
				ops.push(symbol);
				lastNum = false;
			}
			else if (symbol == '(' || symbol == '[' || closingBracket)	//ops after ops
			{
				closingBracket = false;
				ops.push(symbol);
			}
			else error = true;
		}
		else if (symbol == ')')
		{
			closingBracket = true;
			if (lastNum)
			{
				poliz.push_back(to_string(num));
				num = 0;
				lastNum = false;
			}
			while (!ops.empty() && ops.top() != '(')
			{
				tmp_str = ops.top();
				poliz.push_back(tmp_str);
				ops.pop();
			}
			if (ops.top() == '(')
				ops.pop();
			else error = true;
		}
		else if (symbol == ']')
		{
			closingBracket = true;
			if (lastNum)
			{
				poliz.push_back(to_string(num));
				num = 0;
				lastNum = false;
			}
			while (!ops.empty() && ops.top() != '[')
			{
				tmp_str = ops.top();
				poliz.push_back(tmp_str);
				ops.pop();
			}
			if (ops.top() == '[')
				ops.pop();
			else error = true;
		}
		else if (symbol == '\0')	//end of expression
		{
			if (lastNum)
			{
				poliz.push_back(to_string(num));
				num = 0;
				lastNum = false;
			}
			break;
		}
		else error = true;
	}
	while (!ops.empty())	//poping ops
	{
		tmp_str = ops.top();
		poliz.push_back(tmp_str);
		ops.pop();
	}
	if (error)	//error
		cout << "Error\n";
	else        //poliz output
	{
		for (auto iter = poliz.begin(); iter != poliz.end(); iter++)
		{
			cout << *iter << ' ';
		}
		auto iter = poliz.begin();
		while (poliz.size() != 1)
		{
			iter = poliz.begin();
			try {
				while (stof(*iter) >= INT_MIN && stof(*iter) <= INT_MAX) iter++;
			}
			catch (exception e)
			{
			}
			if (*iter == "+")
			{
				auto op = iter;
				auto a = iter;
				a--;
				auto b = iter;
				b--;
				b--;
				poliz.insert(a, to_string(stof(*b) + stof(*a)));
				poliz.erase(op);
				poliz.erase(a);
				poliz.erase(b);
			}
			else if (*iter == "-")
			{
				auto op = iter;
				auto a = iter;
				a--;
				auto b = iter;
				b--;
				b--;
				poliz.insert(a, to_string(stof(*b) - stof(*a)));
				poliz.erase(op);
				poliz.erase(a);
				poliz.erase(b);
			}
			else if (*iter == "*")
			{
				auto op = iter;
				auto a = iter;
				a--;
				auto b = iter;
				b--;
				b--;
				poliz.insert(a, to_string(stof(*b) * stof(*a)));
				poliz.erase(op);
				poliz.erase(a);
				poliz.erase(b);
			}
			else if (*iter == "/")
			{
				auto op = iter;
				auto a = iter;
				a--;
				auto b = iter;
				b--;
				b--;
				if (stof(*a) == 0)
					poliz.insert(a, "0");
				else
				{
					float f = stof(*b) / stof(*a);
					poliz.insert(a, to_string(f));
				}
				poliz.erase(op);
				poliz.erase(a);
				poliz.erase(b);
			}
		}
		cout << "result: " << fixed << setprecision(3) << stof(poliz.front());
	}
	cout << "\nEND";
	getchar();
}