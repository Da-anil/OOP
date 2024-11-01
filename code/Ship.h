#pragma once

enum class SegmentState { intact = 2, damaged = 1, destroyed = 0 };
enum class Direction { horizontal, vertical };
class Ship {
    private:
        int length;
        SegmentState segments[4];
    public:
        Ship(int length);
        bool isDestroyed();
        int getLength();
        SegmentState* getSegmentState(int index);
};