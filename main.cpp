#include <iostream>
#include "funcLib.h"
#include <string>
#include <fstream>// ������ � �������
#include <stack>

using namespace std;

string flags[3]={"--forward","--file","--reverse"};

int main(int argc, char* argv[]){

    //���� ��������� ������� � ������ ������
    setlocale(LC_ALL, "Russian");
    int rej=0,source=0;//0 - inverse 1-forward; 0-console 1-file
    if (argc==1){
        cout<<"����������� ������: ����������� �����\n ������������� ��������� � ������� ��������������� �����";
        return 0;
    }
    for (int i=1;i<argc;i++){//���� ������������� ����� ������ � ������ ����� ���������
        string elem=argv[i];
        if (!(isInMassStr(elem,flags,3))){
            cout<<"����������� ������: ������������ ����\n ������������� ��������� � ������� ���������� �����";
            return 0;
        }
        if(elem==flags[0]){
            rej+=1;
            continue;
        }
        if(elem==flags[1]){
            source+=1;
            continue;
        }
    }
    cout<<"������� ������ ��� �������� �����(���� ������ ���� --file) :\n";
    //���� ��������� ������� � ������ ������

    //���� ������
    string data,file;
    if(source==0){
        getline(cin, data);
    }
    if (source==1){
        getline(cin, file);
        data=readFromFile(file);
        if (data=="Error"){
            cout<<"����������� ������ : �� ������� ������� ����, ��������� ������������ ����� � ������������� ���������";
            return 0;
        }
    }
    //������� ������ � ����
    stack <double> stackOfNums;
    stack <char> stackOfOp;
    if (rej==1){
        int checker=straightStack(stackOfNums,stackOfOp,&data);
        if (checker){
            return 0;
        }
        else{
            cout<<"�����: "<<stackOfNums.top()<<"\n";
        }
    }
    else{
        int checker=revrseStack(stackOfNums,stackOfOp,&data);
        if (checker){
            return 0;
        }
        else{
            cout<<"�����: "<<stackOfNums.top()<<"\n";
        }
    }
    //������� ������ � ����
    //���� ������
    return 0;
}
