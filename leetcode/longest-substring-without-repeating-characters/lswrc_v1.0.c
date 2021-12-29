#include <stdint.h>
#include <stdio.h>

// sliding window
int lengthOfLongestSubstring(char * s){
    int16_t table[128] = {0};
    int tmp, max_substr = 0, left = 0, right = 0;
    
    if (s == NULL) return 0;
    
    while (s[right]) {
        table[s[right]]++;
        while (table[s[right]] > 1) {
            table[s[left++]]--;
        }
        tmp = right - left + 1;
        max_substr =  tmp > max_substr ? tmp : max_substr;
        right++;
    }
    return max_substr;
} 
