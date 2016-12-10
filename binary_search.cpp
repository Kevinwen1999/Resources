#include <iostream>
using namespace std;

int main() {
	int arr[10] = {0, 1, 2, 3, 4, 5, 5, 5, 6, 7};
	int l = 0 , h = 9, mid;
	while (l <= h)
    {
        mid = l + (h-l) / 2;
        //if (arr[mid]==5){cout<<mid<<endl; break;}
        if (arr[mid] < 5) // replace with <= for upperbound
        {
            l = mid + 1;
        }
        else
        {
            h = mid - 1;
        }
    }
    cout<<l<<endl;
	return 0;
}
