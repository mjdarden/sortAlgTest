#include <iostream>
#include <stdlib.h>
#include <time.h> 

using namespace std;

int compare_counter = 0;
int move_counter = 0;

//------------------------------------------------------------------
// Initialize data array with random values
//------------------------------------------------------------------
void create_random_data(int data[], int count, int range)
{
    // Put specified count of random numbers into data array
    srand(time(NULL));
    for (int index = 0; index < count; index++)
        data[index] = rand() % range;
}

//------------------------------------------------------------------
// Initialize data array with mostly sorted values 
//------------------------------------------------------------------
void create_mostly_sorted_data(int data[], int count, int swaps)
{
    // Put sorted data values into array
    for (int index = 0; index < count; index++)
        data[index] = index;

    // Shuffle data by swapping random pairs of values
    for (int index = 0; index < swaps; index++)
    {
        int pos1 = rand() % count;
        int pos2 = rand() % count;
        int temp = data[pos1];
        data[pos1] = data[pos2];
        data[pos2] = temp;
    }
}

bool compareCount() {
    compare_counter++;
    return true;
}

//----------------------------------------------------------------
// Insertion sort algorithm
//----------------------------------------------------------------
void insertion_sort(int data[], int low, int high)
{
    bool swapped = false;
    // Insert each element of unsorted list into sorted list
    for (int unsorted = low + 1; unsorted <= high; unsorted++)
    {
        // Select unsorted value to be inserted
        int value = data[unsorted];
        int position = unsorted;

        // Make room for new data value
        while ((position > 0) && compareCount() && (data[position - 1] > value))
        {
            data[position] = data[position - 1];
            position--;
            move_counter++;
            swapped = true;
        }

        // Put new value into array
        data[position] = value;
        if (swapped) {
            move_counter++;
        }
    }
}

//----------------------------------------------------------------
// Partition function used by Quicksort.
//----------------------------------------------------------------
void partition(int data[], int low, int high, int& mid)
{
    // Select pivot value
    int pivot = data[high];
    int left = low;
    int right = high;

    // Partition array into two parts
    while (left < right)
    {
        // Scan left to right
        while ((left < right) && compareCount() && (data[left] < pivot))
            left++;

        // Scan right to left
        while ((left < right) && compareCount() && (data[right] >= pivot))
            right--;

        // Swap data values
        int temp = data[left];
        data[left] = data[right];
        data[right] = temp;
        move_counter = move_counter + 2;
    }

    // Swap pivot to mid
    mid = left;
    data[high] = data[mid];
    data[mid] = pivot;
    move_counter = move_counter + 2;
}



//----------------------------------------------------------------
// Recursive Quicksort algorithm using basic partition function.
//----------------------------------------------------------------
void quick_sort(int data[], int low, int high)
{
    if (high > 98) {
        // Check terminating condition
        if (low < high)
        {
            // Partition data into two parts
            int mid = 0;
            partition(data, low, high, mid);

            // Recursive calls to sort array
            quick_sort(data, low, mid - 1);
            quick_sort(data, mid + 1, high);
        }
    }
    else {
        insertion_sort(data, low, high);
    }
}

//----------------------------------------------------------------
// Mergesort using secondary storage for data merging.
//----------------------------------------------------------------
void merge_sort(int data[], int low, int high)
{
    if (high > 98) {
        // Check terminating condition
        int range = high - low + 1;
        if (range > 1)
        {
            // Divide the array and sort both halves
            int mid = (low + high) / 2;
            merge_sort(data, low, mid);
            merge_sort(data, mid + 1, high);

            // Create temporary array for merged data
            int* copy = new int[range];

            // Initialize array indices
            int index1 = low;
            int index2 = mid + 1;
            int index = 0;

            // Merge smallest data elements into copy array
            while (index1 <= mid && index2 <= high)
            {
                if (compareCount() && (data[index1] < data[index2])) {
                    copy[index++] = data[index1++];
                    move_counter++;
                }
                else {
                    copy[index++] = data[index2++];
                    move_counter++;
                }
            }

            // Copy any remaining entries from the first half
            while (compareCount() && (index1 <= mid)) {
                copy[index++] = data[index1++];
                move_counter++;
            }

            // Copy any remaining entries from the second half
            while (compareCount() && (index2 <= high)) {
                copy[index++] = data[index2++];
                move_counter++;
            }

            // Copy data back from the temporary array
            for (index = 0; index < range; index++) {
                data[low + index] = copy[index];
                move_counter++;
            }
            delete[]copy;
        }
    }
    else {
        insertion_sort(data, low, high);
    }
}

int main()
{
    const int SIZE = 1000;
    int arr[SIZE];
    int arr2[SIZE];
    int arr3[SIZE];

    cout << "Hybrid algorithm for array size: " << SIZE;

    create_random_data(arr, SIZE, 10);
    quick_sort(arr, 0, (SIZE - 1));
    cout << endl << endl << "Random Data-- # of ccompares: " << compare_counter << " # of moves: " << move_counter;

    compare_counter = 0;
    move_counter = 0;

    create_mostly_sorted_data(arr2, SIZE, (SIZE/10));
    quick_sort(arr2, 0, (SIZE - 1));
    cout << endl << endl << "Mostly Sorted Data-- # of ccompares: " << compare_counter << " # of moves: " << move_counter;

    compare_counter = 0;
    move_counter = 0;

    create_mostly_sorted_data(arr3, SIZE, 0);
    quick_sort(arr3, 0, (SIZE - 1));
    cout << endl << endl << "Sorted Data-- # of ccompares: " << compare_counter << " # of moves: " << move_counter << endl << endl;

    //for (int i = 0; i < SIZE; i++) {
    //    cout << arr[i] << ", ";
    //}
    //cout << endl << endl;
    //for (int i = 0; i < SIZE; i++) {
    //    cout << arr2[i] << ", ";
    //}
    //cout << endl << endl;
    //for (int i = 0; i < SIZE; i++) {
    //    cout << arr3[i] << ", ";
    //}
    //cout << endl << endl;

    return 0;
}
