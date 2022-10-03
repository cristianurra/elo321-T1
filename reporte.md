# Reporte de ejecucion

## Salida

A continuacion se muestra lo obtenido al ejecutar el programa
<pre><code>
cristhian.urra@aragorn:~/elo321-T1$ ./main.out 
======= Los productos disponibles son =======:
 
Sandwich, con un valor de 1 pesos.  
Cafe, con un valor de 1000 pesos.  
Brownie, con un valor de 800 pesos.  
Chocolate, con un valor de 1200 pesos.  
Agua, con un valor de 700 pesos.  
Pepsi, con un valor de 1000 pesos.  

======= Los ID de los productos pedidos son indicados en cada venta=======
 
Hijo 1 vende ID 3
====Hasta ahora se ha vendido $800 ====
Hijo 2 vende ID 4
====Hasta ahora se ha vendido $2000 ====
Hijo 1 vende ID 15
====Hasta ahora se ha vendido $2001 ====
3
Hijo 1 vende ID 6
15
6
====Hasta ahora se ha vendido $3001 ====
Hijo 2 vende ID 5
====Hasta ahora se ha vendido $3701 ====
Hijo 1 vende ID 2
====Hasta ahora se ha vendido $4701 ====
Hijo 2 vende ID 6
====Hasta ahora se ha vendido $5701 ====
Hijo 2 vende ID 15
====Hasta ahora se ha vendido $5702 ====
2
4
5
6
15
<code><pre>

Nótese que los procesos hijos muestran el codigo que estan trabajando de forma asincronica respecto a la ejecucion del proceso padre. Por ello es que al ejecutarse es posible que se obtenga un orden un tanto distinto de los resultados mostrados en pantalla.
