#pragma once

#include <Engine/Object/Component.h>

#include <map>
using namespace std;

#include <Freetype/ft2build.h>
#include FT_FREETYPE_H

#define DEFAULT_FONT_SIZE 60
struct Character {
	GLuint TextureID;   // ID handle of the glyph texture
	vec2 Size;    // Size of glyph (pixels)
	vec2 Bearing;  // Offset from baseline to left/top of glyph (pixels)
	float Advance;    // Horizontal offset to advance to next glyph (pixels)
};

class Text : public Component {
public:
	void Mainloop();
	void Initialise();

	// GL
	inline static GLuint CharacterVAO = -1;
	inline static GLuint CharacterVBO = -1;
	inline static GLuint CharacterShader = -1;

	void InitialiseGLAttributes();
	void Render();

	// Text
	string FontFilePath = "Assets/Defaults/Font.ttf";
	map<GLchar, Character> * FontCharacters;
	string DisplayedText = "Default Text";

	inline static FT_Library FreetypeLibrary;
	inline static bool FreetypeInitialised = false;

	inline static map<string, map<GLchar, Character>> AllFonts;
	inline static map<GLchar, Character> * LoadFont(string FilePath);
};