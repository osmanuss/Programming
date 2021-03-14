#include <iostream>

using namespace std;

int* create(int len, int x0, int c);
int* sort(int* arr, int len);
int* print(int* arr, int len);

int main()
{
    int len, x0, c;
    x0 = 0;
    c = 0;
    setlocale(LC_ALL, "rus");
    cout << "Введите длину массива, и два числа: начальный член и шаг арифметической прогрессии" << endl;
    cin >> len >> x0 >> c;
    int *arr = create(len, x0, c);
    sort(arr, len);
    print(arr, len);
    delete[] arr;
}

int* create(int len, int x0, int c)
{
    int* arr = new int[len];
    arr[0] = x0;
    for (int i = 1; i < len; i++)
    {
        arr[i] = arr[i - 1] + c;
    }
    return arr;
}

int* sort(int* arr, int len)
{
    int a, b;
    for (int i = 1; i < len; i++)
    {
        a = arr[i];
        b = i;
        while ((b > 0) and (arr[b - 1] > a))
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
    cout << "[" << arr[0];
    for (int i = 1; i < len; i++)
    {
        cout << ", " << arr[i];
    }
    cout << "]";
    return arr;
}