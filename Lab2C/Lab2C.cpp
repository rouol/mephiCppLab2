// Словарь слов (список)
#include <iostream>
#include <locale.h>
#include <windows.h>
#include "Dictionary.h"

void sep() {
    std::cout << "-----------------------------------------------------------\n";
}

bool Equal(const String _string1, const String _string2) {
    if (&_string1 == &_string2)
        return true;
    if (_string1.GetLength() == _string2.GetLength())
    {
        for (size_t i = 0; i < _string1.GetLength(); i++)
            if (_string1.Get(i) != _string2.Get(i)) {
                return false;
            }
        return true;
    }
    return false;
}

String charToString(char _char[]) {
    int length = strlen(_char);
    String string = String(length);
    for (int i = 0; i < length; i++) {
        string.Set(_char[i], i);
    }
    return string;
}

template<typename T>
void printSequence(Sequence<T>* sequence, const char sep[] = "") {
    for (int i = 0; i < sequence->GetLength(); i++) {
        if (i != 0) {
            std::cout << sep;
        }
        std::cout << (*sequence)[i];
        
    }
}

String inputString(bool menu = false) {
    char c = ' ';
    String inputstring;
    if (menu) std::cin.get(c);
    while (std::cin.get(c)) {
        if (c == '\n') break;
        inputstring.Append(c);
    }
    return inputstring;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    sep();
    std::cout << "              Построение 'именного указателя'\n";
    std::cout << "                Карачурин Рауль Б19-501\n";
    sep();

    char command;
    while (true) {

        Dictionary<String>* dictionary = new Dictionary<String>;
        
        sep();
        std::cout << "Хотите провести тестирование? +/-\n";
        std::cin >> command;
        if (command == '+') {
            // check on sample
            // sample "Такие были Диммлер-музыкант с женой, Иогель..."
            char samp[] = "Такие были Диммлер-музыкант с женой, Иогель...";
            char samp1[] = "были";
            char samp2[] = "женой";
            String sample = charToString(samp);
            printSequence(&sample);
            std::cout << "\n";
            sep();
            // ban words: "были", "женой"
            dictionary->AddBanned(charToString(samp1));
            dictionary->AddBanned(charToString(samp2));
            // do
            dictionary->AddString(sample);
            
            std::cout << "слово - число вхождений: вхождения\n";
            for (int i = 0; i < dictionary->GetLength(); i++) {
                printSequence(&(dictionary->GetWord(i)));
                std::cout << " - ";
                std::cout << dictionary->GetWordCount(i) << ": ";
                printSequence(&(dictionary->GetWordEntries(i)), ", ");
                std::cout << "\n";
            }

            // right answer should be:
            /*
            Такие - 1: 0
            Диммлер - музыкант - 1 : 11
            с - 1 : 28
            Иогель - 1 : 37
            */
            //checks
            if (
                Equal(dictionary->GetWord(0), charToString(const_cast <char*>("Такие"))) &&
                Equal(dictionary->GetWord(1), charToString(const_cast <char*>("Диммлер-музыкант"))) &&
                Equal(dictionary->GetWord(2), charToString(const_cast <char*>("с"))) &&
                Equal(dictionary->GetWord(3), charToString(const_cast <char*>("Иогель"))) &&
                dictionary->GetWordEntries(0)[0] == 0 &&
                dictionary->GetWordEntries(1)[0] == 11 &&
                dictionary->GetWordEntries(2)[0] == 28 &&
                dictionary->GetWordEntries(3)[0] == 37
                ) {
                std::cout << "тесты пройдены успешно\n";
            }
            else {
                std::cout << "тесты не пройдены\n";
            }
            sep();
            
            continue;
        }
        else {
            std::cin.get(command);
        }

        sep();
        std::cout << "Хотите добавить исключаемые слова? +/-\n";
        std::cin >> command;
        if (command == '+') {
            String input;
            bool first = true;
            while (true) {
                std::cout << "Введите слово или enter, если хотите закончить ввод\n";
                std::cout << "ввод: ";
                String input = inputString(first);
                if (input.GetLength() == 0)
                    break;
                dictionary->AddBanned(input);
                first = false;
            }
        }
        else {
            std::cin.get(command);
        }

        sep();
        std::cout << "Введите строку: ";
        String string = inputString();
        //printSequence(&string);
        //std::cout << "\n";
        sep();

        dictionary->AddString(string);

        std::cout << "слово - число вхождений: вхождения\n";
        for (int i = 0; i < dictionary->GetLength(); i++) {
            printSequence(&(dictionary->GetWord(i)));
            std::cout << " - ";
            std::cout << dictionary->GetWordCount(i) << ": ";
            printSequence(&(dictionary->GetWordEntries(i)), ", ");
            std::cout << "\n";
        }
        sep();
        std::cout << "чтобы продолжить введите 1, для выхода введите 0\n";
        std::cin >> command;
        if (command == '0') {
            exit(0);
        }
    }
}