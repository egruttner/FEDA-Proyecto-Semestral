#include <iostream>
#include <algorithm>
#include <chrono>
#include <string.h>
#include <fstream>
#include <sstream>
#include "grafos.h"

using namespace std;

int multiplicador=10;

//PARA TOMAR EL TIEMPO
template <typename Func>
long long execution_time_ms(Func function, string tarea, int id_dataset) 
{
  auto start_time = std::chrono::high_resolution_clock::now();
  
  function(tarea, id_dataset);

  auto end_time = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
}




// PROCESOS
//1 - Creación de Matriz de Adyacencia
void creaMatrizAdyacencia(int id_dataset)
{
  int tam_matriz = id_dataset*multiplicador;
  MatrizAdyacencia matriz(tam_matriz);
  matriz = crea_matrizAdyacencia(tam_matriz,matriz);

}

//2 - Creación de Lista de Adyacencia
void creaListaAdyacencia(int id_dataset)
{
  int tam_lista = id_dataset*multiplicador;
  ListaAdyacencia lista(tam_lista);
  lista = crea_listaAdyacencia(tam_lista,lista);
}


//3 - Cálculo de Coautoría - Matriz de Adyacencia
void calculaCoautoriaMatrizAdyacencia(int id_dataset, MatrizAdyacencia matriz)
{
  matriz.cuenta_coautoria();
}

//4 - Cálculo de Coautoría - Lista de Adyacencia
void calculaCoautoriaListaAdyacencia(int id_dataset, ListaAdyacencia lista)
{
  lista.cuenta_coautoria();
}



//CENTRO DE LLAMADA DE FUNCIONES
void centro_tareas(string tarea, int id_dataset)
{
    if (tarea=="creaMatrizAdyacencia") {return creaMatrizAdyacencia(id_dataset); } 
    if (tarea=="calculaCoautoriaMatrizAdyacencia") 
    {
      int tam_matriz = id_dataset*multiplicador;
      MatrizAdyacencia matriz(tam_matriz);
      matriz = crea_matrizAdyacencia(tam_matriz,matriz);
      return calculaCoautoriaMatrizAdyacencia(id_dataset,matriz); 
    } 
    if (tarea=="creaListaAdyacencia") {return creaListaAdyacencia(id_dataset); } 

    if (tarea=="calculaCoautoriaListaAdyacencia") 
    {
      int tam_lista = id_dataset*multiplicador;
      ListaAdyacencia lista(tam_lista);
      lista = crea_listaAdyacencia(tam_lista,lista);
      return calculaCoautoriaListaAdyacencia(id_dataset,lista); 
    } 

}

//BLOQUE PRINCIPAL
int main(int argv, char* argc[]) {
  srand(time(NULL)); 

  int n; //tamaño muestras
  int id_proceso;


  int numero_de_experimentos;
  string dir_csv;
  string tarea_seleccionada;
  string nombre_archivo_salida;
  dir_csv = "csv/";

  cout<<"INICIO"<<endl;

  //MatrizAdyacencia matriz(1000);
  //matriz = crea_matrizAdyacencia(1000,matriz);
  //matriz.cuenta_coautoria();




  //TAREAS DE ACUERDO A PARÁMETRO ENVIADO AL PROGRAMA
  id_proceso=atoi(argc[1]);
  switch(id_proceso){

    case 1: tarea_seleccionada = "creaMatrizAdyacencia"; break;
    case 2: tarea_seleccionada = "creaListaAdyacencia"; break;
    case 3: tarea_seleccionada = "calculaCoautoriaMatrizAdyacencia"; break;
    case 4: tarea_seleccionada = "calculaCoautoriaListaAdyacencia"; break;

    default: tarea_seleccionada = ""; break;
  }

  //SI ENTRA CON PARÁMETROS, REALIZA EL TEST
  if((argv > 2) && (strcmp(argc[2],"--test") == 0)){

    int id_dataset = atoi(argc[4]);
    switch(atoi(argc[4]))
    {
      case 1: n = 10000; break;
      case 2: n = 20000; break;
      case 3: n = 30000; break;
      case 4: n = 40000; break;
      case 5: n = 50000; break;

      default: n = 0; break;
    }

    cout<<"Tarea seleccionada: "<< tarea_seleccionada<<endl;



    nombre_archivo_salida = dir_csv + tarea_seleccionada + "-results.csv";
    ofstream outfile(nombre_archivo_salida,std::ios::app);

    double mm_total_time = 0;
    int numero_de_experimentos=1;
    for(int j = 0; j < numero_de_experimentos; j++)
    { 

        long long single_execution_time = execution_time_ms(centro_tareas, tarea_seleccionada, id_dataset);
        mm_total_time += single_execution_time;
      
    }
    double mm_avg_time = mm_total_time / numero_de_experimentos;
    outfile << n << "," << mm_avg_time <<endl;
    outfile.close(); 


    return 0;
  }
  else
  //SINO CREA EL ENCABEZADO PARA GUARDAR EL CSV
  {
    nombre_archivo_salida = dir_csv + tarea_seleccionada + "-results.csv";
    ofstream outfile(nombre_archivo_salida);
    outfile << "Tamaño muestra,Tiempo[ms]\n";

    return 0;
  }


}

