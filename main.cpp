#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>
#include <algorithm>

// Simple command-line music player demonstrating:
// - variables, expressions, conditionals, loops, functions, classes
// - STL data structures (std::vector)
// - file I/O (load/save playlist)
// - dynamic allocation (new/delete) for sf::Music

class MusicPlayer {
private:
std::vector<std::string> playlist; // STL vector // STL vector
int currentIndex = -1;             // variable & expression use
sf::Music* music = nullptr;        // dynamically allocated music object (new/delete)
bool looping = false;
float volume = 100.f; // 0-100


static std::string statusToString(sf::SoundSource::Status s) {
    switch (s) {
        case sf::SoundSource::Stopped: return "Stopped";
        case sf::SoundSource::Paused:  return "Paused";
        case sf::SoundSource::Playing: return "Playing";
        default: return "Unknown";
    }
}


public:
MusicPlayer() = default;

~MusicPlayer() {
    if (music) {
        music->stop();
        delete music;
        music = nullptr;
    }
}

// File I/O: load playlist from a text file (one path per line)
bool loadPlaylistFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) return false;
    std::string line;
    playlist.clear();
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        playlist.push_back(line);
    }
    currentIndex = playlist.empty() ? -1 : 0;
    return true;
}

// File I/O: save playlist to file
bool savePlaylistToFile(const std::string& filename) {
    std::ofstream out(filename);
    if (!out.is_open()) return false;
    for (const auto &p : playlist) out << p << '\n';
    return true;
}

void addSong(const std::string& path) {
    playlist.push_back(path);
    if (currentIndex == -1) currentIndex = 0;
}

bool openTrack(int index) {
    if (index < 0 || index >= static_cast<int>(playlist.size())) return false;
    if (music) {
        music->stop();
        delete music;
        music = nullptr;
    }
    music = new sf::Music(); // demonstration of 'new'
    if (!music->openFromFile(playlist[index])) {
        std::cerr << "Failed to open: " << playlist[index] << std::endl;
        delete music;
        music = nullptr;
        return false;
    }
    music->setVolume(volume);
    music->setLoop(looping);
    currentIndex = index;
    return true;
}

void play() {
    if (!music) {
        if (currentIndex == -1) {
            if (playlist.empty()) {
                std::cout << "No songs in playlist.\n";
                return;
            }
            if (!openTrack(0)) return;
        } else {
            if (!openTrack(currentIndex)) return;
        }
    }
    music->play();
}

void pause() {
    if (music) music->pause();
}

void stop() {
    if (music) music->stop();
}

void next() {
    if (playlist.empty()) return;
    int nextIndex = (currentIndex + 1) % static_cast<int>(playlist.size());
    if (openTrack(nextIndex)) music->play();
}

void previous() {
    if (playlist.empty()) return;
    int prevIndex = (currentIndex - 1 + static_cast<int>(playlist.size())) % static_cast<int>(playlist.size());
    if (openTrack(prevIndex)) music->play();
}

void setVolume(float v) {
    volume = std::clamp(v, 0.f, 100.f);
    if (music) music->setVolume(volume);
}

void toggleLoop() {
    looping = !looping;
    if (music) music->setLoop(looping);
    std::cout << "Looping is now " << (looping ? "ON" : "OFF") << std::endl;
}

void printPlaylist() const {
    std::cout << "Playlist (" << playlist.size() << "):\n";
    for (size_t i = 0; i < playlist.size(); ++i) {
        std::cout << (static_cast<int>(i) == currentIndex ? " -> " : "    ")
                  << i << ": " << playlist[i] << '\n';
    }
}

void printStatus() const {
    std::cout << "Status: ";
    if (music) {
        std::cout << statusToString(music->getStatus());
        if (currentIndex >= 0 && currentIndex < static_cast<int>(playlist.size())) {
            std::cout << " | Track: " << playlist[currentIndex];
        }
        std::cout << " | Volume: " << volume;
        std::cout << " | Loop: " << (looping ? "Yes" : "No");
        std::cout << '\n';
    } else {
        std::cout << "No track loaded\n";
    }
}

// Simple CLI loop (demonstrates loops & conditionals)
void runCLI(const std::string& playlistFile) {
    bool running = true;
    while (running) {
        std::cout << "\n--- Simple Music Player ---\n";
        printStatus();
        std::cout << "Commands:\n"
                  << " (L)oad playlist from file\n"
                  << " (S)ave playlist to file\n"
                  << " (A)dd song (path)\n"
                  << " (P)lay\n"
                  << " (U)Pause\n"
                  << " S(t)op\n"
                  << " (N)ext\n"
                  << " (B)ack (previous)\n"
                  << " (V)olume set\n"
                  << " (O) Toggle loop\n"
                  << " (D)ump playlist\n"
                  << " (Q)uit\n"
                  << "Choice: ";
        std::string choice;
        std::getline(std::cin, choice);
        if (choice.empty()) continue;
        char c = std::toupper(choice[0]);

        if (c == 'L') {
            if (loadPlaylistFromFile(playlistFile)) {
                std::cout << "Loaded playlist from " << playlistFile << '\n';
            } else {
                std::cout << "Failed to load playlist from " << playlistFile << '\n';
            }
        } else if (c == 'S') {
            if (savePlaylistToFile(playlistFile))
                std::cout << "Saved playlist to " << playlistFile << '\n';
            else
                std::cout << "Failed to save playlist to " << playlistFile << '\n';
        } else if (c == 'A') {
            std::cout << "Enter path to audio file: ";
            std::string path;
            std::getline(std::cin, path);
            if (!path.empty()) addSong(path);
        } else if (c == 'P') {
            play();
        } else if (c == 'U') {
            pause();
        } else if (c == 'T') { // Stop (S t)
            stop();
        } else if (c == 'N') {
            next();
        } else if (c == 'B') {
            previous();
        } else if (c == 'V') {
            std::cout << "Enter volume (0-100): ";
            std::string v;
            std::getline(std::cin, v);
            try {
                float fv = std::stof(v);
                setVolume(fv);
            } catch (...) {
                std::cout << "Invalid volume\n";
            }
        } else if (c == 'O') {
            toggleLoop();
        } else if (c == 'D') {
            printPlaylist();
        } else if (c == 'Q') {
            running = false;
            stop();
            std::cout << "Exiting.\n";
        } else {
            std::cout << "Unknown command: " << c << '\n';
        }

        // small sleep so the loop isn't too tight
        std::this_thread::sleep_for(std::chrono::milliseconds(120));
    }
}


};

int main() {
const std::string playlistFile = "playlist.txt";


MusicPlayer player;
// Try to auto-load playlist
if (player.loadPlaylistFromFile(playlistFile)) {
    std::cout << "Loaded playlist: " << playlistFile << std::endl;
    // ✅ Auto-play the first song
    player.play();
    std::cout << "Now playing first track automatically...\n";
} else {
    std::cout << "No playlist found, start by adding songs (A) or load manually (L)." << std::endl;
}

// Continue with interactive menu
player.runCLI(playlistFile);
return 0;


}

