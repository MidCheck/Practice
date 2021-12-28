/*************************************************************************
    > File Name: heap.c
    > Author: MidCHeck
    > Mail: mc.xin@foxmail.com 
    > Created Time: Mon Dec 27 21:03:20 2021
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

void show_arr(int *arr, int len)
{
	int i;
	for (i = 0; i < len; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void show_addr_arr(int **arr, int len)
{
	int i;
	for (i = 0; i < len; ++i) {
		printf("%d ", *arr[i]);
	}
	printf("\n");
}

// #define swap(_a, _b) do { _a ^= _b; _b ^= _a; _a ^= _b; } while(0)

void swap(int **a1, int **a2) {
	int *tmp = *a1;
	*a1 = *a2;
	*a2 = tmp;
}

void max_heapify(int **arr, int start, int end)
{
	int i = start;
	int j = 2*i + 1;
	while (j <= end) {
		if (j + 1 <= end && *arr[j] < *arr[j+1]) j++;
		if (*arr[i] < *arr[j]) {
			swap(&arr[i], &arr[j]);
			i = j;
			j = 2*i + 1;
		} else {
			break;
		}
	}
}

void heap_sort(int **arr, int len)
{
	int i;
	for (i = len / 2 - 1; i >= 0; --i) {
		max_heapify(arr, i, len - 1);
	}
	for (i = len - 1; i > 0; --i) {
		swap(&arr[0], &arr[i]);
		max_heapify(arr, 0, i - 1);
	}
}

int binary_search(int **arr, int end, int target)
{
	int i = 0, mid;
	while (i <= end) {
		mid = (i + end) / 2;
		if (target > *arr[mid]) {
			i = mid + 1;
		} else if (target < *arr[mid]) {
			end = mid - 1;
		} else {
			return mid;
		}
	}
	return -1;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    int start, end, i;
    int **numsAddrArr, *retArr;

    if ((retArr = malloc(sizeof(int)*2)) == NULL) return NULL;
    
    retArr[0] = -1;
    retArr[1] = -1;
    *returnSize = 2;

	if ((numsAddrArr = malloc(sizeof(int*)*numsSize)) == NULL) {
		free(retArr);
		return NULL;
	}

	for (i = 0; i < numsSize; ++i) numsAddrArr[i] = &nums[i];
    
    // sort nums first
    heap_sort(numsAddrArr, numsSize);
	
	for (end = numsSize - 1; end >= 1; --end) {
		start = binary_search(numsAddrArr, end - 1, target - *numsAddrArr[end]);
		if (start >= 0) {
			retArr[0] = numsAddrArr[start] - nums;
			retArr[1] = numsAddrArr[end] - nums;
			break;
		}
	}
    
out:
	free(numsAddrArr);
    return retArr;
}

int main(int argc, char **argv)
{
	int *array, *ret;
	int i, len;
	if (argc < 4) {
		printf("Usage: %s target num1 num2 num3\n", argv[0]);
		return 0;
	}
	len = argc - 2;
	array = malloc(sizeof(int) * len);

	for (i = 0; i < len; ++i) {
		array[i] = atoi(argv[i+2]);
	}

	printf("Target is %s, origin array is:\n", argv[1]);
	show_arr(array, len);
	ret = twoSum(array, len, atoi(argv[1]), &len);
	printf("Result is:\n");
	show_arr(ret, len);
	free(ret);
	free(array);
	return 0;
}
