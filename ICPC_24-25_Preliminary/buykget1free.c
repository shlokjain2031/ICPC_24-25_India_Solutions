#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
   return (*(int*)a - *(int*)b);
}

int main() {
    int t;
    int *arr;
    int n, k;
    int i = 0;
    int j = 0;
    int l, m;
    long long int sum;
    scanf("%d", &t);
    while(t--) {
        i = 0;
        scanf("%d %d", &n, &k);
        arr = (int *) malloc(sizeof(int) * n);
        while(n--) {
            scanf("%d", &arr[i++]);
        }
        n = i;
        //the array is stored

        //now sort the array
        qsort(arr, n, sizeof(int), compare);

        for(j = 1; j <= n; j++) {
            m = 0; sum = 0;
            for(l = (j - 1); l >= 0; l--) {
                if(m == k) {
                    m = 0;
                    continue;
                }
                else {
                    sum += arr[l];
                    m++;
                }
            }
            printf("%lld ", sum);   
        }
        printf("\n");
        //free(arr);
    }
    return 0;
}