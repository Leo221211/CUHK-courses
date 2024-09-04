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

    // all with same frequency 1
    if(maxFreq == 1)
    {
        return true;
    }
    
    // only 1 letter with max others 0 or max-1
    int flag = 0;
    for(int i = 0; i < 26; i ++)
    {
        if(freq[i] == 0 || freq[i] == maxFreq - 1)
        {
            continue;
        }
        else if(freq[i] == maxFreq)
        {
            flag ++;
        }
        else
        {
            return false;
        }
    }

    if(flag == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
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
