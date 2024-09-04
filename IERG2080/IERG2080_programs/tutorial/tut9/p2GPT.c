#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool canBeEqualFrequency(char *word) {
    int freq[26] = {0};
    int n = strlen(word);

    int maxFreq = 0;
    for (int i = 0; i < n; i++) {
        freq[word[i] - 'a']++;
        if (freq[word[i] - 'a'] > maxFreq) {
            maxFreq = freq[word[i] - 'a'];
        }
    }

    int countMaxFreq = 0;
    for (int i = 0; i < 26; i++) {
        if (freq[i] == maxFreq) {
            countMaxFreq++;
        }
    }

    if (countMaxFreq == n || countMaxFreq == n-1) {
        return true;
    }
    
    for (int i = 0; i < 26; i++) {
        if (freq[i] == 0 || freq[i] == maxFreq) {
            continue;
        }
        if (freq[i] == 1 && countMaxFreq == n-2) {
            return true;
        }
        if (freq[i] == maxFreq-1 && countMaxFreq == 1) {
            return true;
        }
    }
    return false;
}

int main() {
    char word[101];
    scanf("%s", word);
    if (canBeEqualFrequency(word)) {
        printf("true\n");
    } else {
        printf("false\n");
    }
    return 0;
}
