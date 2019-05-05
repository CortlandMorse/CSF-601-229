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

//parse input (without scanf because i hate it)
vector<ulli> get_input() {
  string instr; string branch; string flag;
  vector<ulli> out;
  while (cin >> instr) {
    cin >> branch;
    cin >> flag;
    //convert this shit to numbers
    ulli i = stoll(instr,nullptr,16);
    ulli b = stoll(branch,nullptr,16);
    ulli f = 0;
    if (!flag.compare("T")) {//flag is 1 if taken, 0 if not
      f = 1;
    }
    //put it all in
    out.push_back(i);
    out.push_back(b);
    out.push_back(f);
  }

  return out;
}

//return result of sta check
my_tup ret_sta(vector<ulli> vect) {
  my_tup out;
  out = make_tuple(0,0,0);
  for (unsigned int i = 0; i < vect.size(); i+=3) {
    ulli instr = vect[i];
    ulli branch = vect[i+1];
    int taken = (int)vect[i+2];
    int predict = branch < instr;
    if (predict == taken) {
      get<0>(out)++;
    } else {
      get<1>(out)++;
    }
  }

  return out;
}

//i love you
my_tup ret_bah(vector<ulli> vect) {
  my_tup out;
  out = make_tuple(0,0,0);
  vector<int> hash_table(1024,0);
  vector<coll_tup> coll_check;
  //initialize collision checker
  for (int i = 0; i < 1024; i++) {
    coll_check.push_back(make_tuple(0,0));
  }

  //iterate thru input
  for (unsigned int i = 0; i < vect.size(); i+=3) {
    ulli instr = vect[i];
    ulli branch = vect[i+1];
    int flag = (int)vect[i+2];
    int hash_val = instr%1024;
    ulli instr_coll = get<0>(coll_check[hash_val]);
    ulli branch_coll = get<1>(coll_check[hash_val]);
    if ((instr != instr_coll) || (branch != branch_coll)) {
      get<2>(out)++;
    } else if (flag == hash_table[hash_val]) {
      get<0>(out)++;
    } else {
      get<1>(out)++;
    }

    hash_table[hash_val] = flag;
    get<0>(coll_check[hash_val]) = instr;
    get<1>(coll_check[hash_val]) = branch;
  }

  return out;
}

//i love you
my_tup ret_tah(vector<ulli> vect) {
  my_tup out;
  out = make_tuple(0,0,0);
  vector<int> hash_table(1024,0);
  vector<coll_tup> coll_check;
  //initialize collision checker
  for (int i = 0; i < 1024; i++) {
    coll_check.push_back(make_tuple(0,0));
  }

  //iterate thru input
  for (unsigned int i = 0; i < vect.size(); i+=3) {
    ulli instr = vect[i];
    ulli branch = vect[i+1];
    int flag = (int)vect[i+2];
    int hash_val = branch%1024;
    ulli instr_coll = get<0>(coll_check[hash_val]);
    ulli branch_coll = get<1>(coll_check[hash_val]);
    if ((instr != instr_coll) || (branch != branch_coll)) {
      get<2>(out)++;
    } else if (flag == hash_table[hash_val]) {
      get<0>(out)++;
    } else {
      get<1>(out)++;
    }

    hash_table[hash_val] = flag;
    get<0>(coll_check[hash_val]) = instr;
    get<1>(coll_check[hash_val]) = branch;
  }

  return out;
}

//i love you
my_tup ret_bta(vector<ulli> vect) {
  my_tup out;
  out = make_tuple(0,0,0);
  vector<int> hash_table(1024,0);
  vector<coll_tup> coll_check;
  //initialize collision checker
  for (int i = 0; i < 1024; i++) {
    coll_check.push_back(make_tuple(0,0));
  }

  //iterate thru input
  for (unsigned int i = 0; i < vect.size(); i+=3) {
    ulli instr = vect[i];
    ulli branch = vect[i+1];
    int flag = (int)vect[i+2];
    int hash_val = ((branch%32)*32) + instr%32;
    ulli instr_coll = get<0>(coll_check[hash_val]);
    ulli branch_coll = get<1>(coll_check[hash_val]);
    if ((instr != instr_coll) || (branch != branch_coll)) {
      get<2>(out)++;
    } else if (flag == hash_table[hash_val]) {
      get<0>(out)++;
    } else {
      get<1>(out)++;
    }

    hash_table[hash_val] = flag;
    get<0>(coll_check[hash_val]) = instr;
    get<1>(coll_check[hash_val]) = branch;
  }

  return out;
}

//i love you
my_tup ret_col(vector<ulli> vect) {
  my_tup out;
  out = make_tuple(0,0,0);
  vector<int> hash_table(1024,0);
  vector<coll_tup> coll_check;
  //initialize collision checker
  for (int i = 0; i < 1024; i++) {
    coll_check.push_back(make_tuple(0,0));
  }

  //iterate thru input
  for (unsigned int i = 0; i < vect.size(); i+=3) {
    ulli instr = vect[i];
    ulli branch = vect[i+1];
    int flag = (int)vect[i+2];
    int hash_val = instr%1024;
    ulli instr_coll = get<0>(coll_check[hash_val]);
    if ((instr != instr_coll)) {
      int sta_check = branch < instr;
      if (sta_check == flag) {
        get<0>(out)++;
      } else {
        get<1>(out)++;
      }
    } else if (flag == hash_table[hash_val]) {
      get<0>(out)++;
    } else {
      get<1>(out)++;
    }

    hash_table[hash_val] = flag;
    get<0>(coll_check[hash_val]) = instr;
    get<1>(coll_check[hash_val]) = branch;
  }

  return out;
}

//i love you
my_tup ret_sat(vector<ulli> vect) {
  my_tup out;
  out = make_tuple(0,0,0);
  vector<int> hash_table(1024,0);
  vector<coll_tup> coll_check;
  //initialize collision checker
  for (int i = 0; i < 1024; i++) {
    coll_check.push_back(make_tuple(0,0));
  }

  //iterate thru input
  for (unsigned int i = 0; i < vect.size(); i+=3) {
    ulli instr = vect[i];
    ulli branch = vect[i+1];
    int flag = (int)vect[i+2];
    int hash_val = instr%1024;
    ulli instr_coll = get<0>(coll_check[hash_val]);
    ulli branch_coll = get<1>(coll_check[hash_val]);
    if ((instr != instr_coll) || (branch != branch_coll)) {
      get<2>(out)++;
    } else if (((flag)&&(hash_table[hash_val] >= 2))
      || ((!flag)&&(hash_table[hash_val] < 2))) {
      get<0>(out)++;
    } else {
      get<1>(out)++;
    }

    if ((flag) && (hash_table[hash_val] < 3)) {
      hash_table[hash_val]++;
    } else if ((!flag) && (hash_table[hash_val] > 0)) {
      hash_table[hash_val]--;
    }

    get<0>(coll_check[hash_val]) = instr;
    get<1>(coll_check[hash_val]) = branch;
  }

  return out;
}

//i love you
my_tup ret_two(vector<ulli> vect) {
  my_tup out;
  out = make_tuple(0,0,0);
  vector<int> hash_table(1024,0);
  vector<coll_tup> coll_check;
  vector<int> predict_table(32,0);
  //initialize collision checker
  for (int i = 0; i < 1024; i++) {
    coll_check.push_back(make_tuple(0,0));
  }

  //iterate thru input
  for (unsigned int i = 0; i < vect.size(); i+=3) {
    ulli instr = vect[i];
    ulli branch = vect[i+1];
    int flag = (int)vect[i+2];
    int hash_val = instr%1024;
    int predict = predict_table[hash_table[hash_val]];
    ulli instr_coll = get<0>(coll_check[hash_val]);
    ulli branch_coll = get<1>(coll_check[hash_val]);
    if ((instr != instr_coll) || (branch != branch_coll)) {
      get<2>(out)++;
    } else if (flag == predict) {
      get<0>(out)++;
    } else {
      get<1>(out)++;
    }

    predict_table[hash_table[hash_val]] = flag;
    int shift_val = hash_table[hash_val];
    hash_table[hash_val] = ((shift_val << 1)&31) + flag;
    get<0>(coll_check[hash_val]) = instr;
    get<1>(coll_check[hash_val]) = branch;
  }

  return out;
}

//main function
int main() {

  //i like my input parsed
  vector<ulli> input = get_input();

  //call the branch predictors
  my_tup sta = ret_sta(input);
  my_tup bah = ret_bah(input);
  my_tup tah = ret_tah(input);
  my_tup bta = ret_bta(input);
  my_tup col = ret_col(input);
  my_tup sat = ret_sat(input);
  my_tup two = ret_two(input);

  //debug hell
  //hell has frozen over
  //end debug hell

  //i said i wouldnt use scanf but you gave me the code
  printf("STA: %20llu %20llu %20llu\n",get<0>(sta),get<1>(sta),get<2>(sta));
  printf("BAH: %20llu %20llu %20llu\n",get<0>(bah),get<1>(bah),get<2>(bah));
  printf("TAH: %20llu %20llu %20llu\n",get<0>(tah),get<1>(tah),get<2>(tah));
  printf("BTA: %20llu %20llu %20llu\n",get<0>(bta),get<1>(bta),get<2>(bta));
  printf("COL: %20llu %20llu %20llu\n",get<0>(col),get<1>(col),get<2>(col));
  printf("SAT: %20llu %20llu %20llu\n",get<0>(sat),get<1>(sat),get<2>(sat));
  printf("TWO: %20llu %20llu %20llu\n",get<0>(two),get<1>(two),get<2>(two));

  return 0;
}
