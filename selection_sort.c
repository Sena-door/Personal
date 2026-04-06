#include <stdio.h>

void selection_sort(int array[], int n){
    int index;
    int temp;
    for (int i = 0; i < (n - 1); i++){      //* ambos for son para obtener el menor valor del array
        index = i;
        for (int j = (i + 1); j < n; j++){
            if (array[j] < array[index]){
                index = j;     //* se almacena el indice del minimo
            }
        }
        int temp = array[index]; //* estas tres lineas
        array[index] = array[i]; //* son para que el menor valor se asigne al principio del array
        array[i] = temp;  //* intercambiando posiciones con el valor que estaria ahi en primer lugar
    }
}

int main(){

    int array[] = {12, 8, 4, 26, 16, 4, 34, 8, 45, 31, 42, 65, 17, 4, 17};
    int n = (sizeof(array) / sizeof(array[0]));
    printf("n = %d\n", n);

    selection_sort(array, n);

    printf("La lista ordenada es: ");
    for (int i = 0; i < n; i++){
        printf("%d ", array[i]);
    }

   return 0;
}
