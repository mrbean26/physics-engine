#pragma once

#include <Engine/Object/Component.h>

#include <Freetype/ft2build.h>
#include FT_FREETYPE_H

#define DEFAULT_FONT_SIZE 30
struct Character {
	GLuint TextureID;   // ID handle of the glyph texture
	ivec2 Size;    // Size of glyph
	ivec2 Bearing;  // Offset from baseline to left/top of glyph
	GLuint Advance;    // Horizontal offset to advance to next glyph
};

class Text : public Component {
public:
	void Mainloop();

	string fontFilePath;
	map<GLchar, Character> * fontCharacters;
};