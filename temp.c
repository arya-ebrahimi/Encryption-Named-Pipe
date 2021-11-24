#include <stdio.h>

int main() {
    char result[200] = "";

    int j = 0;
    int k = 0;

    char str2[] = "salam $ salam $ salam $ salam $ salam";
    char str[] = "arya sara arya sara";
    for (int i = 0; i < strlen(str2); i++) {
        if (str2[i] == '$') {
            while (str[k] != ' ') {
                result[j++] = str[k++];
            }
            k++;
            
        } else {
            result[j++] = str2[i];
        }
    }

    printf("%s", result);

}