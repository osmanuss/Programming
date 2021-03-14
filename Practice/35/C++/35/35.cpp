#include <iostream>

using namespace std;

struct IntArray {
    int* data;
    int size;
};

void create(IntArray& arr, int size) 
{
    arr.data = new int[size];
    arr.size = size;
}

void create(IntArray* arr, int size) 
{
    create(*arr, size);
}

int get(IntArray& arr, int index) 
{
    if (index < 0 or index >= arr.size) 
    {
        cout << "Index is incorrect" << std::endl;
        exit(1);
    }
    return arr.data[index];
}

int get(IntArray* arr, int index) 
{
    return get(*arr, index);
}

void set(IntArray& arr, int index, int value) 
{
    if (index < 0 or index >= arr.size) 
    {
        cout << "Index is incorrect" << std::endl;
        exit(1);
    }
    arr.data[index] = value;
}

void set(IntArray* arr, int index, int value) 
{
    set(*arr, index, value);
}

void print(IntArray& arr)
{
    cout << "[";
    for (int i = 0; i < arr.size - 1; i++)
    {
        cout << arr.data[i] << ", ";
    }
    cout << arr.data[arr.size - 1] << "]" << endl;
}

void print(IntArray* arr) 
{
    print(*arr);
}

void resize(IntArray& arr, int newSize) 
{
    int* newarr = new int[newSize];
    if (newSize > arr.size) 
    {
        for (int i = 0; i < arr.size; ++i) 
        {
            newarr[i] = arr.data[i];
        }
        for (int i = arr.size; i < newSize; ++i) 
        {
            newarr[i] = 0;
        }

        delete[] arr.data;
        arr.data = newarr;
        arr.size = newSize;
    }
    else 
    {
        for (int i = 0; i < newSize; ++i) 
        {
            newarr[i] = arr.data[i];
        }

        delete[] arr.data;
        arr.data = newarr;
        arr.size = newSize;
    }
}

void resize(IntArray* arr, int newSize) 
{
    resize(*arr, newSize);
}

void destroy(IntArray& arr) 
{
    if (!arr.data) 
    {
        return;
    }
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = 0;
}

void destroy(IntArray* arr) 
{
    destroy(*arr);
}

int main() {
    IntArray arr;
    create(arr, 30);
    for (int i = 0; i < 30; i++) 
    {
        set(arr, i, i + 1);
    }
    print(arr);
    resize(arr, 50);
    print(arr);
    resize(arr, 10);
    print(arr);
    destroy(arr);
}