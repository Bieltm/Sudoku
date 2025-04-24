//Fet per: Biel Torruella Mayos
//La meva estrategia ha estat dividir la practica en parts, creant les funcions que realitzen cada part, 
//per a finalment juntarles a la funció main, gracies a aixo puc trebatllar de manera molt mes ordenada
#include <stdio.h>
#include <stdbool.h>
#define mida 9
//He creat la funció arrel per trobar la mida de les regions, que depen de la mida del sudoku, doncs coneixer aquesta mida em facilita moltes parts del codig
int arrel(int a){
    int k =1;
    while (k*k<a){
        k++;
    }
    return k;
}
#define mida_regio arrel(mida)
//La matriu sol pot adoptar valors del 1 fins a la mida de la matriu
#define rang_min 1
#define rang_max mida

int columna;
int fila;
int regiox;
int regioy;

//Creem una funció per llegir la matriu, i que en cas de que llegeixi algun element que no correspongui al rang del sudoku, 
//o sigui un element que no sigui un numero, o tingui la entrada truncada, doni error.
bool llegir_matriu(int matriu[mida][mida]) {
    printf("Llegint sudoku...\n");
    for (int y = 0 ; y < mida ; y++) {
        for (int x = 0; x < mida ; x++) {
        scanf("%d", &matriu[y][x]);
        if (matriu[y][x] < rang_min || matriu[y][x] > rang_max || matriu[y][x] == '\0'){
            printf("Error de lectura a la casella %d, %d.\n", y+1, x+1); //Incorporem el +1 ja que el programa comença per la posició 0, i el jugador per la posició 1.
            return false;
        }
        }
    }
    printf("Sudoku llegit.\n");
    return true;
}

//Creem una funció per mostrar la matriu tal com es demana a la practica
void mostrar_matriu(int matriu[mida][mida]) {
    //Dibuixar cada columna tal com es demana a la practica
    for (int y = 0 ; y  < mida ; y++) {
        //Dibuixa la linea #===...#
        if (y%arrel(mida)==0) {
            for ( int i = 0; i < mida ; i++) {
            printf("#===");
        }
            printf("#\n");
        //Dibuxiar la linea #---+---+---...#
        } else {
            for ( int i = 0; i < mida ; i++) {
                if (i%arrel(mida) == 0){
                    printf("#---");
                } else {
                    printf("+---");
                }
            }
            printf("#\n");
        }
        //Dibuixar la linea [ x | x | x ... | x [
        for (int x = 0; x < mida ; x++) {
            if (x%arrel(mida)==0){
                //Modifiquem el dibuix depenent del tamañ de la matriu, per aixi poder acceptar numeros <9.
                if (matriu[y][x] < 10) {
                    printf("[ %d ", matriu[y][x]);
                } else {
                    printf("[ %d", matriu[y][x]);
                }
                
            } else {
                if (matriu[y][x] < 10) {
                    printf("| %d ", matriu[y][x]);
                } else {
                    printf("| %d", matriu[y][x]);
                }
            }
        }
        printf("[\n");
    }
    //Dibuixar la ultima linea #==...#
    for ( int i = 0; i < mida ; i++) {
        printf("#===");
    }
    printf("#\n");

} 
//Creem una funcio per comprobar si es repeteix algun dels digits de cada fila
bool error_fila(int matriu[mida][mida]) {
    for ( fila = 0 ; fila < mida ; fila++) {
        for (int i = 0 ; i < mida ; i++ ){
            for (int j = 0; j < mida; j++){
                if (matriu[fila][i] == matriu[fila][j] && i!=j){
                    return true;
                }
            }
        }
    }
    return false;
}
//Creem una funcio per comprobar si es repeteix algun dels digits de cada columna
bool error_columna(int matriu[mida][mida]) {
    for ( columna = 0 ; columna < mida ; columna++) {
        for (int i = 0 ; i < mida ; i++ ){
            for (int j = 0; j < mida ; j++){
                if (matriu[i][columna] == matriu[j][columna] && i!=j){
                    return true;
                }
            }
        }
    }
    return false;
}

//Creem una funcio per detectar si hi ha algun error en cadascuna de les regions de la matriu sencera 
//i modifiqui automaticament el valor de regioy, i regiox, variables que ajuden a saber a quina regio es troba el error.
bool error_regio(int matriu[mida][mida]) {
    for (regioy = 0; regioy < mida_regio ; regioy++) {
        for (regiox = 0; regiox < mida_regio ; regiox++) {
            for (int y = regioy*mida_regio; y < (regioy+1)*mida_regio ; y++){
                for (int j =regioy*mida_regio; j < (regioy+1)*mida_regio; j++) {
                    for (int x = regiox*mida_regio; x < (regiox+1)*mida_regio ; x++) {
                        for (int i = regiox*mida_regio; i < (regiox+1)*mida_regio ; i++) {
                            if (matriu[y][x] == matriu[j][i] && x!=i && y!=j) {
                            return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}
//He decidit crear les funcions i aplicarles al main, en comptes de escriure directament el codig al main, ja que m'ajuda a treballar de forma mes ordenada
int main () {
    int sudoku[mida][mida];
    if (llegir_matriu(sudoku) == true) {
        mostrar_matriu(sudoku);
        //Seguidament fem un programa per detectar si el sudoku es correcte o te un error
        if (error_columna(sudoku) == false && error_fila(sudoku) == false && error_regio(sudoku) == false) {
            printf("La solució al sudoku es correcta\n");
        } else {
            if (error_fila(sudoku) == true) {
                printf("Hi ha un error a la fila: %d\n", fila+1);
            }   else if (error_columna(sudoku) == true) {
                printf("Hi ha un error a la columna: %d\n", columna+1);
            }   else if (error_regio(sudoku) == true) {
                printf("Hi ha un error a la regio: %d, %d.\n", regiox+1, regioy+1);
            }
                printf("La solució al sudoku es incorrecta\n");
        }   
    }
}