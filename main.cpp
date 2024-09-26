#include "Graph.h"
#include "functions.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <format>

using namespace std;

void MenuDeleteLogic(Graph& calculator) {
	int input;
	const int EXIT = 3;

	string menu_edit = 
		"\033[1;31m"
		"\n=============="
		"\n1. Delete"
		"\n2. Reset"
		"\n3. Exit"
		"\n=============="
		"\033[0m";

	do {
		input = EXIT;
		calculator.displayFunctions();
		cout << menu_edit << endl;
		InputBracket(input);

		switch (input)
		{
		case 1: {
			cout << "Select function to delete:" << endl;
			do {
				InputBracket(input);
				cout << input;
			} while (!calculator.deleteFunction(input - 1));
			break;
		}
		case 2: {
			calculator.deleteFunctionAll();
			break;
		}
		default:
			cout << format("Invalid input ({}), out of range.", input) << endl;
			break;
		}
	} while (input != EXIT);
}

int main() {
	int graph_range = 40;
	Graph calculator(graph_range);

	const int MENU_EXIT = 6;
	int menu_choice;

	string menu_main = 
		"\033[1;36m"
		"\n=============="
		"\n1. New function"
		"\n2. Function list"
		"\n3. Delete function"
		"\n4. Plot Graph"
		"\n5. Graph range"
		"\n6. Exit"
		"\n=============="
		"\033[0m";

	do {
		menu_choice = MENU_EXIT;
		cout << menu_main << endl;
		InputBracket(menu_choice);

		switch (menu_choice)
		{
		case 1: {
			double input;
			vector<double> function_var;

			cout << "Enter variables, 's' to stop, ... mx^n + ax^2 + bx + c" << endl;
			cout << ">>> ";

			do {
				cin >> input;

				if (cin.fail()) {
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					break;
				}
				else
					function_var.push_back(input);
			} while (true);

			calculator.calculateFunctionPoints(function_var);

			break;
		}
		case 2: {
			calculator.displayFunctions();
			break;
		}
		case 3: {
			MenuDeleteLogic(calculator);
			break;
		}
		case 4: {
			calculator.plotFunctions();
			calculator.plotGraph();

			break;
		}
		case 5: {
			int new_range;
			InputBracket(new_range);
			calculator.setGraphRange(new_range);

			break;
		}
		default:
			cout << format("Invalid input ({}), out of range.", menu_choice) << endl;
			break;
		}
	} while (menu_choice != MENU_EXIT);

	return 0;
}