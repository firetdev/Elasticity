#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

sf::Color HSVtoRGB(float h, float s, float v) {
    float c = v * s;
    float x = c * (1 - std::fabs(std::fmod(h / 60.f, 2) - 1));
    float m = v - c;

    float r = 0, g = 0, b = 0;

    if (h < 60) {
        r = c; g = x; b = 0;
    }
    else if (h < 120) {
        r = x; g = c; b = 0;
    }
    else if (h < 180) {
        r = 0; g = c; b = x;
    }
    else if (h < 240) {
        r = 0; g = x; b = c;
    }
    else if (h < 300) {
        r = x; g = 0; b = c;
    }
    else {
        r = c; g = 0; b = x;
    }

    return sf::Color(
        static_cast<std::uint8_t>((r + m) * 255),
        static_cast<std::uint8_t>((g + m) * 255),
        static_cast<std::uint8_t>((b + m) * 255)
    );
}
