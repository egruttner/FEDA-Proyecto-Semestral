#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

class ListaAdyacencia {
    vector<vector<pair<int, int>>> listaAdy; // Lista de adyacencia
    int numAutores; // Número de autores del grafo
    int pares;
    int impares;
    int max_cant_coautoria;
    int id_autor1;
    int id_autor2;

public:
    // Constructor que inicializa el grafo con un número dado de autores
    ListaAdyacencia(int numAutores) {
        this->numAutores = numAutores;
        listaAdy.resize(numAutores); // Redimensionar la lista de adyacencia
    }

    // Método para agregar una conexión entre dos autores con una cantidad de publicaciones en común
    void agregarConexion(int autorA, int autorB) 
    {
        int aux;

        if (autorA>autorB)
        {
            aux=autorB;
            autorB=autorA;
            autorA=aux;
        }




        bool hayConexion=false;
        for (const auto& coautor : listaAdy[autorA]) {
            if (coautor.first == autorB) 
            {
                hayConexion=true;
                break;
            }
        }

        //SI NO EXISTE LA CREA
        if (!hayConexion)
        {
            listaAdy[autorA].push_back(make_pair(autorB, 1)); // Agregar autorB y publicacionesEnComun a la lista de adyacencia de autorA
            //listaAdy[autorB].push_back(make_pair(autorA, 1)); // Agregar autorA y publicacionesEnComun a la lista de adyacencia de autorB (si el grafo es no dirigido)
        }
        else
        {
            for (auto& coautor : listaAdy[autorA]) {
                if (coautor.first == autorB) 
                {
                    coautor.second++;
                    break;
                }
            }

            for (auto& coautor : listaAdy[autorB]) {
                if (coautor.first == autorA) 
                {
                    coautor.second++;
                    break;
                }
             }


        }
    }

    void cuenta_coautoria()
    {
        pares=0;
        impares=0;
        max_cant_coautoria=0;

        for (int i = 0; i < numAutores; ++i) {
            for (const auto& coautor : listaAdy[i]) 
            {
                if (coautor.second % 2 == 0) 
                {
                    if (coautor.second!=0) pares++;
                } 
                else 
                {
                    impares++;
                }

                if (coautor.second > max_cant_coautoria)
                {
                    max_cant_coautoria=coautor.second ;
                    id_autor1=i;
                    id_autor2=coautor.first;
                }

            }
        }

        cout << "PARES: " << pares << endl;
        cout << "IMPARES: " << impares << endl;
        cout << "MAYOR CANTIDAD DE COAUTORIA: " << max_cant_coautoria << endl;

    }


    // Método para imprimir la lista de adyacencia del grafo
    void imprimirListaAdyacencia() {
        for (int i = 0; i < numAutores; ++i) {
            std::cout << "Autor " << i << ": ";
            for (const auto& coautor : listaAdy[i]) {
                cout << "(" << coautor.first << ", " << coautor.second << ") ";
            }
            cout << endl;
        }
    }
};