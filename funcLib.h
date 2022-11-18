#include <string>
#include <stack>
#include <fstream>

using namespace std;

int isNumber(char);
int isPermited(char);
int isNumber(char);
int isInMassStr(string ,string*,int);
string readFromFile(string);
int priority(char);
int mathStack(stack<double>&,stack<char>&);
int straightStack(stack<double>&,stack<char>&,string*);
int revrseStack(stack<double>&,stack<char>&,string*);
