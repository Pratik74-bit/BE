#include <iostream>
#include <queue>
#include <stack>
#include <thread>

using namespace std;

const int MAX_VERTICES = 5;

// Perform parallel Breadth-First Search
void parallelBFS(int graph[MAX_VERTICES][MAX_VERTICES], int source) {
    bool visited[MAX_VERTICES] = {false};
    visited[source] = true;

    queue<int> bfsQueue;
    bfsQueue.push(source);

    while (!bfsQueue.empty()) {
        int current = bfsQueue.front();
        bfsQueue.pop();

        cout << "Visiting vertex: " << current << endl;

        vector<thread> threads;

        for (int i = 0; i < MAX_VERTICES; i++) {
            if (graph[current][i] == 1 && !visited[i]) {
                visited[i] = true;
                bfsQueue.push(i);

                threads.emplace_back([&]() {
                    cout << "Visiting vertex: " << i << endl;
                });
            }
        }

        for (auto& thread : threads) {
            thread.join();
        }
    }
}

// Perform parallel Depth-First Search
void parallelDFS(int graph[MAX_VERTICES][MAX_VERTICES], int source) {
    bool visited[MAX_VERTICES] = {false};
    visited[source] = true;

    stack<int> dfsStack;
    dfsStack.push(source);

    while (!dfsStack.empty()) {
        int current = dfsStack.top();
        dfsStack.pop();

        cout << "Visiting vertex: " << current << endl;

        vector<thread> threads;

        for (int i = 0; i < MAX_VERTICES; i++) {
            if (graph[current][i] == 1 && !visited[i]) {
                visited[i] = true;
                dfsStack.push(i);

                threads.emplace_back([&]() {
                    parallelDFS(graph, i);
                });
            }
        }

        for (auto& thread : threads) {
            thread.join();
        }
    }
}

int main() {
    int graph[MAX_VERTICES][MAX_VERTICES] = {
        {0, 1, 1, 0, 0},
        {1, 0, 0, 1, 1},
        {1, 0, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0}
    };

    cout << "Parallel BFS traversal:" << endl;
    parallelBFS(graph, 0);

    cout << "\nParallel DFS traversal:" << endl;
    parallelDFS(graph, 0);

    return 0;
}
