#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

using std::cin; using std::vector;
using std::cout; using std::pair;
using std::string;

//takes stdin and puts byte values into a vector
vector<int> stdin_vector(vector<int> &vect) {
  char byte;//get works best with chars
  while (cin.get(byte) && cin.good()) {
    int val = reinterpret_cast<unsigned char&>(byte);//turn unisgned
    vect.push_back(val);
  }

  return vect;
}

//takes file and puts byte values into a vector
vector<int> filein_vector(vector<int> &vect, string fn) {
  std::ifstream bytes;
  bytes.open(fn);

  if (!bytes) {//returns -1 if file can't be opened
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

//optional, prints memory to file
int fileout_mem(vector<int> &vect, string fn) {
  std::ofstream OutFile;
  OutFile.open(fn, std::ios::out | std::ios::binary);
  if ((OutFile.rdstate()& std::ofstream::failbit) != 0) {
    return 1;
  }

  for (unsigned int i = 0; i < vect.size(); i++) {
    int val = vect[i]%256;
    OutFile << (unsigned char)val;
  }

  OutFile.close();

  return 0;
}

//prints the error message
void err_msg(int error) {
  cout << "ERROR: ";
  switch(error) {
    case 1:
      cout << "The wrong number of arguments were given.(1)\n";
      break;
    case 2:
      cout << "The input file cannot be opened or cannot be read.(2)\n";
      break;
    case 3:
      cout << "The output file cannot be opened or cannot be written.(3)\n";
      break;
    case 4:
      cout << "The program is too large.(4)\n";
      break;
    case 5:
      cout << "An invalid op-code was encountered.(5)\n";
      break;
    case 6:
      cout << "An invalid argument was encountered.(6)\n";
      break;
    case 7:
      cout << "An invalid label was encountered.(7)\n";
      break;
    case 8:
      cout << "There was an unresolved reference.(8)\n";
      break;
    case 9:
      cout << "Memory allocation error.(9)\n";
      break;

  }
}

//returns mem value as a pair
pair<int,int> upp_low(int val) {
  int low = val%16;
  int upp = (val/16)%16;
  return std::make_pair(upp,low);
}

//returns true if instruction has arg
bool arg_bool(int val) {
  if (val > 0 && val < 240) {
    return true;
  }
  return false;
}

//returns the mnemonic for the instruction
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

//workaround for switch statement
int mnemonic_int(int upp, int low) {
  if ((upp == 0)&&(low==0)) {
    return 0;
  } else if (upp == 0) {
    return 1;
  } else if (upp == 15) {
    return low+16;
  }

  return upp+1;
}

//the actual scram simulator
vector<string> scram_sim(vector<int> &mem, int &error) {

  //used for char conversion
  vector<string> h2c {"0","1","2","3","4","5",
    "6","7","8","9","A","B","C","D","E","F"};
  vector<string> out;
  int len = mem.size();
  if (len > 255) {
    len = 255;
  }

  int pc = 0;//program counter
  int acc = 0;//accumulator
  int c = 0;//carry out
  int ext = 0;//used for ext
  int extlast = 0;//used to reset ext
  bool hlt = false;//true when sim is over
  while (!hlt) {
    if (pc > len) {//if attempting to execute past length
      error = 4;//error code
      return out;
    }
    int ind = 0;
    int address = pc;
    int val = mem[pc];
    pair<int,int> instr = upp_low(val);
    int upp = instr.first;
    int low = instr.second;
    string mne = mnemonic(upp,low);
    if (ext == extlast) {
      ext = 0;//resetting ext
    }
    extlast = ext;
    int pos = mnemonic_int(upp,low);

    switch(pos) {
      case 0://hlt
        hlt = true;
        error = 0;
        break;
      case 1://ext
        ext = low;
        break;
      case 2://lda
        ind = ext*16+low;
        if (ind > len) {
          error = 5;
          return out;
        }
        acc = mem[ind];
        break;
      case 3://ldi
        ind = ext*16+low;
        if (ind > len) {
          error = 5;
          return out;
        }
        ind = mem[ind];
        if (ind > len) {
          error = 5;
          return out;
        }
        acc = mem[ind];
        break;
      case 4://sta
        ind = ext*16+low;
        if (ind > len) {
          error = 6;
          return out;
        }
        mem[ind] = acc;
        break;
      case 5://sti
        ind = ext*16+low;
        if (ind > len) {
          error = 5;
          return out;
        }
        ind = mem[ind];
        if (ind > len) {
          error = 6;
          return out;
        }
        mem[ind] = acc;
        break;
      case 6://add
        ind = ext*16+low;
        if (ind > len) {
          error = 5;
          return out;
        }
        acc = acc + mem[ind];
        if (acc > 256) {
          acc = acc%256;
          c = 1;
        }
        break;
      case 7://sub
        ind = ext*16+low;
        if (ind > len) {
          error = 5;
          return out;
        }
        if (acc > 256 || acc < 0) {
          acc = acc%256;
          c = 1;
        }
        acc = acc - mem[ind];

        break;
      case 8://jmp
        ind = ext*16+low;
        if (ind > len-1) {
          error = 5;
          return out;
        }
        pc = ind-1;
        break;
      case 9://jmz
        if (acc != 0) break;
        ind = ext*16+low;
        if (ind > len) {
          error = 5;
          return out;
        }
        pc = ind-1;
        break;
      case 10://and
        ind = ext*16+low;
        if (ind > len) {
          error = 5;
          return out;
        }
        acc = acc&mem[ind];
        break;
      case 11://ior
        ind = ext*16+low;
        if (ind > len) {
          error = 5;
          return out;
        }
        acc = acc|mem[ind];
        break;
      case 12://xor
        ind = ext*16+low;
        if (ind > len) {
          error = 5;
          return out;
        }
        acc = acc^mem[ind];
        break;
      case 13://adl
        acc = acc+low*16;
        if (acc > 256) {
          acc = acc%256;
          c = 1;
        }
        break;
      case 14://adc
        ind = ext*16+low;
        if (ind > len) {
          error = 5;
          return out;
        }
        acc = acc + mem[ind]+c;
        if (acc > 256) {
          acc = acc%256;
          c = 1;
        }
        break;
      case 15://sbb
        ind = ext*16+low;
        if (ind > len) {
          error = 5;
          return out;
        }
        acc = acc + (-1*mem[ind])-1 + c;
        if (acc > 256 || acc < 0) {
          acc = acc%256;
          c = 1;
        }
        break;
      case 16://neg
        acc = -1*acc;
        break;
      case 17://com
        acc = -1*acc-1;
        break;
      case 19://clr
        acc = 0;
        break;
      case 20://set
        acc = 255;
        break;
      case 21://rtl
        acc = (acc<<1)|((acc>>7)&255);
        break;
      case 22://rtr
        acc = (acc<<7)|((acc>>1)&255);
        break;
      case 23://lsl
        acc = (acc<<1)&254;
        break;
      case 24://lsr
        acc = (acc>>1)&127;
        break;
      case 25://asr
        acc = ((acc>>1)&127)|(acc&128);
        break;
      case 26://tst
        if (acc != 0) {
          acc = 1;
        }
        break;
      case 27://clc
        c = 0;
        break;
      case 28://sec
        c = 1;
        break;
      case 29://tca
        acc = c;
        break;
      case 30://tva
        acc = 1;
        break;
      case 31://jal
        pc = acc-1;
        acc = pc+1;
        break;
      case 32://nop
        break;
    }

    pair<int,int> add_split = upp_low(address);
    string line = "";
    line = "0x" + h2c[add_split.first] +
      h2c[add_split.second] + "  " + mne;
    if (arg_bool(val)) {
      line = line + " 0x0" + h2c[low];
    } else {
      line = line + "     ";
    }
    line = line + "    ACC=0x";
    pair<int,int> acc_split = upp_low(acc);
    line = line + h2c[acc_split.first] + h2c[acc_split.second];
    out.push_back(line);
    pc++;
  }

  return out;
}

int main(int argc, char* arg[]) {
  vector<int> mem;//scram data
  if (argc == 1) {//read from stdin
    mem = stdin_vector(mem);
  } else if (argc == 2 || argc == 3) {
    mem = filein_vector(mem,arg[1]);
    if (mem[0] == -1) {//if file cannot be read
      return 2;
    }
  } else {
    return 1;
  }

  vector<string> output;//output of simulation
  int error = 1;
  output = scram_sim(mem,error);
  if (error != 0) {
    err_msg(error);
    return error;
  }

  for (unsigned int i = 0; i < output.size(); i++) {
    cout << output[i] << "\n";
  }

  if (argc == 3) {
    if (fileout_mem(mem,arg[2])) {
      return 3;
    }
  }

  return 0;
}
