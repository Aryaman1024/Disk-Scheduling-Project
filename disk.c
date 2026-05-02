#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// SORT FUNCTION
void sort(int arr[], int n) {
    for(int i=0;i<n-1;i++) {
        for(int j=0;j<n-i-1;j++) {
            if(arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// FCFS
void fcfs(int req[], int n, int head) {
    int total = 0;
    printf("\nOrder: %d ", head);

    for(int i=0;i<n;i++) {
        total += abs(req[i] - head);
        head = req[i];
        printf("-> %d ", head);
    }

    printf("\nTotal Seek Time (FCFS): %d\n", total);
}

// SSTF (SAFE)
void sstf(int req[], int n, int head) {
    int visited[n];
    memset(visited, 0, sizeof(visited));

    int total = 0;
    printf("\nOrder: %d ", head);

    for(int i=0;i<n;i++) {
        int min = 9999, index = -1;

        for(int j=0;j<n;j++) {
            if(!visited[j] && abs(req[j]-head) < min) {
                min = abs(req[j]-head);
                index = j;
            }
        }

        if(index == -1) break;  // safety fix

        visited[index] = 1;
        total += min;
        head = req[index];
        printf("-> %d ", head);
    }

    printf("\nTotal Seek Time (SSTF): %d\n", total);
}

// SCAN (Right direction)
void scan(int req[], int n, int head) {
    int size = 200, total = 0;
    int left[n], right[n];
    int l=0, r=0;

    for(int i=0;i<n;i++) {
        if(req[i] < head)
            left[l++] = req[i];
        else
            right[r++] = req[i];
    }

    sort(left, l);
    sort(right, r);

    printf("\nOrder: %d ", head);

    // right side
    for(int i=0;i<r;i++) {
        total += abs(right[i] - head);
        head = right[i];
        printf("-> %d ", head);
    }

    // go to end
    total += abs(size - head);
    head = size;
    printf("-> %d ", head);

    // left side (reverse)
    for(int i=l-1;i>=0;i--) {
        total += abs(left[i] - head);
        head = left[i];
        printf("-> %d ", head);
    }

    printf("\nTotal Seek Time (SCAN): %d\n", total);
}

// C-SCAN
void cscan(int req[], int n, int head) {
    int size = 200, total = 0;
    int left[n], right[n];
    int l=0, r=0;

    for(int i=0;i<n;i++) {
        if(req[i] < head)
            left[l++] = req[i];
        else
            right[r++] = req[i];
    }

    sort(left, l);
    sort(right, r);

    printf("\nOrder: %d ", head);

    // right side
    for(int i=0;i<r;i++) {
        total += abs(right[i] - head);
        head = right[i];
        printf("-> %d ", head);
    }

    // go to end
    total += abs(size - head);
    head = size;
    printf("-> %d ", head);

    // jump to start
    total += size;
    head = 0;
    printf("-> %d ", head);

    // left side
    for(int i=0;i<l;i++) {
        total += abs(left[i] - head);
        head = left[i];
        printf("-> %d ", head);
    }

    printf("\nTotal Seek Time (C-SCAN): %d\n", total);
}

// LOOK
void look(int req[], int n, int head) {
    int total = 0;
    int left[n], right[n];
    int l=0, r=0;

    for(int i=0;i<n;i++) {
        if(req[i] < head)
            left[l++] = req[i];
        else
            right[r++] = req[i];
    }

    sort(left, l);
    sort(right, r);

    printf("\nOrder: %d ", head);

    // right side
    for(int i=0;i<r;i++) {
        total += abs(right[i] - head);
        head = right[i];
        printf("-> %d ", head);
    }

    // left side (reverse)
    for(int i=l-1;i>=0;i--) {
        total += abs(left[i] - head);
        head = left[i];
        printf("-> %d ", head);
    }

    printf("\nTotal Seek Time (LOOK): %d\n", total);
}

// MAIN FUNCTION
int main() {
    int n, head, choice;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    int req[n];

    printf("Enter requests:\n");
    for(int i=0;i<n;i++) {
        scanf("%d", &req[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("\nChoose Algorithm:\n");
    printf("1. FCFS\n");
    printf("2. SSTF\n");
    printf("3. SCAN\n");
    printf("4. C-SCAN\n");
    printf("5. LOOK\n");

    scanf("%d", &choice);

    switch(choice) {
        case 1: fcfs(req, n, head); break;
        case 2: sstf(req, n, head); break;
        case 3: scan(req, n, head); break;
        case 4: cscan(req, n, head); break;
        case 5: look(req, n, head); break;
        default: printf("Invalid choice\n");
    }

    return 0;
}
