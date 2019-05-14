#include <iostream>
#include <string>

void prefix(std::string pat, int* pi){
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

void kmp(std::string pat, std::string text, int* pi, int pat_len){
  prefix(pat, pi);
  int i = 0, j = pi[pat.length() - 1];
  while (j <= pat_len){
    if (text[i] == pat[j]){
      i++;
      j++;
    }
    if (j == pat_len){
      int dif;
      dif = pat_len - i;
      std::cout << text.length() - dif << std::endl;
      return;
    }
    else if (text[i] != pat[j]){
      break;
    }
  }
  std::cout << "-1" << std::endl;
}

int main(){
  std::string pat, text;
  std::cin >> text >> pat;
  int pat_len = pat.length();
  pat = pat + '$' + text;
  int* pi = new int[pat.length()];
  if(pat_len > text.length())
    std::cout << "-1" << std::endl;
  else
    kmp(pat, text, pi, pat_len);
  delete [] pi;
  return 0;
}
