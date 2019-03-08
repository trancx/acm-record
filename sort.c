/*
 * main.c
 *
 *  Created on: Apr 9, 2018
 *      Author: trance
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

#define RANGE 		100000		/* 数的范围 */
#define RANGE_MASK  (RANGE - 1)	/* 数的MASK */
#define ARRAY_ENTRIES	100000	/* 排序的个数 */
#define TEST_TIME		20		/* 测试的次数 */

typedef unsigned long ul;


static inline void show_array(ul * a, int low, int high) {
	int i;
	printf("low: %d, high: %d\n", low, high);
	for( i =low; i <= high; i++) {
		printf("%lu  ", a[i]);
		if( i !=0 &&  i % 12 == 0)
			puts("");
	}
	puts("");
	puts("");
}



/**
 *  trivial stack implementation
 */

int stack[ARRAY_ENTRIES / 2];
int top;

void stack_init() {
	top = -1;
	memset( stack, -1, sizeof(stack));
}

static inline void push(int i) {
	stack[++top] = i;
}

static inline int pop() {
	return stack[top--];
}

static inline int full() {
	return top == (ARRAY_ENTRIES -1);
}

static inline int empty() {
	return top == -1;
}

static inline int get_para(int num) {
	int idx;
	idx = top - num;
	return stack[idx];
}

static int split(ul * a, int low, int high ) {
	ul sp;
	int i, j;
	if( a[low] > a[high]) {
		if( a[(low+high)/2] >= a[low] )
			sp = a[low];
		else if( a[(low+high)/2] <= a[low] && a[(low+high)/2] >= a[high] )
			sp = a[(low+high)/2];
		else
			sp = a[high];
	}
	i = low;
	j = high;
//	show_array(a,low,high);
	while( i != j ) {
		while( i != j && sp <= a[j]) {
			j--;
		}
		if( i != j ) {
			a[i++] = a[j];  /* a[i] 是可用的位置， 因为一开始为sp */
		}
		while( i != j && sp > a[i])
			i++;
		if( i != j ) {
			a[j--] = a[i];  /* 上面保存了 a[j] 所以 a[j] 就是可用的了 and make a[i] userful */
		}
	}
	a[i] = sp; /* i == j */

	return i;
}

void quick_sort_r(ul * array, int low, int high) {
	int spl;
	if( low < high ) {
		spl = split(array, low, high);
		quick_sort_r(array, low, spl-1);
		quick_sort_r(array, spl+1, high);
	}
}


void quick_sort(ul * array, int low, int high) {
	int i, j, k;
	if (array == NULL || low < 0 || high <= 0 || low>high)
	        return;

	push(high);
	push(low);
	while( !empty() ) {
		i = pop();
		j = pop();
	    if (i < j)
	        {
	            k = split(array, i, j);
	            if (k > i)
	            {
	                push(k - 1);//保存中间变量
	                push(i);  //保存中间变量
	            }
	            if (j > k)
	            {
	                push(j);
	                push(k + 1);
	            }
	        }
	}

}

void quick_sort_me(ul * array, int low, int high) {
	int spl = 0;
	int i, j, pos = 0;

	if( low == high )
		return;
	push(0);
	push(high);
	push(low);
	push(spl);
	while( !empty() ) {
		i = get_para(1);  	/* left */
		j = get_para(2); 		/* right */
		if( i == j)
			goto step2;
		if( pos == 0 ) {
			goto step0;
		} else if( pos == 1) {
			goto step1;
		} else if( pos == 2) {
			goto step2;
		}
step0:;
		spl = split(array, i, j);
		if( spl != i ) {
			push(1);
			push(spl-1);
			push(i);
			push(spl);
			pos = 0;
			continue;
		}
step1:;
		if( spl != j ) {
			push(2);
			push(j);
			push(spl+1);
			push(spl);
			pos = 0;
			continue;
		}
step2:;
		spl = pop();
		pop();
		pop();
		pos = pop();
	}
}

void merge(ul * a, int low, int mid, int high ) {
	ul * tmp;
	int cnt;
	int i, j, k;
	if( low == mid && mid == high )
		return;
	cnt = high - low + 1;  /* [low, mid -1], [mid, high] */
	tmp = malloc( sizeof(ul) * cnt );

	i = low; j = mid; k = 0;
	while( i < mid && j <= high ) {
		if( a[i] < a[j] )
			tmp[k++] = a[i++];
		else
			tmp[k++] = a[j++];
	}

	while( i < mid )
		tmp[k++] = a[i++];
	while( j <= high)
		tmp[k++] = a[j++];
//	puts("tmp a:");
//	show_array(tmp, 0, k-1);

	memcpy(&a[low], tmp, sizeof(ul) * cnt);

	free(tmp);
}

void bottom_up_sort(ul * a, int low, int high) {
	int i, gap, intv;
	int len;
	i = 0;

	len = high + 1;
	gap = 2, intv = gap >> 1;
	while( gap < len ) {
		while( i + gap <= high ) {
			merge(a, i, i + intv, i + gap-1); /* should intv - 1? */
			i += gap;
		}
		/* i + gap > high, so the left < high, or left == 0  */
		if( i <=  high  )
			merge(a, i - gap, i, high);
		/* we simply put the left to the left gap.. not like p10	*/
		gap <<= 1, intv <<= 1, i = 0;
	}
}



struct timespec begin;
struct timespec end;

static inline void init_counter() {
	clock_gettime(CLOCK_MONOTONIC, &begin);
}

static inline void elapse() {
	time_t sec_intv;
	__syscall_slong_t nano_intv;

	clock_gettime(CLOCK_MONOTONIC, &end);
	sec_intv = end.tv_sec - begin.tv_sec;
	nano_intv = end.tv_nsec - begin.tv_nsec;
//	printf("start sec: %lu nanosec: %lu\n", begin.tv_sec, begin.tv_nsec);
//	printf("end sec: %lu nanosec: %lu\n", end.tv_sec, end.tv_nsec);
	if( (int)nano_intv < 0) {
		nano_intv += 1000000000;
		sec_intv--;
	}
	printf("elapsed sec: %lu nanosec: %lu\n", sec_intv, nano_intv);
}



int main( int argc, char * argv [] ) {
	int ret = 0;
	int i, j;
	int fd;

	ul A[ARRAY_ENTRIES];
	ul  B[ARRAY_ENTRIES];
	ul C[ARRAY_ENTRIES];
	ul a;
	stack_init();
	memset(A, 0, sizeof(ul) * ARRAY_ENTRIES);
	memset(C, 0, sizeof(ul) * ARRAY_ENTRIES);
	memset(B, 0, sizeof(ul) * ARRAY_ENTRIES);

	fd = open("/dev/random", O_RDONLY);
	if( fd < 0 ) {
		perror("open error: ");
		exit(1);
	}
	for( j=0; j < TEST_TIME; ++j ) {
		for( i=0; i < ARRAY_ENTRIES ; ++i) {	/* 生成随机数，三个数组处理 */
			read(fd, &a, sizeof(ul));
			a = a & RANGE_MASK;
			A[i]  = B[i] = C[i] = a;
		}
			printf("TEST: %d\n", j+1);
			puts("*****************************");
			puts("BOTTOMUPSORT");
			init_counter();
			bottom_up_sort(A, 0, ARRAY_ENTRIES-1);
			elapse();

			puts("");
			puts("QUICK recursive");
			init_counter();
			quick_sort_r(B, 0, ARRAY_ENTRIES-1);
			elapse();

			puts("");
			puts("QUICK nonrecursive");
			init_counter();
			quick_sort(C, 0, ARRAY_ENTRIES -1);
			elapse();
			puts("*****************************");
		}


	close(fd);
	return ret;
}

