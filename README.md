# Cliente de Streaming de Subtitulos

El cliente se conecta a un servidor por una direccion de IP y Puerto que recibe como argumentos al ser llamado. Establecida
la comunicación realiza dos simples tareas: Un hilo envía un mensaje al servidor cada dos segundos como simple implementación
de un timeout de conexión; Y el proceso principal se encarga de imprimir los datos (subtítulos) que son enviados por el
servidor.

Frente a un comando de fin de archivo, cierra el canal de comunicación y finaliza su ejecución.
