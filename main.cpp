#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Smart_string.h"

using namespace std;

int main(int argc, char* argv[]) {

    char fileName[200] = "data.txt"; // имя файла для тестирования
    char instr[200] = "Это тестовая строка для записи"; // тестовая строка

    print_label();
    cout << "Старт программы ..."
            << "Входные параметры:\n\targc = " << argc
            << endl;
    for (int i = 0; i < argc; i++) {
        cout << "\targv[" << i << "] = " << argv[i] << endl;
    }
    if (argc >= 2) {
        strcpy(fileName, argv[1]);
    }
    if (argc >= 3) {
        strcpy(instr, argv[2]);
    }
    cout << "Имя файла для чтения строк:" << fileName << endl;
    cout << "Тестовая строка:" << instr << endl;

    // это тесты того что сделано
    bool doTests = true;
    if (doTests) {
        test0();
        test1();
        test2();
        test3();
        test4();
        test5(fileName, instr);
        test6();
        test6wex();
        test7();
        // ------------------------------------
        try {
            test8(); // тут исключение и мы его перехватываем программа не слетает
        } catch (runtime_error ex) {
            cerr << ex.what() << endl;
        }
        test9(); // проверка ссылки нескольких объектов на одну сроку
        test10(); // проверка работы c_str()
    }

    SS("-------------- МИКРОПРОВЕРОЧКИ --------------").print(stdout);
    {
        const SS s0("ghghgh");
        SS s1;
        s1 = s0 + "hghghgh";
        s0.print();
        s1.print();
    }
    {
        SS s1("s1=s1");
        s1=s1;
        s1=s1;
        s1=s1;
        s1=s1;
        s1=s1;
        s1=s1;
        s1.print();
    }
            
    {
        const SS s1("abcd");
        SS s2("1234");
        SS r1;
        r1 = s2 + s1;
        r1.print();

        SS r2 = s1 + s2;
        r2.print();

        r2 = "xxxxxxx " + s2;
        r2.print();

        SS r3;
        r3 = s1 + " xxxxxx";
        r3.print();
    }
    {
        SS s1("Проба пера ");
        SS res;
        res = 45 + s1;
        res.print();
        res = s1 + 45;
        res.print();
    }

    {
        // --- ЭТО БЛОК ИЗ ЗАДАНИЯ    
        SS(">>>>>>>>>>>>> НАЧАЛО БЛОКА ПРОВЕРОК ИЗ ТЕСТОВОГО ЗАДАНИЯ <<<<<<<<<<<<<<<<<").print(stdout);
        Smart_string str1, str2("lalala");
        const Smart_string str("Const");

        str1 = str + 500 * str2 + str(0, 2) + str[3];
        str1 += '\n';
        str1 += "Ну и с новой строчки";
        str1 += "2+(" + str2 + ")+3";
        str1.print(stdout);
        SS(".................... КОНЕЦ БЛОКА ПРОВЕРОК ИЗ ТЕСТОВОГО ЗАДАНИЯ ............").print(stdout);
        // --- конец блока из задания
    }
    // ------------------ end of MASTER TEST

    cout << "Конец работы программы\n";
    return 0;
}
