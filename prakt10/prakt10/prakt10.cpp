// prakt10.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>
#include <conio.h>

DWORD WINAPI ThreadFunc(LPVOID lpParam)
{
    int threadNum = *(int*)lpParam;
    std::cout << "Поток " << threadNum << " создан. Через " << threadNum*2 << "сек. он завершится\n";
    threadNum *= 2000;
    Sleep(threadNum);
    threadNum /= 2000;
    std::cout << "Поток " << threadNum << " завершен.\n";
    return 0;
}

int main()
{
    setlocale(LC_ALL, "Rus");
    wchar_t lpszComLine[80];
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    HANDLE hProcess = GetCurrentProcess();
    HANDLE hInheritProcess;
    if (!DuplicateHandle(GetCurrentProcess(),hProcess,GetCurrentProcess(),&hInheritProcess,0,TRUE,DUPLICATE_SAME_ACCESS))
    {
        std::cout << "Дублирование не произошло.\n";
        return -1;
    }
    std::cout << "Наследуемый дубликат создан\n";
    Sleep(2000);
    std::cout << "Дочерний процесс запущен\n";
    int num;
    std::cout << "Введите число, чтобы возвести его в степень: ";
    std::cin >> num;
    wsprintf(lpszComLine, L"C:\\Users\\shurk\\Desktop\\михайлов\\гариев\\prakt10\\x64\\Debug\\prakt10_new.exe %d", num);
    if (!CreateProcess(NULL, lpszComLine, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
    {
        std::cout << "Новый процесс не создан.\n";
        return -1;
    }
    std::cout << "\nPID процесса: " << pi.dwProcessId;
    std::cout << "\nДескриптор процесса: " << pi.hProcess;
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    CloseHandle(hInheritProcess);
    std::cout << "\nПроцесс завершен.\n";
    Sleep(3000);
    const int numThreads = 3;
    HANDLE hThreads[numThreads];
    DWORD threadIds[numThreads];
    for (int i = 0; i < numThreads; ++i)
    {
        int* threadNum = new int(i);
        hThreads[i] = CreateThread(NULL, 0, ThreadFunc, threadNum, 0, &threadIds[i]);
        if (hThreads[i] == NULL)
        {
            std::cout << "Ошибка при создании потока.\n";
            return -1;
        }
    }
    WaitForMultipleObjects(numThreads, hThreads, TRUE, INFINITE);
    for (int i = 0; i < numThreads; ++i)
    {
        CloseHandle(hThreads[i]);
    }
    std::cout << "Все потоки завершены.\n";
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
