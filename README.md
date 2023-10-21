# CCheart
Codigo de un ECG que esta conectado aun servidor el cual se encargara de almacenar los datos que este emita.

Creado por los alumnos del cecyteg plantel penjamo:

Javier Eduardo Mireles Rosales

Antonio Rafael Ramirez Pacheco

Julian Antonio Ramirez Alonso

Acesores:

Jose Luis Luevanos Barragan

Problemática:

En México, cerca de 220 mil personas fallecieron por enfermedades cardiovasculares en 2021, de las cuales 177 mil fueron por infarto al miocardio, que puede ser prevenible al evitar o controlar los factores de riesgo como el tabaquismo, presión arterial alta, colesterol elevado y diabetes no controlada.
Con motivo del Día Mundial del Corazón este 29 de septiembre, el jefe del Departamento de Rehabilitación Cardíaca y Medicina Física del Instituto Nacional de Cardiología “Ignacio Chávez”, Hermes Ilarraza Lomelí, señaló que la atención y tratamiento oportunos, así como la rehabilitación plena permiten a quienes sufrieron un infarto recuperar la función cardiovascular y retomar sus actividades cotidianas.
Ilarraza Lomelí sostuvo que algunas alteraciones del corazón pueden detectarse desde la infancia, como padecimientos congénitos y malformaciones cardiacas. Otros como el infarto al miocardio y las enfermedades isquémicas aparecen después de los 65 años y afectan a tres cuartas partes del total de personas adultas mayores, aunque también se han encontrado casos entre los 30 y 35 años.
La problemática planteada se centra en la alta concentración de pacientes con enfermedades cardiovasculares que acuden simultáneamente a los servicios hospitalarios. Esta situación genera una presión extrema sobre los recursos hospitalarios, aumenta los tiempos de espera y pone en riesgo la calidad de la atención brindada a estos pacientes.

Justificación:
 
El proyecto de Monitoreo Cardiaco (CCN) representa una iniciativa de vanguardia en el campo de la salud y la tecnología, con el potencial de revolucionar la forma en que se aborda la prevención y el monitoreo de enfermedades cardiovasculares al igual que el diseño modular del sistema permite una expansión gradual y escalable sin la necesidad de realizar inversiones significativas en infraestructura adicional. Esto facilita la adaptación a futuras necesidades y la incorporación de nuevas funcionalidades sin un aumento proporcional en los costos.
Este mismo ofrece a los consumidores beneficios económicos sustanciales al reducir los gastos médicos a largo plazo, prevenir emergencias costosas y optimizar el tratamiento y la medicación. Además, proporciona servicios adicionales que pueden resultar en ahorros significativos en el tiempo y los recursos del usuario. Estos beneficios económicos se traducen en una mejora tangible en la calidad de vida y el bienestar financiero de los consumidores.

El Electrocardiograma (ECG) es una herramienta crucial en el campo de la medicina cardiovascular, y su disponibilidad en el hogar puede tener impactos significativos en la salud y bienestar de las personas.
El proyecto tiene como objetivo desarrollar un sistema de monitoreo cardiaco avanzado que integra el módulo AD8232 para la captura de señales cardíacas, una ESP32 para la gestión de datos y comunicación, y una red neuronal de inteligencia artificial para la detección temprana de anomalías y la prevención de enfermedades cardiovasculares. Los datos serán almacenados en un servidor centralizado, permitiendo su acceso y análisis


Objetivo

 El objetivo de este proyecto puede ser muy amplio y multifacético, pero nos enfocamos en desarrollar un sistema de monitoreo de ECG portátil y económico que permita al usuario capturar y visualizar sus datos cardiacos en tiempo real a través de una  interfaz  web, garantizando la accesibilidad y la capacidad de seguimiento continuo y a si mismo La capacidad de monitorear de manera continua y remota el estado cardíaco de los pacientes reduce la probabilidad de hospitalizaciones no programadas y visitas a salas de emergencia. Esto implica una reducción sustancial en los costos directos e indirectos relacionados con la atención de emergencias cardíacas.
Metodología y desarrollo
Componentes 

•	ESP32 dev model
•	Modulo AD8232
•	Electrodos
•	Display Lcd Oled 128x64 1.3 pulgadas
•	Jumpers
•	Batería 1000 mAh 3.7V
Módulo AD8232

Este módulo AD8232 es un dispositivo el cual es capaz de medir actividad eléctrica del corazón. La actividad puede ser desplegada mediante una gráfica tipo ECG o por valores que  en este caso representarían las pulsaciones por minuto o BPM. 





	


 
ESP32

La esp32 es un micro controlador con capacidades WI-FI y Bluetooth esta se encargara de la  adquisición de datos del módulo AD8232 y maneja la comunicación con el servidor web




	






Diagrama de conexiones

 
Conexiones	Pines
GND	GND
3.3V	3.3V
OUTPUT	D34
LO-	D33
LO+	D32
Conexiones	Pines
GND	GND
VCC	5V (VIN)
SCL	D22
SDA	D21








Configuración del ESP32 para la conexión con el servidor
Para este proyecto utilizaremos el software de Arduino para programar la ESP32 ya que este nos da una forma de instalar algunas librerías que necesitamos, para ello incluiremos las siguientes:




Incluiremos las librerías WI-FI y HTTPClient para conectarnos a internet y a haci poder mandar los datos a nuestro servidor web, las librerías SIP, WIRE y Adafruit son para comunicarnos con el display y poder visualizar las pulsaciones.
Enseguida se definen algunos parámetros para conexión a internet en este apartado el esp32 busca el SSID de la red y se conecta con la contraseña previamente asignada, luego inicia una comunicación con el servidor.
En STRING URL se coloca el URL la cual es una dirección web que nos permite interactuar con un API para obtener, enviar o manipular datos. Cuando se hace esa solicitud con una  URL con API generalmente utilizamos métodos HTTP como GET,POST,PUT O DELATE  en nuestro caso utilizaremos el método POST para acceder a los datos.

 
 


CONECCIONES DE LOS ELECTRODOS PARA EL MODULO AD8232

Un electrodo es un pequeño dispositivo conductor que se utiliza  para capturar señales eléctricas del cuerpo, como las que genera el corazón en un electrocardiograma. En esencia, un electrodo es un conductor que se coloca sobre la piel para establecer un contacto eléctrico y registrar las señales biológicas.
En el contexto del módulo AD8232, que se utilizó para medir las señales ECG, los electrodos se conectan de la siguiente manera:
Electrodo de derivación derecha (RA): se coloca en el brazo derecho del paciente, generalmente en la muñeca  o en el antebrazo








Electrodo de derivación izquierda (LA): Este se coloca en el brazo izquierdo de manera similar al electrodo RA.









Electrodo de pernada (RL): se coloca  en la pierna derecha del paciente, generalmente en el tobillo o la pantorrilla.






Estos electrodos se utilizan para crear un sistema bipolar estándar para un ESG. El RA y el LA se usan para medir las diferencias de potencial entre los brazos, mientras que el RL se usa como referencia.
La ubicación adecuada y la calidad de los electrodos es importante para obtener lecturas mucho más precisas del ECG.

















