#include <iostream> //for std::cout ,std::cin
#include <cstdlib>
#include <time.h>c
#include <omp.h>
using namespace std;

void ascendingSwap(int index1, int index2, int *ar) // Swap two values such that they appear in ascending order in the array
{
    if (ar[index2] < ar[index1])
    {
        int temp = ar[index2];
        ar[index2] = ar[index1];
        ar[index1] = temp;
    }
}
void decendingSwap(int index1, int index2, int *ar) // Swap two values such that they appear in decending order in the array
{
    if (ar[index1] < ar[index2])
    {
        int temp = ar[index2];
        ar[index2] = ar[index1];
        ar[index1] = temp;
    }
}
void bitonicSortFromBitonicSequence(int startIndex, int lastIndex, int dir, int *ar) // Form a increaseing or decreasing array when a bitonic input is given to the function
{
    if (dir == 1)
    {
        int counter = 0; // Counter to keep track of already swapped elements ,, parallelising this area results in poor performance due to overhead ,,need to fix
        int noOfElements = lastIndex - startIndex + 1;
        for (int j = noOfElements / 2; j > 0; j = j / 2)
        {
            counter = 0;
            for (int i = startIndex; i + j <= lastIndex; i++)
            {
                if (counter < j)
                {
                    ascendingSwap(i, i + j, ar);
                    counter++;
                }
                else
                {
                    counter = 0;
                    i = i + j - 1;
                }
            }
        }
    }
    else // Descending sort
    {
        int counter = 0;
        int noOfElements = lastIndex - startIndex + 1;
        for (int j = noOfElements / 2; j > 0; j = j / 2)
        {
            counter = 0;
            for (int i = startIndex; i <= (lastIndex - j); i++)
            {
                if (counter < j)
                {
                    decendingSwap(i, i + j, ar);
                    counter++;
                }
                else
                {
                    counter = 0;
                    i = i + j - 1;
                }
            }
        }
    }
}
void bitonicSequenceGenerator(int startIndex, int lastIndex, int *ar) // Generate a bitonic sequence from a random order
{
    int noOfElements = lastIndex - startIndex + 1;
    for (int j = 2; j <= noOfElements; j = j * 2)
    {
        #pragma omp parallel for //parallel implementation results in most performance gains here
        for (int i = 0; i < noOfElements; i = i + j)
        {
            if (((i / j) % 2) == 0)
            {
                bitonicSortFromBitonicSequence(i, i + j - 1, 1, ar);
            }
            else
            {
                bitonicSortFromBitonicSequence(i, i + j - 1, 0, ar);
            }
        }
    }
}

int main() //main driver function
{
    omp_set_dynamic(0);                           // Disabled so that the os doesnt override the thread settings
    int maxNumberOfThreads = omp_get_num_procs(); // Gives number of logical cores
    omp_set_num_threads(maxNumberOfThreads);      // Set the no of threads
    int n;
    cout << "Enter the number of elements to be sorted (number should be in the order of 2^n)";
    cin >> n;
    int *ar = new int[n];
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        ar[i] = i + rand() % 1000;
    }
    double start, end;
    start = omp_get_wtime();
    bitonicSequenceGenerator(0, n - 1, ar);
    end = omp_get_wtime();
    cout << "Time taken for Parallel Execution  : " << end-start << endl;
}
