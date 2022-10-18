#pragma once
#include <string>
#include <vector>
#include <stack>

using namespace std;

int task1(int number) {
	int fact = 1;
	for (int i = number+1; i > 1; i--)
	{
		fact *= i - 1;
	}
	return fact;
}

bool isClosingBracket(char bracket) {

	switch (bracket) {
	case '}':
	case ')':
	case ']':
		return true;
	}
	return false;
}

bool isOpeningBracket(char bracket) {

	switch (bracket) {
	case '{':
	case '(':
	case '[':
		return true;
	}
	return false;
}

bool task2(const string& list) {
	
	stack<char> brackets;

	for (size_t i = 0; i < list.length(); i++)
	{
		if (isOpeningBracket(list[i])) {
			brackets.push(list[i]);
		}
		else if (isClosingBracket(list[i])) {
			if (!brackets.empty()) {
				switch (brackets.top()) {
				case '{':
					if (list[i] == '}') {
						brackets.pop();
						break;
					}
					else {
						return false;
					}
				case '[':
					if (list[i] == ']') {
						brackets.pop();
						break;
					}
					else {
						return false;
					}
				case '(':
					if (list[i] == ')') {
						brackets.pop();
						break;
					}
					else {
						return false;
					}
				}
			}
			else {
				return false;
			}
		}

	}
	return true;
}

void recursion(unsigned curr, unsigned to, vector<bool>& visited, const vector<vector<int>>& g, bool& flag) {

	if (curr == to) {
		flag = true;
	}

	visited[curr] = true;

	for (int i : g[curr]) {
		if (!visited[i]) {
			recursion(i, to, visited, g, flag);
		}
	}
	
}


bool task3(const vector<vector<int>>& g, unsigned from, unsigned to) {
	
	vector<bool> visited(g.size());
	bool flag = false;
	recursion(from, to, visited, g, flag);
	return flag;

}

bool isLetter(char input) {

	if (input > 64 && input < 91) {
		return true;
	}

	return false;

}

string task4(const string& input) {
	string cur;
	string end;
	string number;
	stack<int> multiplies;

	for (size_t i = 0; i < input.size(); i++)
	{
		if (isdigit(input[i])) {
			number.push_back(input[i]);
			if (!isdigit(input[i + 1])) {
				multiplies.push(stoi(number));
				number.clear();
			}
			continue;
		}
		else if (isLetter(input[i])) {
			cur.push_back(input[i]);
			if (isClosingBracket(input[i+1])) {

				for (size_t i = 0; i < multiplies.top(); i++)
				{
					end.append(cur);
				}
				multiplies.pop();
				cur.clear();

			}
		}
	}

	while (!multiplies.empty()) {
		for (size_t i = 0; i < multiplies.top()-1; i++)
		{
			end += end;
		}
		multiplies.pop();
	}

	return end;

}

bool task5(vector<vector<int>>g, unsigned from, unsigned to) {
	
	stack<int> stck;
	vector<bool> visited(g.size());
	stck.push(from);

	while (!stck.empty()) {

		int cur = stck.top();
		stck.pop();

		if (!visited[cur]) {
			visited[cur] = true;
		}

		for (int i : g[cur]) {

			if (i == to) {
				return true;
			}
			if (!visited[i]) {
				stck.push(i);
			}	

		}

	}
	return false;

}

bool isletter(char input) {

	if (input > 96 && input < 123) {
		return true;
	}

	return false;

}

string calcString(string input) {

	string curr;
	string helper;
	char sign;
	
	for (size_t i = 0; i < input.size()-2; i++)
	{
		if (isletter(input[i])) {
			curr.push_back(input[i]);
		}
		else if (input[i] == '+' || input[i] == '-') {

			if (isOpeningBracket(input[i + 1])) {
				int index = i + 2;
				while (!isClosingBracket(input[index]) && !isOpeningBracket(input[index])) {
					if (isletter(input[index])) {
						if (input[index] - 1 != '+' && input[index] - 1 != '-' && curr.back() != '+' && curr.back() != '-') {
							curr.push_back(input[i]);
						}
						curr.push_back(input[index]);
						index++;
						continue;
					}
					switch (input[i]) {
					case '+':
						switch (input[index]) {
						case '+':
							curr.push_back('+');
							break;
						case '-':
							curr.push_back('-');
							break;
						}
						break;
					case '-':
						switch (input[index]) {
						case '+':
							curr.push_back('-');
							break;

						case '-':
							curr.push_back('+');
							break;
						}
						break;
					}
					index++;

				}
				
				for (size_t i = 0; i < curr.size(); i++)
				{
					helper.push_back(curr[i]);
				}

				for (size_t i = curr.size() + 1; i < input.size(); i++)
				{
					helper.push_back(input[i]);
				}
				input = helper;
				helper.clear();
				i = index - 3;

			}
			else {
				curr.push_back(input[i]);
			}
			
		}

	}


	return input;

}

void clearString(string& str) {

	for (size_t i = 0; i < str.size(); i++)
	{
		if (isOpeningBracket(str[i]) || isClosingBracket(str[i])) {
			str.erase(i);
		}
	}

}

bool compare(string first, string second) {

	if (first.size() != second.size()) {
		return false;
	}

	for (size_t i = 0; i < first.size(); i++)
	{

		if (first[i] != second[i]) {
			return false;
		}

	}

	return true;
}

bool task6(const string& a, const string& b) {

	string first = calcString(a);
	string second = calcString(b);
	clearString(first);
	clearString(second);

	

	return compare(first, second);
}