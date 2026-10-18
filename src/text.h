/*
Font LoadFontFromImage(Image image, Color key, int firstChar);                                    // Load font from Image (XNA style)
CharInfo *LoadFontData(const char *fileName, int fontSize, int *fontChars, int charsCount, int type); // Load font data for further use
Image GenImageFontAtlas(CharInfo *chars, int charsCount, int fontSize, int padding, int packMethod);  // Generate image font atlas using chars info
*/

/* Get a c like string, but also works with buffers. */
static const char *jaylib_getcstring(const Janet *argv, int32_t n) {
    if (janet_checktype(argv[n], JANET_BUFFER)) {
        JanetBuffer *buf = janet_unwrap_buffer(argv[n]);
        janet_buffer_push_u8(buf, 0);
        buf->count--;
        return (const char *)buf->data;
    }
    return janet_getcstring(argv, n);
}

static Janet cfun_GetFontDefault(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    Font *font = janet_abstract(&AT_Font, sizeof(Font));
    *font = GetFontDefault();
    return janet_wrap_abstract(font);
}

static Janet cfun_LoadFont(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    const char *fileName = janet_getcstring(argv, 0);
    Font *font = janet_abstract(&AT_Font, sizeof(Font));
    *font = LoadFont(fileName);
    return janet_wrap_abstract(font);
}

static Janet cfun_IsFontValid(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Font font = *jaylib_getfont(argv, 0);
    if (IsFontValid(font)) {
        return janet_wrap_true();
    } else {
        return janet_wrap_false();
    }
}

static Janet cfun_LoadFontEx(int32_t argc, Janet *argv) {
    janet_arity(argc, 2, 3);
    const char *fileName = janet_getcstring(argv, 0);
    int fontSize = janet_getinteger(argv, 1);
    Font *font = janet_abstract(&AT_Font, sizeof(Font));
    if (argc == 2) {
        *font = LoadFontEx(fileName, fontSize, NULL, 0);
    } else {
        JanetView ints = janet_getindexed(argv, 2);
        int *raw_ints = janet_smalloc(sizeof(int) * ints.len);
        for (int32_t i = 0; i < ints.len; i++) {
            raw_ints[i] = janet_getinteger(ints.items, i);
        }
        *font = LoadFontEx(fileName, fontSize, raw_ints, ints.len);
        janet_sfree(raw_ints);
    }
    return janet_wrap_abstract(font);
}

static Janet cfun_LoadFontFromMemory(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 5);

    const char *fileType = janet_getcstring(argv, 0);
    const unsigned char *fileData = jaylib_getunsignedcstring(argv, 1);
    int dataSize = janet_getinteger(argv, 2);
    int fontSize = janet_getinteger(argv, 3);
    JanetView ints = janet_getindexed(argv, 4);
    int *raw_ints = janet_smalloc(sizeof(int) * ints.len);
    for (int32_t i = 0; i < ints.len; i++) {
        raw_ints[i] = janet_getinteger(ints.items, i);
    }
    Font *font = janet_abstract(&AT_Font, sizeof(Font));
    *font = LoadFontFromMemory(fileType, fileData, dataSize, fontSize, raw_ints, ints.len);
    janet_sfree(raw_ints);
    return janet_wrap_abstract(font);
}

static Janet cfun_UnloadFont(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Font font = *jaylib_getfont(argv, 0);
    UnloadFont(font);
    return janet_wrap_nil();
}

static Janet cfun_DrawFPS(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    int x = janet_getinteger(argv, 0);
    int y = janet_getinteger(argv, 1);
    DrawFPS(x, y);
    return janet_wrap_nil();
}

static Janet cfun_DrawText(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 5);
    const char *text = jaylib_getcstring(argv, 0);
    int x = janet_getinteger(argv, 1);
    int y = janet_getinteger(argv, 2);
    int fontSize = janet_getinteger(argv, 3);
    Color color = jaylib_getcolor(argv, 4);
    DrawText(text, x, y, fontSize, color);
    return janet_wrap_nil();
}

static Janet cfun_DrawTextEx(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 6);
    Font font = *jaylib_getfont(argv, 0);
    const char *text = jaylib_getcstring(argv, 1);
    Vector2 position = jaylib_getvec2(argv, 2);
    float fontSize = (float) janet_getnumber(argv, 3);
    float spacing = (float) janet_getnumber(argv, 4);
    Color color = jaylib_getcolor(argv, 5);
    DrawTextEx(font, text, position, fontSize, spacing, color);
    return janet_wrap_nil();
}

static Janet cfun_DrawTextPro(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 8);
    Font font = *jaylib_getfont(argv, 0);
    const char *text = jaylib_getcstring(argv, 1);
    Vector2 position = jaylib_getvec2(argv, 2);
    Vector2 origin = jaylib_getvec2(argv, 3);
    float rotation = (float) janet_getnumber(argv, 4);
    float fontSize = (float) janet_getnumber(argv, 5);
    float spacing = (float) janet_getnumber(argv, 6);
    Color tint = jaylib_getcolor(argv, 7);
    DrawTextPro(font, text, position, origin, rotation, fontSize, spacing, tint);
    return janet_wrap_nil();
}

static Janet cfun_DrawTextCodepoint(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 5);
    Font font = *jaylib_getfont(argv, 0);
    int codepoint = janet_getinteger(argv, 1);
    Vector2 position = jaylib_getvec2(argv, 2);
    float fontSize = (float) janet_getnumber(argv, 3);
    Color tint = jaylib_getcolor(argv, 4);
    DrawTextCodepoint(font, codepoint, position, fontSize, tint);
    return janet_wrap_nil();
}

static Janet cfun_DrawTextCodepoints(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 6);
    Font font = *jaylib_getfont(argv, 0);
    JanetView ints = janet_getindexed(argv, 1);
    int *raw_ints = janet_smalloc(sizeof(int) * ints.len);
    for (int32_t i = 0; i < ints.len; i++) {
        raw_ints[i] = janet_getinteger(ints.items, i);
    }
    Vector2 position = jaylib_getvec2(argv, 2);
    float fontSize = (float) janet_getnumber(argv, 3);
    float spacing = (float) janet_getnumber(argv, 4);
    Color tint = jaylib_getcolor(argv, 5);
    DrawTextCodepoints(font, raw_ints, ints.len, position, fontSize, spacing, tint);
    janet_sfree(raw_ints);
    return janet_wrap_nil();
}


static Janet cfun_MeasureText(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    const char *text = jaylib_getcstring(argv, 0);
    int fontSize = janet_getinteger(argv, 1);
    return janet_wrap_integer(MeasureText(text, fontSize));
}

static Janet cfun_MeasureTextEx(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    Font font = *jaylib_getfont(argv, 0);
    const char *text = jaylib_getcstring(argv, 1);
    float fontSize = (float) janet_getnumber(argv, 2);
    float spacing = (float) janet_getnumber(argv, 3);
    return jaylib_wrap_vec2(MeasureTextEx(font, text, fontSize, spacing));
}

static Janet cfun_GetGlyphIndex(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Font font = *jaylib_getfont(argv, 0);
    int character = janet_getinteger(argv, 1);
    return janet_wrap_integer(GetGlyphIndex(font, character));
}

static Janet cfun_GetFontTexture(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Font font = *jaylib_getfont(argv, 0);
    Texture2D *texture = janet_abstract(&AT_Texture2D, sizeof(Texture2D));
    *texture = font.texture;
    return janet_wrap_abstract(texture);
}

static Janet cfun_MeasureTextCodepoints(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    Font font = *jaylib_getfont(argv, 0);
    JanetView ints = janet_getindexed(argv, 1);
    int *raw_ints = janet_smalloc(sizeof(int) * ints.len);
    for (int32_t i = 0; i < ints.len; i++) {
        raw_ints[i] = janet_getinteger(ints.items, i);
    }
    float fontSize = (float) janet_getnumber(argv, 2);
    float spacing = (float) janet_getnumber(argv, 3);
    Vector2 size = MeasureTextCodepoints(font, raw_ints, ints.len, fontSize, spacing);
    janet_sfree(raw_ints);
    return jaylib_wrap_vec2(size);
}

static Janet cfun_LoadTextLines(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    const char *text = jaylib_getcstring(argv, 0);
    int count = 0;
    char **lines = LoadTextLines(text, &count);
    JanetArray *array = janet_array(0);
    for (int i = 0; i < count; i++) {
        janet_array_push(array, janet_cstringv(lines[i]));
    }
    UnloadTextLines(lines, count);
    return janet_wrap_array(array);
}

static Janet cfun_TextRemoveSpaces(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    const char *text = jaylib_getcstring(argv, 0);
    return janet_cstringv(TextRemoveSpaces(text));
}

static Janet cfun_GetTextBetween(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    const char *text = jaylib_getcstring(argv, 0);
    const char *begin = jaylib_getcstring(argv, 1);
    const char *end = jaylib_getcstring(argv, 2);
    char *between = GetTextBetween(text, begin, end);
    return janet_cstringv(between);
}

static Janet cfun_TextReplaceAlloc(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    const char *text = jaylib_getcstring(argv, 0);
    const char *search = jaylib_getcstring(argv, 1);
    const char *replacement = jaylib_getcstring(argv, 2);
    char *replaced = TextReplaceAlloc(text, search, replacement);
    if (replaced == NULL) {
        return janet_wrap_nil();
    }
    Janet out = janet_cstringv(replaced);
    MemFree(replaced);
    return out;
}

static Janet cfun_TextReplaceBetween(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    const char *text = jaylib_getcstring(argv, 0);
    const char *begin = jaylib_getcstring(argv, 1);
    const char *end = jaylib_getcstring(argv, 2);
    const char *replacement = jaylib_getcstring(argv, 3);
    return janet_cstringv(TextReplaceBetween(text, begin, end, replacement));
}

static Janet cfun_TextReplaceBetweenAlloc(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    const char *text = jaylib_getcstring(argv, 0);
    const char *begin = jaylib_getcstring(argv, 1);
    const char *end = jaylib_getcstring(argv, 2);
    const char *replacement = jaylib_getcstring(argv, 3);
    char *replaced = TextReplaceBetweenAlloc(text, begin, end, replacement);
    if (replaced == NULL) {
        return janet_wrap_nil();
    }
    Janet out = janet_cstringv(replaced);
    MemFree(replaced);
    return out;
}

static Janet cfun_TextInsertAlloc(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    const char *text = jaylib_getcstring(argv, 0);
    const char *insert = jaylib_getcstring(argv, 1);
    int position = janet_getinteger(argv, 2);
    char *inserted = TextInsertAlloc(text, insert, position);
    if (inserted == NULL) {
        return janet_wrap_nil();
    }
    Janet out = janet_cstringv(inserted);
    MemFree(inserted);
    return out;
}

static Janet cfun_TextToSnake(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    const char *text = jaylib_getcstring(argv, 0);
    return janet_cstringv(TextToSnake(text));
}

static Janet cfun_TextToCamel(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    const char *text = jaylib_getcstring(argv, 0);
    return janet_cstringv(TextToCamel(text));
}

static Janet cfun_TextToFloat(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    const char *text = jaylib_getcstring(argv, 0);
    return janet_wrap_number((double) TextToFloat(text));
}

static JanetReg text_cfuns[] = {
    {"get-font-default", cfun_GetFontDefault, 
        "(get-font-default)\n\n" 
        "Get the default Font"
    },
    {"load-font", cfun_LoadFont, 
        "(load-font file-name)\n\n"
        "Load font from file into GPU memory (VRAM)"
    },
    {"font-valid?", cfun_IsFontValid,
        "(font-valid? font)\n\n"
        "Check if a font is valid"
    },
    {"load-font-ex", cfun_LoadFontEx,
        "(load-font-ex file-name font-size &opt font-chars)\n\n"
        "Load font from file with extended parameters"
    },
    {"load-font-from-memory", cfun_LoadFontFromMemory,
        "(load-font-from-memory file-type file-data data-size font-size font-chars)\n\n"
        "Load font from memory"
    },
    {"unload-font", cfun_UnloadFont, 
        "(unload-font font)\n\n" 
        "Unload Font from GPU memory (VRAM)"
    },
    {"draw-fps", cfun_DrawFPS, 
        "(draw-fps pos-x pos-y)\n\n" 
        "Draw current FPS"
    },
    {"draw-text", cfun_DrawText, 
        "(draw-text text pos-x pos-y font-size color)\n\n" 
        "Draw text (using default font)"
    },
    {"draw-text-ex", cfun_DrawTextEx, 
        "(draw-text-ex font text [pos-x pos-y] font-size spacing tint)\n\n" 
        "Draw text using font and additional parameters"
    },
    {"draw-text-pro", cfun_DrawTextPro,
        "(draw-text-pro font text [pos-x pos-y] [origin-x origin-y] rotation font-size spacing tint)\n\n"
        "Draw text using font and pro parameters (rotation)"
    },
    {"draw-text-codepoint", cfun_DrawTextCodepoint,
        "(draw-text-codepoint font codepoint [pos-x pos-y] font-size tint)\n\n"
        "Draw one character (codepoint)"
    },
    {"draw-text-codepoints", cfun_DrawTextCodepoints,
        "(draw-text-codepoints font codepoints [pos-x pos-y] font-size spacing tint)\n\n"
        "Draw multiple characters (codepoints)"
    },
    {"measure-text", cfun_MeasureText, 
        "(measure-text text font-size)\n\n" 
        "Measure string width for default font"
    },
    {"measure-text-ex", cfun_MeasureTextEx, 
        "(measure-text-ex font text font-size spacing)\n\n" 
        "Measure string size for Font"
    },
    {"get-glyph-index", cfun_GetGlyphIndex, 
        "(get-glyph-index font codepoint)\n\n" 
        "Get glyph index position in font for a codepoint (unicode character), fallback to '?' if not found"
    },
    {"get-font-texture", cfun_GetFontTexture,
        "(get-font-texture font)\n\n"
        ""
    },
    {"measure-text-codepoints", cfun_MeasureTextCodepoints,
        "(measure-text-codepoints font codepoints font-size spacing)\n\n"
        "Measure string size for an array of codepoints for Font"
    },
    {"load-text-lines", cfun_LoadTextLines,
        "(load-text-lines text)\n\n"
        "Load text as separate lines (split on newline), returning an array of strings. "
        "The C memory for the lines is released immediately, so there is no unload-text-lines binding"
    },
    {"text-remove-spaces", cfun_TextRemoveSpaces,
        "(text-remove-spaces text)\n\n"
        "Remove text spaces, concat words"
    },
    {"get-text-between", cfun_GetTextBetween,
        "(get-text-between text begin end)\n\n"
        "Get text between two strings"
    },
    {"text-replace-alloc", cfun_TextReplaceAlloc,
        "(text-replace-alloc text search replacement)\n\n"
        "Replace text string with new string"
    },
    {"text-replace-between", cfun_TextReplaceBetween,
        "(text-replace-between text begin end replacement)\n\n"
        "Replace text between two specific strings"
    },
    {"text-replace-between-alloc", cfun_TextReplaceBetweenAlloc,
        "(text-replace-between-alloc text begin end replacement)\n\n"
        "Replace text between two specific strings"
    },
    {"text-insert-alloc", cfun_TextInsertAlloc,
        "(text-insert-alloc text insert position)\n\n"
        "Insert text in a defined byte position"
    },
    {"text-to-snake", cfun_TextToSnake,
        "(text-to-snake text)\n\n"
        "Get Snake case notation version of provided string"
    },
    {"text-to-camel", cfun_TextToCamel,
        "(text-to-camel text)\n\n"
        "Get Camel case notation version of provided string"
    },
    {"text-to-float", cfun_TextToFloat,
        "(text-to-float text)\n\n"
        "Get float value from text"
    },
    {NULL, NULL, NULL}
};
