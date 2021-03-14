#include <iostream>

using namespace std;

void create(int** arr, int len, int x0 = 0, int c = 0) 
{
    *arr = new int[len];
    (*arr)[0] = x0;
    for (int i = 1; i < len; ++i)
    {
        (*arr)[i] = (*arr)[i - 1] + c;
    }
}

int* sort(int* arr, int len)
{
    int a, b;
    for (int i = 1; i < len; i++)
    {
        a = arr[i];
        b = i;
        while (b > 0 and arr[b - 1] > a) 
        {
            arr[b] = arr[b - 1];
            b--;
        }
        arr[b] = a;
    }
    return arr;
}

int* print(int* arr, int len) 
{
    std::cout << "[";
    for (int i = 0; i < len - 1; ++i)
    {
        std::cout << arr[i] << ", ";
    }
    std::cout << arr[len - 1] << "]";
    return  arr;
}

void destroy(int** arr) 
{
    if (*arr) 
    {
        delete[] *arr;
        *arr = nullptr;
    }
}

int main() 
{
    int len, x0, c;
    int* arr;
    cout << "Input: " << endl;
    cin >> len >> x0 >> c;
    create(&arr, len, x0, c);
    sort(arr, len);
    print(arr, len);
    destroy(&arr);
}