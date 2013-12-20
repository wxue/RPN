#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <fstream>
#include <cctype>
#include <vector>


using namespace std;

/*
 *  global variables
 */
int error_flag = 0;
int dot_flag = 0;
vector <double> operands;
string queue;

/*
 *  functions
 */
void
serror()
{
  cout << "SYNTAX ERROR" << endl;
  error_flag = 0;
}

void
qtov()
{
  double fraction=0.0;
  double entire=0.0;

  if (queue.size() != 0) {
    if (!dot_flag)
      operands.push_back(double(atoi(queue)));
    else {  // dot_flag = 1
      fraction = double(atoi(queue));
      fraction = fraction/(queue.size()*10);
      entire = operands.back() + fraction;
      operands.pop_back();
      operands.push_back(entire);
    }
  }
  queue = "";
}

/*
 *  MAIN
 */
int 
main() 
{
  string location;
  char character;
  queue="";
  double operand_I, operand_II, temp_result;

  /* read input file into the queue */
  cout << "Please locate your input text file: " << endl;
  cin >> location;

  ifstream input (location);
  if (input.fail()) {
    cout << "Failed to open the input file" << endl;
    return 1;
  }

  while (!input.eof()) {
    input.get(character);

    /* meet the end of a queue and output the result/error */
    if (input.eof() || character == '\n') {
      qtov();
      if ((operands.size() > 1) || error_flag == 1)
        serror();
      else {
        cout << operands.back() << endl;
        operands.clear();
      }
      continue;
    }

    /* dot */
    if (character == '.') {
      if (dot_flag)
        error_flag = 1;
      else {
        qtov();
        dot_flag = 1;
      }
      input.get(character);
    }

    /* space */
    if (isspace(character)) {
      qtov();
      input.get(character);
    }

    /* number */
    if (!dot_flag && isdigit(character)) {
      queue = queue+character;
    }

    /* operations and other */
    switch (character) {
      case '+':
        if (error_flag)
          break;
        if (operands.size() < 2) {
          error_flag = 1;
          break;
        }
        operand_II = operands.back();
        operands.pop_back();
        operand_I = operands.back();
        operands.pop_back();
        temp_result = operand_I + operand_II;
        operands.push_back(temp_result);
        break;

      default:
        serror();
    }
  }

  input.close();

  return 0;
  }