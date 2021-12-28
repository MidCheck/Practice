#include <stdio.h>
#include <stdlib.h>

int hash(int key, int size)
{
    return key > 0 ? key % size : -key % size;
}

void insert(int **hashtable, int size, int *key_addr)
{
    int index = hash(*key_addr, size);
    while (hashtable[index] != NULL) {
        index = (index + 1) % size;
    }

    hashtable[index] = key_addr;
}

int* search(int **hashtable, int size, int key)
{
    int index = hash(key, size);
    while (hashtable[index] != NULL) {
        if (*hashtable[index] == key) {
            return hashtable[index];
        }
        index = (index + 1) % size;
    }
    return NULL;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
    int **addr_arr, *ret_arr, i, key, *ret_addr;

    if ((addr_arr = calloc(sizeof(int*), numsSize)) == NULL) {
        return NULL;
    }

    if ((ret_arr = malloc(sizeof(int)*2)) == NULL) {
        free(addr_arr);
        return NULL;
    } else {
        ret_arr[0] = -1;
        ret_arr[1] = -1;
    }

    for (i = 0; i < numsSize; ++i) {
        key = target - nums[i];
        ret_addr = search(addr_arr, numsSize, key);
        if (ret_addr != NULL) {
            ret_arr[0] = ret_addr - nums;
            ret_arr[1] = i;
            goto out;
        } else {
            insert(addr_arr, numsSize, &nums[i]);
        }
    }

out:
    free(addr_arr);
    *returnSize = 2;
    return ret_arr;
}

void show_arr(int *arr, int len)
{
	int i;
	for (i = 0; i < len; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");
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
