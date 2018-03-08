/*
	MC970 - T1
	Leonardo Henrique Batista
	RA: 171985
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

/* Count Sort Paralelo */
double count_sort_paralelo(double a[], int n, double *ret) {
	int i, j, count;
	double start, end, duracao;

	start = omp_get_wtime();

	# pragma omp for
	for (i = 0; i < n; i++) {
		count = 0;

		for (j = 0; j < n; j++) {
			if (a[j] < a[i]) {
				count++;
			} else if (a[j] == a[i] && j < i) {
				count++;
			}
		}

		ret[count] = a[i];
	}
	end = omp_get_wtime();

	duracao = end - start;

	return duracao;
}

int main(int argc, char * argv[]) {
	int i, n, nt;
	double  *a, *ret, t_s;

	/* Numero de threads */
	scanf("%d",&nt);

	/* Numero de valores */
	scanf("%d",&n);

	/* Aloca os vetores de valores para o teste em serial(b) e para o teste em paralelo(a) */
	a = (double *)malloc(n*sizeof(double));
	ret = (double *)malloc(n*sizeof(double));

	/* Entrada dos valores */
	for(i=0;i<n;i++) {
		scanf("%lf",&a[i]);
	}

	/* Chama a funcao de count sort em paralelo */
	# pragma omp parallel num_threads (nt) shared (ret)
	t_s = count_sort_paralelo(a,n,ret);

	/* Imprime o vetor ordenado */
	for(i=0;i<n;i++) {
		printf("%.2f ",ret[i]);
	}
	printf("\n");

	/* Imprime os tempos obtidos e o speedup */
	printf("%f\n",t_s);

	/* Liberacao da memoria ds vetores alocados */
	free(a);
	free(ret);

	return 0;
}
