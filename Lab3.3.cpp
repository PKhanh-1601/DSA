/*
STT: 22520639
Full Name: Ngô Hoàng Phương Khanh
Session 01 - Exercise 02
Notes or Remarks: ......
*/
#include <bits/stdc++.h>
using namespace std;

int interpolationSearch(string arr[], int n, string x)
{
    int low = 0;
    int high = n - 1;

    while (low <= high && x >= arr[low] && x <= arr[high])
    {
        if (low == high)
        {
            if (arr[low] == x)
            {
                return low;
            }
            return -1;
        }
        int pos = low + ((double)(x.compare(arr[low])) * (high - low) / (arr[high].compare(arr[low])));
        if (arr[pos] == x) {
            return pos;
        }

        if (arr[pos].compare(x) < 0)
            low = pos + 1;
        else
            high = pos - 1;
    }

    return -1;
}

int main()
{
    string arr[1000], target;
    int n;
    cout << "Nhap so luong phan tu: ";
    cin >> n;

    cout << "Nhap mang: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "Nhap muc tieu: ";
    cin >> target;

    int index = interpolationSearch(arr, n, target);

    if (index != -1)
        cout << "Phan tu tim thay tai chi so " << index << endl;
    else
        cout << "Phan tu khong tim thay." << endl;

    return 0;
}

