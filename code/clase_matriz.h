#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

class MatrizAdyacencia {
    vector< vector<int> > matriz;
    int numNodos;
    int pares;
    int impares;
    int max_cant_coautoria;
    int id_autor1;
    int id_autor2;

public:
    MatrizAdyacencia(int numNodos){
        this->numNodos = numNodos;
        matriz.resize(numNodos, vector<int>(numNodos, 0));
    }

    void inserta_matrizAdyacencia(int nodo1, int nodo2)
    {
        if (nodo1>nodo2)
        {
            matriz[nodo2][nodo1]++;
        }
        else
        {
            matriz[nodo1][nodo2]++;
        }
    };

    void cuenta_coautoria()
    {
        pares=0;
        impares=0;
        max_cant_coautoria=0;

        int aux=0;
        for (int i = 0; i < numNodos; i++) 
        {
            for (int j = 0+aux; j < numNodos; j++) 
            {
                if (matriz[i][j] % 2 == 0) 
                {
                    if (matriz[i][j]!=0) pares++;
                } 
                else 
                {
                    impares++;
                }

                if (matriz[i][j]>max_cant_coautoria)
                {
                    max_cant_coautoria=matriz[i][j];
                    id_autor1=i;
                    id_autor2=j;
                }

            }
            aux++;
        }

        cout << "PARES: " << pares << endl;
        cout << "IMPARES: " << impares << endl;
        cout << "MAYOR CANTIDAD DE COAUTORIA: " << max_cant_coautoria << endl;

    };

    void show_matrizAdyacencia()
    {
        for (int i = 0; i < numNodos; i++) 
        {
            for (int j = 0; j < numNodos; j++) 
            {
                cout << matriz[i][j] << " ";
            }
            cout << endl;
        }
    };

};

