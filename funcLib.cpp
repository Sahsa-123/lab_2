#include "funcLib.h"
#include <string>
#include <fstream>
#include <iostream>
#include <stack>
#include <cmath>

using namespace std;

int isNumber(char a){
    if (('0'<=a && a<='9'))return 1;
    return 0;
}

int isPermited(char a){
    if (isNumber(a)||a=='/'||a=='*'||a=='+'||a=='-'|| a=='.'||a==','||a=='('||a==')')return 1;
    return 0;
}
int isInMassStr(string a,string *mass,int len){
    for (int i=0;i<len;i++){
        if(a==mass[i]) return 1;
    }
    return 0;
}
string readFromFile(string name){
    ifstream file;
    file.open(name);
    if (!file.is_open())return "Error";
    string data;
    getline(file,data);
    file.close();
    return data;
}

int priority(char a){
    if (a=='+' || a=='-')return 1;
    else if (a=='*' || a=='/')return 2;
    return 0;
}

int mathStack(stack<double> &nums,stack<char> &ops){
    double a=nums.top();
    nums.pop();
    switch(ops.top()){
        case '+':{
            double b=nums.top();
            nums.pop();
            ops.pop();
            //cout<<b<<"+"<<a<<"\n";
            double c=floor((b+a)*10000.0)/10000.0;
            nums.push(c);
            break;}
        case '-':{
            double b=nums.top();
            //cout<<b<<"-"<<a<<"\n";
            nums.pop();
            ops.pop();
            double c=floor((b-a)*10000.0)/10000.0;
            nums.push(c);
            break;}
        case '*':{
            double b=nums.top();
            //cout<<b<<"*"<<a<<"\n";
            nums.pop();
            ops.pop();
            double c=floor((b*a)*10000.0)/10000.0;
            nums.push(c);
            break;}
        case '/':{
            if (a==0.0){
                //cout<<"Попавсь2";
                cout<<"Error";
                return 1;
            }
            double b=nums.top();
            //cout<<b<<"/"<<a<<"\n";
            nums.pop();
            ops.pop();
            double c=floor((b/a)*10000.0)/10000.0;
            nums.push(c);
            break;}
    }
    return 0;
}

int straightStack(stack<double> &nums,stack<char> &ops,string *data){
    string primer=*(data);
    double num =0;
    int cnum=0;//считывалмя нам между элементами или нет
    int mantisa=0;
    double n=10.0;
    for (int i=0;i<primer.size();i++){
        if (!isPermited(primer[i])){
            cout<<"Error";
            return 1;
        }
        else if (isNumber(primer[i]) && mantisa==0){
            num=10*num+(int(primer[i])-48);
            cnum+=1;
            if (i+1==primer.size()){
                nums.push(num);
            }
            continue;
        }
        else if (primer[i]=='.' || primer[i]==','){
            mantisa+=1;
            cnum+=1;
            if (i+1==primer.size()){
                cout<<"в поcледнем числе отмутствует дробная часть";
                return 1;
            }
            continue;
        }
        else if (isNumber(primer[i]) && mantisa==1){
            //cout<<num<<"\n";
            //cout<<(int(primer[i])-48)/n<<"\n";
            num=num+((int(primer[i])-48)/n);
            n*=10.0;
            cnum+=1;
            if (i+1==primer.size()){
                nums.push(num);
            }
            continue;
        }
        else{
            //cout<<"Зашли \n";
            //cout<<"Добавлен"<<num<<"\n";
            //cout<<num;
            if (cnum!=0)nums.push(num);
            cnum=0;
            num=0;
            mantisa=0;
            n=10.0;
            if (ops.empty()){
                ops.push(primer[i]);
            }
            else if (priority(ops.top())<priority(primer[i])||primer[i]=='('){
                ops.push(primer[i]);
            }
            else if (priority(ops.top())>=priority(primer[i])){
                while(!ops.empty()&&priority(ops.top())>=priority(primer[i])&&ops.top()!='('){
                    if(mathStack(nums,ops)==1)return 1;
                }
                if (ops.top()=='(' && primer[i]==')')ops.pop();
                else{
                    ops.push(primer[i]);
                }
            }
            //cout<<"Добавлен"<<primer[i]<<"\n";
            continue;
        }
    }
    while (!ops.empty()){
        if(mathStack(nums,ops)==1){
            return 1;
        }
        else{
            continue;
        }
    }
    return 0;
}
int revrseStack(stack<double> &nums,stack<char> &ops,string *data){
    string primer=*(data);
    double num =0;
    int cnum=0;
    int mantisa=0;
    double n=10.0;
    for (int i=0;i<primer.size();i++){
        if (!isPermited(primer[i])&&primer[i]!=' '){
            cout<<"Error";
            return 1;
        }
        else if (isNumber(primer[i]) && mantisa==0){
            num=10*num+(int(primer[i])-48);
            cnum+=1;
            if (i+1==primer.size()){
                nums.push(num);
            }
            continue;
        }
        else if (primer[i]=='.' || primer[i]==','){
            mantisa+=1;
            cnum+=1;
            if (i+1==primer.size()){
                cout<<"в поcледнем числе отмутствует дробная часть";
                return 1;
            }
            continue;
        }
        else if (isNumber(primer[i]) && mantisa==1){
            //cout<<num<<"\n";
            //cout<<(int(primer[i])-48)/n<<"\n";
            num=num+((int(primer[i])-48)/n);
            n*=10.0;
            cnum+=1;
            if (i+1==primer.size()){
                nums.push(num);
            }
            continue;
        }
        else{
            //cout<<"Зашли \n";
            //cout<<"Добавлен"<<num<<"\n";
            //cout<<num;
            if (cnum!=0)nums.push(num);
            num=0;
            mantisa=0;
            cnum=0;
            n=10.0;
            if (primer[i]==' ')continue;
            else {
                ops.push(primer[i]);
                if(mathStack(nums,ops)==1){
                    return 1;
                }
            }
        }
    }
    return 0;
}
