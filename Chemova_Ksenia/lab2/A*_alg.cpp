#include <iostream>
#include <cstring>
#include <climits>
#include <queue>

#define N 26

typedef struct Priority {
  std::vector <int> path;
  double prior_vertex;
  double character;
} Priority;

bool operator < (const Priority &comp_var_1, const Priority &comp_var_2) {
  return comp_var_1.prior_vertex > comp_var_2.prior_vertex;
}

class A_star{
private:
  double graph[N][N];
  std::vector <int> result;
  std::vector <int> str;
public:
  A_star(int start) {
    result.push_back(start);
    for (int i = 0; i < N; i++)
      memset(graph[i], 0.0, N * sizeof(double));
  }

  ~A_star() {
    result.clear();
    str.clear();
  }

  void insert_paths(int i, int j, double path_length) { //заполнение длин путей графа
    graph[i][j] = path_length;
  }

  void print() { //вывод результата
    if (result.size() - 1) {
      for (int i = 0; i < result.size(); i++)
        std::cout << (char)(result[i] + 'a');
        std::cout << std:: endl;
      }
    else std::cout << "Пути не существует!" << std::endl;
  }

  void algorithm(int first, int finish, std:: priority_queue <Priority> &queue, double common_way, std:: vector <double> &evristic) {
    std::vector <int> check(N, 0);
    int run = 1;
    while (run) {
      for (int j = 0; j < N; j++) //проходим по всем вершинам
	       if (graph[first][j] != 0 && check[j] == 0){    //если соседи, т.е существует ребро
		        check[j] = 1;
            Priority new_elem;
            new_elem.character = evristic[j];
            new_elem.prior_vertex = graph[first][j] + common_way + new_elem.character;
            for (int i = 0; i < str.size(); i++)
              new_elem.path.push_back(str[i]);
            new_elem.path.push_back(j);
            queue.push(new_elem);
          }
      if (queue.empty())
        run = 0;
      if (!queue.empty()) {
        Priority temp;
        temp = queue.top();
        queue.pop();
        first = temp.path[temp.path.size()-1];
        str = temp.path;
        common_way = temp.prior_vertex - temp.character;
      }
      if (str[str.size() - 1] == finish) {
        for (int i = 0; i < str.size(); i++)
          result.push_back(str[i]);
        run = 0;
      }
    }
  }
};

int main() {
  char start, finish, from, to, curr;
  double path_length, evristic;
  int count = 0;
  std::vector <double> character(N, 0);
  std::cin >> start >> finish;
  std::cin >> count;
  for (int i = 0; i < count; i++) {
    std::cin >> curr >> evristic;
    if (evristic >= 0.0)
      character[curr - 'a'] = evristic;
    else {
      std::cout << "Введены неверные значения!" << std::endl;
      return 0;
    }
  }
  std::priority_queue <Priority> queue;
  A_star graph(start - 'a');
  while (std::cin >> from >> to >> path_length)
    graph.insert_paths(from - 'a', to - 'a', path_length);
  graph.algorithm(start - 'a', finish - 'a', queue, 0.0, character);
  graph.print();
  character.clear();
  return 0;
}
