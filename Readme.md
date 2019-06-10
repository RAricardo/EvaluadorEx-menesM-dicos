
# Evaluador de Exámenes Médicos
Proyecto final de Sistemas Operativos ST0257 <br>
Ricardo Azopardo <br>
Diego Fonseca <br>
Alex Montoya <br>

## Introducción
La finalidad de la aplicación es simular el análisis de muestras biológicas con fines médicos. El sistema recibe las muestras por medio de ficheros o en un modo interactivo y se encarga de hacer el procesamiento y luego entregar los resultados.  
## Componentes

El sistema, evaluator, está constituido por 5 componentes principales **Registro**, **Entrada**, **Evaluador**, **Salida** y **Reporte**. El registro permite la interacción con el sistema, la entrada es encargada de recibir los exámenes. Éstos son almacenados en colas de entrada de acuerdo a la información contenida. Luego, son organizados de acuerdo al tipo de muestras que contega el examen y pasan a ser procesados en el evaluador. Al obtener una respuesta se alojan en una cola de salida esperando a ser reportados los resultados obtenidos. 

### Registro
El registro es el encargado de recibir todos los comandos ingresados por el usuario y realizar los llamados a los componentes necesarios para realizar las operaciones solicitadas. Los comandos que pueden ser ejecutados son: 
* **init:** Inicializa los parámetros principales del sistema.
* **reg:** Permite ingresar exámenes a ser analizados. 
* **ctrl:** Revisa el estado del sistema y permite actualizar algunos parámetros de éste.
* **rep:** Entrega las muestras ya procesadas.
* **stop:** Finaliza la ejecución del sistema y regresa los recursos ocupados.

Cada comando posee subcomandos propios para interactuar de maneras específicas con el sistema. 

## Entrada
El sistema puede recibir exámenes ya sea de un fichero o en modo interactivo. La entrada se encarga de recibir esta información para ser utilizada por el sistema. El formato correcto de los exámenes es el siguiente:

> <# Cola de entrada (int) > < Tipo de muestra (char)> < Cantidad de muestras (int)>

Dependiendo de este contenido el examen es asignado a una cola de entrada específica la cual tiene un hilo propio con el propósito de organizar los exámenes dependiendo del tipo de muestras.  Cada examen se ubica en una de tres colas internas, específicas dependiendo del tipo de muestra. Al ser ingresado un examen al sistema se le asigna un identificador. Si el examen fue ingresado por un fichero se creará un fichero nuevo con los identificadores correspondientes en la ubicación actual del fichero de entrada. Si se ingresa de manera interactiva los identificadores serán impresos. 

## Evaluador

Cada una de estas colas internas se encargará del procesamiento de un tipo de muestras. Para esto cada una posee un hilo. El procesamiento consiste, en primer lugar, generar aleatoriamente una cantidad de reactivo que consumirá el procesamiento de la muestra. La muestra puede ser procesada si se tiene suficiente reactivo, sino se deberá actualizar el valor pertinente. Luego se genera un número aleatorio con una distribución uniforme para decidir si el resultado es positivo, negativo o no concluyente. 

## Salida

Luego de ser procesadas las muestras, éstas pasan a la cola de salida en donde esperarán a ser reportadas cuando se indique con el comando rep. 

## Reporte

El reporte imprime los resultados de los exámenes con 'P' siendo positivo, 'N' negativo y '?' no concluyente.

## Control del flujo del programa y los recursos

###  Semáforos
Cada cola es manejada por medio de semáforos, utilizando un modelo productor consumidor. Cada cola tiene tres semáforos, uno indica el número de espacios vacíos en la cola, otro el número de espacios ocupados y por último uno para la sección crítica. De esta manera no es posible el ingreso de exámenes a una cola llena o recuperar exámenes de una cola vacía. El hilo tendrá que esperar a realizar su acción hasta que se cumplan las condiciones necesarias. También, con este modelo, se asegura que solamente un hilo pueda acceder a la cola en un momento específico.

### Memoria Compartida
Los recursos de entrada y salida del sistema son almacenados en un espacio de memoria compartida el cual es nombrado por el usuario y puede ser accedido por diferentes procesos del mismo sistema. De esta manera varios usuarios pueden hacer uso de una instancia del sistema. Esta memoria compartida es manejada con un buffer que almacena la información de los exámenes y la actualiza a medida que éstos pasan a distintas fases dentro del sistema.

### Procesos
Es posible que varios usuarios utilicen una instancia del sistema sabiendo el nombre de una región de memoria compartida que haya sido inicializada por medio del comando init. Se pueden tener diferentes instancias del programa funcionando con diferentes regiones de memoria compartida.

### Hilos
El programa tambien hace uso de hilos para dividir el trabajo y tener una ejecución más efectiva. Las colas de entrada, cada una con su propio hilo, separan los exámenes por tipo de muestra y cada cola de tipo de muestra se encarga de hacer que sus exámenes sean procesados, también con hilos propios. 

## Compilación y uso

Para compilar el programa se cuenta con un Makefile. En la carpeta principal del proyecto:

> $ make

El make crea los ficheros objeto en una carpeta, build y el ejecutable en una carpeta bin.

También se cuenta con una función de clean que elimina todos los productos de la compilación, dejando solamente los archivos fuente.

> $ make clean

El uso es el indicado en el enunciado de la práctica:

> $ bin/evaluator < comando > < argumentos >

