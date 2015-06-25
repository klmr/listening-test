#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <vector>

struct sound_generator {
    void play(int frequency, sf::Time duration) {
        unsigned constexpr sample_rate{44100};

        unsigned const samples_size{static_cast<unsigned>(sample_rate * duration.asSeconds())};
        std::vector<sf::Int16> samples(samples_size);

        unsigned const amplitude{30000};
        double const two_pi{2 * 4 * std::atan(1)};
        double const increment{static_cast<double>(frequency) / sample_rate};
        double x{};
        for (unsigned i{}; i < samples_size; ++i) {
            samples[i] = amplitude * std::sin(x * two_pi);
            x += increment;
        }

        if (not sound_buffer.loadFromSamples(samples.data(), samples_size, 1, sample_rate))
            throw "Failed to load buffer";

        sound.setBuffer(sound_buffer);
        sound.play();
    }

    void stop() {
        sound.stop();
    }

    sf::SoundBuffer sound_buffer;
    sf::Sound sound;
};

unsigned find_inaudible(unsigned start, unsigned stop, unsigned step) {
    sound_generator gen;
    for (unsigned i{start}; i < stop; i += step) {
        gen.play(i, sf::milliseconds(500));
        while (gen.sound.getStatus() == sf::SoundSource::Status::Playing) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                return i;
            sf::sleep(sf::milliseconds(10));
        }
    }

    return stop;
}

int main() try {
    std::cout << "Press <Return> once you cannot hear the sound any more." << std::flush;
    unsigned const start{1000};
    unsigned const stop{24000};
    unsigned const step{500};
    unsigned const result = find_inaudible(start, stop, step);
    std::cout << "You stopped hearing sound at " << result << " Hz frequency\n";
}
catch (...) {
    std::cerr << "An error occurred\n";
    return 1;
}
