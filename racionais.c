#include "racionais.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* coloque demais includes aqui */

/* Funcoes privadas restritas a este modulo.
 * Voce deve implementa-las pois serao necessarias,
 * embora elas nao precisem estar no .h */

/* retorna um numero aleatorio entre min e max, inclusive. */
int aleat (long int min, long int max){
    return min - rand() % (max - min + 1);
}

/* Maximo Divisor Comum entre a e b.         */
/* Calcula o mdc pelo metodo de Euclides.    */
/* Dica: a versao recursiva eh bem elegante! */
long int mdc (long int a, long int b){
    if(b == 0)
        return a;
    return mdc(b, a % b);
}

/* Minimo Multiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long int mmc (long int a, long int b){
    return (a * b) / mdc(a,b);
}

/* Recebe um numero racional e o retorna simplificado no parametro *r.
   Quem chama esta funcao deve garantir que *r seja valido e nao NULL. */
void simplifica_r(struct racional **r) {
    if (!r || !valido_r(*r))
        return;

    int both_mdc = mdc((*r)->num, (*r)->den);

    struct racional *new_r = malloc(sizeof(struct racional));
    if (!new_r) {
        return;
    }

    new_r->num = (*r)->num / both_mdc;
    new_r->den = (*r)->den / both_mdc;

    if (new_r->den < 0) {
        new_r->num *= -1;
        new_r->den *= -1;
    }

    free(*r);
    *r = new_r;
}



struct racional *cria_r (long int numerador, long int denominador){
    struct racional *r;
    r = malloc (sizeof (struct racional));
    if(!r)
        return NULL;
    
    r->num = numerador;
    r->den = denominador;

    if (denominador != 0)
        simplifica_r(&r);
    return r;
    
}

struct racional *sorteia_r(long int max) {
    srand(time(NULL));

    struct racional *r = malloc(sizeof (struct racional));
    if (!r) {
        return NULL;
    }

    r->num = aleat(-max, max);
    r->den = aleat(-max, max);

    if (!valido_r(r)) {
        free(r);
        return NULL;
    }

    simplifica_r(&r);

    return r;
}

void destroi_r (struct racional **r) {
    free(r);

}

long int numerador_r(struct racional *r) {
    return r->num;
}

long int denominador_r(struct racional *r) {
    if (!r || r->den == 0) {
        return 0;
    }
    return r->den;
}

int valido_r (struct racional *r) {
	if (!r || r->den == 0)
		return 0;
	return 1;
}

struct racional *soma_r(struct racional *r1, struct racional *r2) {
    if (r1 == NULL || r2 == NULL || r1->den == 0 || r2->den == 0) {
        return NULL;
    }

    struct racional *r3 = malloc(sizeof (struct racional));
    if (r3 == NULL) {
        return NULL;
    }

    long int divisor = mmc(r1->den, r2->den);
    long int valor1 = (divisor / r1->den) * r1->num;
    long int valor2 = (divisor / r2->den) * r2->num;

    r3->num = valor1 + valor2;
    r3->den = divisor;
    simplifica_r(&r3);

    free(r1);
    free(r2);

    return r3;
}

struct racional *subtrai_r (struct racional *r1, struct racional *r2){
    if (r1 == NULL || r2 == NULL || r1->den == 0 || r2->den == 0) {
        return NULL;
    }

    struct racional *r3 = malloc(sizeof (struct racional));
    if (r3 == NULL) {
        return NULL;
    }

    long int divisor = mmc(r1->den, r2->den);
    long int valor1 = (divisor / r1->den) * r1->num;
    long int valor2 = (divisor / r2->den) * r2->num;

    r3->num = valor1 - valor2;
    r3->den = divisor;
    simplifica_r(&r3);

    return r3;
}

struct racional *multiplica_r (struct racional *r1, struct racional *r2) {
	if (r1 == NULL || r2 == NULL || r1->den == 0 || r2->den == 0) {
        return NULL;
    }	

    struct racional *r3 = malloc(sizeof (struct racional));
    if (r3 == NULL) {
        return NULL;
    }

	r3->num = r1->num * r2->num;
	r3->den = r1->den * r2->den;
	simplifica_r (&r3);
	
	return r3;
}

struct racional *divide_r(struct racional *r1, struct racional *r2) {
    if (r1 == NULL || r2 == NULL || r1->den == 0 || r2->den == 0) {
        return NULL;
    }

    struct racional *r3 = malloc(sizeof (struct racional));
    if (r3 == NULL) {
        return NULL;
    }

    if (!valido_r(r1) || !valido_r(r2))
        return NULL;

    r3->num = r1->num * r2->den;
    r3->den = r1->den * r2->num;

    simplifica_r(&r3);

    return r3;
}

int compara_r(struct racional *r1, struct racional *r2) {
    if (!r1 || !r2)
        return 0;
    
    int divisor = mmc(r1->den, r2->den);
    long int valor1 = r1->num * (divisor / r1->den);
    long int valor2 = r2->num * (divisor / r2->den);

    if (valor1 < valor2)
        return -1;
    else if (valor1 > valor2)
        return 1;
    else
        return 0;
}


void imprime_r (struct racional *r) {
	if (!r)
		printf (" NULO");
	else if (!valido_r(r)) {
		printf (" INVALIDO");
	}
	else if (r->num == 0)
		printf (" %ld", r->num);
	else if (r->den == 1)
		printf (" %ld", r->num);
	else if (r->num == r->den)
		printf (" 1");
	else
		printf (" %ld/%ld", r->num, r->den);
}

/* int compara_QS (const void a, const void  b) 
{
    struct racional r1 == (struct racional a);
    struct racional r2 == (struct racional b);

    return compara_r(r1, *r2);
} */

/* aqui voce pode definir mais funcoes internas, caso queira ou precise */

/* Implemente aqui as funcoes cujos prototipos estao em racionais.h */
