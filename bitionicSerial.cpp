/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include<bits/stdc++.h> 
#include <chrono>
#include <ctime>  

using namespace std; 

// compare and swap the elements if element of
// first half is greater than second half while 
// merging two bitonic sequences
void compAndSwap(int a[], int i, int j, int order) 
{ 
  if (order == (a[i]>a[j])) 
    swap(a[i],a[j]); 
} 

//function to merge two bitonic sequences 
void bitonicMerge(int a[], int low, int length, int order) 
{ 
    if (length>1) 
  { 
    int k = length/2; 
    for (int i=low; i<low+k; i++) 
      compAndSwap(a, i, i+k, order); 
    bitonicMerge(a, low, k, order); 
    bitonicMerge(a, low+k, k, order); 
  } 
} 

// Bitonic sort function
void bitonicSort(int a[],int low, int length, int order) 
{ 
  if (length>1) 
  { 
    int k = length/2; 

    // sort in ascending order because order is 1 
    bitonicSort(a, low, k, 1); 

    // sort in descending order because order is 0 
    bitonicSort(a, low+k, k, 0); 

    // merge whole sequence in ascending order  
    bitonicMerge(a,low, length, order); 
  } 
} 

// Driver function 
int main() 
{ 
    
    int n;
    cout << "Enter the number of elements to be sorted (number should be in the order of 2^n)";
    cin >> n;
    int *a = new int[n];
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        a[i] = i + rand() % 1000;
    }
    auto start = std::chrono::system_clock::now();
    int incr = 1; // 1 represents ascending order 
    bitonicSort(a, 0, n, incr); 

    printf("Sorted array: "); 
    for (int i=0; i<n; i++) 
        printf("%d ", a[i]); 
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "Time taken for serial execution : " << elapsed_seconds.count() << "s\n";

  return 0; 
}
