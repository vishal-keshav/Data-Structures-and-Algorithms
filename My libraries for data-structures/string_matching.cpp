/* String matching class
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
#include <stdio.h>
#include <string>

using namespace std;

void LPS(string str, int *out, int n){
	//Initialize first char with LPS 0
	out[0] = 0;
	int i=1,j=0;
	//Iterate until all cells are done
	while(i<n){
		if(str[j] == str[i]){
			out[i] = j+1;
			i++;
			j++;
		}
		else{
			/*Find the next longest lps string ending at i-1
			  By symmetry argument for lps until i-1, next
			  lps can be found as lps[j-1]
			*/
			if(j==0){
				out[i] = 0;
				i++;
			}
			else{
				j = out[j-1];
			}
		}
	}
	return;
}

int main(){
	string sample = "ananabcbanana";
	int *lps = new int[sample.size()];
	LPS(sample, lps, sample.size());
	for(int i=0;i<sample.size();i++){
		cout << lps[i] << " ";
	}

	return 0;
}
