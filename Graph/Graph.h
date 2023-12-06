#pragma once
//@author �������� �.�. 

#include <iostream>
#include<vector>
#include<stack>
#include<queue>
#include <iomanip>
#include <fstream>
#include <unordered_map>
#include <string>


using namespace std;

template <class T>
class Graph {
private:
    int numVertices;                    // ���������� ������ � �����
    //int numEdges;                     // ���������� ����� � �����
    vector<T> vertices;                 // ������ ������ �����
    vector<vector<int>> adjMatrix;      // ������� ���������

public:

    // ����������� � �����������
    Graph(int numVertices) {
        this->numVertices = numVertices;

        // �������������� ������� ���������
        adjMatrix.resize(numVertices, vector<int>(numVertices, 0));\

        // �������������� ������ ������
        vertices.resize(numVertices);
        for (int i = 0; i < numVertices; ++i) {
            vertices[i] = i;
        }
    }

    // ���������� ����� � ����
    /// <param name="source"> ��������� �������� ������� ����� </param>
    /// <param name="destination"> ��������� �������� ������� ����� </param>
    /// <param name="weight">  ��������� ��� ����� </param>
    void addEdge(int source, int destination, int weight) {
        adjMatrix[source][destination] = weight;    // ������������� ��� ��� ���������������� �����
    }

    // ���������� ������� � ����
    void addVertex() {
        numVertices++;                        // ����������� ���������� ������ �� 1
        adjMatrix.resize(numVertices, vector<int>(numVertices, 0));    // ��������� ����� ������ � ������� ���������

        // ��������� ����� ������� � ������ ������
        vertices.push_back(numVertices - 1);
    }

    // �������� ������� �� �����
    void removeVertex(int vertex) {
        if (vertex >= 0 && vertex < numVertices) {
            // ������� ������ � ������� ��� ��������� ������� �� ������� ���������
            adjMatrix.erase(adjMatrix.begin() + vertex);
            for (auto& row : adjMatrix) {
                row.erase(row.begin() + vertex);
            }
            numVertices--;  // ��������� ���������� ������ �� 1
            // ������� ������� �� ������� ������
            vertices.erase(vertices.begin() + vertex);
        }
    }

    // �������� ����� �� �����
    void removeEdge(int source, int destination) {
        if (source >= 0 && source < numVertices && destination >= 0 && destination < numVertices) {
            adjMatrix[source][destination] = 0;    // ������������� ��� ����� � 0
        }
    }

    // ��������� ���������� ������ � �����
    int getNumVertices() const {
        return numVertices;
    }

    //���������� ����� � �����
    int NumEdges() {

        int countEdge = 0;
        for (int i = 0; i < numVertices; i++) {
            //for (int j = i; j < numVertices; j++) 
            for (int j = 0; j < numVertices; j++) {
                if (adjMatrix[i][j] != 0)
                    countEdge++;
            }
        }
        return countEdge;
    }

    // ��������� ������� ������
    vector<T> getVertices() const {
        return vertices;
    }   

    // ��������� ���� ����� ����� ����� ���������
    int getWeight(int source, int destination) const {
        if (source >= 0 && source < numVertices && destination >= 0 && destination < numVertices) {
            return adjMatrix[source][destination];
        }
        else {
            return 0;   // ���������� 0, ���� ������� �����������
        }
    }

    void DFS(int startVertex) {
        std::vector<bool> visited(numVertices, false);  // ������� ������ ���������� ������, ������������� ��� �������� ��� false
        std::stack<int> stack;  // ������� ���� ��� �������� ������

        stack.push(startVertex);  // �������� ��������� ������� � ����

        while (!stack.empty()) {  // ���� ���� �� ����
            int currentVertex = stack.top();  // �������� ������� �� ������� �����
            stack.pop();  // ������� ������� �� �����

            if (!visited[currentVertex]) {  // ���� ������� �� ���� ��������
                std::cout << currentVertex << " ";  // ������� ������� �������
                visited[currentVertex] = true;  // �������� ������� ��� ����������

                for (int neighbor = 0; neighbor < numVertices; ++neighbor) {  // �������� �� �������� ��������
                    if (adjMatrix[currentVertex][neighbor] != 0 && !visited[neighbor]) {  // ���� ���� ����� � �������� ������� �� ��������
                        stack.push(neighbor);  // �������� �������� ������� � ����
                    }
                }
            }
        }
    }

    void BFS(int startVertex) {
        std::vector<bool> visited(numVertices, false);  // ������� ������ ���������� ������, ������������� ��� �������� ��� false
        std::queue<int> queue;  // ������� ������� ��� �������� ������

        queue.push(startVertex);  // �������� ��������� ������� � �������

        while (!queue.empty()) {  // ���� ������� �� �����
            int currentVertex = queue.front();  // �������� ������� �� ������ �������
            queue.pop();  // ������� ������� �� �������

            if (!visited[currentVertex]) {  // ���� ������� �� ���� ��������
                std::cout << currentVertex << " ";  // ������� ������� �������
                visited[currentVertex] = true;  // �������� ������� ��� ����������

                for (int neighbor = 0; neighbor < numVertices; neighbor++) {  // �������� �� �������� ��������
                    if (adjMatrix[currentVertex][neighbor] != 0 && !visited[neighbor]) {  // ���� ���� ����� � �������� ������� �� ��������
                        queue.push(neighbor);  // �������� �������� ������� � �������
                    }
                }
            }
        }
    }

    int findVertexIndex(const T& value) const {
        auto it = std::find(vertices.begin(), vertices.end(), value);
        if (it != vertices.end()) {
            return std::distance(vertices.begin(), it);
        }
        return -1;  // ������� �� �������
    }

    // ����� �����
    void printGraph() {
        cout << endl;
        cout << "<���������� ������> = " << getNumVertices() << endl;
        cout << "������ ������ �����: " << endl;
        vector<int> vertices = getVertices();
        for (int i = 0; i < numVertices; i++) {
            cout << "������� " << i << "  " << vertices[i] << endl;
        }
        cout << endl;

        cout << "<���������� �����> = " << NumEdges() << endl;
        for (int i = 0; i < numVertices; i++) {
            // for (int j = i + 1; j < numVertices; j++) 
            for (int j = 0; j < numVertices; j++) {
                if (adjMatrix[i][j] != 0) {
                    cout << "����� " << i << "-" << j << "  ���: " << adjMatrix[i][j] << endl;
                }
            }
        }
        cout << "������� ���������:" << endl;
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {

                cout << setw(3) << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    vector<int> Dijkstra(int startNode) {
        vector<int> distances(numVertices, numeric_limits<int>::max()); // �������������� ���������� ��������������
        distances[startNode] = 0; // ���������� �� ��������� ������� ����� 0

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push(make_pair(0, startNode)); // ��������� ��������� ������� � ������������ �������

        while (!pq.empty()) {
            int currentDistance = pq.top().first;
            int currentNode = pq.top().second;
            pq.pop();

            if (currentDistance > distances[currentNode]) {
                continue; // ���� ������� ���������� ������, ���������� �������
            }

            // �������� �� ������� ��������
            for (int neighbor = 0; neighbor < numVertices; ++neighbor) {
                int edgeWeight = adjMatrix[currentNode][neighbor];
                if (edgeWeight != 0) {
                    int distance = currentDistance + edgeWeight;
                    if (distance < distances[neighbor]) {
                        distances[neighbor] = distance;
                        pq.push(make_pair(distance, neighbor));
                    }
                }
            }
        }

        return distances;
    }

    void exportToGraphML(const string& filename) {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            // ���������� ��������� � ��������� ��� <graph>
            outFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
            outFile << "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\"\n";
            outFile << "    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n";
            outFile << "    xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns\n";
            outFile << "    http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">\n";
            outFile << "  <graph id=\"G\" edgedefault=\"directed\">\n";
            //��� ����� ���� -������� ��� ���� �������������
            outFile << R"(<key id="weight" for="edge" attr.name="weight" attr.type="double"/>)" << '\n';

            // ���������� �������
            for (int i = 0; i < numVertices; ++i) {
                outFile << "    <node id=\"" << i << "\"/>\n";
            }

            // ���������� �����
            int edgeId = 0;
            for (int i = 0; i < numVertices; ++i) {
                for (int j = 0; j < numVertices; ++j) {
                    int edgeWeight = adjMatrix[i][j];
                    if (edgeWeight != 0) {
                        outFile << "    <edge id=\"" << edgeId++ << "\" source=\"" << i << "\" target=\"" << j << "\">\n";
                        outFile << "      <data key=\"weight\">" << edgeWeight << "</data>\n";
                        outFile << "    </edge>\n";
                    }
                }
            }

            // ��������� ����
            outFile << "  </graph>\n";
            outFile << "</graphml>\n";

            outFile.close();
            cout << "Graph exported to " << filename << " in GraphML format." << endl;
        }
        else {
            cout << "Failed to export graph to " << filename << "." << endl;
        }
    }
   

 
};
