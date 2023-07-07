import matplotlib.pyplot as plt
import pandas as pd
import sys

data1 = pd.read_csv(sys.argv[1])
data2 = pd.read_csv(sys.argv[2])

label1 = sys.argv[3]
label2 = sys.argv[4]

title = sys.argv[5]

x1 = data1['Tamaño muestra'].values
y1 = data1['Tiempo[ms]'].values

x2 = data2['Tamaño muestra'].values
y2 = data2['Tiempo[ms]'].values

plt.plot(x1, y1, label=label1)
plt.legend()
plt.plot(x2, y2, label=label2)
plt.legend()

plt.xlabel('Tamaño muestra')
plt.ylabel('Tiempo[ms]')

plt.title(title)

plt.grid()

#plt.show()
plt.savefig('./graficos/' + title + '.png')
