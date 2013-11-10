/*
 * Name: Aditi.R
 * Quicksort
 */

#include "quicksort.h"
#include "stdlib.h"
#include <stdio.h>

/*Function to swap 2 integers
 *Param1 : Pointer to the first integer
 *Param2 : Pointer to the second integer
 */

void swap(int* i, int* j){
  int temp;
  temp=*i;
  *i=*j;
 *j=temp;
}

/*Function to perform quicksort on array
 *Param1 : Array to be sorted
 *Param2 : The starting position to be sorted
 *Param3 : The ending position to be sorted
 */

void aux_quicksort(int *arr, int left, int right,int *arr2){
  if(left>=right)
    return;
  int piv_index=rand()%(right-left+1)+left;
  int i,piv_pos;
  int piv_value=arr[piv_index];
  //to make splitting the array easier
  swap(arr+right, arr+piv_index);
  swap(arr2+right, arr2+piv_index);
  piv_pos=left;
  for(i=left;i<right;i++){
    if(arr[i]<piv_value){
      swap(arr+i,arr+piv_pos);
      swap(arr2+i, arr2+piv_pos);
      piv_pos++;
    }
  }
  swap(arr+right,arr+piv_pos);
  swap(arr2+right,arr2+piv_pos);
  //recursive call
  aux_quicksort(arr, left, piv_pos-1,arr2);
  aux_quicksort(arr, piv_pos+1,right,arr2);
}


/*Function to quicksort an array
 *Param1 : Number of elements to be sorted
 *Param2 : Pointer to the array to sorted
 */

void quicksort(int n, int *arr,int *arr2){
 srand(time(NULL));
 aux_quicksort(arr, 0, n-1,arr2);
}  
