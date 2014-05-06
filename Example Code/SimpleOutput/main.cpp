#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
    for (int i=0; i<100; i++)
    {
        cout << "Hello world!" << i <<endl;
        Sleep(100);
    }
    return 0;
}
