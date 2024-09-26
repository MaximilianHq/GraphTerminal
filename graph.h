#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

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
    const string black      = "\033[30m";
    const string red        = "\033[31m";
    const string green      = "\033[32m";
    const string yellow     = "\033[33m";
    const string blue       = "\033[34m";
    const string magenta    = "\033[35m";
    const string cyan       = "\033[36m";
    const string white      = "\033[37m";

	const string axis_x = red;		    // x-axis
	const string axis_y = red;		    // y-axis
	const string intersect = magenta;	// intersect (graph)
	const string root = blue;			// x = 0
	const string end = "\033[0m";	    // end of color change

    const vector<string> color_list = {
        //black,
        //red,
        green,
        yellow,
        blue,
        magenta,
        cyan,
        white
    };
}

struct Point {
    int x;
    int y;
};

struct Function {
	vector<double> variables;
	vector<Point> points;
};

class Graph {
public:
    Graph(int range);
    void initializeGraph();
    void plotGraph();
    void calculateFunctionPoints(const vector<double>& coeff);
    void plotFunctions();
    void displayFunctions() const;
    int sizeFunctions() const;
    bool deleteFunction(const int i);
    void deleteFunctionAll();
    void setGraphRange();
    void setGraphRange(const int r);

    // Other member functions...

private:
    int range;
    int rows;
    int cols;
    int range_half;
    vector<Function> functions;
    vector<vector<string>> graph;
};

#endif // GRAPH_H