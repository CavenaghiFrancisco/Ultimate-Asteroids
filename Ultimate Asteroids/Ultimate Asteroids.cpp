#include "raylib.h"
#include <math.h>
#include "intro.h"

void main() {
	Intro* intro = new Intro();
	intro->StartIntro();
	delete intro;
}
