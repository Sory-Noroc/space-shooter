#include <iostream>

using namespace std;

int main(void)
{
    int x= 10;
	int* p = nullptr;
    p = &x;
    cout<<p;
	return 0;
}