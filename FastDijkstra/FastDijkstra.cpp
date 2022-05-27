#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

struct Edge;

struct Vertex {
    int numberInGraph;
    bool isChek = false;
    int distance = INT_MAX;
    std::vector<Edge> edgeTo;
    
};

struct Edge {
    int vertexTo;
    int wight;
};

struct heap {
    std::vector<int> tree;

    heap() {
        tree.push_back(0);
    }

    void push(int x) {
        tree.push_back(x);
        sift_up(tree.size() - 1);
    }

    int max() {
        if (tree.size() > 1) {
            return tree[1];
        }
        else {
            return -1;
        }
    }

    void pop() {
        if (tree.size() > 1) {
            tree[1] = tree.back();
            tree.pop_back();
            sift_down(1);
        }
        else {
            std::cout << "куча пуста";
            return;
        }
    }


    void sift_up(int v) {
        if (v == 1) {
            return;
        }

        if (tree[v / 2] > tree[v]) {
            std::swap(tree[v], tree[v / 2]);
            sift_up(v / 2);
        }
    }


    void sift_down(int v) {
        if (v * 2 >= tree.size()) {
            return;
        }


        int max_idx;
        if (v * 2 + 1 == tree.size()) {
            max_idx = v * 2;
        }
        else if (tree[v * 2] <= tree[v * 2 + 1]) {
            max_idx = v * 2;
        }
        else {
            max_idx = v * 2 + 1;
        }

        if (tree[v] > tree[max_idx]) {
            std::swap(tree[v], tree[max_idx]);
            sift_down(max_idx);
        }
    }

    bool empty() {
        return tree.size() == 1;
    }
};

heap q;



void searchWay(std::vector<Vertex> &graph, int vertex) {

    graph[vertex].isChek = true;

    for (int i = 0; i < graph[vertex].edgeTo.size(); i++) {
        int indexNextVertex = graph[vertex].edgeTo[i].vertexTo;

        if (graph[indexNextVertex].isChek){
            continue;
        }

        graph[indexNextVertex].distance = (graph[vertex].distance + graph[vertex].edgeTo[i].wight < graph[indexNextVertex].distance) ? graph[vertex].distance + graph[vertex].edgeTo[i].wight : graph[indexNextVertex].distance;
        
        q.push(graph[indexNextVertex].numberInGraph);
        
    }

    if (q.empty()) {
        return;
    }

    
    //MergeSort(q, 0, q.size() - 1, Comp);

    int tempVertex = graph[q.max()].numberInGraph;
    q.pop();
    searchWay(graph, tempVertex);

}

int main()
{
    std::ifstream inp("input.txt");
    std::ofstream out("output.txt");

    int n, m, s;
    inp >> n >> m >> s;

    std::vector<Vertex> graph(n + 1);

    for (int i = 1; i < graph.size(); i++) {
        graph[i].numberInGraph = i;
    }

    for (int i = 0; i < m; i++) {
        int from, to, wight;
        inp >> from >> to >> wight;
        Edge temp = { to, wight };
        graph[from].edgeTo.push_back(temp);
    }

    graph[s].distance = 0;

    searchWay(graph, s);

    for (int i = 1; i < graph.size(); i++) {
        out << ((graph[i].distance == INT_MAX) ? -1 : graph[i].distance) << ' ';
    }
}
