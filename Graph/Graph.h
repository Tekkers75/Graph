#pragma once
//@author Maltseva K.V. 

#include <iostream>
#include<vector>
#include<stack>
#include<queue>
#include <iomanip>
using namespace std;

//взвешанный ориентированный граф
template <class T>
class WeightedGraph {
private:
    int maxVertices;//Максимальный размер графа
    int numVertices; // Количество вершин графа
    //int* vertices; // Массив вершин графа 

    vector<T> vertices;  // Вектор вершин графа
    int** adjacencyMatrix; // Матрица смежности
public:

    // Конструктор с параметром (максимальный размер графа)
    WeightedGraph(int _maxVertices) {
        maxVertices = _maxVertices;
        numVertices = 0;

        //// Выделяем память для массива вершин и инициализируем его значениями 
        //vertices = new int[maxVertices];
        //for (int i = 0; i < maxVertices; i++) {
        //    vertices[i] =  i + 1;
        //}

        // Выделяем память для матрицы смежности и инициализируем значениями 0,так как изначально матрица пуста
        adjacencyMatrix = new int* [maxVertices];
        for (int i = 0; i < maxVertices; i++) {
            adjacencyMatrix[i] = new int[maxVertices];
            for (int j = 0; j < maxVertices; j++) {
                adjacencyMatrix[i][j] = 0;
            }
        }
    }

    //добавление вершины
    void addVertex(const char& vertex) {
        if (numVertices >= maxVertices) {
            // Достигнут максимальный размер графа, необходимо расширить память
            int newMaxVertices = maxVertices * 2;

            // Создаем новую матрицу смежности с увеличенным размером
            int** newAdjacencyMatrix = new int* [newMaxVertices];
            for (int i = 0; i < newMaxVertices; i++) {
                newAdjacencyMatrix[i] = new int[newMaxVertices];
            }

            // Копируем значения из старой матрицы смежности в новую 
            for (int i = 0; i < maxVertices; i++) {
                memcpy(newAdjacencyMatrix[i], adjacencyMatrix[i], maxVertices * sizeof(int));
            }

            // Инициализируем новые элементы значением 0
            for (int i = maxVertices; i < newMaxVertices; i++) {
                memset(newAdjacencyMatrix[i], 0, newMaxVertices * sizeof(int));
            }

            // Освобождаем память старой матрицы смежности
            for (int i = 0; i < maxVertices; i++) {
                delete[] adjacencyMatrix[i];
            }
            delete[] adjacencyMatrix;

            // Обновляем указатель на новую матрицу смежности и максимальный размер
            adjacencyMatrix = newAdjacencyMatrix;
            maxVertices = newMaxVertices;
        }

        // Добавляем новую вершину в массив вершин
       // vertices[numVertices] = vertex;
        vertices.push_back(vertex);
        // Увеличиваем количество вершин
        numVertices++;
    }
    //добавление ребра
    void addEdge(const T& source, const T& destination, double weight) {
        // Проверяем, что вершины находятся в допустимых пределах
        if (source >= 0 && source < numVertices && destination >= 0 && destination < numVertices) {
            // Добавляем ребро с весом в матрицу 
            adjacencyMatrix[source][destination] = weight;
            // adjacencyMatrix[destination][source] = weight; 
        }
        else {

            // генерируем исключение 
            throw invalid_argument("Отсутствуют вершины, нельзя добавить ребро");
        }
    }
    //удаление ребра
    void removeEdge(const T& source, const T& destination) {
        // Проверяем, что вершины находятся в допустимых пределах
        if (source >= 0 && source < numVertices && destination >= 0 && destination < numVertices) {
            // Удаляем ребро из матрицы смежности
            adjacencyMatrix[source][destination] = 0;
        }
        else {

            // генерируем исключение 
            throw invalid_argument("Такого ребра в графе нет");
        }
    }
    //удаление вершины
    void removeVertex(const T& vertex) {
        // Проверяем, что вершина находится в допустимых пределах
        if (vertex >= 0 && vertex < numVertices) {

            //// Удаляем вершину из списка вершин, сдвигая вершину влево
            //for (int i = vertex; i < numVertices - 1; i++) {
            //    vertices[i] = vertices[i + 1];
            //}

             // Удаляем вершину из вектора вершин, сдвигая вершины влево
            vertices.erase(vertices.begin() + vertex);
            // Удаляем строку и столбец, соответствующие вершине, из матрицы смежности
            //сдвигаясь на позицию влево по столбцу и вверх по строке
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
            //уменьшаем количество вершин в графе
            numVertices--;
        }
        //иначе генерируем исключение
        else {
            throw invalid_argument("Такой вершины в графе нет");
        }
    }


    // печать данных о графе 
    void printGraph() {
        cout << endl;
        cout << "<Количество вершин> = " << getNumVertices() << endl;
        cout << "Список вершин графа: " << endl;
        for (int i = 0; i < numVertices; i++) {
            cout << "Вершина" << i << "  " << vertices[i] << endl;
        }
        cout << endl;

        cout << "<Количество ребер> = " << NumEdges() << endl;
        for (int i = 0; i < numVertices; i++) {
            // for (int j = i + 1; j < numVertices; j++) 
            for (int j = 0; j < numVertices; j++) {
                if (adjacencyMatrix[i][j] != 0) {
                    cout << "Ребро " << i << "-" << j << "  Вес: " << adjacencyMatrix[i][j] << endl;
                }
            }
        }
        cout << "Матрица смежности:" << endl;
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {

                cout << setw(3) << adjacencyMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }


    //количество вершин в графе
    int getNumVertices() const {
        return numVertices;
    }
    //количество ребер в графе
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
    //получить вес между вершинами
    int getWeight(const T& source, const T& destination) {
        // Проверяем, что вершины находятся в допустимых пределах
        if (source >= 0 && source < numVertices && destination >= 0 && destination < numVertices) {
            // Возвращаем вес ребра из матрицы 
            return adjacencyMatrix[source][destination];
        }
        //иначе генерируем исключение
        else {

            throw invalid_argument("Отсутствуют вершины или ребро");
            //return -1;
        }
    }
    // получение вектора вершин
    vector<T> getVertices() const {
        return vertices;
    }
    ////Получение вектора вершин графа
    //vector<int> getVertices() const {
    //    vector<int> vertexVector;
    //    for (int i = 0; i < numVertices; i++) {
    //        vertexVector.push_back(vertices[i]);
    //    }
    //    return vertexVector;
    //}
    //обход в глубину

    //Обход в глубину на основе стека
    vector<T> DepthFirst(const T& startNode) {
        //вектор контейнер посещенных вершин, изначально все false,т.к не посещены
        vector<bool> visitedVertices(numVertices, false);
        //стек для вершин, которые нужно обработать
        stack<int> nodeStack;
        //добавляем в стек начальную вершину
        nodeStack.push(startNode);
        //помещаем в посещенные вершины
        visitedVertices[startNode] = true;
        //вектор для записи результата обхода
        vector<int> SaveVertices;
        //пока стек не пуст
        while (!nodeStack.empty()) {
            //вытаскиваем вершину стека
            int currentNode = nodeStack.top();
            nodeStack.pop();
            //сохраняем 
            SaveVertices.push_back(currentNode);
            //cout << currentNode << " ";
            // Просматриваем все смежные вершины
            for (int i = 0; i < numVertices; i++) {
                // Если есть ребро между текущей вершиной и вершиной i, и вершина i еще не посещена
                if (adjacencyMatrix[currentNode][i] && !visitedVertices[i]) {
                    //добавляем вершину в стек
                    nodeStack.push(i);
                    //помечаем вершину как посещенную
                    visitedVertices[i] = true;
                }
            }
        }
        //  cout << endl;
          //возвращаем вектор на основе обхода
        return SaveVertices;
    }
    //Обход в ширину на основе кучи
    vector<T> BreadthFirst(const T& startNode) {
        //вектор контейнер посещенных вершин, изначально все false,т.к не посещены
        vector<bool> visitedVertices(numVertices, false);
        //куча для вершин, которые нужно обработать
        queue<int> nodeQueue;
        //добавляем в кучу начальную вершину
        nodeQueue.push(startNode);
        //помещаем в посещенные вершины
        visitedVertices[startNode] = true;
        //вектор для записи результата обхода
        vector<int> SaveVertices;
        //пока куча не пуста
        while (!nodeQueue.empty()) {
            //вытаскиваем вершину
            int currentNode = nodeQueue.front();
            nodeQueue.pop();
            //сохраняем
            SaveVertices.push_back(currentNode);
            //cout << currentNode << " ";
            // Просматриваем все смежные вершины
            for (int i = 0; i < numVertices; i++) {
                // Если есть ребро между текущей вершиной и вершиной i, и вершина i еще не посещена
                if (adjacencyMatrix[currentNode][i] && !visitedVertices[i]) {
                    //добавляем вершину в кучу
                    nodeQueue.push(i);
                    //помечаем вершину как посещенную
                    visitedVertices[i] = true;
                }
            }
        }
        //cout << endl;
        //возвращаем вектор на основе обхода
        return  SaveVertices;
    }

    // поиск индекса вершины в векторе vertices по значению
    int findVertexIndex(const T& vertex) {
        //проходим по вектору
        for (int i = 0; i < numVertices; i++) {
            //сравниваем с каждым элементом
            if (vertices[i] == vertex) {
                //возвращаем индекс вершины
                return i;
            }
        }
        //возвращаем -1 
        return -1;
    }
    //Алгоритм Дейкстры
    //поиск кратчайшего пути от начальной вершины startNode до всех остальных вершин в графе
    void dijkstrasAlgorithm(const T& startNode) {
        //присваиваем следующие значения: расстояние = "бесконечность", посещено = "не посещено"//
        vector<int> distance(numVertices, numeric_limits<int>::max()); // Расстояния от начальной вершины до остальных
        vector<bool> visited(numVertices, false); // Посещенные вершины

        // Находим индекс начальной вершины,чтобы правильно задать путь до нее( в ноль)
        int startIndex = findVertexIndex(startNode);
        if (startIndex == -1) {
            // Начальная вершина не найдена
            return;
        }

        // Расстояние от начальной вершины до нее самой равно 0
        distance[startIndex] = 0;

        //выполняем нужное количество итераций, пока узел достижим и не посещен
        while (startIndex != -1) {
            // Для соседних вершин сравниваем предварительное и заданное расстояние
            for (int i = 0; i < numVertices; i++) {
                //получаем вес ребра между текущей вершиной и соседней i
                int weight = getWeight(startIndex, i);
                //если вес не равен 0 и вершина не посещена и новый путь через текущую вершину короче текущего расстояния до вершины i
                if (weight != 0 && !visited[i] && (weight + distance[startIndex] < distance[i])) {
                    //расстояние обновляется на новую длину пути
                    distance[i] = weight + distance[startIndex];
                }
            }

            // Отмечаем текущую вершину как "посещенную" и выбираем следующую
            visited[startIndex] = true;
            startIndex = -1;
            int mindistance = numeric_limits<int>::max();
            for (int i = 0; i < numVertices; i++) {
                //поиск следующей непосещенной вершины
                if (!visited[i] && distance[i] < mindistance) {
                    //установление индекса новой текущей вершины
                    startIndex = i;
                    //текущее минимальное расстояние = расстояниею до выбранной вершины
                    mindistance = distance[i];
                }
            }
        }

        // Выводим результаты
        for (int i = 0; i < numVertices; i++) {
            cout << "Кратчайшее расстояние от вершины " << startNode << " до вершины "
                << vertices[i] << ": ";
            if (distance[i] == numeric_limits<int>::max()) {
                cout << "нет пути" << endl;
            }
            else {
                cout << distance[i] << endl;
            }
        }
    }

    // https://medium.com/nuances-of-programming/%D0%B3%D1%80%D0%B0%D1%84%D1%8B-%D0%B8-%D0%BF%D1%83%D1%82%D0%B8-%D0%B0%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC-%D0%B4%D0%B5%D0%B9%D0%BA%D1%81%D1%82%D1%80%D1%8B-fa0b404c3a85
        //деструктор
    ~WeightedGraph() {
        // Освобождаем память, выделенную для массива вершин
      //  delete[] vertices;

        // Освобождаем память, выделенную для матрицы смежности
        for (int i = 0; i < numVertices; i++) {
            delete[] adjacencyMatrix[i];
        }
        delete[] adjacencyMatrix;
    }
};
