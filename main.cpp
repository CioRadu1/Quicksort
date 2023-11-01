/*
*  Ciobanu Radu-Rares
*  Grupa 30222
	*In acest cod am testat 2 algoritmi de sortare, si am verificat complexitatea pentru fiecare,
     dar si diferenta nr de operatii efectutate de un algoritm de sortare la apelul recursiv, acestia fiind:

	* Quicksort
	* Heapsort
    * InsetionSortRecursiv


	* Pentru cazul in care ne este dat un vector nesortat (average case)
	   - algoritmul Quicksort efectueaza cele mai putine operatii si drept urmare este mai eficient
	   - complexitatea metodei HeapSort este de O(nlog) in timp ce metoda OuickSort are complexitatea in general O(n^2)
	   - timpii de rulare pentru InsrtionSort si InsertionSortRecursiv difera, InsertionSoertRecursiv avand un timp de rulare mai mare
	     dar fiind mai eficient

	* Pentru cazul in care ne este dat un vector sortat crescator (best case)
		- algoritmul OuickSort in cazul best care are pijotul la mijloc este cel mai eficient tot cu complexitatea O(nlogn)
		- in acest caz algoritmul heapsort este cel mai ineficient, iar pentru un Quicksort cu pivotul la final operatiile cresc considerabil
		- timpii de rulare pentru InsrtionSort si InsertionSortRecursiv se comporta ca in cazul anterior, InsertionSoertRecursiv ramanand
		  cel mai eficient

	* Pentru cazul in care ne este dat un vector sortat descrescator (worst case)
		- algoritmul QuickSort cu pivoutul pe mijloc este cel mai eficient
		- al doilea algoritm in clasament este HeapSort fiind in cazul sau best, urmat de Quicksort cu pivotul fiind ultimul element
		- timpii de rulare pentru InsrtionSort si InsertionSortRecursiv se comporta ca in cazul anterior, InsertionSoertRecursiv ramanand
		  cel mai eficient

*/

#include <stdio.h>
#include "Profiler.h"
using namespace std;

#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_TESTE1 5
#define NR_TESTE2 100


Profiler p("HeapSort_OuickSort");

int partition_best(int a[], int n, int m, int constanta) {

    Operation atrib = p.createOperation("Atribuiri_QuickSort_Best", constanta);
    Operation comp = p.createOperation("Comparatii_QuickSort_Best", constanta);

    int q = a[(n + m) / 2];
    while (1) {
        comp.count();
        while (a[n] < q) {
            n++;
            comp.count();
        }
        comp.count();
        while (a[m] > q) {
            m--;
            comp.count();
        }
        if (n >= m) {
            return m;
        }
        atrib.count(3);
        swap(a[n], a[m]);
        n++;
        m--;
    }
}

void quick_sort_best(int a[], int n, int m, int constanta) {
    if (n < m) {
        int q = partition_best(a, n, m, constanta);
        quick_sort_best(a, n, q , constanta);
        quick_sort_best(a, q + 1, m, constanta);
    }
}


int partitionare(int a[], int n, int m, int constanta) {

	Operation atrib = p.createOperation("Atribuiri_QuickSort", constanta);
	Operation comp = p.createOperation("Comparatii_QuickSort", constanta);
	int i = n - 1;
	for (int j = n; j < m; j++) {
		comp.count();
		if (a[j] <= a[m]) {
			atrib.count(3);
			i++;
			swap(a[i], a[j]);
		}
	}
	atrib.count(3);
	swap(a[i + 1], a[m]);
	return i + 1;
}

void quicksort(int a[], int n, int m, int constanta) {

	if (n < m) {
		int q = partitionare(a, n, m, constanta);
		quicksort(a, n, q - 1, constanta);
		quicksort(a, q + 1, m, constanta);
	}
}

void heapify(int a[], int index, int n, int constanta) {

	Operation comparatii = p.createOperation("Comparatii_heapsort", constanta);
	Operation atribuiri = p.createOperation("Atribuiri_heapsort", constanta);

	int left = (2 * index) + 1;
	int right = (2 * index) + 2;
	int max = index;

	if (left < n) {
		comparatii.count();
		if (a[left] > a[index]) {
			max = left;
		}
	}
	if (right < n) {
		comparatii.count();
		if (a[right] > a[max]) {
			max = right;
		}
	}
	if (max != index)
	{
		atribuiri.count(3);
		swap(a[index], a[max]);
		heapify(a, max, n, constanta);
	}

}

void bottom_up(int a[], int n, int constanta) {

	for (int i = ((n / 2) - 1); i >= 0; i--) {
		heapify(a, i, n, constanta);
	}
}

void heap_sort(int a[], int n, int constanta) {

	Operation comparatii = p.createOperation("Comparatii_heapsort", constanta);
	Operation atribuiri = p.createOperation("Atribuiri_heapsort", constanta);
	bottom_up(a, n, constanta);
	for (int i = n - 1; i > 0; i--) {
		atribuiri.count(3);
		swap(a[0], a[i]);
		heapify(a, 0, i, constanta);
	}
}

void insertion_sort(int v[], int n) {

	Operation comp = p.createOperation("insertion_sort_comp", n);
	Operation atribuire = p.createOperation("insertion_sort_atribuiri", n);
	int val = 0;
	int j = 0;
	for (int i = 1; i < n; i++) {
		atribuire.count();
		val = v[i];
		j = i - 1;
		while (j >= 0) {
			comp.count();
			if (v[j] > val) {
				atribuire.count();
				v[j + 1] = v[j];
				j--;
			}
			else
				break;
		}
		atribuire.count();
		v[j + 1] = val;
	}
}


void insertion_sort_recursiv(int v[], int n, int m) {

	Operation comp = p.createOperation("insertion_sort_rec_comp", m);
	Operation atribuire = p.createOperation("insertion_sort_rec_atribuiri", m);
	if (n <= 1) {
		return;
	}
	insertion_sort_recursiv(v, n - 1, m);
	int val = v[n - 1];
	int j = n - 2;
	while (j >= 0) {
		comp.count();
		if (v[j] > val) {
			atribuire.count();
			v[j + 1] = v[j];
		}
		else {
			break;
		}
		j--;
	}
	atribuire.count();
	v[j + 1] = val;
}

void demo() {
	int v[] = { 9, 23, 19, 100, 34, 71, 12, 5, 7 };
	int n = sizeof(v) / sizeof(v[0]);
	int v1[100];
	int v2[100];
	int v3[100];
	int v4[100];
	copy(v, v + n, v1);
	copy(v, v + n, v2);
	copy(v, v + n, v3);
	copy(v, v + n, v4);
    quicksort(v, 0 , n - 1, 0 );
	heap_sort(v1, n, 0);
	insertion_sort(v2, n);
	insertion_sort_recursiv(v3, n, 0);
	printf("QuickSort: ");
	for (int i = 0; i < n; i++) {
		printf("%d ", v[i]);
	}
	printf("\n");
	printf("HeapSort: ");
	for (int i = 0; i < n; i++) {
		printf("%d ", v1[i]);
	}
	printf("\n");
	printf("InsertionSort: ");
	for (int i = 0; i < n; i++) {
		printf("%d ", v2[i]);
	}
	printf("\n");
	printf("InsertionSortRecursiv: ");
	for (int i = 0; i < n; i++) {
		printf("%d ", v3[i]);
	}
}

void grafice(int order) {

	int v[MAX_SIZE];
	int v1[MAX_SIZE];
	int v2[MAX_SIZE];
	int v3[MAX_SIZE];
	int v4[MAX_SIZE];
	int v5[MAX_SIZE];
	int v6[MAX_SIZE];
	int v7[MAX_SIZE];
	int n;
	for (n = STEP_SIZE; n < MAX_SIZE; n += STEP_SIZE) {
		FillRandomArray(v, n, 10, 10000, false, order);
		copy(v, v + n, v1);
		copy(v, v + n, v2);
		copy(v, v + n, v3);
		copy(v, v + n, v4);
		copy(v, v + n, v5);
		copy(v, v + n, v6);
		copy(v, v + n, v7);
		p.startTimer("InsertionSort", n);
		for (int test = 0; test < NR_TESTE2; test++) {
			copy(v, v + n, v6);
			insertion_sort(v6, n);
		}
		p.stopTimer("InsertionSort", n);
		p.startTimer("InsertionSortRecursiv", n);
		for (int test = 0; test < NR_TESTE2; test++) {
			copy(v, v + n, v1);
			insertion_sort_recursiv(v1, n, n);
		}
		p.stopTimer("InsertionSortRecursiv", n);
		for (int test = 0; test < NR_TESTE1; test++) {

			copy(v, v + n, v2);
			copy(v, v + n, v3);
			copy(v, v + n, v4);
			copy(v, v + n, v5);
			copy(v, v + n, v7);

            quick_sort_best(v7, 0 , n - 1, n);
			quicksort(v2, 0, n - 1, n);
			heap_sort(v3, n, n);
			insertion_sort(v4, n);
			insertion_sort_recursiv(v5, n, n);
		}

	}

	p.divideValues("Atribuiri_QuickSort", NR_TESTE1);
	p.divideValues("Comparatii_QuickSort", NR_TESTE1);
    p.divideValues("Atribuiri_QuickSort_Best", NR_TESTE1);
    p.divideValues("Comparatii_QuickSort_Best", NR_TESTE1);

	p.divideValues("Comparatii_heapsort", NR_TESTE1);
	p.divideValues("Atribuiri_heapsort", NR_TESTE1);

	p.divideValues("insertion_sort_rec_comp", NR_TESTE1);
	p.divideValues("insertion_sort_rec_atribuiri", NR_TESTE1);

	p.divideValues("insertion_sort_comp", NR_TESTE1);
	p.divideValues("insertion_sort_atribuiri", NR_TESTE1);


	if (order == ASCENDING) {

		p.addSeries("QuickSortBest", "Atribuiri_QuickSort_Best", "Comparatii_QuickSort_Best");
		p.addSeries("HeapSort", "Atribuiri_heapsort", "Comparatii_heapsort");

		p.addSeries("Insertion", "insertion_sort_atribuiri", "insertion_sort_comp");
		p.addSeries("InsertionRec", "insertion_sort_rec_atribuiri", "insertion_sort_rec_comp");
        p.createGroup("Insertion","Insertion");
        p.createGroup("InsertionRec","InsertionRec");
        p.createGroup("AtribuiriInsertion", "insertion_sort_atribuiri","insertion_sort_rec_atribuiri");
        p.createGroup("ComparatiiInsertion", "insertion_sort_comp","insertion_sort_rec_comp");

		p.createGroup("TimpiPentruInsertionSort", "InsertionSort", "InsertionSortRecursiv");

		p.createGroup("Comparatii", "Comparatii_heapsort", "Comparatii_QuickSort_Best");
		p.createGroup("Atribuiri", "Atribuiri_heapsort", "Atribuiri_QuickSort_Best");

		p.createGroup("Algoritmi", "QuickSortBest", "HeapSort");
		p.createGroup("DiferentaNrOperatiiInsert", "Insertion", "InsertionRec");
	}

	if (order == UNSORTED) {

		p.addSeries("QuickSort", "Atribuiri_QuickSort", "Comparatii_QuickSort");
		p.addSeries("HeapSort", "Atribuiri_heapsort", "Comparatii_heapsort");

		p.addSeries("Insertion", "insertion_sort_atribuiri", "insertion_sort_comp");
		p.addSeries("InsertionRec", "insertion_sort_rec_atribuiri", "insertion_sort_rec_comp");
        p.createGroup("Insertion","Insertion");
        p.createGroup("InsertionRec","InsertionRec");
        p.createGroup("AtribuiriInsertion", "insertion_sort_atribuiri","insertion_sort_rec_atribuiri");
        p.createGroup("ComparatiiInsertion", "insertion_sort_comp","insertion_sort_rec_comp");

		p.createGroup("TimpiPentruInsertionSort", "InsertionSort", "InsertionSortRecursiv");

		p.createGroup("Comparatii", "Comparatii_heapsort", "Comparatii_QuickSort");
		p.createGroup("Atribuiri", "Atribuiri_heapsort", "Atribuiri_QuickSort");

		p.createGroup("Algoritmi", "QuickSort", "HeapSort");
		p.createGroup("DiferentaNrOperatiiInsert", "Insertion", "InsertionRec");
	}

	if (order == DESCENDING) {

		p.addSeries("QuickSort", "Atribuiri_QuickSort", "Comparatii_QuickSort");
		p.addSeries("HeapSort", "Atribuiri_heapsort", "Comparatii_heapsort");

		p.addSeries("Insertion", "insertion_sort_atribuiri", "insertion_sort_comp");
		p.addSeries("InsertionRec", "insertion_sort_rec_atribuiri", "insertion_sort_rec_comp");
        p.createGroup("Insertion","Insertion");
        p.createGroup("InsertionRec","InsertionRec");
        p.createGroup("AtribuiriInsertion", "insertion_sort_atribuiri","insertion_sort_rec_atribuiri");
        p.createGroup("ComparatiiInsertion", "insertion_sort_comp","insertion_sort_rec_comp");

		p.createGroup("TimpiPentruInsertionSort", "InsertionSort", "InsertionSortRecursiv");

		p.createGroup("Comparatii", "Comparatii_heapsort", "Comparatii_QuickSort");
		p.createGroup("Atribuiri", "Atribuiri_heapsort", "Atribuiri_QuickSort");

		p.createGroup("Algoritmi", "QuickSort", "HeapSort");
        p.createGroup("HeapSort1", "Heapsort");
		p.createGroup("DiferentaNrOperatiiInsert", "Insertion", "InsertionRec");
	}



}

void grafice_all() {

	grafice(UNSORTED);
	p.reset("Best");
	grafice(ASCENDING);
	p.reset("Worst");
	grafice(DESCENDING);

	p.showReport();

}

int main() {

	demo();
	//grafice_all();
	return 0;
}