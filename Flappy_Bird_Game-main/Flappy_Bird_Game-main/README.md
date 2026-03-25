#  Flappy Bird Clone in C++ & SFML

A simple, beginner-friendly **Flappy Bird** clone created using **C++** and the **SFML 2.5.1** graphics library.

---

##  Gameplay

- Press **Space** to flap
- Avoid hitting the pipes
- Earn points by flying through gaps
- Game over if you crash!

---

##  Features

- Smooth 2D graphics with SFML
- Custom sprites and sound effects
- Object-Oriented code structure
- Scoring system
- Game over logic

---

##  Folder Structure

<img width="701" height="765" alt="image" src="https://github.com/user-attachments/assets/aa61389f-5616-4a26-b12b-e337caf6c4eb" />

---

##  How to Run

###  Prerequisites

- Visual Studio 2022
- SFML 2.5.1 (download: https://www.sfml-dev.org/download.php)


## 	Set Include and Library Paths

-	Click Project > Properties
-	Set to "All Configurations" (top dropdown)
-	Set Platform to "x86"

-set path,

C/C++ → General → Additional Include Directories	..\..\ YourGameProject\lib\SFML-2.5.1\include

Linker → General → Additional Library Directories	..\..\ YourGameProject\lib\SFML-2.5.1\lib

Linker → Input → Additional Dependencies	

For Release mode:

sfml-graphics.lib,
sfml-window.lib,
sfml-system.lib,
sfml-audio.lib,

For Debug mode:
 
sfml-graphics-d.lib,
sfml-window-d.lib, 
sfml-system-d.lib,
sfml-audio-d.lib,





