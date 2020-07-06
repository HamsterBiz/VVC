// TestNaŁadowanieObrazu.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include "Image.h"
int main()
{
  Image* image = new Image(176, 144, 1);
  image->ReadVideo();

}


