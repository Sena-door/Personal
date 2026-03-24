#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


int partition(int array[], int inicio, int final){
    
    srand(time(NULL));
    int posicion_pivote = (rand() % (final - inicio + 1)) + inicio;
    int valor_pivote = array[posicion_pivote];
    int temp;
    
    printf("Tomamos de pivote al numero: %d, en la posicion: %d\n", valor_pivote, posicion_pivote);
    //dejamos el pivote al final de array para devolverlo al final
    temp = array[final];
    array[final] = array[posicion_pivote];
    array[posicion_pivote] = temp;
    
    // todos los valores menores al pivote los vamos a posicionar al inicio del array
    int j = inicio;
    printf("partimos el for desde la posicion %d hasta %d\n", inicio, final);
    for (int i = inicio; i < final; i++){
        printf("posicion i: %d valor %d, posicion j: %d valor %d\n", i, array[i], j, array[j]);
        if (array[i] < array[final]){
            printf("como %d es menor a %d ", array[i], array[final]);
            printf("Intercambiamos %d con %d\n", array[i], array[j]);
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            j++;
        }else{
        printf("como %d es mayor o igual a %d no cambiamos nada\n", array[i], array[final]);
        }
    }
    // al final, el pivote tiene que ir en la posicion j, ya que hasta j - 1 se encuentran todos los valorees menores a j 
    // y desde j + 1 empieza la lista de los que son mayores al pivote
    temp = array[final];
    array[final] = array[j];
    array[j] = temp;
    
    //nos queda un array tal que el pivote se ecuentra en la posicion correcta (la posicion inicio + posicion j)
    return j;
}

void quicksort(int array[], int inicio, int final){
    
    if (inicio <= final){
        printf("le pasamos a la funcion partition el array de los indices del %d al %d\n", inicio, final);
        int posicion_pivote = partition(array, inicio, final);
        printf("-----------------------------------------------");
        printf("EL NUMERO DE LA POSICION %d YA ESTA ORDENADO", posicion_pivote);
        printf("-----------------------------------------------\n");
        quicksort(array, inicio, posicion_pivote - 1);
        quicksort(array, posicion_pivote + 1, final);
    }
    return;
}

int main(){
    int array[] = {12, 8, 4, 26, 16, 4, 34, 8, 45, 31, 42, 65, 17, 4, 17};
    
    int minimo = 0;
    int maximo = sizeof(array)/sizeof(array[0]) - 1;
    printf("el array inicia con %d elementos\n", maximo);

    printf("array original\n");
    for (int i = minimo; i < maximo; i++){
        printf("%d ", array[i]);
    }
    printf("\n");

    quicksort(array, minimo, maximo);
    printf("LISTA ORDENADA :D\n");

    printf("array ordenado\n");
    for (int i = minimo; i < maximo; i++){
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}