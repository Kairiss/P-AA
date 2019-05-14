#include <iostream>
#include <string>
#include <vector>

void prefix(std::string pat, int* pi) {
  pi[0] = 0;
  int l = 0;
  for (int i = 1; i < pat.length();){
    if (pat[i] == pat[l]){
      pi[i] = l+1;
      i++;
      l++;
    }
    else{
      if (l != 0)
        l = pi[l - 1];
      else{
        pi[i] = l;
        i++;
      }
    }
  }
}

void kmp(std::string pat, std::string text, int* pi){
  prefix(pat, pi);
  vector <int> answer;
  int i = 0, j = 0;
  while (i < text.length()){
    if (text[i] == pat[j]){
      i++;
      j++;
    }
    if (j == pat.length()){
      answer.push_back(i - j);
      j = pi[j - 1];
    }
    else if (text[i] != pat[j]){
      if (j != 0)
        j = pi[j - 1];
        else
          i++;
    }
  }
  if (answer.empty())
    std::cout << "-1";
  else
    for (int m = 0; m < answer.size(); m++){
      std::cout << answer[m];
      if (m != answer.size() - 1)
        std::cout << ',';
    }
  std::cout << endl;
}

int main(){
  std::string pat, text;
  std::cin >> pat >> text;
  int pi[pat.length()];
  if (pat.length() > text.length())
    std::cout << "-1" << endl;
  else
    kmp(pat, txt, pi);
  return 0;
}
