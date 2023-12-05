#pragma once
//@author Maltseva K.V. 

#include <iostream>
#include<vector>
#include<stack>
#include<queue>
#include <iomanip>
using namespace std;

//���������� ��������������� ����
template <class T>
class WeightedGraph {
private:
    int maxVertices;//������������ ������ �����
    int numVertices; // ���������� ������ �����
    //int* vertices; // ������ ������ ����� 

    vector<T> vertices;  // ������ ������ �����
    int** adjacencyMatrix; // ������� ���������
public:

    // ����������� � ���������� (������������ ������ �����)
    WeightedGraph(int _maxVertices) {
        maxVertices = _maxVertices;
        numVertices = 0;

        //// �������� ������ ��� ������� ������ � �������������� ��� ���������� 
        //vertices = new int[maxVertices];
        //for (int i = 0; i < maxVertices; i++) {
        //    vertices[i] =  i + 1;
        //}

        // �������� ������ ��� ������� ��������� � �������������� ���������� 0,��� ��� ���������� ������� �����
        adjacencyMatrix = new int* [maxVertices];
        for (int i = 0; i < maxVertices; i++) {
            adjacencyMatrix[i] = new int[maxVertices];
            for (int j = 0; j < maxVertices; j++) {
                adjacencyMatrix[i][j] = 0;
            }
        }
    }

    //���������� �������
    void addVertex(const char& vertex) {
        if (numVertices >= maxVertices) {
            // ��������� ������������ ������ �����, ���������� ��������� ������
            int newMaxVertices = maxVertices * 2;

            // ������� ����� ������� ��������� � ����������� ��������
            int** newAdjacencyMatrix = new int* [newMaxVertices];
            for (int i = 0; i < newMaxVertices; i++) {
                newAdjacencyMatrix[i] = new int[newMaxVertices];
            }

            // �������� �������� �� ������ ������� ��������� � ����� 
            for (int i = 0; i < maxVertices; i++) {
                memcpy(newAdjacencyMatrix[i], adjacencyMatrix[i], maxVertices * sizeof(int));
            }

            // �������������� ����� �������� ��������� 0
            for (int i = maxVertices; i < newMaxVertices; i++) {
                memset(newAdjacencyMatrix[i], 0, newMaxVertices * sizeof(int));
            }

            // ����������� ������ ������ ������� ���������
            for (int i = 0; i < maxVertices; i++) {
                delete[] adjacencyMatrix[i];
            }
            delete[] adjacencyMatrix;

            // ��������� ��������� �� ����� ������� ��������� � ������������ ������
            adjacencyMatrix = newAdjacencyMatrix;
            maxVertices = newMaxVertices;
        }

        // ��������� ����� ������� � ������ ������
       // vertices[numVertices] = vertex;
        vertices.push_back(vertex);
        // ����������� ���������� ������
        numVertices++;
    }
    //���������� �����
    void addEdge(const T& source, const T& destination, double weight) {
        // ���������, ��� ������� ��������� � ���������� ��������
        if (source >= 0 && source < numVertices && destination >= 0 && destination < numVertices) {
            // ��������� ����� � ����� � ������� 
            adjacencyMatrix[source][destination] = weight;
            // adjacencyMatrix[destination][source] = weight; 
        }
        else {

            // ���������� ���������� 
            throw invalid_argument("����������� �������, ������ �������� �����");
        }
    }
    //�������� �����
    void removeEdge(const T& source, const T& destination) {
        // ���������, ��� ������� ��������� � ���������� ��������
        if (source >= 0 && source < numVertices && destination >= 0 && destination < numVertices) {
            // ������� ����� �� ������� ���������
            adjacencyMatrix[source][destination] = 0;
        }
        else {

            // ���������� ���������� 
            throw invalid_argument("������ ����� � ����� ���");
        }
    }
    //�������� �������
    void removeVertex(const T& vertex) {
        // ���������, ��� ������� ��������� � ���������� ��������
        if (vertex >= 0 && vertex < numVertices) {

            //// ������� ������� �� ������ ������, ������� ������� �����
            //for (int i = vertex; i < numVertices - 1; i++) {
            //    vertices[i] = vertices[i + 1];
            //}

             // ������� ������� �� ������� ������, ������� ������� �����
            vertices.erase(vertices.begin() + vertex);
            // ������� ������ � �������, ��������������� �������, �� ������� ���������
            //��������� �� ������� ����� �� ������� � ����� �� ������
            for (int i = vertex; i < numVertices - 1; i++) {
                for (int j = 0; j < numVertices; j++) {
                    adjacencyMatrix[i][j] = adjacencyMatrix[i + 1][j];
                }
            }
            for (int i = 0; i < numVertices; i++) {
                for (int j = vertex; j < numVertices - 1; j++) {
                    adjacencyMatrix[i][j] = adjacencyMatrix[i][j + 1];
                }
            }
            //��������� ���������� ������ � �����
            numVertices--;
        }
        //����� ���������� ����������
        else {
            throw invalid_argument("����� ������� � ����� ���");
        }
    }


    // ������ ������ � ����� 
    void printGraph() {
        cout << endl;
        cout << "<���������� ������> = " << getNumVertices() << endl;
        cout << "������ ������ �����: " << endl;
        for (int i = 0; i < numVertices; i++) {
            cout << "�������" << i << "  " << vertices[i] << endl;
        }
        cout << endl;

        cout << "<���������� �����> = " << NumEdges() << endl;
        for (int i = 0; i < numVertices; i++) {
            // for (int j = i + 1; j < numVertices; j++) 
            for (int j = 0; j < numVertices; j++) {
                if (adjacencyMatrix[i][j] != 0) {
                    cout << "����� " << i << "-" << j << "  ���: " << adjacencyMatrix[i][j] << endl;
                }
            }
        }
        cout << "������� ���������:" << endl;
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {

                cout << setw(3) << adjacencyMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }


    //���������� ������ � �����
    int getNumVertices() const {
        return numVertices;
    }
    //���������� ����� � �����
    int NumEdges() {

        int countEdge = 0;
        for (int i = 0; i < numVertices; i++) {
            //for (int j = i; j < numVertices; j++) 
            for (int j = 0; j < numVertices; j++) {
                if (adjacencyMatrix[i][j] != 0)
                    countEdge++;
            }
        }
        return countEdge;
        /* int countEdge = 0;
         for (int i = 0; i < numVertices; i++) {
             for (int j = 0; j < numVertices; j++) {
                 if (adjacencyMatrix[i][j] != 0 )
                     countEdge++;
             }

         }
         return countEdge;*/
    }
    //�������� ��� ����� ���������
    int getWeight(const T& source, const T& destination) {
        // ���������, ��� ������� ��������� � ���������� ��������
        if (source >= 0 && source < numVertices && destination >= 0 && destination < numVertices) {
            // ���������� ��� ����� �� ������� 
            return adjacencyMatrix[source][destination];
        }
        //����� ���������� ����������
        else {

            throw invalid_argument("����������� ������� ��� �����");
            //return -1;
        }
    }
    // ��������� ������� ������
    vector<T> getVertices() const {
        return vertices;
    }
    ////��������� ������� ������ �����
    //vector<int> getVertices() const {
    //    vector<int> vertexVector;
    //    for (int i = 0; i < numVertices; i++) {
    //        vertexVector.push_back(vertices[i]);
    //    }
    //    return vertexVector;
    //}
    //����� � �������

    //����� � ������� �� ������ �����
    vector<T> DepthFirst(const T& startNode) {
        //������ ��������� ���������� ������, ���������� ��� false,�.� �� ��������
        vector<bool> visitedVertices(numVertices, false);
        //���� ��� ������, ������� ����� ����������
        stack<int> nodeStack;
        //��������� � ���� ��������� �������
        nodeStack.push(startNode);
        //�������� � ���������� �������
        visitedVertices[startNode] = true;
        //������ ��� ������ ���������� ������
        vector<int> SaveVertices;
        //���� ���� �� ����
        while (!nodeStack.empty()) {
            //����������� ������� �����
            int currentNode = nodeStack.top();
            nodeStack.pop();
            //��������� 
            SaveVertices.push_back(currentNode);
            //cout << currentNode << " ";
            // ������������� ��� ������� �������
            for (int i = 0; i < numVertices; i++) {
                // ���� ���� ����� ����� ������� �������� � �������� i, � ������� i ��� �� ��������
                if (adjacencyMatrix[currentNode][i] && !visitedVertices[i]) {
                    //��������� ������� � ����
                    nodeStack.push(i);
                    //�������� ������� ��� ����������
                    visitedVertices[i] = true;
                }
            }
        }
        //  cout << endl;
          //���������� ������ �� ������ ������
        return SaveVertices;
    }
    //����� � ������ �� ������ ����
    vector<T> BreadthFirst(const T& startNode) {
        //������ ��������� ���������� ������, ���������� ��� false,�.� �� ��������
        vector<bool> visitedVertices(numVertices, false);
        //���� ��� ������, ������� ����� ����������
        queue<int> nodeQueue;
        //��������� � ���� ��������� �������
        nodeQueue.push(startNode);
        //�������� � ���������� �������
        visitedVertices[startNode] = true;
        //������ ��� ������ ���������� ������
        vector<int> SaveVertices;
        //���� ���� �� �����
        while (!nodeQueue.empty()) {
            //����������� �������
            int currentNode = nodeQueue.front();
            nodeQueue.pop();
            //���������
            SaveVertices.push_back(currentNode);
            //cout << currentNode << " ";
            // ������������� ��� ������� �������
            for (int i = 0; i < numVertices; i++) {
                // ���� ���� ����� ����� ������� �������� � �������� i, � ������� i ��� �� ��������
                if (adjacencyMatrix[currentNode][i] && !visitedVertices[i]) {
                    //��������� ������� � ����
                    nodeQueue.push(i);
                    //�������� ������� ��� ����������
                    visitedVertices[i] = true;
                }
            }
        }
        //cout << endl;
        //���������� ������ �� ������ ������
        return  SaveVertices;
    }

    // ����� ������� ������� � ������� vertices �� ��������
    int findVertexIndex(const T& vertex) {
        //�������� �� �������
        for (int i = 0; i < numVertices; i++) {
            //���������� � ������ ���������
            if (vertices[i] == vertex) {
                //���������� ������ �������
                return i;
            }
        }
        //���������� -1 
        return -1;
    }
    //�������� ��������
    //����� ����������� ���� �� ��������� ������� startNode �� ���� ��������� ������ � �����
    void dijkstrasAlgorithm(const T& startNode) {
        //����������� ��������� ��������: ���������� = "�������������", �������� = "�� ��������"//
        vector<int> distance(numVertices, numeric_limits<int>::max()); // ���������� �� ��������� ������� �� ���������
        vector<bool> visited(numVertices, false); // ���������� �������

        // ������� ������ ��������� �������,����� ��������� ������ ���� �� ���( � ����)
        int startIndex = findVertexIndex(startNode);
        if (startIndex == -1) {
            // ��������� ������� �� �������
            return;
        }

        // ���������� �� ��������� ������� �� ��� ����� ����� 0
        distance[startIndex] = 0;

        //��������� ������ ���������� ��������, ���� ���� �������� � �� �������
        while (startIndex != -1) {
            // ��� �������� ������ ���������� ��������������� � �������� ����������
            for (int i = 0; i < numVertices; i++) {
                //�������� ��� ����� ����� ������� �������� � �������� i
                int weight = getWeight(startIndex, i);
                //���� ��� �� ����� 0 � ������� �� �������� � ����� ���� ����� ������� ������� ������ �������� ���������� �� ������� i
                if (weight != 0 && !visited[i] && (weight + distance[startIndex] < distance[i])) {
                    //���������� ����������� �� ����� ����� ����
                    distance[i] = weight + distance[startIndex];
                }
            }

            // �������� ������� ������� ��� "����������" � �������� ���������
            visited[startIndex] = true;
            startIndex = -1;
            int mindistance = numeric_limits<int>::max();
            for (int i = 0; i < numVertices; i++) {
                //����� ��������� ������������ �������
                if (!visited[i] && distance[i] < mindistance) {
                    //������������ ������� ����� ������� �������
                    startIndex = i;
                    //������� ����������� ���������� = ����������� �� ��������� �������
                    mindistance = distance[i];
                }
            }
        }

        // ������� ����������
        for (int i = 0; i < numVertices; i++) {
            cout << "���������� ���������� �� ������� " << startNode << " �� ������� "
                << vertices[i] << ": ";
            if (distance[i] == numeric_limits<int>::max()) {
                cout << "��� ����" << endl;
            }
            else {
                cout << distance[i] << endl;
            }
        }
    }

    // https://medium.com/nuances-of-programming/%D0%B3%D1%80%D0%B0%D1%84%D1%8B-%D0%B8-%D0%BF%D1%83%D1%82%D0%B8-%D0%B0%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC-%D0%B4%D0%B5%D0%B9%D0%BA%D1%81%D1%82%D1%80%D1%8B-fa0b404c3a85
        //����������
    ~WeightedGraph() {
        // ����������� ������, ���������� ��� ������� ������
      //  delete[] vertices;

        // ����������� ������, ���������� ��� ������� ���������
        for (int i = 0; i < numVertices; i++) {
            delete[] adjacencyMatrix[i];
        }
        delete[] adjacencyMatrix;
    }
};
