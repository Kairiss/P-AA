#include <iostream>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <limits>
using namespace std;

class Flow{
private:
  map <char, map<char, int>> graph;
  char u;
  char v;
public:
  Flow(){}

  void read(){
    char a, b;
    int n, w;
    cin >> n >> u >> v;
    for(int i = 0; i < n; i++){
      cin >> a >> b >> w;
      graph[a][b] = w;
    }
    maxFlow(u, v);
  }

  map <char, pair <char, int>> find_way(map <char, map <char, int>> m, char start, char finish){
    map <char, pair<char, int>> way;
    map <char, bool> visited;
    vector <char> path; //переименовать стек
    typename map<char, map<char, int>>::iterator it;
    typename map<char, map<char, int>>::iterator t;
    for (it = m.begin(); it != m.end(); it++)
      visited[it->first] = false;
    path.push_back(start);
    it = graph.begin();
    for ( ; it != m.end(); it++){
      if (path[path.size() - 1] == finish)
        break;
      visited[path[path.size()-1]] = true;
      vector <pair<char, int>> neighborhood;
      for (pair <char, int> neighbor: m.find(path[path.size()-1])->second)
        if (!visited[neighbor.first])
          neighborhood.push_back(neighbor);
        if (neighborhood.empty()){
          if (way.size() == 1 || way.empty()){
            way.clear();
            return way;
          }
          way.erase(path[path.size()-1]);
          path.pop_back();
          continue;
        }
        pair <char, int> max = *max_element(neighborhood.begin(), neighborhood.end(), [](pair<char, int>& n1, pair<char, int>& n2){
          return  n1.second < n2.second;
        });//находит набольший вес дуг
        way[path[path.size()-1]] = pair<char, int>(max.first, max.second);
        path.push_back(max.first);
    }
    return way;
  }

  int get_min_flow(map<char, pair<char, int>> way){
    auto t = way.begin();
    int min_flow = t->second.second;
    for (; t != way.end(); t++){
      if (min_flow > t->second.second)
        min_flow = t->second.second;
    }
    return min_flow;
  }

  void change(map<char, map<char, int>> & network, map<char, pair<char, int>> way){
    int min_flow = min_flow(way);
    for (auto t = way.begin(); t!=way.end(); t++){
      if (t->second.second - min_flow == 0)
        network[t->first].erase(t->second.first);
      else
        network[t->first][t->second.first] -= min_flow;
      network[t->second.first][t->first] += min_flow;
    }
  }

  void maxFlow(char source, char drain){
    map<char, map<char, int>> network = graph;
    map<char, pair<char, int>> way = find_way(network, source, drain);
    while (!way.empty()){
      change(network, way);
      way = find_way(network, source, drain);
    }
    int max_flow = 0;
    for_each(graph[source].begin(), graph[source].end(), [&max_flow, &network, source](pair<char, int> neighbor){
      max_flow += neighbor.second - network[source][neighbor.first];
    });
    cout << max_flow << endl;
    for_each(graph.begin(), graph.end(), [&network](pair<char, map<char, int>> neighbors){
      for_each(neighbors.second.begin(), neighbors.second.end(), [&network, neighbors](pair<char, int> ver){
        std::cout << neighbors.first << " " << ver.first << " ";
        if (ver.second - network[neighbors.first][ver.first] >= 0)
         cout << ver.second - network[neighbors.first][ver.first] << endl;
        else
          cout << 0 << endl;
      });
    });
  }
};

int main(){
  Flow a;
  a.read();
  return 0;
}
