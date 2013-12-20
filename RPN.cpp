#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <cctype>
#include <vector>
#include <stdlib.h>


using namespace std;

/*
 *  global variables
 */
int error_flag = 0;
int dot_flag = 0;
vector <double> operands;
string queue = "";

/*
 *  functions
 */
void
serror()
{
  cout << "SYNTAX ERROR" << endl;
  error_flag = 0;
  dot_flag = 0;
  queue = "";
  operands.clear();
}

void
qtov()
{
  double fraction=0.0;
  double entire=0.0;
  char *temp;

  if (queue.size() != 0) {
    if (dot_flag)
      queue = queue+'0';
    strcpy(temp, queue.c_str());
    operands.push_back(strtod(temp, NULL));
    printf("temp: %s\n", temp);
    dot_flag = 0;
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
  double operand_I, operand_II, temp_result;
  // int end_of_queue = 0;

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
      // if (queue.size() != 1)
      //   break;
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
        queue = queue+character;
        // printf("%s\n", queue.c_str());
        dot_flag = 1;
      }
      continue;
    }

    /* space */
    if (isspace(character)) {
      qtov();
      continue;
    }

    /* number */
    if (isdigit(character)) {
      queue = queue+character;
      continue;
    }

    if (error_flag)
      continue;
    if (operands.size() < 2) {
      error_flag = 1;
      continue;
    }
    /* operations and other */
    switch (character) {
      case '+':
      case '-':
      case '*':
      case '/':
        qtov();
        operand_II = operands.back();
        operands.pop_back();
        operand_I = operands.back();
        operands.pop_back();
        switch (character) {
          case '+':
            temp_result = operand_I + operand_II;
            break;
          case '-':
            temp_result = operand_I - operand_II;
            break;
          case '*':
            temp_result = operand_I * operand_II;
            break;
          case '/':
            temp_result = operand_I / operand_II;
            break;
        }
        cout << operand_I << " "<< operand_II << " " << temp_result << endl;
        operands.push_back(temp_result);
        break;

      default:
        error_flag = 1;
        break;
    }
  }

  input.close();

  return 0;
  }