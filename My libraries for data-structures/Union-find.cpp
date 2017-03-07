/* Easy and extended versions of union find implementation
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

/*Union find data structure*/
/*Version 1 supports following funtionality:
1. bool = union_set(i,j)
2. long int = find_set(i)
3. bool is_same_set(i,j)
4. long int number_of_sets(void)
5. long int size_of_set(i)

Version 1 will utilized Path compresion and union by rank for efficiency*/

#define VERSION1

#include <iostream>
#ifndef VERSION1
#include <vector>
#endif
using namespace std;


#define DEBUG

#ifdef VERSION1
class uf{
	public:
		uf(long int initial_set_size){
			set_array = new long int[initial_set_size];
			rank_array = new long int[initial_set_size];
			size_array = new long int[initial_set_size];
			for(long int i = 0;i<initial_set_size;i++){
				set_array[i] = i;
				rank_array[i] = 1;
				size_array[i] = 1;
			}
			nr_sets = initial_set_size;
			nr_elements = initial_set_size;
		}

		long int find_set(long int node){
			if(set_array[node]!=set_array[set_array[node]]){
				set_array[node] = find_set(set_array[node]);
			}
			return set_array[node];
		}

		bool union_set(long int node1, long int node2){
			long int parent1 = find_set(node1);
			long int set_size1 = size_array[find_set(node1)];

			long int parent2 = find_set(node2);
			long int set_size2 = size_array[find_set(node2)];

			if(parent1==parent2){
				return false;
			}
			int temp;
			if(rank_array[parent1] > rank_array[parent2]){
				temp = parent1;
				parent1 = parent2;
				parent2 = temp;
			}
			if(rank_array[parent1] == rank_array[parent2]){
				rank_array[parent2]++;
			}
			set_array[parent1] = parent2;
			size_array[find_set(parent1)] = set_size1 + set_size2;
			nr_sets--;
			return true;
		}

		bool is_same_set(long int node1, long int node2){
			if(find_set(node1)==find_set(node2)){
				return true;
			}
			else{
				return false;
			}
		}
		long int number_of_sets(void){
			return nr_sets;
		}
		long int size_of_set(long int node){
			return size_array[find_set(node)];
		}

	private:
		long int nr_sets;
		long int nr_elements;
		long int *set_array;
		long int *rank_array;
		long int *size_array;

};
#endif // VERSION

#ifndef VERSION1
//Version 2 has basic funtionality, thanks to Steven Halim
#define iterate(var, from, to) for(long int var = long int(from); var<=long int(to); var++)
vector<long int> pset(1000);
void initSet(long int _size) {pset.resize(_size); iterate(i,0,_size-1) pset[i] = i;}
int findset(long int i) {return (pset[i]==i)?i:(pset[i] = findset(pset[i]));}
void unionset(long int i, long int j) {pset[findset(i)] = findset(j);}
bool issameset(long int i, long int j) {return findset(i)==findset(j);}
#endif // VERSION


int main(){
#ifdef DEBUG
    uf my_sets(10);
    my_sets.union_set(0,1);
    my_sets.union_set(2,3);
    my_sets.union_set(4,5);
    if(my_sets.is_same_set(3,2)){
        cout << "2 and 3 lies in same set" << endl;
    }
    if(!my_sets.is_same_set(1,4)){
        cout << "1 and 4 lies in different sets" << endl;
    }
    my_sets.union_set(0,5);
    if(my_sets.is_same_set(1,4)){
        cout << "1 and 4 now lies in same set" << endl;
    }
    cout << my_sets.size_of_set(1) << " is the size of set for 1" << endl;
    cout << my_sets.size_of_set(5) << " is the size of set for 5" << endl;
    cout << my_sets.size_of_set(2) << " is the size of set for 2" << endl;
    cout << my_sets.size_of_set(8) << " is the size of set for 8" << endl;
    cout << my_sets.number_of_sets() << " is the total number of sets right now" << endl;
#endif
	return 0;
}
