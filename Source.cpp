#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <format>

using namespace std;

// Text Color Codes:
// \033[30m // Black
// \033[31m // Red
// \033[32m // Green
// \033[33m // Yellow
// \033[34m // Blue
// \033[35m // Magenta
// \033[36m // Cyan
// \033[37m // White

// Background Color Codes:
// \033[40m // Black
// \033[41m // Red
// \033[42m // Green
// \033[43m // Yellow
// \033[44m // Blue
// \033[45m // Magenta
// \033[46m // Cyan
// \033[47m // White

// Text Style Codes:
// \033[0m  // Reset all styles
// \033[1m  // Bold
// \033[2m  // Faint (not widely supported)
// \033[3m  // Italic (not widely supported)
// \033[4m  // Underline
// \033[5m  // Slow Blink (not widely supported)
// \033[6m  // Rapid Blink (not widely supported)
// \033[7m  // Reverse Video (swap text and background colors)
// \033[8m  // Conceal (not widely supported)
// \033[9m  // Crossed Out (not widely supported)

// Reset All Attributes:
// \033[0m

namespace graph_color {
	const string axis_x = "\033[31m";		// x-axis
	const string axis_y = "\033[31m";		// y-axis
	const string function = "\033[32m";		// graph
	const string intersect = "\033[35m";	// intersect (graph)
	const string root = "\033[34m";			// x = 0
	const string end = "\033[0m";			// end of color change
}

struct Point {
	int x = 0;
	int y = 0;
};

struct Function {
	vector<double> variables;
	vector<Point> points;
};

class Graph {
public:

	Graph(int range) : range(range) {
		setGraphRange(range);
	}

	void initializeGraph() {
		graph = vector<vector<string>>(rows, vector<string>(cols, " "));
		int range_x = 0;
		int range_y = 0;

		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++) {
				// set numbers on x-axis
				if (j == range_half) {
					graph[i][j] = graph_color::axis_y + to_string(range_y) + graph_color::end;

					// While on the positive side of 0
					if (i < range_half)
						range_y--;
					// While on the negative side of 0
					else
						range_y++;

					// switch at tens
					if (range_y < 0) // 0 9 8 7 ...
						range_y = 9;
					else if (range_y > 9) // 0 1 2 3 ...
						range_y = 0;

					// move range_x once at center (replaced by y-axis)
					if (i == range_half)
						range_x++;
				}
				// set numbers on y-axis
				else if (i == range_half) {
					graph[i][j] = graph_color::axis_x + to_string(range_x) + graph_color::end;

					// While on the negative side of 0
					if (j < range_half)
						range_x--;
					// While on the positive side of 0
					else
						range_x++;

					// switch at tens
					if (range_x < 0) // 0 9 8 7 ...
						range_x = 9;
					else if (range_x > 9) // 0 1 2 3 ...
						range_x = 0;
				}
			}
	}

	void plotGraph() {
		// iterate through and display all
		for (int i = 0; i <= range; i++) {
			for (int j = 0; j <= range; j++) {
				// separate with " "
				cout << graph[i][j] << " ";
			}
			// row-break
			cout << endl;
		}
	}

	void calculateFunctionPoints(vector<double>& coeff) {
		// initialize new Function
		Function new_function;
		// store function variables
		new_function.variables = coeff;
		// reverse vector to be able to loop with i
		reverse(coeff.begin(), coeff.end());

		for (int x = -range / 2; x <= range / 2; x++) {
			Point new_point;
			new_point.x = x;
			for (int i = coeff.size() - 1; i >= 0; i--) {
				// v{a, b, c} => v_r = {c, b, a}. v_r[i] = a; x^i; i index of a = 2
				new_point.y += round(coeff[i] * pow(x, i));
			}
			// add point to function
			new_function.points.push_back(new_point);
		}
		// add function to function list
		functions.push_back(new_function);
	}

	void plotFunctions() {
		for (auto& func : functions) // iterate through every function
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < cols; j++)
					for (auto& point : func.points)
						// y becomes larger as i goes towards 0, while x becomes larger as i goes towards infinity
						if (i == -point.y + range_half and j == point.x + range_half) {
							if (i == range_half)
								graph[i][j] = graph_color::root + "0" + graph_color::end;
							else if (graph[i][j] != " " and j != range_half) // <-- prevent y axis override
								graph[i][j] = graph_color::intersect + "0" + graph_color::end;
							else
								graph[i][j] = graph_color::function + "0" + graph_color::end;
						}
	}

	void displayFunctions() {
		int func_index = 1;
		for (auto& func : functions) {
			cout << "\nFunction " << func_index++ << endl;
			cout << "f(x):";
			for (auto& var : func.variables)
				cout << " " << var;
			cout << endl;
		}
	}

	int sizeFunctions() {
		return functions.size();
	}

	bool deleteFunction(int i) {
		if (i >= 0 and i < functions.size()) {
			// erase vector at specified index
			functions.erase(functions.begin() + i);
			return true;
		}

		return false;
	}

	void deleteFunctionAll() {
		for (int i = 0; i < functions.size(); i++)
			deleteFunction(i);
	}

	void setGraphRange(const int r) {
		// needs safety
		range = r;
		rows = range + 1;
		cols = range + 1;
		range_half = range / 2;
	}

private:
	int range;
	int rows;
	int cols;
	int range_half;

	vector<Function> functions;
	vector<vector<string>> graph;
};

void displayMenu() {
	cout << "\033[1;36m"
		"\n=============="
		"\n1. New function"
		"\n2. Function list"
		"\n3. Delete function"
		"\n4. Plot Graph"
		"\n5. Graph range"
		"\n6. Exit"
		"\n=============="
		"\033[0m" << endl;
}

void displayMenuEdit() {
	cout << "\033[1;31m"
		"\n=============="
		"\n1. Delete"
		"\n2. Reset"
		"\n3. Exit"
		"\n=============="
		"\033[0m" << endl;
}

template <typename T>
void InputBracket(T& input) {
	cout << ">>> ";
	cin >> input;
}

void MenuDeleteLogic(Graph& calculator) {
	int input;
	const int EXIT = 3;

	do {
		input = EXIT;
		calculator.displayFunctions();
		displayMenuEdit();
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

	do {
		menu_choice = MENU_EXIT;
		displayMenu();
		InputBracket(menu_choice);

		switch (menu_choice)
		{
		case 1: {
			double input;
			vector<double> function_var;

			cout << "Enter variables, 's' to stop, ... ax ^ 2 + bx + c" << endl;
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
			calculator.initializeGraph();
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