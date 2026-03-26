#pragma once

#include <raylib.h>
#include <iostream>

/*
Classe che permette la creazione di semplici checkbox:
-Vengono selezionate e deselezionate
-Comprendono un titolo da passare al costruttore
-Il click viene verificato tramite la funzione event
-Lo stato della checkbox(selezionata o no) viene preso con getStatus
*/

class Checkbox
{
public:
    Checkbox(float posX, float posY, int side, const char* title);

    void event();
    bool getStatus();

    void setScale(float xScale, float yScale);
    
    void render();
    
private:
    Rectangle m_case;
    Rectangle m_scaled;
    const char* m_title;
    float m_fontSizeScaled;

    bool m_status;
    bool m_down;
};