
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include "queue.h"

using namespace std;


void mapTraverse(unordered_map<string, vector<string>>);

// generates and retuns a 2D vector of routs
vector<vector<string>> generateRoutes();

// takes the routs to generate the Edges into a map
unordered_map<string, vector<string>> addEdges(vector<vector<string>>);

void retracePath(string, unordered_map<string, string>);

void breadthFirstSearch(string start, unordered_map<string, vector<string>> adjacencyList, string end);

int main()
{
    // create hash map string, vector of strings
    unordered_map<string, vector<string>> adjacencyList;
    //vector<string> cities = generateCityList();
    // create vector for key's values
    vector<vector<string>> routes = generateRoutes();
    // use routes in addEdges to generate adjList
    adjacencyList = addEdges(routes);
    mapTraverse(adjacencyList);
    string start, end;
    // loop breaks when the user gives cities that exist
    while (true) {
        cout << "Enter the city to start the search from: ", cin >> start;
        cout << "Enter the the city to search for: ", cin >> end;
        // Make sure the user inputs cities that exist
        vector<string> emptyVector;
        if (adjacencyList[start] != emptyVector && adjacencyList[end] != emptyVector) break;
        else cout << "Please input cities that exist\n";
    }
    
    breadthFirstSearch(start, adjacencyList, end);
    return 0;
}


void mapTraverse(unordered_map<string, vector<string>> adjacencyList) {
    for (auto& [key, values] : adjacencyList)
        // using structured binding introduced in c++17
    {
        cout << key << " has the following edges -> ";

        for (int i = 0; i < values.size(); i++) {
            cout << values[i] + " ";
        }
        cout << endl;
    }
    cout << endl;
}


unordered_map<string, vector<string>> addEdges(vector<vector<string>> routes) {
    
    unordered_map<string, vector<string>> adjacencyList;
    // temporary vector to store and  alter adjList values
    vector<string> values;

    for (int i = 0; i < routes.size(); i++) {
        // check if key has value, remember that adjacency list values are a vector<string>
        bool isFound = find(adjacencyList[routes[i][0]].begin(), 
                            adjacencyList[routes[i][0]].end(), routes[i][1]) != adjacencyList[routes[i][0]].end();
                                          //key                 //value
        // if key already has value skip adding value
        if (isFound) continue;
        // get current values of the key you want to edit
        string key = routes[i][0];
        values = adjacencyList[key];
        // map["cairo"] = {value1,value2};
        // push the new route from city 1 to city 2    
        string value = routes[i][1];
        values.push_back(value);
        // add it to the adjList
        adjacencyList[key] = values;
        //  "cairo": {"Giza", "Alex", "portsaid"}
        //  make it so it's undirected (switch key with value)
        key = routes[i][1];
        values = adjacencyList[key];
        value = routes[i][0];
        values.push_back(value);
        adjacencyList[key] = values;

    }

    return adjacencyList;
}


// creates 2D vector to represent routes

vector<vector<string>> generateRoutes() {
    // 2D vector to store all routes
    vector<vector <string> > routes;
    string city1, city2;
    cout << "Please input routes in this format: City1  City2 , Enter 0 when you are done\n";
    // loop until user breaks
    while(true){
        // vector to store each route
        vector<string> route;
        cin >> city1;
        if (city1 == "0") break;
        else route.push_back(city1);

        cin >> city2;
        // Make sure user doesn't stop before inputing city2
        while (city2 == "0") cout << "Please insert City 2 before finishing the route list\n", cin >> city2;
        // Make sure user didn't input the same city twice
        if(city1 == city2) cout << "A city can't a have a route to it self, Please enter a different city\n", cin >> city2;

        route.push_back(city2);
        // add the route to routes
        routes.push_back(route);
    } 

    /*for (int i = 0; i < routes.size(); i++)
    {
        cout << routes[i][0] << " " << routes[i][1] << endl;
    }*/
    return routes;

}

// Path: cairo alex cairo port alex giza alex aswan port suez port sharm giza cairo aswan luxor aswan mahala suez cairo suez menia sharm sina menia luxor
void breadthFirstSearch(string start, unordered_map<string, vector<string>> adjacencyList, string end) {
    if (start == end) { cout << "You are where you wanna go mate ;)"; return; }
    // initialize queueSize to 0
    int queueSize;

    set<string> visited;
    unordered_map<string, string> oldPath;

    Enqueue(start);
    visited.insert(start);

    queueSize = length();

    while (queueSize > 0)
    {
        // key is the parentNode of value
        string key = dequeue();
        // loop through each value in key's values
        for (int i = 0; i < adjacencyList[key].size(); i++) {
            // value is a child Node of key
            string value = adjacencyList[key][i];
            if (value == end) {
                cout << end << " is found!\n";
                oldPath[value] = key;
                retracePath(value, oldPath);
                return;

            }
            // contains introduced in c++20
            if (!visited.contains(value)) {
                visited.insert(value);
                Enqueue(value);
                // update queueSize
                queueSize = length();
                // remember which path the node took by storing node as key and parent as value in oldPath map
                oldPath[value] = key;
            }
        }
    }
}

void retracePath(string Node, unordered_map<string, string> oldPath) {
    // vector to store shortestPath
    vector<string> shortestPath;

    while (Node != "") {
        // push each Node
        shortestPath.push_back(Node);
        // remember that every Node in oldPath points to it's parent if exists
        // use the Node as Key that points to new Node
        Node = oldPath[Node];

    }
    // reverse the vector to obtain the path in the correct order (top to bottom)
    std::reverse(shortestPath.begin(), shortestPath.end());
    // using ranges to loop through path vector and print each value
    // just a for loop
    //std::ranges::copy(shortestPath, std::ostream_iterator<string>(cout, " "));

    cout << "Fastest Path -> ";
    for (int i = 0; i < shortestPath.size(); i++) {
        cout << shortestPath[i] << " ";
    }
}
