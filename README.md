# Z-Order
Porcentajes de Similitud en búsquedas kNN tras aplicar una proyección en Z-order

Se compila de la siguiente manera:

    g++ main.cpp -o z_order -std=c++17
  
Se ejecuta de la siguiente manera:

    ./z_order k
  
Donde k es el número de vecinos más cercanos.

El programa retorna el porcentaje de similtud solicitado. Tras varias prueba se llegó a la conclusión de que no importa el parámetro k y que el promedio para todos los casos (k = 5,10,15,20) es de aproximadamente 18%, variando entre 8 y 22.
