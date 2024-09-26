#include "Graph.h"
#include <iostream>
#include <cmath>

using namespace std;

Graph::Graph(int range) : range(range) {
		setGraphRange(range);
        initializeGraph();
	}

void Graph::initializeGraph() {
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

void Graph::plotGraph() {
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

void Graph::calculateFunctionPoints(const vector<double>& coeff) {
    // initialize new Function
    Function new_function;
    // store function variables
    new_function.variables = coeff;
    // reverse vector to be able to loop with i

    for (int x = -range / 2; x <= range / 2; x++) {
        Point new_point;
        new_point.x = x;
        new_point.y = 0;
        for (int i = coeff.size() - 1, j = 0; i >= 0, j < coeff.size(); i--, j++)
            new_point.y += coeff[j] * pow(x, i);
        new_point.y = round(new_point.y);
        // add point to function
        new_function.points.push_back(new_point);
    }
    
    // add function to function list
    functions.push_back(new_function);
}

void Graph::plotFunctions() {

    // for (auto& func : functions) // iterate through every function
    for (int f = 0; f < functions.size(); f++)
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                for (auto& point : functions[f].points)
                    // y becomes larger as i goes towards 0, while x becomes larger as i goes towards infinity
                    if (i == -point.y + range_half and j == point.x + range_half) {
                        // if (i == range_half)
                        //     graph[i][j] = graph_color::root + "0" + graph_color::end;
                        // else if (graph[i][j] != " " and j != range_half) // <-- prevent y axis override
                        //     graph[i][j] = graph_color::intersect + "0" + graph_color::end;
                        // else
                            graph[i][j] = graph_color::color_list[f] + "0" + graph_color::end;
                    }
}

void Graph::displayFunctions() const {
    int func_index = 1;
    for (auto& func : functions) {
        cout << "\nFunction " << func_index++ << endl;
        cout << "f(x):";
        for (auto& var : func.variables)
            cout << " " << var;
        cout << endl;
    }
}

int Graph::sizeFunctions() const {
    return functions.size();
}

bool Graph::deleteFunction(const int i) {
    if (i >= 0 and i < functions.size()) {
        // erase vector at specified index
        functions.erase(functions.begin() + i);
        return true;
    }

    return false;
}

void Graph::deleteFunctionAll() {
    for (int i = 0; i < functions.size(); i++)
        deleteFunction(i);
}

void Graph::setGraphRange(const int r) {
    // needs safety
    range = r;
    rows = range + 1;
    cols = range + 1;
    range_half = range / 2;
}