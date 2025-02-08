# Media Player

A simple media player built using **SFML** for audio playback and **tinyfiledialogs** for file selection. The application allows users to load individual tracks or entire folders of music files and provides basic playback controls.

## Features
- **Load Individual Track:** Select and play a single audio file.
- **Load Folder:** Load all `.ogg` files from a folder into the queue.
- **Playback Controls:** Play, pause, stop, next track, and previous track functionality.
- **Track Queue:** Displays and navigates through multiple tracks.
- **Graphical Interface:** SFML-based UI with buttons for easy interaction.

## Prerequisites
- C++ compiler (g++)
- SFML library (`libsfml-dev` on Linux)
- `tinyfiledialogs` library

## Installation & Compilation

### Install SFML (if not installed)
#### On Ubuntu/Debian:
```bash
sudo apt-get install libsfml-dev
```
#### On Windows:
Download SFML from [SFML's official website](https://www.sfml-dev.org/) and set up your compiler.

### Clone and Compile
```bash
g++ -std=c++17 media_player.cpp tinyfiledialogs.c -o media_player -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system
```

## Usage
Run the compiled executable:
```bash
./media_player
```

## Controls
- **Load Track:** Opens a file explorer to choose a single `.ogg` file.
- **Load Folder:** Select a folder to load all `.ogg` files into the queue.
- **Play:** Plays or resumes the current track.
- **Pause:** Pauses the current track.
- **Stop:** Stops the current track.
- **Next:** Moves to the next track in the queue.
- **Previous:** Moves to the previous track in the queue.

## Notes
- This player currently supports **.ogg** files only. Other formats may require additional codecs.
- If no track is loaded, playback buttons will have no effect.

## License
This project is open-source. Feel free to modify and improve it!

## Acknowledgments
- **SFML** for audio and graphics handling.
- **tinyfiledialogs** for file selection dialogs.

