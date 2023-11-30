#include <stdio.h>
#include <stdlib.h>
#define MAX 20
#define MAX_STACK 1000
#define SWAP(x, y, t) (mov++, (t)=(x), (x)=(y), (y)=(t) )

int com = 0;
int mov = 0;

// partition 함수
int partition(int list[], int left, int right) {
	int pivot, temp;
	int low, high;

	low = left;
	high = right + 1;
	pivot = list[left];
	do {
		do {
			low++;
			com++;
		}
		while (low <= right && list[low] < pivot);
		do {
			high--;
			com++;
		}
		while (high >= left && list[high] > pivot);
		if (low < high)
			SWAP(list[low], list[high], temp);
	} while (low < high);

	SWAP(list[left], list[high], temp);
	return high;
}

// 퀵 정렬 함수
void quick_sort(int list[], int left, int right) {
	if (left < right) {
		int q = partition(list, left, right);
		for (int i = 0; i < MAX; i++) {
			printf("%d ", list[i]);
		}
		printf("\n");
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
}

// 퀵 정렬 함수에서 이동 횟수와 비교 횟수를 카운팅 할 함수
void quick_sort_re(int list[], int left, int right) {
	if (left < right) {
		int q = partition(list, left, right);
		quick_sort_re(list, left, q - 1);
		quick_sort_re(list, q + 1, right);

	}
}

typedef struct Range{
	int left;
	int right;
} Range;

// 반복적 방법으로 퀵정렬
void quick_sort_iter(int list[], int left, int right, int isFirst) {
	Range stack[MAX_STACK];
	int top = -1;
	Range r;

	stack[++top] = (Range){ left, right };

	while (top >= 0) {
		r = stack[top--];

		if (r.left < r.right) {
			int q = partition(list, r.left, r.right);

			if (isFirst) {
				for (int i = 0; i < MAX; i++) {
					printf("%d ", list[i]);
				}
				printf("\n");
			}
			if (q + 1 < r.right) stack[++top] = (Range){ q + 1, r.right };
			if (r.left < q - 1) stack[++top] = (Range){ r.left, q - 1 };
		}
	}
}

int main(int argc, char* argv[]) {
	int n = MAX;
	srand(time(NULL));
	int list[MAX];
	for (int i = 0; i < n; i++)
		list[i] = rand() % 100;
	// 기본 퀵정렬(재귀)
	printf("Original List \n");
	for (int i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n\nQuick Sort\n");
	quick_sort(list, 0, (n - 1));
	
	// 이동횟수와 비교횟쉬를 구하기 위함
	for (int t = 0; t < (n-1); t++) {
		for (int i = 0; i < n; i++) {
			list[i] = rand() % 100;
		}
		quick_sort_re(list, 0, (n - 1));
	}
	printf("Average Move Count : %d \n", (mov / n));
	printf("Average Compare Count : %d \n \n \n", (com / n));

	// 반복 퀵정렬
	printf("Iterate Quick Sort \n");
	int list_i[MAX];
	for (int i = 0; i < n; i++)
		list_i[i] = rand() % 100;
	printf("Original List \n");
	for (int i = 0; i < n; i++)
		printf("%d ", list_i[i]);
	printf("\n\nQuick Sort\n");
	int j = 0;
	quick_sort_iter(list_i, 0, n-1, j == 0);

	return 0;
}
