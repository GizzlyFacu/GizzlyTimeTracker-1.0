This is literally my first project with Qt and C++. The principal concept/idea of this project is a personal time tracker for my daily study-time. I just wanted to make something like the Steam Recent-Activity wall.
How this little app works? When you click the Guardar Button, this actually saves your time-data inside a JSON file (Using the nlohmann c++ json library). Doesn't save automatically.
About future updates:
1. This project is basic asf, so I really want to make a better app with better front-end and settings using Qt Designer or another tool like Tauri.
2. France.
3. One of the reasons I chose JSON was: for make a connection between another app I've made that shows the time spent in discord, but I'll add this feature later... maybe.

Obsidian Personal Notes: (SPANISH)
- Name: GizzlyTimeTracker-1.0.
- Estado: FINALIZADO
- Descripcion: Tracker de horas de X actividad. Principalmente destinada a: Informarme sobre cuanto tiempo gasto estudiando VS tiempo gastado jugando e Informarme cuantas horas llevo estudiando X Materia.

Update Notes:

 | 17/03/2024 | - Hice toda la parte del back basica, punteros de structs guardadas en un vector, funcionalidad basica de casi todos los botones / cBox, Qtimer funcional.
Que me falta?:
- Guardar los segundos del QTimer en el struct.
- Mejorar imagen de UI en formato HH:MM:SS.
- Poder Editar el nombre de la config.
- Exportar E importar.
- | 21/03/2024 | - Complete lo de arriba, quite un boton de Cambiar Nombre, y aprendi cosas nuevas con respecto a los [[Signal & Slots 2 UI Objects]]. Solo me queda pendiente:
- Exportar E Importar.
- | 24/03/2024 | - Ya termine todo. Hay un bug nomas que por alguna razon no me deja borrar. Pero bueno despues sacare nuevas versiones.
- Dejar mas bonito y subir a GitHub.
- | 26/03/2024 | - Subido y Finalizado.
