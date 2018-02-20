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

void search(char pat[], char txt[], int q)
{
    int M = strlen(pat);
    int N = strlen(txt);
    int i, j;
    int p = 0;
    int t = 0;
    int h = 1;
 
    for (i = 0; i < M-1; i++)
        h = (h*d)%q;
 
    for (i = 0; i < M; i++)
    {
        p = (d*p + pat[i])%q;
        t = (d*t + txt[i])%q;
    }
    for (i = 0; i <= N - M; i++)
    {
 
        if ( p == t )
        {

            for (j = 0; j < M; j++)
            {
                if (txt[i+j] != pat[j])
                    break;
            }

            if (j == M)
                printf("Pattern found at index %d \n", i);
        }
 
        if ( i < N-M )
        {
            t = (d*(t - txt[i]*h) + txt[i+M])%q;

            if (t < 0)
            t = (t + q);
        }
    }
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
