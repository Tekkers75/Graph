#pragma once
#include <iostream>
#include "Graph.h"
#include <cassert>

void testAddEdge() {
    Graph<int> graph(5);  // ������� ���� � 5 ���������

    // ��������� �����
    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 5);
    graph.addEdge(1, 2, 3);
    graph.addEdge(1, 3, 7);
    graph.addEdge(2, 3, 2);
    graph.addEdge(3, 4, 1);

    // ��������� �������� ����� �����
    assert(graph.getWeight(0, 1) == 10);
    assert(graph.getWeight(0, 2) == 5);
    assert(graph.getWeight(1, 2) == 3);
    assert(graph.getWeight(1, 3) == 7);
    assert(graph.getWeight(2, 3) == 2);
    assert(graph.getWeight(3, 4) == 1);

    // ��������� ���������� ������
    assert(graph.getNumVertices() == 5);

    std::cout << "���� ������� ����� �������" << std::endl;
}

void testAddVertex() {
    Graph<int> graph(3);  // ������� ���� � 3 ���������

    // ��������� ��������� ���������� ������
    assert(graph.getNumVertices() == 3);

    // ��������� ����� �������
    graph.addVertex();

    // ��������� ����������� ���������� ������
    assert(graph.getNumVertices() == 4);

    std::cout << "���� ������� ������� �������" << std::endl;
}

void testRemoveVertex() {
    Graph<int> graph(4);  // ������� ���� � 4 ���������

    // ������� ������� � �������� 2
    graph.removeVertex(2);

    // ��������� ���������� ������ ����� ��������
    assert(graph.getNumVertices() == 3);

    // ������� �������������� ������� � �������� 5
    graph.removeVertex(5);

    // ���������, ��� ���������� ������ �������� ����������
    assert(graph.getNumVertices() == 3);

    std::cout << "���� �������� ������� �������" << std::endl;
}

void testRemoveEdge() {
    Graph<int> graph(4);  // ������� ���� � 4 ���������

    // ������������� ����� ����� ��������� 1 � 2
    graph.removeEdge(1, 2);

    // ���������, ��� ��� ����� ����� ��������� 1 � 2 ����� 0
    assert(graph.getWeight(1, 2) == 0);

    // �������� ������� ����� ����� ��������������� ��������� 5 � 6
    graph.removeEdge(5, 6);

    std::cout << "���� �������� ����� �������" << std::endl;
}

void testGetNumVertices() {
    Graph<int> graph(5);  // ������� ���� � 5 ���������

    // ���������, ��� ���������� ������ ����� 5
    assert(graph.getNumVertices() == 5);

    std::cout << "���� � ��������� ������ �������" << std::endl;
}

//void testNumEdges() {
//    Graph<int> graph(4);  // ������� ���� � 4 ���������
//            
//    // ������������� ��������� �����
//    graph.addEdge(0, 1,0);
//    graph.addEdge(1, 2,0);
//    graph.addEdge(2, 3,0);
//
//    // ��������� ���������� �����
//    assert(graph.NumEdges() == 3);
//
//    std::cout << "���� � ��������� ����� �������" << std::endl;
//}

void testGetVertices() {
    Graph<int> graph(3);  // ������� ���� � 3 ���������

    // �������� ������ ������
    std::vector<int> vertices = graph.getVertices();

    // ��������� ������ �������
    assert(vertices.size() == 3);

    // ��������� �������� ������
    assert(vertices[0] == 0);
    assert(vertices[1] == 1);
    assert(vertices[2] == 2);

    std::cout << "���� � ���������� ������ �������" << std::endl;
}


void testGetWeight() {
    Graph<int> graph(3);  // ������� ���� � 3 ���������

    // ������������� ����� ����� ��������� 1 � 2 �� ����� 5
    graph.addEdge(1, 2, 5);

    // ��������� ��� ����� ����� ��������� 1 � 2
    assert(graph.getWeight(1, 2) == 5);

    // ��������� ��� ��������������� �����
    assert(graph.getWeight(0, 2) == 0);

    std::cout << "���� � ���������� ����� �������" << std::endl;
}

void testFindVertexIndex() {
    Graph<int> graph(4);  // ������� ���� � 4 ���������

    // ��������� ������ ������������ �������
    assert(graph.findVertexIndex(1) == 1);

    // ��������� ������ �������������� �������
    assert(graph.findVertexIndex(6) == -1);

    std::cout << "���� � ������� ������ �� ������� �������" << std::endl;
}

void testDFS() {
    Graph<int> graph(4);  // ������� ���� � 4 ���������

    // ������������� �����
    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 5);
    graph.addEdge(1, 2, 3);

    std::cout << "���� ������ � �������: ";
    graph.DFS(0);  // ����� � �������, ������� � ������� 0

    std::cout << std::endl;
}

void testBFS() {
    Graph<int> graph(4);  // ������� ���� � 4 ���������

    // ������������� �����
    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 5);
    graph.addEdge(1, 2, 3);

    std::cout << "���� ������ � ������: ";
    graph.BFS(0);  // ����� � ������, ������� � ������� 0

    std::cout << std::endl;
}

void testDijkstra() {
    Graph<int> graph(6);  // ������� ���� � 6 ���������

    // ������������� ����� � �� ����
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

    // ��������� ���������� �� ��������� ������� �� ��������� ������
    assert(distances[0] == 0);
    assert(distances[1] == 3);
    assert(distances[2] == 3);
    assert(distances[3] == 4);
    assert(distances[4] == 6);
    assert(distances[5] == 7);

    std::cout << "���� ��������" << std::endl;
}