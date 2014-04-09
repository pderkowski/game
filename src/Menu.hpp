/* Copyright 2014 <Piotr Derkowski> */

#ifndef MENU_HPP_
#define MENU_HPP_

class Menu {
public:
    Menu(float width, float height);

    float width() const;
    float height() const;

private:
    float width_;
    float height_;
};

#endif  // MENU_HPP_
