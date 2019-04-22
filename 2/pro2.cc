#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

char h2c[17] = "0123456789ABCDEF";

vector<int> stdin_vector(vector<int> &vect) {
  char byte;
  while (cin.get(byte)) {
    int val = reinterpret_cast<unsigned char&>(byte);
    vect.push_back(val);
  }

  return vect;
}

vector<int> filein_vector(vector<int> &vect, string fn) {
  ifstream bytes;
  bytes.open(fn);

  if (!bytes) {
    vect.push_back(-1);
    return vect;
  }

  char byte;
  while (bytes.get(byte)){
    int val = reinterpret_cast<unsigned char&>(byte);
    vect.push_back(val);
  }

  return vect;
}

bool arg_bool(int val) {
  if (val > 0 && val < 240) {
    return true;
  }
  return false;
}

string mnemonic(int upp, int low) {
  string code[32] = {"HLT","EXT","LDA","LDI","STA","STI","ADD","SUB",
    "JMP","JMZ","AND","IOR","XOR","ADL","ADC","SBB","NEG","COM",
    "CLR","SET","RTL","RTR","LSL","LSR","ASR","TST","CLC","SEC",
    "TCA","TVA","JAL","NOP"};

  if ((upp == 0) && (low == 0)) {
    return "HLT";
  } else if (upp == 0) {
    return "EXT";
  } else if (upp == 15) {
    return code[low + 16];
  }
  return code[upp+1];
}

void print_scram(vector<int> &vect) {
  for (unsigned int i = 0; i < vect.size() && i < 256; i++) {
    int val = vect[i];
    int low = val%16;
    int upp = (val/16)%16;
    string mne = mnemonic(upp,low);
    bool arg = arg_bool(val);
    cout << "0x" << h2c[upp] << h2c[low] << "  " << mne;
    if (arg) {
      cout << " 0x" << h2c[low];
    }
    cout << "\n";
  }
}

int main(int argc, char* arg[]) {
  vector<int> hex;
  if (argc == 1) {
    hex = stdin_vector(hex);
  } else if (argc == 2) {
    hex = filein_vector(hex,arg[1]);
    if (hex[0] == -1) {
      return 2;
    }
  } else {
    return 1;
  }

  print_scram(hex);
  return 0;
}
