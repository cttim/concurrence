#include <iostream>
//#include <uC++.h>
#include "q1mergesort.h"
#include <cstdlib>
#include <stdio.h>
#include <math.h>
using namespace std;

/*
void merge(int *a, int *b, int low, int pivot, int high){
	int h,i,j,k;
	h = low;
	i = low;
	j = pivot+1;

	while((h<=pivot)&&(j<=high)){
		if(a[h]<=a[j]){
			b[i] = a[h];
			h++;
		}
		else{
			b[i] = a[j];
			j++;
		}
		i++;
	}
	if(h>pivot){
		for(k = j; i<=high; k++){
			b[i] = a[k];
			i++;
		}
	}
	else{
		for(k=h; k<=pivot; k++){
			b[i] = a[k];
			i++;
		}
	}

	for(int i = low; i <= high; i++){
		a[i] = b[i];
	}
}


template <typename T>
Mergesort<T>:: Mergesort(T values[], unsigned int low, unsigned int high, unsigned int depth){
	ori = values;
	l = low;
	h = high;
	d = depth;
	cp = new int[sizeof(values)/sizeof(*values)];

	if(d == 0){

	}

	else{
		int pivot = (l+h)/2;
		int d1 = log(pivot-l)/log(2);
		int d2 = log(h-pivot)/log(2);
		{
			Mergesort<T> a(ori, cp, l, pivot, d1);
			Mergesort<T> b(ori, cp, pivot+1, h, d2);
		}

		merge(ori, cp, l, pivot, h);

	}

}

template <typename T>
Mergesort<T>:: Mergesort(T values[], int *c, unsigned int low, unsigned int high, unsigned int depth){
	ori = values;
	l = low;
	h = high;
	d = depth;
	cp = c;
	if(d == 0){

	}
	else{
		int pivot = (l+h)/2;
		int d1 = log(pivot-l)/log(2);
		int d2 = log(h-pivot)/log(2);
		{
			Mergesort<T> a(ori, cp, l, pivot, d1);
			Mergesort<T> b(ori, cp, pivot+1, h, d2);
		}

		merge(ori, cp, l, pivot, h);
	}

}
*/






















