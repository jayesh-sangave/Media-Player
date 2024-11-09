#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include "tinyfiledialogs.h" // For file explorer

namespace fs = std::filesystem;

class MediaPlayer {
private:
    std::vector<std::string> trackQueue;  // Stores the list of track names in the queue
    int currentTrackIndex;                // Index of the currently playing track
    sf::Music music;
    bool isPaused;

public:
    MediaPlayer() : currentTrackIndex(-1), isPaused(false) {}

    // Load all tracks from a folder
    void loadFolder(const std::string& folderPath) {
        trackQueue.clear();  // Clear any existing queue
        for (const auto& entry : fs::directory_iterator(folderPath)) {
            if (entry.path().extension() == ".ogg") {
                trackQueue.push_back(entry.path().string());
            }
        }
        if (!trackQueue.empty()) {
            currentTrackIndex = 0;  // Start with the first track
            loadTrack(trackQueue[currentTrackIndex]);
            std::cout << "Loaded folder: " << folderPath << " with " << trackQueue.size() << " tracks." << std::endl;
        } else {
            std::cerr << "No .ogg files found in folder: " << folderPath << std::endl;
        }
    }

    // Load a specific track
    void loadTrack(const std::string& trackPath) {
        if (!music.openFromFile(trackPath)) {
            std::cerr << "Error loading track: " << trackPath << std::endl;
        } else {
            std::cout << "Loaded track: " << trackPath << std::endl;
            isPaused = false;
        }
    }

    // Play or resume the track
    void play() {
        if (currentTrackIndex >= 0 && currentTrackIndex < trackQueue.size()) {
            if (isPaused) {
                music.play();
                isPaused = false;
                std::cout << "Resumed track: " << getFileName(trackQueue[currentTrackIndex]) << std::endl;
            } else if (music.getStatus() != sf::SoundSource::Playing) {
                loadTrack(trackQueue[currentTrackIndex]);
                music.play();
                std::cout << "Playing track: " << getFileName(trackQueue[currentTrackIndex]) << std::endl;
            }
        }
    }

    // Pause the track
    void pause() {
        if (music.getStatus() == sf::SoundSource::Playing) {
            music.pause();
            isPaused = true;
            std::cout << "Paused track: " << getFileName(trackQueue[currentTrackIndex]) << std::endl;
        }
    }

    // Stop the track
    void stop() {
        if (music.getStatus() == sf::SoundSource::Playing || isPaused) {
            music.stop();
            isPaused = false;
            std::cout << "Stopped playing: " << getFileName(trackQueue[currentTrackIndex]) << std::endl;
        }
    }

    // Get the file name from a full path
    std::string getFileName(const std::string& filePath) const {
        size_t lastSlashPos = filePath.find_last_of("/\\");
        return (lastSlashPos == std::string::npos) ? filePath : filePath.substr(lastSlashPos + 1);
    }

    // Get the current track name
    std::string getCurrentTrack() const {
        return currentTrackIndex >= 0 ? getFileName(trackQueue[currentTrackIndex]) : "No track loaded";
    }

    // Get the track queue
    const std::vector<std::string>& getTrackQueue() const {
        return trackQueue;
    }
};

int main() {
    // Create a larger window
    sf::RenderWindow window(sf::VideoMode(600, 500), "Enhanced Media Player");

    // Load font
    sf::Font font;
    if (!font.loadFromFile("BrownieStencil.ttf")) {
        std::cerr << "Error loading font\n";
        return -1;
    }

    MediaPlayer player;

    // Create and align buttons
    sf::RectangleShape playButton(sf::Vector2f(100, 50));
    playButton.setFillColor(sf::Color::Green);
    playButton.setPosition(50, 100);

    sf::RectangleShape pauseButton(sf::Vector2f(100, 50));
    pauseButton.setFillColor(sf::Color::Cyan);
    pauseButton.setPosition(200, 100);

    sf::RectangleShape stopButton(sf::Vector2f(100, 50));
    stopButton.setFillColor(sf::Color::Red);
    stopButton.setPosition(350, 100);

    sf::RectangleShape loadFolderButton(sf::Vector2f(150, 50));
    loadFolderButton.setFillColor(sf::Color::Blue);
    loadFolderButton.setPosition(225, 200);

    // Texts for buttons
    sf::Text playText("Play", font, 20);
    playText.setPosition(70, 115);
    sf::Text pauseText("Pause", font, 20);
    pauseText.setPosition(220, 115);
    sf::Text stopText("Stop", font, 20);
    stopText.setPosition(370, 115);
    sf::Text loadFolderText("Load Folder", font, 20);
    loadFolderText.setPosition(245, 215);

    // Title
    sf::Text title("Enhanced Media Player", font, 25);
    title.setPosition(150, 20);

    // Track name display
    sf::Text trackName("No track loaded", font, 15);
    trackName.setPosition(50, 300);

    // Queue display
    sf::Text queueTitle("Track Queue:", font, 20);
    queueTitle.setPosition(50, 340);

    sf::Text queueList("", font, 15);
    queueList.setPosition(50, 370);

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Handle button clicks
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            if (playButton.getGlobalBounds().contains(mousePos)) {
                player.play();
            }

            if (pauseButton.getGlobalBounds().contains(mousePos)) {
                player.pause();
            }

            if (stopButton.getGlobalBounds().contains(mousePos)) {
                player.stop();
            }

            if (loadFolderButton.getGlobalBounds().contains(mousePos)) {
                const char* folderPath = tinyfd_selectFolderDialog("Select Music Folder", "");
                if (folderPath) {
                    player.loadFolder(folderPath);
                    trackName.setString("Now Playing: " + player.getCurrentTrack());

                    // Update queue list display
                    std::string queueText;
                    for (const auto& track : player.getTrackQueue()) {
                        queueText += player.getFileName(track) + "\n";
                    }
                    queueList.setString(queueText);
                }
            }
        }

        // Clear the window
        window.clear();

        // Draw elements
        window.draw(playButton);
        window.draw(pauseButton);
        window.draw(stopButton);
        window.draw(loadFolderButton);
        window.draw(playText);
        window.draw(pauseText);
        window.draw(stopText);
        window.draw(loadFolderText);
        window.draw(title);
        window.draw(trackName);
        window.draw(queueTitle);
        window.draw(queueList);

        // Display the contents of the window
        window.display();
    }

    return 0;
}
