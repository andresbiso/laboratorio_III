# Consignas
1. Realizar un programa que simule la producción y consumo de productos.
    1. La producción se debe realizar por lotes de productos de 10 unidades, y cada unidad producida se debe almacenar en un archivo
de texto denominado “producto.txt”.
    2. Cada unidad representa una línea de texto en el archivo con el siguiente formato:
“PRODUCTO-%02d\n”, donde “%02d” es un valor numérico secuencial comenzando por “1”, luego “2”... hasta “n”.
    3. El consumo de productos se realiza al leer el archivo y deberá mostrar por pantalla cada línea leída;
o sea, cada vez que se lee una línea del archivo, se está consumiendo un producto.
    4. El programa debe contemplar la apertura del archivo con distintos punteros FILE, uno para la producción y otro para el consumo.
    5. Cada vez que se fabrican productos, se usa la opción “w” en el comando fopen; y, al consumir, se usa la opción “r”.
2. Entregar el código fuente.
3. Indicar cuál es el comportamiento observado al ejecutar el código.
4. ¿Cómo se tendría que comportar para simular la realidad de una industria que fabrica autos?¿Cuál sería la falla?
