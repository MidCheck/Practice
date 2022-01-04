#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>

int lengthOfLongestSubstring(char * s){
    int table[128] = {0};
    int left = 0, right = 0, max = 0, tmp;
    
    if (s == NULL) return 0;
    
    while (s[right]) {
        tmp = table[s[right]];
        if (tmp > 0) {
            if (tmp > left) left = tmp;
        }
        tmp = right - left + 1;
        if (tmp > max) max = tmp;
        table[s[right]] = right + 1;
        right++;
    }
    return max;
}

