#include <iostream>
#include <bitset>

using namespace std;

int main() {
  cout << "5: " << bitset<8>(5) << "\n";
  int shift = (5<<7)|(5>>1)&255;
  cout << shift << ": " << bitset<8>(shift)  << "\n";
}
