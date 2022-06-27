#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

struct Edge;

struct Vertex {
    bool isChek = false;
    int distance = INT_MAX;
    std::vector<Edge> edgeTo;
    
};

struct Edge {
    int vertexTo;
    short int wight;
};

std::vector<Vertex> graph;

struct heap {
    int* mas;
    int size;

    heap(int n) {
        mas = (int*)malloc((n + 1) * sizeof(int));
        size = 0;
    }

    void push(int x) {
        size++;
        mas[size] = x;
        sift_up(size);
    }

    /*int max() {
        if (tree.size() > 1) {
            return tree[1];
        }
        else {
            return -1;
        }
    }*/

    void pop() {
        if (size > 0) {
            mas[1] = mas[size];
            size--;
            if (size > 0) {
                sift_down(1);
            }
        }
    }


    void sift_up(int v) {
        if (v == 1) {
            return;
        }

        if (graph[mas[v / 2]].distance > graph[mas[v]].distance) {
            std::swap(mas[v], mas[v / 2]);
            sift_up(v / 2);
        }
    }


    void sift_down(int v) {
        if (v * 2 > size) {
            return;
        }


        int max_idx = v * 2;
        if (v * 2 + 1 > size && graph[mas[v * 2 + 1]].distance < graph[mas[max_idx]].distance) {
            max_idx = v * 2 + 1;
        }

        if (graph[mas[v]].distance > graph[mas[max_idx]].distance) {
            std::swap(mas[v], mas[max_idx]);
            sift_down(max_idx);
        }
    }

    bool empty() {
        return size == 0;
    }
};

void searchWay(int vertex, heap& q) {

    graph[vertex].isChek = true;

    for (int i = 0; i < graph[vertex].edgeTo.size(); i++) {
        int indexNextVertex = graph[vertex].edgeTo[i].vertexTo;

        if (graph[vertex].distance + graph[vertex].edgeTo[i].wight < graph[indexNextVertex].distance) {
            graph[indexNextVertex].distance = graph[vertex].distance + graph[vertex].edgeTo[i].wight;
            q.push(indexNextVertex);
        }

    }

    if (q.empty()) {
        return;
    }

    int tempVertex = q.mas[1];
    q.pop();
    searchWay(tempVertex, q);

}

int main()
{
    std::ifstream inp("input.txt");
    std::ofstream out("output.txt");

    int n, m, s;
    inp >> n >> m >> s;
     
    graph.resize(n + 1);
    heap q(n);

    for (int i = 0; i < m; i++) {
        int from, to;
        short int wight;
        inp >> from >> to >> wight;
        Edge temp = { to, wight };
        graph[from].edgeTo.push_back(temp);
    }

    graph[s].distance = 0;

    searchWay(s, q);

    for (int i = 1; i < graph.size(); i++) {
        out << ((graph[i].distance == INT_MAX) ? -1 : graph[i].distance) << ' ';
    }
}
