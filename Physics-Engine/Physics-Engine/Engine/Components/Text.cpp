#include <Engine/Engine.h>
#include <Engine/Components/Text.h>

#include <Engine/Background/Shaders.h>
#include <GLM/gtc/matrix_transform.hpp>

void Text::Mainloop() {
	Initialise();
	Render();
}
void Text::Initialise() {
	if (initialised) {
		return;
	}

	FontCharacters = LoadFont(FontFilePath);
	InitialiseGLAttributes();

	initialised = true;
}

void Text::InitialiseGLAttributes() {
	if (CharacterVAO > -1) {
		return;
	}

	vector<float> ButtonVertices = {
		-1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 0.0f, 1.0f, 1.0f,

		-1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &CharacterVAO);
	glBindVertexArray(CharacterVAO);

	glGenBuffers(1, &CharacterVBO);
	glBindBuffer(GL_ARRAY_BUFFER, CharacterVBO);

	glBufferData(GL_ARRAY_BUFFER, ButtonVertices.size() * sizeof(float), ButtonVertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Shader
	int vertex = CreateShader("Assets/Shaders/Text_v.txt", GL_VERTEX_SHADER);
	int fragment = CreateShader("Assets/Shaders/Text_f.txt", GL_FRAGMENT_SHADER);

	CharacterShader = CreateProgram({ vertex, fragment });
}
void Text::Render() {
	glBindVertexArray(CharacterVAO);
	glUseProgram(CharacterShader);

	glActiveTexture(GL_TEXTURE0);
	SetShaderInt(CharacterShader, "texture0", 0);

	Transform* ObjectTransform = parentObject->GetComponent<Transform*>();
	SetShaderVec3(CharacterShader, "colour", vec3(1.0f));

	int TextLength = DisplayedText.length();
	for (int i = 0; i < TextLength; i++) {
		glBindTexture(GL_TEXTURE_2D, FontCharacters->at(DisplayedText[i]).TextureID);

		mat4 ModelMatrix = mat4(1.0f);
		

		SetShaderMat4(CharacterShader, "model", ModelMatrix);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
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

	vec2 MaxDimensions = ivec2(0);

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
			vec2(NewFont->glyph->bitmap.width, NewFont->glyph->bitmap.rows),
			vec2(NewFont->glyph->bitmap_left, NewFont->glyph->bitmap_top),
			NewFont->glyph->advance.x >> 6 // advance is measured in 1/64 of a pixels, so multiply by 2^6 to get to standard pixels
		};

		MaxDimensions = vec2(glm::max(NewCharacter.Size.x, MaxDimensions.x), glm::max(NewCharacter.Size.y, MaxDimensions.y));

		NewCharacterMap.insert(make_pair(character, NewCharacter));
	}

	FT_Done_Face(NewFont);
	
	// Normalise characters
	for (GLubyte character = 0; character < 128; character++) {
		NewCharacterMap[character].Size = NewCharacterMap[character].Size / MaxDimensions;
	}

	// Insert
	AllFonts.insert(make_pair(FilePath, NewCharacterMap));
	return &AllFonts[FilePath];
}