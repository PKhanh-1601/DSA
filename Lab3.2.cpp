/*
STT: 22520639
Full Name: Ngô Hoàng Phương Khanh
Session 01 - Exercise 02
Notes or Remarks: ......
*/

#include <bits/stdc++.h>
using namespace std;

int jumpSearch(int arr[], int n, int target, int step_size)
{
    int prev = 0;
    int curr = 0;

    while (curr < n && arr[curr] < target)
    {
        prev = curr;
        curr = min(curr + step_size, n - 1);
    }

    for (int i = prev; i <= curr; i++)
    {
        if (arr[i] == target)
        {
            return i;
        }
    }
    return -1;
}

int main() {
    int arr[1000], n, target, step_size;
    cout<< "Nhap so luong phan tu: ";
    cin>>n;
    cout<<"Nhap mang: ";
    for(int i=0; i<n; i++)
        cin>>arr[i];
    cout << "Nhap muc tieu: ";
    cin >> target;

    cout << "Nhap kich thuoc buoc: ";
    cin >> step_size;

    int result = jumpSearch(arr, n, target, step_size);
    if (result != -1) {
        cout << "Phan tu tim thay tai chi so: " << result << endl;
    } else {
        cout << "Phan tu khong tim thay." << endl;
    }

    return 0;
}
