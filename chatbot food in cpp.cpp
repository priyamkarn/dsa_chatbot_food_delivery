#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <climits>
#include <stack>
#include <algorithm>

using namespace std;


struct MenuItem {
    string name;
    int price;
};


unordered_map<string, int> menu = {
    {"pizza", 10},
    {"burger", 5},
    {"fries", 3},
    {"cola", 2}
};


struct Vertex {
    string name;
    vector<pair<int, int>> edges;
};

// This line of code defines a vertex in the graph, with the identifier of 0, and a name of "restaurant". The vertex has two edges that connect to other vertices in the graph. 
//The first edge connects to vertex 1 with a distance of 5, and the second edge connects to vertex 2 with a distance of 2.
unordered_map<int, Vertex> graph = {
    {0, {"restaurant", {{1, 5}, {2, 2}}}},
    {1, {"home", {{3, 10}}}},
    {2, {"office", {{3, 5}}}},
    {3, {"delivery", {}}}
};

// Define a function to calculate the shortest path using Dijkstra's algorithm
vector<int> dijkstra(int start, int end) {
    vector<int> distances(graph.size(), INT_MAX);
    vector<int> previous(graph.size(), -1);
    vector<bool> visited(graph.size(), false);
    distances[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});
    while (!pq.empty()) {
        int current = pq.top().second;
        pq.pop();
        if (visited[current]) {
            continue;
        }
        visited[current] = true;
        for (auto &edge : graph[current].edges) {
            int next = edge.first;
            int distance = edge.second;
            if (distances[next] > distances[current] + distance) {
                distances[next] = distances[current] + distance;
                previous[next] = current;
                pq.push({distances[next], next});
            }
        }
    }
    vector<int> path;
    int current = end;
    while (current != -1) {
        path.push_back(current);
        current = previous[current];
    }
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    vector<string> order;
    order.push_back("pizza");
    order.push_back("cola");
    int total = 0;
    for (auto &item : order) {
        total += menu[item];
    }
    cout << "Total: $" << total << endl;
    vector<int> path = dijkstra(0, 2);
    cout << "Path: ";
    for (auto &vertex : path) {
        cout << graph[vertex].name << " -> ";
    }
   // cout << "delivery" << endl;
}
