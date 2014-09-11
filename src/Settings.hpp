/* Copyright 2014 <Piotr Derkowski> */

#ifndef Settings_HPP_
#define Settings_HPP_


struct Settings {
    static Settings getDefaultSettings();

    unsigned rows;
    unsigned columns;
    unsigned tileWidth;
    unsigned tileHeight;
};


#endif  // Settings_HPP_
