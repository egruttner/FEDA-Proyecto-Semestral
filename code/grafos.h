#include <iostream>
#include <string.h>
#include <fstream>
#include "clase_matriz.h"
#include "clase_lista.h"

using namespace std;


ListaAdyacencia crea_listaAdyacencia(int tam_lista, ListaAdyacencia lista);
void cuenta_coautoria_lista(ListaAdyacencia lista);

MatrizAdyacencia crea_matrizAdyacencia(int tam_matriz, MatrizAdyacencia matriz);
void cuenta_coautoria_matriz(MatrizAdyacencia matriz);



void show_Matriz(MatrizAdyacencia matriz);
