#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <sstream>
#include <map>

using std::cin; using std::vector;
using std::cout; using std::pair;
using std::string; using std::getline;
using std::size_t; using std::map;

//takes stdin and puts lines into a vector
vector<string> stdin_vector(vector<string> &vect) {
  string line; //line to read input
  while (getline(cin,line) && cin.good()) {
    vect.push_back(line);
  }

  return vect;
}

//optional, reads file and puts line into a vector
vector<string> filein_vector(vector<string> &vect, string fn, int &error) {
  std::ifstream lines;
  lines.open(fn);

  if (!lines) {//returns -1 if file can't be opened
    error = 2;
    return vect;
  }

  string line;
  while (getline(lines,line)){
    vect.push_back(line);
  }

  return vect;
}

//takes bin and prints to stdout
void stdout_bin(vector<int> vect, int &error) {
  for (unsigned int i = 0; i < vect.size(); i++) {
    unsigned char ch = (unsigned char)vect[i];
    cout << ch;
  }
  return;
}

//optional, prints memory to file
int fileout_bin(vector<int> vect, string fn, int &error) {
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
void error_check(int error) {
  switch(error) {
    case 0:
      break;
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

//returns value to place at location in bin
int bin_val(string instr, int good_arg, int arg_val, int &error) {
  int better_arg = 0;//to find if we can use arg for most instructions
  int better_val = 0;//value
  if ((arg_val >= -8 && arg_val <= 15)&&(good_arg == 1)) {
    better_arg = 1;
    better_val = arg_val&15;
  }
  if (!instr.compare("HLT")) {
    if (better_arg) {
      error = 6;
    }
    return 0;
  } else if (!instr.compare("EXT")) {
    if (!better_arg) {
      error = 6;
    }
    if (arg_val == 0) {
      error = 5;
    }
    return better_val;
  } else if (!instr.compare("LDA")) {
    if (!better_arg) {
      error = 6;
    }
    return better_val+16;
  } else if (!instr.compare("LDI")) {
    if (!better_arg) {
      error = 6;
    }
    return better_val+32;
  } else if (!instr.compare("STA")) {
    if (!better_arg) {
      error = 6;
    }
    return better_val+48;
  } else if (!instr.compare("STI")) {
    if (!better_arg) {
      error = 6;
    }
    return better_val+64;
  } else if (!instr.compare("ADD")) {
    if (!better_arg) {
      error = 6;
    }
    return better_val+80;
  } else if (!instr.compare("SUB")) {
    if (!better_arg) {
      error = 6;
    }
    return better_val+96;
  } else if (!instr.compare("JMP")) {
    if (!better_arg) {
      error = 6;
    }
    return better_val+112;
  } else if (!instr.compare("JMZ")) {
    if (!better_arg) {
      error = 6;
    }
    return better_val+128;
  } else if (!instr.compare("AND")) {
    if (!better_arg) {
      error = 6;
    }
    return better_val+144;
  } else if (!instr.compare("IOR")) {
    if (!better_arg) {
      error = 6;
    }
    return better_val+160;
  } else if (!instr.compare("XOR")) {
    if (!better_arg) {
      error = 6;
    }
    return better_val+176;
  } else if (!instr.compare("ADL")) {
    if (!better_arg) {
      error = 6;
    }
    return better_val+192;
  } else if (!instr.compare("ADC")) {
    if (!better_arg) {
      error = 6;
    }
    return better_val+208;
  } else if (!instr.compare("SBB")) {
    if (!better_arg) {
      error = 6;
    }
    return better_val+224;
  } else if (!instr.compare("NEG")) {
    if (good_arg) {
      error = 6;
    }
    return 240;
  } else if (!instr.compare("COM")) {
    if (good_arg) {
      error = 6;
    }
    return 241;
  } else if (!instr.compare("CLR")) {
    if (good_arg) {
      error = 6;
    }
    return 242;
  } else if (!instr.compare("SET")) {
    if (good_arg) {
      error = 6;
    }
    return 243;
  } else if (!instr.compare("RTL")) {
    if (good_arg) {
      error = 6;
    }
    return 244;
  } else if (!instr.compare("RTR")) {
    if (good_arg) {
      error = 6;
    }
    return 245;
  } else if (!instr.compare("LSL")) {
    if (good_arg) {
      error = 6;
    }
    return 246;
  } else if (!instr.compare("LSR")) {
    if (good_arg) {
      error = 6;
    }
    return 247;
  } else if (!instr.compare("ASR")) {
    if (good_arg) {
      error = 6;
    }
    return 248;
  } else if (!instr.compare("TST")) {
    if (good_arg) {
      error = 6;
    }
    return 249;
  } else if (!instr.compare("CLC")) {
    if (good_arg) {
      error = 6;
    }
    return 250;
  } else if (!instr.compare("SEC")) {
    if (good_arg) {
      error = 6;
    }
    return 251;
  } else if (!instr.compare("TCA")) {
    if (good_arg) {
      error = 6;
    }
    return 252;
  } else if (!instr.compare("TVA")) {
    if (good_arg) {
      error = 6;
    }
    return 253;
  } else if (!instr.compare("JAL")) {
    if (good_arg) {
      error = 6;
    }
    return 254;
  } else if (!instr.compare("NOP")) {
    if (good_arg) {
      error = 6;
    }
    return 255;
  }

  error = 5;
  return 0;
}

//helper function which counts # of words
int count_words(string line) {
  std::stringstream s(line);
  int count = 0;
  string word;
  while (s >> word) {
    count++;
  }

  return count;
}

//input processing
vector<string> process_inp(vector<string> inp, int &error) {
  int len = inp.size();
  vector<string> out;//output vector
  for (int i = 0; i < len; i++) {
    string line = inp[i];
    //remove the comment
    size_t comment = line.find(";");
    if (comment != string::npos) {
      line = line.substr(0,comment);
    }

    int w_count = count_words(line);
    std::stringstream s(line);

    string label_str = "";
    string instr_str = "";
    string arg_str = "";
    if (w_count == 0) {
      //do nothing
    } else if (w_count == 1) {
      if (isspace(line[0])) {
        s >> instr_str;
      } else {
        s >> label_str;
      }
    } else if (w_count == 2) {
      if (isspace(line[0])) {
        s >> instr_str;
        s >> arg_str;
      } else {
        s >> label_str;
        s >> instr_str;
      }
    } else if (w_count == 3) {
        if (isspace(line[0])) {
          error = 6;
          return out;
        }
        s >> label_str;
        s >> instr_str;
        s >> arg_str;
    } else {
      error = 7;
    }

    if (label_str.size()) {
      size_t pos = label_str.find(":");
      if (pos == string::npos) {
        error = 7;
        return out;
      }
      for (unsigned int i = 0; i < pos-1; i++) {
        if (!isalnum(label_str[i]) && (label_str[i] != '_')) {//can only be alnum
          error = 7;
          return out;
        }
      }
    }

    if (instr_str.size()) {
      if (instr_str.size() != 3) {
        error = 5;
        return out;
      }
    }

    if (arg_str.size()) {
      size_t pos = arg_str.find(".");
      if (pos != string::npos) {
        error = 6;
        return out;
      }
    }

    if (label_str.size()+instr_str.size()+arg_str.size()) {
      out.push_back(label_str);
      out.push_back(instr_str);
      out.push_back(arg_str);
    }
  }

  return out;
}

//processing to ints
vector<int> to_bin(vector<string> inp, int &error) {
  int pc = -1;//program counter
  vector<int> bin(256,0);
  map<string,int> labels;

  //reading all the labels first
  for (unsigned int i = 0; i < inp.size(); i+=3) {
    string label = inp[i];
    string instr = inp[i+1];
    string arg = inp[i+2];

    int good_arg = 0;//attempting to read arg value
    int arg_val = 0;
    if (arg.size()) {//if arg exists
      good_arg = 1;
      try {
        arg_val = stoi(arg,nullptr,0);
      } catch (const std::invalid_argument& e) {
        good_arg = 0;
      }
    }

    if (label.size()) {//attempting to read label
      if (pc < 0) {//label error check
        error = 7;
        return bin;
      }
      label = label.substr(0,label.size()-1);//label still has colon
      map<string,int>::iterator it = labels.find(label);
      if (it == labels.end()) {//if label is undeclared
        if (pc > 255) {//program too large
          error = 4;
          return bin;
        }
        labels[label] = pc;
      } else {//if label is already declared
        error = 7;
        return bin;
      }
    }

    if (instr.size()) {//reading instr
      if (!instr.compare("ORG")) {
        if (label.size()) {//check if label on ORG
          error = 7;
          return bin;
        }
        if (!(good_arg&&arg.size())) {
          error = 6;
          return bin;
        }
        pc = arg_val;
      } else if (instr.size()) {
        pc++;
      }
    }
  }

  //main bin production block
  pc = -1;
  for (unsigned int i = 0; i < inp.size(); i+=3) {
    string instr = inp[i+1];
    string arg = inp[i+2];

    int good_arg = 0;//attempting to read arg value
    int arg_val = 0;
    if (arg.size()) {//if arg exists
      good_arg = 1;
      map<string,int>::iterator it = labels.find(arg);
      if (it != labels.end()) {
        arg_val = it->second;//arg is label value
        if (!instr.compare("EXT")) {
          arg_val = ((arg_val)&240)>>4;
        } else if ((instr.compare("DAT")) && (arg_val < -8 || arg_val > 15)) {
          arg_val = arg_val&15;
        }
      } else try {
        arg_val = stoi(arg,nullptr,0);
      } catch (const std::invalid_argument& e) {
        good_arg = 0;
      }

      if (!good_arg) {//mainly for unresolved label
        arg_val = 1;
        good_arg = 1;
        int needs_arg = bin_val(instr,good_arg,arg_val,error);
        if ((!needs_arg) || (needs_arg >= 240)) {//if instr shouldnt have label
          error = 6;
          return bin;
        }
        error = 8;
        return bin;
      }
    }

    if (instr.size()) {
      if (!instr.compare("ORG")) {
        if (!arg.size()) {
          error = 6;
          return bin;
        }
        pc = arg_val;
      } else if (!instr.compare("DAT")) {
        if (!arg.size()) {
          error = 6;
          return bin;
        } else if ((arg_val < 0) || (arg_val > 255)) {
          error = 6;
          return bin;
        }
        if (pc > 255) {//program too large
          error = 4;
          return bin;
        }
        bin[pc] = arg_val;
        pc++;
      } else {
        int place = bin_val(instr,good_arg,arg_val,error);
        if (error) {
          return bin;
        }
        if (pc > 255) {//program too large
          error = 4;
          return bin;
        }
        bin[pc] = place;
        pc++;
      }
    }
  }

  return bin;
}

//main, takes 2 optional arguments (inFile,outFile)
int main(int argc, char* arg[]) {
  vector<string> inp;//scram data
  int error = 0;
  if (argc == 1) {//read from stdin
    inp = stdin_vector(inp);
  } else if (argc == 2 || argc == 3) {
    inp = filein_vector(inp,arg[1],error);
    if (error) {//if file cannot be read
      error_check(error);
      return 2;
    }
  } else {
    error_check(1);
    return 1;
  }

  //process input, seperates all words
  vector<string> inp_new = process_inp(inp,error);
  if (error) {
    error_check(error);
    return error;
  }

  //place instructions into scram
  vector<int> bin = to_bin(inp_new,error);
  if (error) {
    error_check(error);
    return error;
  }

  if (argc == 3) {//print to file
    fileout_bin(bin,arg[2],error);
  } else {//print to stdout
    stdout_bin(bin,error);
  }

  if (error) {//one last error check
    error_check(error);
    return error;
  }

  return 0;
}
