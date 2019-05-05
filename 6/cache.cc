#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <tuple>
#include <stdio.h>

//im a man of convenience
using std::string; using std::cin;
using std::cout; using std::vector;
using std::tuple; using std::get;
using std::make_tuple;

typedef unsigned long long int ulli;//way too damn long
typedef tuple<ulli,ulli,ulli> my_tup;//im lazy what can i say
typedef tuple<ulli,ulli> coll_tup;//goes in collision checker

//reads input from stdin, puts into vector
vector<ulli> get_input() {
  string address; string flag;
  vector<ulli> out;
  while(cin >> address) {
    cin >> flag;
    ulli a = stoll(address,nullptr,16);
    ulli f = 0;
    if (!flag.compare("S")) {
      f = 1;
    }

    out.push_back(a);
    out.push_back(f);
  }

  return out;
}

int main() {
  vector<ulli> input = get_input();

  for (int i = 0; i < input.size(); i++) {
    cout << input[i] << " ";
  }
  cout << "\n";

  return 0;
}
