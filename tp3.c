/* Arquivo MAIN que usa o TAD racionais */

#include "racionais.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* coloque seus includes aqui */

void trocar (struct racional **v, int a, int b) {
	struct racional *aux;
	aux = v[a];
	v[a] = v[b];
	v[b] = aux;
}

int minimo (struct racional **v, int inicio, int n){
    if (!v)
        return 0;
    
    if (inicio >= n)
        return inicio;

    int m;
    m = minimo(v,inicio, n - 1);
    if (compara_r(v[n], v[m]) == -1 )
        m = n;
    
    return m;
}

void selectionSort (struct racional **v, int inicio, int n) {
	if (!v || inicio >= n)
		return;
	int m;
	m = minimo (v, inicio, n);
	trocar (v, inicio, m);
	selectionSort (v, inicio + 1, n);
}

void imprimeVetor(int n, struct racional **v)
{
    int i;
    for (i = 0; i < n; i++)
    {
        imprime_r(v[i]);
    }

    printf("\n");
}


int main (){

    srand(0);

    /* vetor de ponteiros para racionais */
    struct racional **v;  /* equivalente a struct racional *v[] */
    struct racional *soma;

    int n, i, j, dado1, dado2;

    do{
        scanf("%d", &n);
    } while (n < 0 || n >= 100);

    v = malloc(n *sizeof (struct racional));

    for (i = 0; i < n; i++)
    {
        scanf("%d %d", &dado1, &dado2);
        v[i] = cria_r(dado1, dado2);
    }

    imprimeVetor(n,v);

    /* arrumar essa merda do krl */
    for (i = 0; i < n; i++)
    {
        if (!valido_r(v[i]))
        {
            free(v[i]);
            for (j = i; j < n - 1; j++)
                v[j] = v[j + 1];

            n--;
            i--;
        }
    }
    imprimeVetor(n,v);

    selectionSort(v, 0, n - 1);
    imprimeVetor(n,v);

    printf("a soma de todos os elementos eh: ");
    soma = cria_r(0,1);

    for (i = 0; i < n; i++)
        soma = soma_r(v[i], soma);
        
    free(v);
    imprime_r(soma);
    free(soma);
        
    printf("\n");

    return 0;
}
