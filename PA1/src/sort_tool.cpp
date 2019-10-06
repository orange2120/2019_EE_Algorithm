// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2019/9/6 Cheng-Yun Hsieh]
// **************************************************************************

#include "sort_tool.h"
#include <iostream>
#include <climits>
#include <ctime>

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    int n = data.size();
    for (int i = 1; i < n; ++i)
    {
        int key = data[i];
        int j = i - 1;
        while(j >= 0 && data[j] > key)
        {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = key;
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data){
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    if(high > low)
    {
        int split = randomPartition(data, low, high);
        QuickSortSubVector(data, low, split - 1);
        QuickSortSubVector(data, split + 1, high);
    }
}

int SortTool::randomPartition(vector<int>& data, int low, int high)
{
    srand(time(NULL));
    int r = low + rand() % (high - low + 1);
    swap(data[r], data[high]);
    return Partition(data, low, high);
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    // Hint : Textbook page 171
    int pivot = data[high]; // pick middle element as pivot
    int i = low - 1;

    for (int j = low; j < high; ++j)
    {
        if(data[j] < pivot)
        {
            i++;
            swap(data[i], data[j]);
        }
    }
    swap(data[i + 1], data[high]);
    return i + 1;
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if(high > low)
    {
        int mid = (high + low) / 2;
        MergeSortSubVector(data, low, mid);
        MergeSortSubVector(data, mid + 1, high);
        Merge(data, low, mid, mid + 1, high);
    }
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int i = 0;
    int j = 0;

    vector<int> lhs(data.begin() + low, data.begin() + middle1 + 1);
    vector<int> rhs(data.begin() + middle2, data.begin() + high + 1);
    lhs.insert(lhs.end(), INT_MAX); // insert "infinity" to the end of the subarray
    rhs.insert(rhs.end(), INT_MAX);

    for (int k = low; k <= high; ++k)
    {
        if(lhs[i] <= rhs[j])
        {
            data[k] = lhs[i];
            i++;
        }
        else 
        {
            data[k] = rhs[j];
            j++;
        }
    }
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int max = 0;
    int l = 2 * root + 1;  // left child index
    int r = 2 * root + 2;  // right child index
    if (l < heapSize && data[l] > data[root])
        max = l;
    else
        max = root;

    if(r < heapSize && data[r] > data[max])
        max = r;

    if (max != root)
    {
        swap(data[root], data[max]);
        MaxHeapify(data, max);
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for (int i = heapSize / 2; i >= 0; --i)
        MaxHeapify(data, i);
}
