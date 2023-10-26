#pragma once
#include "All_Includes.h"

namespace sf {


class GameObject : public::Transformable {

};

}

//Nicht ganz. Um eine Klasse in C++ als abstrakt zu kennzeichnen, müssen Sie mindestens eine sogenannte "rein virtuelle Funktion" in der Klasse haben. 
//Eine rein virtuelle Funktion wird mit virtual und = 0 gekennzeichnet und hat keine Implementierung in der Basisklasse.
//In C++ gibt es keine direkte Entsprechung zur Schlüsselwort abstract, wie es in einigen anderen Programmiersprachen wie C# oder Java verwendet wird