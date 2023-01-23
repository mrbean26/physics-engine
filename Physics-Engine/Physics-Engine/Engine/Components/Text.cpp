#include <Engine/Engine.h>
#include <Engine/Components/Text.h>

void Text::Mainloop() {
	Initialise();
}
void Text::Initialise() {
	if (initialised) {
		return;
	}

	FontCharacters = LoadFont(FontFilePath);

	initialised = true;
}

map<GLchar, Character>* Text::LoadFont(string FilePath) {
	// check if already loaded
	if (AllFonts.find(FilePath) != AllFonts.end()) {
		return &AllFonts[FilePath];
	}

	// initialise
	if (!FreetypeInitialised) {
		if (FT_Init_FreeType(&FreetypeLibrary)) {
			throw "Freetype cannot be initialised";
		}
	}

	// load
	FT_Face NewFont;
	if (FT_New_Face(FreetypeLibrary, FilePath.data(), 0, &NewFont)) {
		throw ("Could not load font:" + FilePath).data();
	}

	FT_Set_Pixel_Sizes(NewFont, 0, DEFAULT_FONT_SIZE);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Load First 128 ASCII Characters
	map<GLchar, Character> NewCharacterMap;

	for (GLubyte character = 0; character < 128; character++) {
		if (FT_Load_Char(NewFont, character, FT_LOAD_RENDER)) {
			throw ("Could not load character:" + to_string(character) + ", font: " + FilePath).data();
		}

		// Generate GL Texture
		GLuint newTextureID;
		glGenTextures(1, &newTextureID);
		glBindTexture(GL_TEXTURE_2D, newTextureID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, NewFont->glyph->bitmap.width, NewFont->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, NewFont->glyph->bitmap.buffer);
		
		// Texture Options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Store
		Character NewCharacter = {
			newTextureID,
			ivec2(NewFont->glyph->bitmap.width, NewFont->glyph->bitmap.rows),
			ivec2(NewFont->glyph->bitmap_left, NewFont->glyph->bitmap_top),
			NewFont->glyph->advance.x
		};

		NewCharacterMap.insert(make_pair(character, NewCharacter));
	}

	FT_Done_Face(NewFont);
	
	AllFonts.insert(make_pair(FilePath, NewCharacterMap));
	return &AllFonts[FilePath];
}