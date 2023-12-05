//@author Саранчин К.А. 

#include <iostream>
#include "Graph.h"
//#include "TestGraph.h"

int main() {

    setlocale(LC_ALL, "rus");
    try {
        // Создаем граф
        WeightedGraph<int> graph(10);
        graph.addVertex(0);
        graph.addVertex(1);
        graph.addVertex(2);
        graph.addVertex(3);
        // Добавляем ребра с весами
        graph.addEdge(0, 1, -2);
        graph.addEdge(1, 0, 6);
        graph.addEdge(0, 2, 4);
        graph.addEdge(1, 3, 1);
        graph.addEdge(2, 3, 3);

        graph.addVertex(4);
        graph.addEdge(4, 4, 9);
        cout << "Обход графа в глубину " << endl;
        graph.DepthFirst(0);
        cout << "Обход графа в ширину " << endl;
        graph.BreadthFirst(0);
        graph.printGraph();
        // Удаляем ребро между вершинами 
        graph.removeEdge(0, 4);
        graph.removeVertex(2);
        graph.printGraph();
        graph.dijkstrasAlgorithm(0);


    }
    catch (const invalid_argument& e) {
        // Обработка исключения
        cout << "Ошибка: " << e.what() << endl;
    }

    cout << "Тесты" << endl;
    testAddVertex();
    testAddEdge();
    testRemoveEdge();
    testGetWeight();
    testRemoveVertex();
    testGetNumVertices();
    testNumEdges();
    testBreadthFirst();
    testDephtFirst();


    return 0;
}
