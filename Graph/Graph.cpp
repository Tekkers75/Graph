//@author Саранчин К.А. 

#include <iostream>
#include "Graph.h"
//#include "TestGraph.h"

int main() {

    setlocale(LC_ALL, "rus");

    // Создание графа с 4 вершинами
    Graph<int> graph(4);

    // Добавление ребер
    graph.addEdge(0, 1, 5);
    graph.addEdge(0, 2, 3);
    graph.addEdge(1, 2, 2);
    graph.addEdge(2, 3, 7);
    graph.addEdge(0, 3, 1);

    // Вывод графа
    graph.printGraph();

    //// Удаление вершины
    //graph.removeVertex(2);

    //// Вывод графа после удаления вершины
    //std::cout << "После удаления вершины:" << std::endl;
    //graph.printGraph();

    //// Удаление ребра
    //graph.removeEdge(0, 1);

    //// Вывод графа после удаления ребра
    //std::cout << "После удаления ребра:" << std::endl;
    //graph.printGraph();


    std::cout << "DFS traversal starting from vertex 0: ";
    graph.DFS(0);
    std::cout << std::endl;

    std::cout << "BFS traversal: ";
    graph.BFS(0);
    std::cout << std::endl;


    int index = graph.findVertexIndex(2);  // Ищем индекс вершины со значением 2
    if (index != -1) {
        std::cout << "Index of vertex 2: " << index << std::endl;
    }
    else {
        std::cout << "Vertex 2 not found" << std::endl;
    }

    int startNode = 0;
    vector<int> distances = graph.Dijkstra(startNode);

    // Выводим кратчайшие расстояния от начальной вершины до всех остальных вершин
    for (int i = 0; i < distances.size(); ++i) {
        cout << "Shortest distance from node " << startNode << " to node " << i << ": " << distances[i] << endl;
    }

    string filename = "graph.graphml";
    graph.exportToGraphML(filename);


    return 0;
}
