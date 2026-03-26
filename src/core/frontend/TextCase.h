#pragma once

#include <raylib.h>
#include <string.h>
#include <string>
#include <unordered_set>

/*
Classe che permette la creazione di semplici caselle di testo:
-Il testo può essere preso come array di caratteri tramite il
 metodo getText
-Il testo può essere cancellato tramite il metodo clearText
-Sono evidenziati quando selezionati
-Comprendono un piccolo titolo inseiribile sopra di esse tramite
 il metodo setTitle
-Possono essere inserite delle restrizioni per i caratteri scritti
 tramite il metodo setValid, che prende un hashset contenente i
 caratteri validi
*/

class TextCase
{
public:
    TextCase(float posX, float posY, int width, int height, int max);
    ~TextCase();

    void event();
    void render();
    
    std::string getText();
    void clearText();

    void setScale(float xScale, float yScale);
    void setTitle(const char* title);
    void setValid(std::unordered_set<char> &valid);
    void unSelect();

private:
    Rectangle m_case;
    Rectangle m_scaled;

    const char* m_title;
    std::string m_text;
    int m_fontSize;
    int m_fontSizeScaled;
    int m_max;
    std::unordered_set<char> *m_valid;

    bool m_down;
    bool m_isUsing;
};