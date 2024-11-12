/*
STT: 22520639
Full Name: Ngô Hoàng Phương Khanh
Session 01 - Exercise 07
Notes or Remarks: ......
*/

#include <bits/stdc++.h>
using namespace std;

int findMin(int arr[], int n)
{
    int min = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

int findMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int countLessOrEqual(int arr[], int n, int mid)
{
    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (arr[i] <= mid) {
            ++count;
        }
    }
    return count;
}

int kthSmallestUsingBinarySearch(int arr[], int n, int k) {
    int low = findMin(arr, n);
    int high = findMax(arr, n);

    while (low < high) {
        int mid = low + (high - low) / 2;
        int count = countLessOrEqual(arr, n, mid);

        if (count < k)
        {
            low = mid + 1;
        }
        else
        {
            high = mid;
        }
    }
    return low;
}

int main() {
    int arr[100], n, k;

    cout << "Nhap so luong phan tu: ";
    cin >> n;

    cout << "Nhap mang: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "Nhap k: ";
    cin >> k;

    if (k <= 0 || k > n) {
        cout << "Gia tri k khong hop le!" << endl;
        return -1;
    }

    int result = kthSmallestUsingBinarySearch(arr, n, k);
    cout << "The " << k << "th smallest element is " << result << endl;

    return 0;
}
