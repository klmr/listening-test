#include <SFML/Audio.hpp>
#include <cmath>
#include <iostream>

int main() {
    unsigned constexpr samples = 44100;
    unsigned constexpr rate = 44100;

    unsigned constexpr amplitude = 30000;
    double constexpr two_pi = 6.28318;
    double constexpr increment = 440.0 / 44100;

    sf::Int16 raw_buffer[samples];

    double x{};
    for (unsigned i{}; i < samples; ++i) {
        raw_buffer[i] = amplitude * std::sin(x * two_pi);
        x += increment;
    }

    sf::SoundBuffer buffer;
    if (! buffer.loadFromSamples(raw_buffer, samples, 1, rate)) {
        std::cerr << "Loading failed\n";
        return 1;
    }

    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.setLoop(true);
    sound.play();
    for (;;)
        sf::sleep(sf::milliseconds(100));
}
