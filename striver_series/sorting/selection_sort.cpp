#include <bits/stdc++.h>
using namespace std;
// INSERTION SORT
// We move the smallest element to the beginning of the array by comparing each element with the min_element.Further, here
// min_element is assigned to curr element of the outer loop.
int main() {
	// your code goes 
	int arr[] = {13, 46, 24, 52, 20, 9};
	int index=-1;
	for(int i=0;i<6;i++){
		int mine = arr[i];
		for(int j=i;j<6;j++){
			if(arr[j]<mine)
			index = j,mine=min(mine,arr[j]);
			
		}
		
		swap(arr[index],arr[i]);
		// cout<<"after swap arr[i] "<<arr[i]<<" and arr[5] "<<arr[5]<<endl;
	}
	for(int i=0;i<6;i++){
		cout<<arr[i]<<" ";
	}
}