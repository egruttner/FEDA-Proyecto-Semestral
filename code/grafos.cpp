#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <fstream>
#include "clase_matriz.h"
#include "clase_lista.h"
#include "rapidxml.hpp"
#include <string.h>

using namespace rapidxml;
using namespace std;

vector < string > indice_autores; //Se guardarán los autores que se vayan encontrando en los artículos


int total_autores;

void show_listaAutores()
{

    for (size_t i = 0; i < indice_autores.size(); i++) {
        cout << i << "-" << indice_autores[i] << " " << endl;
    }
    cout << "\n";
}


int inserta_autor(string autor)
{
    //El primero, para no confundir con 0
    if (indice_autores.size()==0)
    {
        indice_autores.push_back(autor);
        total_autores++;
        return 0;
    }

    //Busca si ya está el registro
    for (size_t i = 0; i < indice_autores.size(); i++) 
    {
        if (indice_autores[i]==autor)
        {
            return i; //SI ESTÁ ENTREGA LA POSICIÓN
        }
    }

    indice_autores.push_back(autor);
    total_autores++;

    return indice_autores.size()-1;
};



void cuenta_coautoria_matriz(MatrizAdyacencia matriz)
{
    matriz.cuenta_coautoria();
}

void cuenta_coautoria_lista(ListaAdyacencia lista)
{
    lista.cuenta_coautoria();
}


void show_Matriz(MatrizAdyacencia matriz)
{
    matriz.show_matrizAdyacencia();

}



MatrizAdyacencia crea_matrizAdyacencia(int tam_matriz, MatrizAdyacencia matriz)
{

    ifstream myfile("test.xml");
    xml_document<> doc; //Acá se almacena todo el documento XML

    //Abre el archivo y lo parsea
    vector<char> buffer((istreambuf_iterator<char>(myfile)), istreambuf_iterator<char>( ));
    doc.parse<0>(&buffer[0]); 

    int id_autor1;
    int id_autor2;
    total_autores=0;

    //Comienza la lectura del XML almacenado en memoria
    bool freno_emergencia=false;
    xml_node<>* root = doc.first_node();

    for (xml_node<>* node = root->first_node(); node; node = node->next_sibling()) 
    {
        if (freno_emergencia) break;

        string nodeName = node->name();

        if (nodeName == "article" || nodeName == "inproceedings") 
        {
            // Itera sobre los nodos hijos del nodo actual
            for (xml_node<>* childNode = node->first_node(); childNode; childNode = childNode->next_sibling()) 
            {
                string childNodeName = childNode->name();

                if (childNodeName == "author") 
                {
                    string root = childNode->value(); //RAIZ DE BUSQUEDA

                    if (total_autores>=tam_matriz)
                    {
                        freno_emergencia = true;
                        break;
                    }
                    id_autor1 = inserta_autor(root);

                    if (childNode->next_sibling())
                    {
                        xml_node<>* restoAutores = childNode->next_sibling(); //SACA EL SIGUIENTE AUTOR
                        
                        while (restoAutores->next_sibling())
                        {
                            string tempo = restoAutores->name();
                            if (tempo=="author")
                            {
                                string autor2 = restoAutores->value();
                                if (total_autores>=tam_matriz)
                                {
                                    freno_emergencia = true;
                                    break;
                                }
                                id_autor2=inserta_autor(restoAutores->value());

                                if (id_autor1!=id_autor2)
                                {

                                    matriz.inserta_matrizAdyacencia(id_autor1,id_autor2);
                                }
                            }
                            restoAutores=restoAutores->next_sibling();
                        }
                    }      
                }
            }
        }

    }

    show_listaAutores();
    matriz.show_matrizAdyacencia();
    //matriz.cuenta_coautoria();

    return matriz;

}

ListaAdyacencia crea_listaAdyacencia(int tam_lista, ListaAdyacencia lista)
{

    ifstream myfile("test.xml");
    xml_document<> doc; //Acá se almacena todo el documento XML

    //Abre el archivo y lo parsea
    vector<char> buffer((istreambuf_iterator<char>(myfile)), istreambuf_iterator<char>( ));
    doc.parse<0>(&buffer[0]); 

    int id_autor1;
    int id_autor2;
    total_autores=0;
    indice_autores.clear();

    //Comienza la lectura del XML almacenado en memoria
    bool freno_emergencia=false;
    xml_node<>* root = doc.first_node();

    for (xml_node<>* node = root->first_node(); node; node = node->next_sibling()) 
    {
        if (freno_emergencia) break;

        string nodeName = node->name();

        if (nodeName == "article" || nodeName == "inproceedings") 
        {
            // Itera sobre los nodos hijos del nodo actual
            for (xml_node<>* childNode = node->first_node(); childNode; childNode = childNode->next_sibling()) 
            {
                string childNodeName = childNode->name();

                if (childNodeName == "author") 
                {
                    string root = childNode->value(); //RAIZ DE BUSQUEDA

                    if (total_autores>=tam_lista)
                    {
                        freno_emergencia = true;
                        break;
                    }
                    id_autor1 = inserta_autor(root);


                    if (childNode->next_sibling())
                    {
                        xml_node<>* restoAutores = childNode->next_sibling(); //SACA EL SIGUIENTE AUTOR
                        
                        while (restoAutores->next_sibling())
                        {
                            string tempo = restoAutores->name();
                            if (tempo=="author")
                            {
                                string autor2 = restoAutores->value();
                                if (total_autores>=tam_lista)
                                {
                                    freno_emergencia = true;
                                    break;
                                }
                                id_autor2=inserta_autor(restoAutores->value());

                                if (id_autor1!=id_autor2)
                                {
                                    lista.agregarConexion(id_autor1,id_autor2);
                                }
                            }
                            restoAutores=restoAutores->next_sibling();
                        }
                    }      
                }
            }
        }

    }


    show_listaAutores();
    lista.imprimirListaAdyacencia();
    //lista.cuenta_coautoria();

    return lista;
}

