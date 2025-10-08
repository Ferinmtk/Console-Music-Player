# 🎵 Simple C++ Music Player

A basic command-line music player written in **C++17** using the **SFML Audio** library.
It supports loading playlists, adding songs, playing, pausing, skipping, and saving your music list.

---

## Features

* Play `.ogg` or `.wav` audio files
* Load and save playlists from a file
* Add songs manually or automatically
* Control playback (Play, Pause, Stop, Next, Previous)
* Adjustable volume
* Loop mode toggle
* Uses C++ classes, STL vectors, conditionals, loops, and file I/O

---

##  Requirements

* **Fedora Linux** (or any Linux with GCC & SFML)
* **SFML Audio library**
* **C++17 compiler**

Install dependencies:

```bash
sudo dnf install sfml-devel ffmpeg
```

---
 Folder Structure

```
music_player/
├── main.cpp
├── player
├── playlist.txt
└── songs/
    ├── track1.ogg
    └── track2.ogg
```

---

##  Playlist Format

Each line in `playlist.txt` should contain a valid relative path to a song file:

```
songs/ETHIC - PANDANA.ogg
songs/Lil Uzi Vert - You Was Right.ogg
```

---

##  Compilation

Compile with:

```bash
g++ -std=c++17 main.cpp -o player -lsfml-audio -lsfml-system
```

---

## ▶ Running

Run the program:

```bash
./player
```

If the playlist is in place, load it with:

```
L
```

Then play music:

```
P
```

---

## 🎛️ Commands

| Command | Description             |
| ------- | ----------------------- |
| L       | Load playlist from file |
| S       | Save playlist to file   |
| A       | Add a song path         |
| P       | Play                    |
| U       | Pause                   |
| t       | Stop                    |
| N       | Next song               |
| B       | Previous song           |
| V       | Set volume              |
| O       | Toggle loop mode        |
| D       | Dump playlist           |
| Q       | Quit                    |

---

##  Notes

* Supported formats: `.ogg`, `.wav`
* `.mp3` is **not** supported by SFML
* Convert MP3 files using:

  ```bash
  ffmpeg -i input.mp3 output.ogg
  ```
* Ensure `playlist.txt` has **no trailing spaces** in its filename

---

##  Educational Value

This project demonstrates:

* Variables, expressions, conditionals, and loops
* Functions and classes
* STL `vector` data structure
* File input/output
* Dynamic memory allocation (`new` / `delete`)

---

##  Author

**Ferin Armstrong Mutuku**
C++ | Data Analysis | Software Development | BYU IDAHO Projects# Console-Music-Player
