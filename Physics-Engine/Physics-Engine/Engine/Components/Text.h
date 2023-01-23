#pragma once

#include <Engine/Object/Component.h>

#include <map>
using namespace std;

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
	void Initialise();

	string FontFilePath = "Assets/Defaults/Font.ttf";
	map<GLchar, Character> * FontCharacters;

	inline static FT_Library FreetypeLibrary;
	inline static bool FreetypeInitialised = false;

	inline static map<string, map<GLchar, Character>> AllFonts;
	inline static map<GLchar, Character> * LoadFont(string FilePath);
};