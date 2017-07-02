/* Get the next permutation
 * Copyright (C) bulletcross (Vishal Keshav)

 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */


#include <iostream>
using namespace std;

bool next_factorial(int *arr, int N){
	int i=-1,j,index,temp;
	for(index=N-1;index>0;index--){
		if(arr[index-1]<arr[index]){
			i=index;
			break;
		}
	}
	if(i==-1){
        return false;
	}
	for(index=N-1;index>=i;index--){
		if(arr[index]>arr[i-1]){
			j=index;
			break;
		}
	}
	temp = arr[j];
	arr[j] = arr[i-1];
	arr[i-1] = temp;
	for(index=i,j=N-1;index<j;index++,j--){
		temp = arr[index];
		arr[index] = arr[j];
		arr[j] = temp;
	}
	return true;
}

int main(){
	int nr_elem = 4,fact=1;
	int *arr = new int[nr_elem];

	for(int i=1;i<=nr_elem;i++){
		fact = fact*i;
		arr[i-1] = i;
	}
	do{
        for(int j=0;j<nr_elem;j++){
			cout << arr[j] << " ";
		}
		cout << endl;
	}while(next_factorial(arr,nr_elem));

    return 0;
}
