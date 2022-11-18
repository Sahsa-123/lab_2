#include <iostream>
#include "funcLib.h"
#include <string>
#include <fstream>// работа с файлами
#include <stack>

using namespace std;

string flags[3]={"--forward","--file","--reverse"};

int main(int argc, char* argv[]){

    //блок установки режимов и чтения флагов
    setlocale(LC_ALL, "Russian");
    int rej=0,source=0;//0 - inverse 1-forward; 0-console 1-file
    if (argc==1){
        cout<<"Критическая ошибка: отсутствуют флаги\n Перезапустите программу и введите соответствующие флаги";
        return 0;
    }
    for (int i=1;i<argc;i++){//цикл устанавливает режим чтения и способ ввода уравнения
        string elem=argv[i];
        if (!(isInMassStr(elem,flags,3))){
            cout<<"Критическая ошибка: некорректный флаг\n Перезапустите программу и введите корректный флаги";
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
    cout<<"Введите пример или название файла(если выбран флаг --file) :\n";
    //блок установки режимов и чтения флагов

    //блок чтнеия
    string data,file;
    if(source==0){
        getline(cin, data);
    }
    if (source==1){
        getline(cin, file);
        data=readFromFile(file);
        if (data=="Error"){
            cout<<"Критическая ошибка : не удалось открыть файл, проверьте расположение файла и перезапустите программу";
            return 0;
        }
    }
    //подблок записи в стек
    stack <double> stackOfNums;
    stack <char> stackOfOp;
    if (rej==1){
        int checker=straightStack(stackOfNums,stackOfOp,&data);
        if (checker){
            return 0;
        }
        else{
            cout<<"Ответ: "<<stackOfNums.top()<<"\n";
        }
    }
    else{
        int checker=revrseStack(stackOfNums,stackOfOp,&data);
        if (checker){
            return 0;
        }
        else{
            cout<<"Ответ: "<<stackOfNums.top()<<"\n";
        }
    }
    //подблок записи в стек
    //блок чтнеия
    return 0;
}
