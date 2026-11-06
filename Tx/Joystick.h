#ifndef JOYSTICK_H
#define JOYSTICK_H

// Defines the structure for a joystick, mostly used to neatly pack transmitted values
struct Joystick
{
    int x;
    int y;

    bool sw;
};


#endif // JOYSTICK_H
