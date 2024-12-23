#include "Ship.h"
#include <stdexcept>
#include <iostream>
Ship::Ship(int length) {
    if (length < 1 || length > 4) {
        throw std::invalid_argument("Ship length must be between 1 and 4");
    }
    this->length = length;
    for (int i = 0; i < length; i++) {
        segments[i] = SegmentState::intact;
    }
}

bool Ship::isDestroyed() {
    for (int i = 0; i < length; i++) {
        if (segments[i] != SegmentState::destroyed) {
            return false;
        }
    }
    return true;
}

int Ship::getLength() {
    return length;
}

void Ship::setSegmentState(int index, SegmentState state) {
    if (index < 0 || index >= length) {
        throw std::invalid_argument("Invalid segment index");
    }
    segments[index] = state;
}

SegmentState* Ship::getSegmentState(int index) {
    if (index < 0 || index >= length) {
        throw std::invalid_argument("Invalid segment index");
    }
    return &segments[index];
}