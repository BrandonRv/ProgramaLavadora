##ProgramaLavadora

Gestiona todo el mecanismo de una lavadora. El sistema de hidronivel está gestionado a través de un sensor de presión diferencial MPX2010DP. Ya que este sensor maneja una señal en milivoltios, se utilizó un OpAmp LM358P para poder manejar el rango adecuado en el Arduino a través del pin analógico A0. Este rango se mapeó en el programa. El rango de salida va desde 0V a 5V, que está en el promedio aceptable que puede manejar cómodamente el Arduino Uno o ATmega328P. También se usó un display 20x4, que se gestiona a través de la interfaz I2C.

* Adjunto el esquema para el mismo hidronivel en:

- Esquema para Hidronivel Digital.png

Sugiero usar este proyecto para lavadoras antiguas con el mecanismo de funcionamiento de timer, ya que a muchas no se les encuentra repuesto y este proyecto sería muy útil para ello. En lavadoras modernas, recomendaría reparar la placa base o comprarla nueva. Yo en este caso, solo por hobby, quise hacerlo para este modelo, pero en lavadoras antiguas de timer mecánico se ahorran el sensor de nivel y pueden usar el presostato original que traen esas lavadoras, ya que he realizado el mismo trabajo para otras y funciona perfectamente con el mismo código, solo que hay que adaptar el código para que en vez de trabajar un pin analógico lo trabaje como digital, ya que un presostato mecánico solo tiene 2 estados: high y low.

Haré un video próximamente y lo subiré a mi canal de Youtube, donde explicaré con más detalle al respecto, sobre todo el esquema eléctrico completo. Por ahora solo tengo esta demostración:

https://www.youtube.com/watch?v=-HzdV9QrZBc
