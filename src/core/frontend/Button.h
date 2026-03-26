#pragma once

#include <iostream>
#include <raylib.h>

/*
Classe che permette la creazione di semplici pulsanti:
-Reagiscono al click
-Comprendono un titolo da passare al costruttore
-Il click può essere verificato tramite il metodo pressed
*/

class Button
{    
public:
    Button(float posX, float posY, int width, int height, const char* title, int fontSize);

    bool pressed();

    void setScale(float xScale, float yScale);
    
    void render();
    
private:
    Rectangle m_case;
    Rectangle m_scaled;

    const char* m_title;
    int m_fontSize;
    int m_fontSizeScaled;
    bool m_down;
};