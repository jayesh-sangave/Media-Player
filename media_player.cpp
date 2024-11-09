#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

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

    // Get the current track name
    std::string getCurrentTrack() const {
        return currentTrack;
    }
};

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(400, 300), "Simple Media Player");

    MediaPlayer player;
    player.loadTrack("/home/jxy/Documents/Jayesh/DS/x.ogg"); // Load an audio file (make sure to provide a valid path)

    // Create buttons
    sf::RectangleShape playButton(sf::Vector2f(100, 50));
    playButton.setFillColor(sf::Color::Green);
    playButton.setPosition(50, 100);

    sf::RectangleShape pauseButton(sf::Vector2f(100, 50));
    pauseButton.setFillColor(sf::Color::Yellow);
    pauseButton.setPosition(150, 100);

    sf::RectangleShape stopButton(sf::Vector2f(100, 50));
    stopButton.setFillColor(sf::Color::Red);
    stopButton.setPosition(250, 100);

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
        }

        // Clear the window
        window.clear();

        // Draw buttons
        window.draw(playButton);
        window.draw(pauseButton);
        window.draw(stopButton);

        // Display the contents of the window
        window.display();
    }

    return 0;
}
