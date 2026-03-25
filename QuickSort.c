#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


int partition(int array[], int inicio, int final){
    
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

    srand(time(NULL)); //necesario para elegir un numero random

    int array[] = {
    482, 17, 305, 88, 754, 233, 619, 41, 900, 126,
    367, 512, 74, 289, 638, 155, 420, 793, 63, 344,
    581, 210, 475, 832, 99, 267, 714, 38, 593, 181,
    449, 876, 22, 337, 665, 118, 502, 789, 54, 423,
    710, 195, 568, 843, 31, 276, 641, 157, 394, 829,
    73, 488, 215, 600, 341, 724, 89, 456, 193, 617,
    342, 781, 46, 223, 558, 105, 392, 847, 29, 514,
    261, 698, 133, 470, 915, 58, 345, 782, 201, 636,
    93, 428, 765, 312, 549, 176, 413, 850, 37, 592,
    229, 674, 111, 448, 793, 66, 383, 820, 257, 594,
    141, 478, 815, 302, 639, 184, 421, 758, 95, 432,
    769, 316, 553, 190, 427, 864, 41, 578, 215, 652,
    89, 426, 763, 308, 645, 172, 509, 846, 33, 570,
    207, 644, 81, 418, 755, 292, 629, 166, 503, 840,
    27, 564, 201, 638, 175, 412, 849, 86, 423, 760,
    297, 634, 71, 408, 745, 282, 619, 156, 493, 830,
    65, 402, 839, 276, 513, 150, 487, 824, 261, 698,
    135, 472, 909, 46, 383, 820, 157, 494, 831, 268,
    705, 142, 479, 816, 53, 390, 827, 164, 501, 838,
    75, 412, 849, 186, 523, 860, 97, 434, 871, 308,
    645, 182, 519, 856, 93, 430, 867, 204, 541, 878,
    315, 652, 189, 526, 863, 100, 437, 874, 211, 548,
    885, 322, 659, 196, 533, 870, 107, 444, 881, 218,
    555, 892, 329, 666, 203, 540, 877, 114, 451, 888,
    225, 562, 899, 336, 673, 210, 547, 884, 121, 458,
    895, 232, 569, 906, 343, 680, 217, 554, 891, 128,
    465, 902, 239, 576, 913, 350, 687, 224, 561, 898,
    135, 472, 809, 246, 583, 920, 357, 694, 231, 568,
    905, 142, 479, 816, 253, 590, 927, 364, 701, 238,
    575, 912, 149, 486, 823, 260, 597, 934, 371, 708,
    245, 582, 919, 156, 493, 830, 267, 604, 941, 378,
    715, 252, 589, 926, 163, 500, 837, 274, 611, 948,
    385, 722, 259, 596, 933, 170, 507, 844, 281, 618,
    955, 392, 729, 266, 603, 940, 177, 514, 851, 288,
    625, 962, 399, 736, 273, 610, 947, 184, 521, 858,
    295, 632, 969, 406, 743, 280, 617, 954, 191, 528,
    865, 302, 639, 976, 413, 750, 287, 624, 961, 198,
    535, 872, 309, 646, 983, 420, 757, 294, 631, 968,
    205, 542, 879, 316, 653, 990, 427, 764, 301, 638,
    975, 212, 549, 886, 323, 660, 997, 434, 771, 308,
    645, 982, 219, 556, 893, 330, 667, 4,   441, 778,
    315, 652, 989, 226, 563, 900, 337, 674, 11,  448,
    785, 322, 659, 996, 233, 570, 907, 344, 681, 18,
    455, 792, 329, 666, 3,   240, 577, 914, 351, 688,
    25, 462, 799, 336, 673, 10,  247, 584, 921, 358,
    695, 32, 469, 806, 343, 680, 17, 254, 591, 928,
    365, 702, 39, 476, 813, 350, 687, 24, 261, 598,
    935, 372, 709, 46, 483, 820, 357, 694, 31, 268,
    605, 942, 379, 716, 53, 490, 827, 364, 701, 38,
    275, 612, 949, 386, 723, 60, 497, 834, 371, 708
};


    
    int minimo = 0;
    int maximo = sizeof(array)/sizeof(array[0]) - 1;
    printf("el array inicia con %d elementos\n", maximo);
    
    printf("array original\n");
    for (int i = minimo; i <= maximo; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
    
    quicksort(array, minimo, maximo);
    printf("LISTA ORDENADA :D\n");

    printf("array ordenado\n");
    for (int i = minimo; i <= maximo; i++){
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}