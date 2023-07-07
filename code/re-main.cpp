#include <stdio.h>
#include <iostream>
#include <fstream>
#include <map>
#include "rapidxml.hpp"
#include <vector>
using namespace rapidxml;
using namespace std;


vector < string > indice_autores; //Se guardarán los autores que se vayan encontrando en los artículos


bool busca_autor(string autor)
{
    bool encontrada = false;
    for (size_t i = 0; i < indice_autores.size(); i++) 
    {
        if (indice_autores[i]==autor)
        {
            encontrada=true;
        }
    }
    return encontrada;
}

void inserta_autor(string autor)
{
    if (!busca_autor(autor))
    {
        indice_autores.push_back(autor);
    }

}

void carga_xml()
{
    cout<< "START" << endl;
    //TEST
    ifstream myfile("test.xml");
    //PROD
    //ifstream myfile("dblp.xml");

    xml_document<> doc;
    vector<char> buffer((istreambuf_iterator<char>(myfile)), istreambuf_iterator<char>( ));
    doc.parse<0>(&buffer[0]); 
    //cout << "Name of my first node is: " << doc.first_node()->name() << "\n";  /*test the xml_document */

    cout<< "PROCESA" << endl;
    int aux=0;
    map<string, int> autores;

    // Obtén el nodo raíz
    xml_node<>* root = doc.first_node();

    // Itera sobre los nodos "inproceedings" y "proceedings"
    for (xml_node<>* node = root->first_node(); node; node = node->next_sibling()) 
    {
        string nodeName = node->name();

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
                    //cout << "Root: " << root;
                    //cout << endl;

                    inserta_autor(root);


                    //REVISAR EL CASO CON UN SOLO AUTOR
                    //REVISAR LOOP CUANDO NO QUEDAN MAS AUTORES

                    xml_node<>* restoAutores = childNode->next_sibling(); //SACA EL SIGUIENTE AUTOR
                    //cout << "Par inicial: " << root << "-" << restoAutores->value()<<endl;
                    
                    string aux = "author";
                    while (restoAutores->next_sibling())
                    {
                        restoAutores=restoAutores->next_sibling();
                        string tempo = restoAutores->name();
                        if (tempo=="author")
                        {
                            inserta_autor(tempo);

                        //      cout << "Siguiente par: " << root << "-" << restoAutores->value()<<endl;
                        }
                    }

                    //cout << endl;

                }

            }

            for (xml_node<>* childNode = node->first_node(); childNode; childNode = childNode->next_sibling()) {
                string childNodeName = childNode->name();

                // Verifica si el nodo hijo es "author"
                if (childNodeName == "author") {
                    // Imprime el contenido del elemento "author"
                    string autor = childNode->value();
                    
                    ++autores[autor];
                    
                }
            }

            cout<<endl;
        }
    }
    map<string, int> :: iterator it;
    for(it=autores.begin();it !=autores.end();++it)
        {
        //cout << it->first << ' ' <<it->second << ' ';
        //cout << endl;
        }  

    for (size_t i = 0; i < indice_autores.size(); i++) {
        cout << i << "-" << indice_autores[i] << " " << endl;
    }
    std::cout << "\n";



}



/* 
ZONA DE PRUEBAS

J&eacute;r&eacute;my Barbay


*/