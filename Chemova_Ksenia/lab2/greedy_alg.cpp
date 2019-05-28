#include <iostream>
#include <string>

class Matrix{
  int size;
  double** matrix;
  bool* mtr;
public:
  Matrix(): size(26){
    mtr = new bool [size];
    matrix = new double *[size];
    for (int i=0; i<size; i++) {
      matrix[i] = new double [size];
      for (int j=0; j<size; j++)
        matrix[i][j] = 0;
    }
  };

  void make_arc(char tmp1, char tmp2, double tmp_wt) { //создает дугу
    int i_tmp1 = static_cast<int>(tmp1)-97;
    int i_tmp2 = static_cast<int>(tmp2)-97;
    matrix[i_tmp1][i_tmp2] = tmp_wt;
  }

  void del_loop(){ //убирает петли
    for (int i=0; i<size; i++)
      matrix[i][i] = 0;
  }

  int find_min_arc(int start_tmp) { //возвращает новую вершину
    int vert = -1, i = 0, weight = 0;
    for (i = 0; i<size; i++)
      if (matrix[start_tmp][i] > 0.0 && !mtr[i]) {
        weight = matrix[start_tmp][i];
        vert = i;
        break;
      }
    for (; i<size; i++)
      if (matrix[start_tmp][i] > 0 && matrix[start_tmp][i] < weight && !mtr[i]) {
        weight = matrix[start_tmp][i];
        vert = i;
      }
    return vert;
  }

  void find_min_way(int start, int end, int prev, std::string &answer) {
    int tmp_vert;
    mtr[start] = true;
    tmp_vert = find_min_arc(start);
    answer.push_back(tmp_vert+97);
    std::cout << "tmp_vert " << tmp_vert <<'\n';
    print_mtr();
    if (tmp_vert == end)
      return;
    if (tmp_vert < 0) {
      answer.pop_back();
      answer.pop_back();
      mtr[prev] = false;
      std::cout << "mtr[prev] " << mtr[prev] << '\n';
      print_mtr();
      find_min_way(prev, end, prev, answer);
      return;
    }
    //answer.push_back(tmp_vert+97);
    find_min_way(tmp_vert, end, start, answer);
  }

  ~Matrix() {
    delete[] mtr;
    for (int i=0; i<size; i++)
      delete[] matrix[i];
    delete[] matrix;
  };

  void print_mtr() {
    std::cout << "mtr: ";
    for (int i=0; i<size; i++)
      std::cout << mtr[i];
    std::cout << '\n';
  }
};

int main(){
  Matrix matr;
  char start, end, tmp1, tmp2;
  double tmp_wt;
  std::string answer;
  std::cin >> start >> end;
  answer.push_back(start);
  int start_int = static_cast<int>(start) - 97;
  int end_int = static_cast<int>(end) - 97;
  while (std::cin >> tmp1){
    if (tmp1 == '!')
      break;
    std::cin >> tmp2 >> tmp_wt;
    matr.make_arc(tmp1, tmp2, tmp_wt);
  }
  matr.del_loop(); //убрали петли
  matr.find_min_way(start_int, end_int, start_int, answer);
  answer.push_back('\n');
  std::cout << answer;
  return 0;
}
