/*
STT: 22520639
Full Name: Ngô Hoàng Phương Khanh
Session 01 - Exercise 04
Notes or Remarks: ......
*/

#include <iostream>
using namespace std;

void Sort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int findMissingNumber(int arr[], int n)
{
    Sort(arr, n);
    int left = 0, right = n - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (arr[mid] == mid)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return left;
}

int main() {
    int arr[1000], n;
    cout << "Nhap so luong phan tu: ";
    cin >> n;

    cout << "Nhap mang: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cout << "So bi thieu la: " << findMissingNumber(arr, n) << endl;
    return 0;
}
