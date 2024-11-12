#include <stdio.h>
#include <stdlib.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
void sort(int **nums_addr, int numsSize) {
    for (int i = 0; i < numsSize - 1; ++i) {
        for (int j = 0; j < numsSize - i - 1; ++j) {
            if (*nums_addr[j] > *nums_addr[j + 1]) {
                int *temp = nums_addr[j];
                nums_addr[j] = nums_addr[j + 1];
                nums_addr[j + 1] = temp;
            }
        }
    }
}

int binary_search(int **nums_addr, int numsSize, int target) {
    if (*nums_addr[0] > target || *nums_addr[numsSize-1] < target) return -1;
    int mid = 0;
    for (int i = 0, j = numsSize - 1; i <= j;) {
        mid = (i + j) / 2;
        if (target > *nums_addr[mid]) {
            i = mid + 1;
        } else if (target < *nums_addr[mid]) {
            j = mid - 1;
        } else {
            return mid;
        }
    }
    return -1;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int *array = (int*)malloc(sizeof(int)*2);
    *returnSize = 0;
    
    if (numsSize <= 2) {
        if (nums[0] + nums[1] == target) {
            array[0] = 0;
            array[1] = 1;
            *returnSize = 2;
        }
    } else {
        int **nums_addr = (int**)malloc(sizeof(int*)*numsSize);
        for (int i = 0; i < numsSize; ++i) nums_addr[i] = nums + i;
        sort(nums_addr, numsSize);
        for (int i = 0; i < numsSize - 1; ++i) {
            int index = binary_search(
                nums_addr + i + 1, numsSize - i - 1, target - *nums_addr[i]
            );
            if (index >= 0) {
                array[0] = nums_addr[i] - nums;
                array[1] = nums_addr[index + i + 1] - nums;
                *returnSize = 2;
                break;
            }
        }
        free(nums_addr);
    }
    return array;
}

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

int main(int *argc, char **argv) {
    int array[] = {
        // 2, 7, 11, 15
        // 3, 2, 4
        // 0,4,3,0
        // -3,4,3,90
        -1,-2,-3,-4,-5
    };
    int target = -8, retSize = 0;
    int *result = twoSum(array, ARRAY_SIZE(array), target, &retSize);
    if (retSize > 0) {
        printf(
            "Found: %d, %d -> %d + %d = %d\n", 
            result[0], result[1], array[result[0]], array[result[1]],
            target
        );
    } else {
        printf("Not Found!\n");
    }
}
