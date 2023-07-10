#Individuales
python3 plot.py csv/creaMatrizAdyacencia-results.csv MatrizAdyacencia "Creación de Matriz de Adyacencia"
python3 plot.py csv/creaListaAdyacencia-results.csv ListaAdyacencia "Creación de Lista de Adyacencia"

python3 plot.py csv/calculaCoautoriaMatrizAdyacencia-results.csv MatrizAdyacencia "Cálculo de Coautoría - Matriz de Adyacencia"
python3 plot.py csv/calculaCoautoriaListaAdyacencia-results.csv ListaAdyacencia "Cálculo de Coautoría - Lista de Adyacencia"

python3 plot_dos.py csv/creaMatrizAdyacencia-results.csv csv/creaListaAdyacencia-results.csv Matriz Lista "Creación de Estructuras - Matriz vs Lista"
python3 plot_dos.py csv/calculaCoautoriaMatrizAdyacencia-results.csv csv/calculaCoautoriaListaAdyacencia-results.csv Matriz Lista "Cálculo de Coautoría - Matriz vs Lista"




