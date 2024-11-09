#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "tinyfiledialogs.h" // For file explorer

class MediaPlayer {
private:
    std::string currentTrack; // Stores the name of the track
    sf::Music music;          // SFML Music object to handle audio playback

public:
    // Constructor
    MediaPlayer() : currentTrack("") {}

    // Load a track (abstraction)
    void loadTrack(const std::string& track) {
        currentTrack = track;
        if (!music.openFromFile(currentTrack)) { // Attempt to open the track file
            std::cerr << "Error loading track: " << currentTrack << std::endl;
        } else {
            std::cout << "Loaded track: " << currentTrack << std::endl;
        }
    }

    // Play the track
    void play() {
        if (!currentTrack.empty()) {
            music.play(); // Use SFML to play the music
            std::cout << "Playing track: " << currentTrack << std::endl;
        } else {
            std::cout << "No track loaded." << std::endl;
        }
    }

    // Pause the track
    void pause() {
        if (music.getStatus() == sf::SoundSource::Playing) {
            music.pause(); // Pause playback using SFML
            std::cout << "Paused track: " << currentTrack << std::endl;
        }
    }

    // Stop the track
    void stop() {
        if (music.getStatus() == sf::SoundSource::Playing) {
            music.stop(); // Stop playback using SFML
            std::cout << "Stopped playing: " << currentTrack << std::endl;
        }
    }

    // Open file explorer to choose a track
    void openFileExplorer() {
        const char* filters[] = { "*.ogg" }; // You can add other formats if needed
        const char* filePath = tinyfd_openFileDialog(
            "Select a music track", "", 1, filters, NULL, 0);
        if (filePath) {
            loadTrack(filePath);
        }
    }

    // Get the current track name
    std::string getCurrentTrack() const {
        return currentTrack;
    }
};

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(400, 300), "Simple Media Player");

    // Load font
    sf::Font font;
    if (!font.loadFromFile("BrownieStencil.ttf")) {
        std::cerr << "Error loading font\n";
        return -1;
    }

    MediaPlayer player;

    // Create buttons
    sf::RectangleShape playButton(sf::Vector2f(100, 50));
    playButton.setFillColor(sf::Color::Green);
    playButton.setPosition(50, 100);

    sf::RectangleShape pauseButton(sf::Vector2f(100, 50));
    pauseButton.setFillColor(sf::Color::Cyan);
    pauseButton.setPosition(150, 100);

    sf::RectangleShape stopButton(sf::Vector2f(100, 50));
    stopButton.setFillColor(sf::Color::Red);
    stopButton.setPosition(250, 100);

    sf::RectangleShape loadButton(sf::Vector2f(100, 50));
    loadButton.setFillColor(sf::Color::Blue);
    loadButton.setPosition(150, 200);

    // Texts for buttons
    sf::Text playText("Play", font, 20);
    playText.setPosition(65, 115);
    sf::Text pauseText("Pause", font, 20);
    pauseText.setPosition(165, 115);
    sf::Text stopText("Stop", font, 20);
    stopText.setPosition(265, 115);
    sf::Text loadText("Load", font, 20);
    loadText.setPosition(165, 215);

    // Run the main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Handle button clicks
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            // Play button
            if (playButton.getGlobalBounds().contains(mousePos)) {
                player.play();
            }

            // Pause button
            if (pauseButton.getGlobalBounds().contains(mousePos)) {
                player.pause();
            }

            // Stop button
            if (stopButton.getGlobalBounds().contains(mousePos)) {
                player.stop();
            }

            // Load button
            if (loadButton.getGlobalBounds().contains(mousePos)) {
                player.openFileExplorer();
            }
        }

        // Clear the window
        window.clear();

        // Draw buttons
        window.draw(playButton);
        window.draw(pauseButton);
        window.draw(stopButton);
        window.draw(loadButton);

        // Draw button labels
        window.draw(playText);
        window.draw(pauseText);
        window.draw(stopText);
        window.draw(loadText);

        // Display the contents of the window
        window.display();
    }

    return 0;
}
