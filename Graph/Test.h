#pragma once
#include <iostream>
#include "Graph.h"
#include <cassert>

void testAddEdge() {
    Graph<int> graph(5);  // Создаем граф с 5 вершинами

    // Добавляем ребра
    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 5);
    graph.addEdge(1, 2, 3);
    graph.addEdge(1, 3, 7);
    graph.addEdge(2, 3, 2);
    graph.addEdge(3, 4, 1);

    // Проверяем значения весов ребер
    assert(graph.getWeight(0, 1) == 10);
    assert(graph.getWeight(0, 2) == 5);
    assert(graph.getWeight(1, 2) == 3);
    assert(graph.getWeight(1, 3) == 7);
    assert(graph.getWeight(2, 3) == 2);
    assert(graph.getWeight(3, 4) == 1);

    // Проверяем количество вершин
    assert(graph.getNumVertices() == 5);

    std::cout << "Тест вставки ребра пройден" << std::endl;
}

void testAddVertex() {
    Graph<int> graph(3);  // Создаем граф с 3 вершинами

    // Проверяем начальное количество вершин
    assert(graph.getNumVertices() == 3);

    // Добавляем новую вершину
    graph.addVertex();

    // Проверяем увеличенное количество вершин
    assert(graph.getNumVertices() == 4);

    std::cout << "Тест вставки вершины пройден" << std::endl;
}

void testRemoveVertex() {
    Graph<int> graph(4);  // Создаем граф с 4 вершинами

    // Удаляем вершину с индексом 2
    graph.removeVertex(2);

    // Проверяем количество вершин после удаления
    assert(graph.getNumVertices() == 3);

    // Удаляем несуществующую вершину с индексом 5
    graph.removeVertex(5);

    // Проверяем, что количество вершин осталось неизменным
    assert(graph.getNumVertices() == 3);

    std::cout << "Тест удаления вершины пройден" << std::endl;
}

void testRemoveEdge() {
    Graph<int> graph(4);  // Создаем граф с 4 вершинами

    // Устанавливаем ребро между вершинами 1 и 2
    graph.removeEdge(1, 2);

    // Проверяем, что вес ребра между вершинами 1 и 2 равен 0
    assert(graph.getWeight(1, 2) == 0);

    // Пытаемся удалить ребро между несуществующими вершинами 5 и 6
    graph.removeEdge(5, 6);

    std::cout << "Тест удаления ребра пройден" << std::endl;
}

void testGetNumVertices() {
    Graph<int> graph(5);  // Создаем граф с 5 вершинами

    // Проверяем, что количество вершин равно 5
    assert(graph.getNumVertices() == 5);

    std::cout << "Тест с подсчетом вершин пройден" << std::endl;
}

//void testNumEdges() {
//    Graph<int> graph(4);  // Создаем граф с 4 вершинами
//            
//    // Устанавливаем несколько ребер
//    graph.addEdge(0, 1,0);
//    graph.addEdge(1, 2,0);
//    graph.addEdge(2, 3,0);
//
//    // Проверяем количество ребер
//    assert(graph.NumEdges() == 3);
//
//    std::cout << "Тест с подсчетом ребер пройден" << std::endl;
//}

void testGetVertices() {
    Graph<int> graph(3);  // Создаем граф с 3 вершинами

    // Получаем вектор вершин
    std::vector<int> vertices = graph.getVertices();

    // Проверяем размер вектора
    assert(vertices.size() == 3);

    // Проверяем значения вершин
    assert(vertices[0] == 0);
    assert(vertices[1] == 1);
    assert(vertices[2] == 2);

    std::cout << "Тест с получением вершин пройден" << std::endl;
}


void testGetWeight() {
    Graph<int> graph(3);  // Создаем граф с 3 вершинами

    // Устанавливаем ребро между вершинами 1 и 2 со весом 5
    graph.addEdge(1, 2, 5);

    // Проверяем вес ребра между вершинами 1 и 2
    assert(graph.getWeight(1, 2) == 5);

    // Проверяем вес несуществующего ребра
    assert(graph.getWeight(0, 2) == 0);

    std::cout << "Тест с получением весов пройден" << std::endl;
}

void testFindVertexIndex() {
    Graph<int> graph(4);  // Создаем граф с 4 вершинами

    // Проверяем индекс существующей вершины
    assert(graph.findVertexIndex(1) == 1);

    // Проверяем индекс несуществующей вершины
    assert(graph.findVertexIndex(6) == -1);

    std::cout << "Тест с поиском вершин по индексу пройден" << std::endl;
}

void testDFS() {
    Graph<int> graph(4);  // Создаем граф с 4 вершинами

    // Устанавливаем ребра
    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 5);
    graph.addEdge(1, 2, 3);

    std::cout << "Тест обхода в глубину: ";
    graph.DFS(0);  // Обход в глубину, начиная с вершины 0

    std::cout << std::endl;
}

void testBFS() {
    Graph<int> graph(4);  // Создаем граф с 4 вершинами

    // Устанавливаем ребра
    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 5);
    graph.addEdge(1, 2, 3);

    std::cout << "Тест обхода в ширину: ";
    graph.BFS(0);  // Обход в ширину, начиная с вершины 0

    std::cout << std::endl;
}

void testDijkstra() {
    Graph<int> graph(6);  // Создаем граф с 6 вершинами

    // Устанавливаем ребра и их веса
    //graph.removeEdge(0, 1);
    graph.addEdge(0, 2, 3);
    graph.addEdge(1, 2, 2);
    graph.addEdge(1, 3, 5);
    graph.addEdge(2, 3, 1);
    graph.addEdge(2, 4, 4);
    graph.addEdge(3, 4, 2);
    graph.addEdge(3, 5, 6);
    graph.addEdge(4, 5, 1);
    graph.addEdge(0, 1, 3);

    int startNode = 0;
    vector<int> distances = graph.Dijkstra(startNode);

    // Проверяем расстояния от начальной вершины до остальных вершин
    assert(distances[0] == 0);
    assert(distances[1] == 3);
    assert(distances[2] == 3);
    assert(distances[3] == 4);
    assert(distances[4] == 6);
    assert(distances[5] == 7);

    std::cout << "Тест Дейкстры" << std::endl;
}