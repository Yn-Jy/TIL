// 2022.04.26 YJY
// 기수 정렬(Radix Sort) 구현을 위한 코드 : 정렬 대상들이 같은 길이를 가질 때만 사용이 가능하다!
// 길이 다른것도 별도의 알고리즘을 추가로 사용하면 되지만 그 마저도 제한적 이용 필요.. 굳이..?라서 사용x

#include <stdio.h>
// 버킷의 기능을 위해 리스트 기반 큐를 활용한다.
#include "ListBaseQueue.h"


#define BUCKET_NUM		10

void RadixSort(int arr[], int num, int maxLen)   // maxLen은 가장 긴 데이터의 길이 정보가 전달
{
	Queue buckets[BUCKET_NUM];
	int bi;
	int pos;
	int di;
	int divfac = 1;
	int radix;

	// 총 10개의 버킷 초기화
	for (bi = 0; bi < BUCKET_NUM; bi++)
		QueueInit(&buckets[bi]);

	// 가장 긴 데이터의 길이만큼 반복
	for (pos = 0; pos < maxLen; pos++)
	{
		// 정렬 대상의 수만큼 반복
		for (di = 0; di < num; di++)
		{
			// N번째 자리의 숫자 추출
			radix = (arr[di] / divfac) % 10;

			// 추출한 숫자를 근거로 데이터 버킷에 저장
			Enqueue(&buckets[radix], arr[di]);
		}

		// 버킷 수만큼 반복
		for (bi = 0, di = 0; bi < BUCKET_NUM; bi++)
		{
			// 버킷에 저장된 것 순서대로 다 꺼내서 다시 arr에 저장
			while (!QIsEmpty(&buckets[bi]))
				arr[di++] = Dequeue(&buckets[bi]);
		}

		// N번째 자리의 숫자 추출을 위한 피제수의 증가
		divfac *= 10;
	}
}

int main(void)
{
	int arr[7] = { 13, 212, 14, 7141, 10987, 6, 15 };

	int len = sizeof(arr) / sizeof(int);
	int i;

	RadixSort(arr, len, 5);

	for (i = 0; i < len; i++)
		printf("%d ", arr[i]);

	printf("\n");
	return 0;
}