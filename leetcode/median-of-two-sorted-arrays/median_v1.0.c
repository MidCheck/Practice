#include <stdio.h>

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size){
    int *nums, i = 0, j = 0, k = 0;
    double value;
    if (nums1 == NULL || nums2 == NULL || nums1Size < 0 || nums1Size > 1000 || nums2Size < 0 || nums2Size > 1000)
        return 0.0;
        
    if ((nums = malloc(sizeof(int) * (nums1Size + nums2Size))) == NULL) {
        return 0.0;
    }
    
    while (i < nums1Size && j < nums2Size) {
        if (nums1[i] <= nums2[j]) {
            nums[k++] = nums1[i++];
        } else {
            nums[k++] = nums2[j++];
        }
    }
    
    while (i < nums1Size) {
        nums[k++] = nums1[i++];
    }
    
    while (j < nums2Size) {
        nums[k++] = nums2[j++];
    }
    
    i = 0;
    j = nums1Size + nums2Size;
    k = (i + j) / 2;
    
    if (j % 2 == 0) {
        value = j == 0 ? 0.0 : (double)(nums[k - 1] + nums[k]) / 2;
    } else {
        value = (double)nums[k];
    }
    
    free(nums);
    return value;
}
