#include "grafos.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <fstream>
#include <map>
#include "rapidxml.hpp"

using namespace rapidxml;
using namespace std;

vector < string > indice_autores; //Se guardarán los autores que se vayan encontrando en los artículos
vector < vector<int> > matrizData;

//int numNodos=1;
int numNodos=1000000;
int pares;
int impares;
int max_cant_coautoria;
int id_autor1;
int id_autor2;


#include <iostream>
#include <vector>
#include <string>
#include <utility>

// Clase para representar un grafo utilizando lista de adyacencia
class Grafo {
    int numAutores; // Número de autores del grafo
    vector<vector<pair<string, int>>> listaAdy; // Lista de adyacencia

public:
    // Constructor que inicializa el grafo con un número dado de autores
    Grafo(int numAutores) {
        this->numAutores = numAutores;
        listaAdy.resize(numAutores); // Redimensionar la lista de adyacencia
    }

    // Método para agregar una conexión entre dos autores con una cantidad de publicaciones en común
    void agregarConexion(int autorA, int autorB) 
    {
        bool hayConexion=false;
        for (const auto& coautor : listaAdy[autorA]) {
            if (coautor.first == std::to_string(autorB)) 
            {
                hayConexion=true;
                break;
            }
        }

        //SI NO EXISTE LA CREA
        if (!hayConexion)
        {

            listaAdy[autorA].push_back(make_pair(to_string(autorB), 1)); // Agregar autorB y publicacionesEnComun a la lista de adyacencia de autorA
            listaAdy[autorB].push_back(make_pair(to_string(autorA), 1)); // Agregar autorA y publicacionesEnComun a la lista de adyacencia de autorB (si el grafo es no dirigido)
        }
        else
        {
            for (auto& coautor : listaAdy[autorA]) {
                if (coautor.first == std::to_string(autorB)) 
                {
                    coautor.second++;
                    break;
                }
            }

            for (auto& coautor : listaAdy[autorB]) {
                if (coautor.first == std::to_string(autorA)) {
                    coautor.second++;
                    break;
                }
             }
        }
        //SI EXISTE LA ACTUALIZA



    }

    void actualizarConexion(int autorA, int autorB) {

    }




    // Método para imprimir la lista de adyacencia del grafo
    void imprimirListaAdyacencia() {
        for (int i = 0; i < numAutores; ++i) {
            std::cout << "Autor " << i << ": ";
            for (const auto& coautor : listaAdy[i]) {
                std::cout << "(" << coautor.first << ", " << coautor.second << ") ";
            }
            std::cout << std::endl;
        }
    }
};



void cuenta_coautoria()
{
    pares=0;
    impares=0;
    max_cant_coautoria=0;

    int aux;
    for (int i = 0; i < numNodos; i++) 
    {
        for (int j = 0+aux; j < numNodos; j++) 
        {
            if (matrizData[i][j] % 2 == 0) 
            {
                if (matrizData[i][j]!=0) pares++;
            } 
            else 
            {
                impares++;
            }

            if (matrizData[i][j]>max_cant_coautoria)
            {
                max_cant_coautoria=matrizData[i][j];
                id_autor1=i;
                id_autor2=j;
            }

        }
        aux++;
    }

    cout << "PARES: " << to_string(pares) << endl;
    cout << "IMPARES: " << impares << endl;
    cout << "MAYOR CANTIDAD DE COAUTORIA: " << max_cant_coautoria << endl;
    cout << "AUTOR 1: " << indice_autores[id_autor1] << endl;
    cout << "AUTOR 2: " << indice_autores[id_autor2] << endl;

};

int cuenta_aristas_impares()
{

    return 0;
};


void show_matrizAdyacencia()
{
    for (int i = 0; i < numNodos; i++) 
    {
        for (int j = 0; j < numNodos; j++) 
        {
            cout << matrizData[i][j] << " ";
        }
        cout << endl;
    }
};






void show_listaAutores()
{
    for (size_t i = 0; i < indice_autores.size(); i++) {
        cout << i << "-" << indice_autores[i] << " " << endl;
    }
    cout << "\n";
}



void inserta_matrizAdyacencia(int nodo1, int nodo2)
{
    matrizData.resize(numNodos, vector<int>(numNodos, 0));

    //Revisa si hay info guardada en esa posición de la matriz, sino aumenta

    matrizData[nodo1][nodo2]++;
    matrizData[nodo2][nodo1]++;    

};




int inserta_autor(string autor)
{
    //Busca si ya está el registro
    for (size_t i = 0; i < indice_autores.size(); i++) 
    {
        if (indice_autores[i]==autor)
        {
            return i; //SI ESTA ENTREGA LA POSICIÓN
        }
    }

    indice_autores.push_back(autor);

    return indice_autores.size()-1;

};

void carga_xml()
{
    //TEST
    //ifstream myfile("test.xml");
    //PROD
    ifstream myfile("dblp.xml");

    //Abre el archivo y lo parsea
    xml_document<> doc;
    vector<char> buffer((istreambuf_iterator<char>(myfile)), istreambuf_iterator<char>( ));
    doc.parse<0>(&buffer[0]); 

    cout<< "PROCESA" << endl;
    int id_autor1=0;
    int id_autor2=0;
    int total_registros = 0;


    Grafo grafo(1000000);



    map<string, int> autores;
    xml_node<>* root = doc.first_node();

    // Itera sobre los nodos "inproceedings" y "proceedings"
    for (xml_node<>* node = root->first_node(); node; node = node->next_sibling()) 
    {
        string nodeName = node->name();

        if (total_registros>numNodos) break;

        if (nodeName == "article") 
        {
            // Itera sobre los nodos hijos del nodo actual
            for (xml_node<>* childNode = node->first_node(); childNode; childNode = childNode->next_sibling()) 
            {
                string childNodeName = childNode->name();


                //Se busca el hijo "author" y se itera sobre él
                if (childNodeName == "author") 
                {
                    string root = childNode->value(); //RAIZ DE BUSQUEDA
                    id_autor1 = inserta_autor(root);
                    total_registros++;

                    if (childNode->next_sibling())
                    {
                        xml_node<>* restoAutores = childNode->next_sibling(); //SACA EL SIGUIENTE AUTOR
                        //cout << "Par inicial: " << root << "-" << restoAutores->value()<<endl;
                        
                        while (restoAutores->next_sibling())
                        {
                            string tempo = restoAutores->name();
                            if (tempo=="author")
                            {
                                id_autor2=inserta_autor(restoAutores->value());
                                total_registros++;

                                //inserta_matrizAdyacencia(id_autor1,id_autor2);
                                grafo.agregarConexion(id_autor1, id_autor2);


                            }
                            restoAutores=restoAutores->next_sibling();
                        }
                    }      
                }

            }
        }
    }

    //show_matrizAdyacencia();
    //show_listaAutores();
    cuenta_coautoria();
    grafo.imprimirListaAdyacencia();


};


//


// Clase para representar un grafo utilizando lista de adyacencia


