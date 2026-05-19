# ezx-nes-android

Este proyecto es una adaptación y port moderno a **Android** del emulador clásico de NES desarrollado originalmente en 2006 por **OopsWare** para la plataforma de teléfonos móviles Motorola (Moto EZX). 

La optimización y corrección del código actual se ha realizado utilizando la librería gráfica **SDL 1.2** y entornos de desarrollo móvil nativos como **C4droid**.

---

## 🛠️ Correcciones y Mejoras Aplicadas

Para lograr que el núcleo clásico de 2006 corriera de forma estable en dispositivos Android actuales, se implementaron los siguientes cambios:

* **Eliminación de Crasheos de Memoria (Null Pointer Dereference):** Se parchó la función `.lock()` del gestor de audio (`ezx_sound_mgr`), asignándole un buffer simulado legal en la memoria RAM (`FakeAudioBuffer`). Esto evitó que el sistema de audio obsoleto corrompiera la pila gráfica y cerrara la app espontáneamente en C4droid.
* **Corrección de la Geometría de Pantalla:** Se solucionó el problema de las líneas y barras verticales entrelazadas ajustando el salto de línea (*stride/pitch*) a 320 píxeles dentro del bucle de renderizado `memcpy`, sincronizándolo milimétricamente con el mapa de memoria nativo del emulador.
* **Estabilización por Software:** Migración de configuraciones físicas de GPU obsoletas a superficies estables administradas por software (`SDL_SWSURFACE`), asegurando compatibilidad absoluta con hilos ARM modernos.

---

## 🚀 Cómo Compilar y Ejecutar

1. Clona o descarga este repositorio en tu dispositivo Android.
2. Abre el proyecto utilizando **C4droid** (asegúrate de tener instalado el plugin de C4droid para SDL).
3. Introduce la ROM del juego de Nintendo (NES) que deseas probar en la raíz del proyecto y renombrala exactamente como `game.nes`.
4. Compila y ejecuta el archivo `main.cpp`.

---

## 🎮 Controles por Defecto (Mapeo SDL)
El motor captura los eventos estándar del teclado en el bucle principal, mapeando los botones táctiles de la siguiente manera:
* **D-Pad (Arriba, Abajo, Izquierda, Derecha):** Flechas de dirección físicas o virtuales.
* **Botón A (NES):** Tecla `Z`
* **Botón B (NES):** Tecla `X`
* **START:** Tecla `ENTER`
* **SELECT:** Tecla `ESPACIO`

---

## 📄 Licencia
Este repositorio hereda la licencia original **GNU General Public License v2 (GPL-v2)** establecida por OopsWare en 2006.

