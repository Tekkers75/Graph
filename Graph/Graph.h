#pragma once
//@author Саранчин К.А. 

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
//взвешанный ориентированный граф
class Graph {
private:
    int numVertices;                    // Количество вершин в графе
    vector<T> vertices;                 // Вектор вершин графа
    vector<vector<int>> adjMatrix;      // Матрица смежности

public:

    // Конструктор с параметрами
    Graph(int numVertices) {
        this->numVertices = numVertices;

        // Инициализируем матрицу смежности
        adjMatrix.resize(numVertices, vector<int>(numVertices, 0));

        // Инициализируем вектор вершин
        vertices.resize(numVertices);
        for (int i = 0; i < numVertices; ++i) {
            vertices[i] = i;
        }
    }

    // Добавление ребра в граф
    /// <param name="source"> Указывает исходную вершину ребра </param>
    /// <param name="destination"> Указывает конечную вершину ребра </param>
    /// <param name="weight">  Указывает вес ребра </param>
    void addEdge(int source, int destination, int weight) {
        adjMatrix[source][destination] = weight;    // Устанавливаем вес для соответствующего ребра
    }

    // Добавление вершины в граф
    void addVertex() {
        // Увеличиваем количество вершин на 1
        numVertices++;              
        // Добавляем новую строку в матрицу смежности
        adjMatrix.resize(numVertices, vector<int>(numVertices, 0));     

        // Добавляем новую вершину в вектор вершин
        vertices.push_back(numVertices - 1);
    }

    // Удаление вершины из графа
    void removeVertex(int vertex) {
        if (vertex >= 0 && vertex < numVertices) {
            // Удаляем строку и столбец для указанной вершины из матрицы смежности
            adjMatrix.erase(adjMatrix.begin() + vertex);
            for (auto& row : adjMatrix) {
                row.erase(row.begin() + vertex);
            }
            numVertices--;  // Уменьшаем количество вершин на 1
            // Удаляем вершину из вектора вершин
            vertices.erase(vertices.begin() + vertex);
        }
    }

    // Удаление ребра из графа
    void removeEdge(int source, int destination) {
        if (source >= 0 && source < numVertices && destination >= 0 && destination < numVertices) {
            adjMatrix[source][destination] = 0;    // Устанавливаем вес ребра в 0
        }
    }

    // Получение количества вершин в графе
    int getNumVertices() const {
        return numVertices;
    }

    //количество ребер в графе
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

    // получение вектора вершин
    vector<T> getVertices() const {
        return vertices;
    }   

    // Получение веса ребра между двумя вершинами
    int getWeight(int source, int destination) const {
        if (source >= 0 && source < numVertices && destination >= 0 && destination < numVertices) {
            return adjMatrix[source][destination];
        }
        else {
            return 0;   // Возвращаем 0, если вершины некорректны
        }
    }

    //Обход в глубину на основе стека
    void DFS(int startVertex) {
        vector<bool> visited(numVertices, false);  // Создаем вектор посещенных вершин, инициализируя все значения как false
        stack<int> stack;  // Создаем стек для хранения вершин

        stack.push(startVertex);  // Помещаем начальную вершину в стек

        while (!stack.empty()) {  // Пока стек не пуст
            int currentVertex = stack.top();  // Получаем вершину из вершины стека
            stack.pop();  // Удаляем вершину из стека

            if (!visited[currentVertex]) {  // Если вершина не была посещена
                cout << currentVertex << " ";  // Выводим текущую вершину
                visited[currentVertex] = true;  // Помечаем вершину как посещенную

                for (int neighbor = 0; neighbor < numVertices; ++neighbor) {  // Проходим по соседним вершинам
                    if (adjMatrix[currentVertex][neighbor] != 0 && !visited[neighbor]) {  // Если есть ребро и соседняя вершина не посещена
                        stack.push(neighbor);  // Помещаем соседнюю вершину в стек
                    }
                }
            }
        }
    }

    //Обход в ширину на основе очереди
    void BFS(int startVertex) {
        vector<bool> visited(numVertices, false);  // Создаем вектор посещенных вершин, инициализируя все значения как false
        queue<int> queue;  // Создаем очередь для хранения вершин

        queue.push(startVertex);  // Помещаем начальную вершину в очередь

        while (!queue.empty()) {  // Пока очередь не пуста
            int currentVertex = queue.front();  // Получаем вершину из начала очереди
            queue.pop();  // Удаляем вершину из очереди

            if (!visited[currentVertex]) {  // Если вершина не была посещена
                cout << currentVertex << " ";  // Выводим текущую вершину
                visited[currentVertex] = true;  // Помечаем вершину как посещенную

                for (int neighbor = 0; neighbor < numVertices; neighbor++) {  // Проходим по соседним вершинам
                    if (adjMatrix[currentVertex][neighbor] != 0 && !visited[neighbor]) {  // Если есть ребро и соседняя вершина не посещена
                        queue.push(neighbor);  // Помещаем соседнюю вершину в очередь
                    }
                }
            }
        }
    }

    // поиск индекса вершины в векторе vertices по значению
    int findVertexIndex(const T& value) const {
        auto it = find(vertices.begin(), vertices.end(), value);
        if (it != vertices.end()) {
            return distance(vertices.begin(), it);
        }
        return -1;  // Вершина не найдена
    }

    // Вывод графа
    void printGraph() {
        cout << endl;
        cout << "<Количество вершин> = " << getNumVertices() << endl;
        cout << "Список вершин графа: " << endl;
        vector<int> vertices = getVertices();
        for (int i = 0; i < numVertices; i++) {
            cout << "Вершина " << i << "  " << vertices[i] << endl;
        }
        cout << endl;

        cout << "<Количество ребер> = " << NumEdges() << endl;
        for (int i = 0; i < numVertices; i++) {
            // for (int j = i + 1; j < numVertices; j++) 
            for (int j = 0; j < numVertices; j++) {
                if (adjMatrix[i][j] != 0) {
                    cout << "Ребро " << i << "-" << j << "  Вес: " << adjMatrix[i][j] << endl;
                }
            }
        }
        cout << "Матрица смежности:" << endl;
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {

                cout << setw(3) << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    //Алгоритм Дейкстры
    //поиск кратчайшего пути от начальной вершины startNode до всех остальных вершин в графе
    vector<int> Dijkstra(int startNode) {
        // Инициализируем расстояния бесконечностью
        vector<int> distances(numVertices, numeric_limits<int>::max()); 
        // Расстояние до начальной вершины равно 0
        distances[startNode] = 0; 

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // Добавляем начальную вершину в приоритетную очередь, make_pair - используется для создания пары (расстояние, вершина)
        //  и добавления этой пары в приоритетную очередь
        pq.push(make_pair(0, startNode)); 

        //выполняем нужное количество итераций, пока приоритетную очередь не пуста
        while (!pq.empty()) {
            //top - используется для получения ссылки на самую верхнюю пару (расстояние, вершина)
            int currentDistance = pq.top().first;
            int currentNode = pq.top().second;
            pq.pop();

            if (currentDistance > distances[currentNode]) {
                continue; // Если текущее расстояние больше, игнорируем вершину
            }

            // Проходим по смежным вершинам
            // начинается цикл, в котором проходим по всем вершинам, смежным с текущей вершиной currentNode. 
            // numVertices представляет общее количество вершин в графе.
            for (int neighbor = 0; neighbor < numVertices; ++neighbor) {
                // получаем вес ребра между текущей вершиной currentNode и смежной вершиной neighbor из матрицы смежности adjMatrix. 
                // Если вес ребра равен 0, это означает, что между вершинами нет прямого ребра и мы пропускаем эту смежную вершину.
                int edgeWeight = adjMatrix[currentNode][neighbor];
                if (edgeWeight != 0) {
                    //вычисляем новое расстояние distance от начальной вершины до смежной вершины через текущую вершину.
                    // Суммируем текущее
                    int distance = currentDistance + edgeWeight;
                    // проверяем, является ли новое расстояние distance меньше, 
                    // чем уже известное расстояние distances[neighbor] до смежной вершины neighbor.
                    if (distance < distances[neighbor]) {
                        distances[neighbor] = distance;
                        // добавляем пару (distance, neighbor) в приоритетную очередь 
                        pq.push(make_pair(distance, neighbor));
                    }
                }
            }
        }

        return distances;
    }

    /// Вывод графа в файл .graphml
    void exportToGraphML(const string& filename) {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            // Записываем заголовок и открываем тег <graph>
            outFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
            outFile << "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\"\n";
            outFile << "    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n";
            outFile << "    xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns\n";
            outFile << "    http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">\n";
            outFile << "  <graph id=\"G\" edgedefault=\"directed\">\n";
            //для ребер ключ -атрибут вес типа вещественного
            outFile << R"(<key id="weight" for="edge" attr.name="weight" attr.type="double"/>)" << '\n';

            // Записываем вершины
            for (int i = 0; i < numVertices; ++i) {
                outFile << "    <node id=\"" << i << "\"/>\n";
            }

            // Записываем ребра
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

            // Закрываем теги
            outFile << "  </graph>\n";
            outFile << "</graphml>\n";

            outFile.close();
            cout << "Граф экспортирован в файл " << filename << " в формате GraphML" << endl;
        }
        else {
            cout << "Не удалось экспортировать граф в файл " << filename << "." << endl;
        }
    }
   

 
};
