static Janet cfun_rlViewport(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    int posX = janet_getinteger(argv, 0);
    int posY = janet_getinteger(argv, 1);
    int width = janet_getinteger(argv, 2);
    int height = janet_getinteger(argv, 3);
    rlViewport(posX, posY, width, height);
    return janet_wrap_nil();
}

static const KeyDef matrix_mode_flags[] = {
    {"rl-modelview", RL_MODELVIEW},
    {"rl-projection", RL_PROJECTION},
    {"rl-texture", RL_TEXTURE}
};


static Janet cfun_rlMatrixMode(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    const uint8_t *arg_flag = janet_getkeyword(argv, 0);
    int flag = 0;
    for (unsigned j = 0; j < (sizeof(matrix_mode_flags) / sizeof(KeyDef)); j++) {
        if (!janet_cstrcmp(arg_flag, matrix_mode_flags[j].name)) {
            flag = matrix_mode_flags[j].key;
           break;
        }
    }

    if (0 == flag) {
        JanetArray *available = janet_array(0);
        for (unsigned j = 0; j < (sizeof(matrix_mode_flags) / sizeof(KeyDef)); j++) {
            janet_array_push(available, janet_ckeywordv(matrix_mode_flags[j].name));
        }
        janet_panicf("unknown flag %v - available flags are %p", argv[0],
            janet_wrap_array(available));
    }
    
    rlMatrixMode(flag);
    return janet_wrap_nil();
}

static Janet cfun_rlLoadIdentity(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    rlLoadIdentity();
    return janet_wrap_nil();
}

static Janet cfun_rlOrtho(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 6);
    float left = (float) janet_getnumber(argv, 0);
    float right = (float) janet_getnumber(argv, 1);
    float bottom = (float) janet_getnumber(argv, 2);
    float top = (float) janet_getnumber(argv, 3);
    float znear = (float) janet_getnumber(argv, 4);
    float zfar = (float) janet_getnumber(argv, 5);
    rlOrtho(left, right, bottom, top, znear, zfar);
    return janet_wrap_nil();
}

static Janet cfun_rlTranslatef(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    float x = (float) janet_getnumber(argv, 0);
    float y = (float) janet_getnumber(argv, 1);
    float z = (float) janet_getnumber(argv, 2);
    rlTranslatef(x, y, z);
    return janet_wrap_nil();
}

static Janet cfun_rlRotatef(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    float angle = (float) janet_getnumber(argv, 0);
    float x = (float) janet_getnumber(argv, 1);
    float y = (float) janet_getnumber(argv, 2);
    float z = (float) janet_getnumber(argv, 3);
    rlRotatef(angle, x, y, z);
    return janet_wrap_nil();
}

static Janet cfun_rlScalef(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    float x = (float) janet_getnumber(argv, 0);
    float y = (float) janet_getnumber(argv, 1);
    float z = (float) janet_getnumber(argv, 2);
    rlScalef(x, y, z);
    return janet_wrap_nil();
}

static Janet cfun_rlEnableScissorTest(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    rlEnableScissorTest();
    return janet_wrap_nil();
}

static Janet cfun_rlScissor(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    int posX = janet_getinteger(argv, 0);
    int posY = janet_getinteger(argv, 1);
    int width = janet_getinteger(argv, 2);
    int height = janet_getinteger(argv, 3);
    rlScissor(posX, posY, width, height);
    return janet_wrap_nil();
}

static Janet cfun_rlPushMatrix(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    rlPushMatrix();
    return janet_wrap_nil();
}

static Janet cfun_rlPopMatrix(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    rlPopMatrix();
    return janet_wrap_nil();
}

static Janet cfun_rlMultMatrixfScreenScale(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    Vector2 v = GetWindowScaleDPI();
    float s = v.x * v.y;
    rlMultMatrixf(&s); // Apply screen scaling
    return janet_wrap_nil();
}

static Janet cfun_rlDrawRenderBatchActive(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    rlDrawRenderBatchActive();
    return janet_wrap_nil();
}

static Janet cfun_rlSetClipPlanes(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    double nearPlane = janet_getnumber(argv, 0);
    double farPlane = janet_getnumber(argv, 1);
    rlSetClipPlanes(nearPlane, farPlane);
    return janet_wrap_nil();
}

static Janet cfun_rlGetCullDistanceNear(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    return janet_wrap_number(rlGetCullDistanceNear());
}

static Janet cfun_rlGetCullDistanceFar(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    return janet_wrap_number(rlGetCullDistanceFar());
}

static Janet cfun_rlGetActiveFramebuffer(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    return janet_wrap_integer(rlGetActiveFramebuffer());
}

static Janet cfun_rlBindFramebuffer(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    unsigned int target = (unsigned int) janet_getinteger(argv, 0);
    unsigned int framebuffer = (unsigned int) janet_getinteger(argv, 1);
    rlBindFramebuffer(target, framebuffer);
    return janet_wrap_nil();
}

static Janet cfun_rlColorMask(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    bool r = janet_getboolean(argv, 0);
    bool g = janet_getboolean(argv, 1);
    bool b = janet_getboolean(argv, 2);
    bool a = janet_getboolean(argv, 3);
    rlColorMask(r, g, b, a);
    return janet_wrap_nil();
}

static Janet cfun_rlDisablePointMode(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    rlDisablePointMode();
    return janet_wrap_nil();
}

static Janet cfun_rlSetPointSize(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    float size = (float) janet_getnumber(argv, 0);
    rlSetPointSize(size);
    return janet_wrap_nil();
}

static Janet cfun_rlGetPointSize(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    return janet_wrap_number(rlGetPointSize());
}

static Janet cfun_rlGetProcAddress(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    const char *procName = janet_getcstring(argv, 0);
    return janet_wrap_pointer(rlGetProcAddress(procName));
}

static Janet cfun_rlCopyFramebuffer(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 5);
    int x = janet_getinteger(argv, 0);
    int y = janet_getinteger(argv, 1);
    int width = janet_getinteger(argv, 2);
    int height = janet_getinteger(argv, 3);
    int format = janet_getinteger(argv, 4);
    if (width < 0 || height < 0) {
        janet_panicf("expected non-negative width and height, got (%d, %d)", width, height);
    }
    size_t size = (size_t) width * height * 4;
    void *pixels = janet_smalloc(size);
    rlCopyFramebuffer(x, y, width, height, format, pixels);
    JanetBuffer *buf = janet_buffer((int32_t) size);
    janet_buffer_push_bytes(buf, (const uint8_t *) pixels, (int32_t) size);
    janet_sfree(pixels);
    return janet_wrap_buffer(buf);
}

static Janet cfun_rlResizeFramebuffer(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    int width = janet_getinteger(argv, 0);
    int height = janet_getinteger(argv, 1);
    rlResizeFramebuffer(width, height);
    return janet_wrap_nil();
}

static Janet cfun_rlLoadShader(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    const char *code = janet_getcstring(argv, 0);
    int type = janet_getinteger(argv, 1);
    return janet_wrap_integer(rlLoadShader(code, type));
}

static Janet cfun_rlLoadShaderProgramEx(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    unsigned int vsId = (unsigned int) janet_getinteger(argv, 0);
    unsigned int fsId = (unsigned int) janet_getinteger(argv, 1);
    return janet_wrap_integer(rlLoadShaderProgramEx(vsId, fsId));
}

static Janet cfun_rlLoadShaderProgramCompute(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    unsigned int csId = (unsigned int) janet_getinteger(argv, 0);
    return janet_wrap_integer(rlLoadShaderProgramCompute(csId));
}

static Janet cfun_rlUnloadShader(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    unsigned int id = (unsigned int) janet_getinteger(argv, 0);
    rlUnloadShader(id);
    return janet_wrap_nil();
}

static Janet cfun_rlSetUniformMatrices(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    int locIndex = janet_getinteger(argv, 0);
    JanetView mats = janet_getindexed(argv, 1);
    Matrix *raw_mats = janet_smalloc(sizeof(Matrix) * mats.len);
    for (int32_t i = 0; i < mats.len; i++) {
        raw_mats[i] = jaylib_getmatrix(mats.items, i);
    }
    rlSetUniformMatrices(locIndex, raw_mats, mats.len);
    janet_sfree(raw_mats);
    return janet_wrap_nil();
}

static JanetReg rlgl_cfuns[] = {
    {"rl-viewport", cfun_rlViewport, NULL},
    {"rl-matrix-mode", cfun_rlMatrixMode, NULL},
    {"rl-ortho", cfun_rlOrtho, NULL},
    {"rl-push-matrix", cfun_rlPushMatrix, NULL},
    {"rl-pop-matrix", cfun_rlPopMatrix, NULL},
    {"rl-load-identity", cfun_rlLoadIdentity, NULL},
    {"rl-translatef", cfun_rlTranslatef, NULL},
    {"rl-rotatef", cfun_rlRotatef, NULL},
    {"rl-scalef", cfun_rlScalef, NULL},
    {"rl-enable-scissor-test", cfun_rlEnableScissorTest, NULL},
    {"rl-scissor", cfun_rlScissor, NULL},
    {"rl-mult-matrixf-screen-scale", cfun_rlMultMatrixfScreenScale, NULL},
    {"rl-draw-render-batch-active", cfun_rlDrawRenderBatchActive, NULL},
    {"rl-set-clip-planes", cfun_rlSetClipPlanes, NULL},
    {"rl-get-cull-distance-near", cfun_rlGetCullDistanceNear, NULL},
    {"rl-get-cull-distance-far", cfun_rlGetCullDistanceFar, NULL},
    {"rl-get-active-framebuffer", cfun_rlGetActiveFramebuffer, NULL},
    {"rl-bind-framebuffer", cfun_rlBindFramebuffer, NULL},
    {"rl-color-mask", cfun_rlColorMask, NULL},
    {"rl-disable-point-mode", cfun_rlDisablePointMode, NULL},
    {"rl-set-point-size", cfun_rlSetPointSize, NULL},
    {"rl-get-point-size", cfun_rlGetPointSize, NULL},
    {"rl-get-proc-address", cfun_rlGetProcAddress, NULL},
    {"rl-copy-framebuffer", cfun_rlCopyFramebuffer, NULL},
    {"rl-resize-framebuffer", cfun_rlResizeFramebuffer, NULL},
    {"rl-load-shader", cfun_rlLoadShader, NULL},
    {"rl-load-shader-program-ex", cfun_rlLoadShaderProgramEx, NULL},
    {"rl-load-shader-program-compute", cfun_rlLoadShaderProgramCompute, NULL},
    {"rl-unload-shader", cfun_rlUnloadShader, NULL},
    {"rl-set-uniform-matrices", cfun_rlSetUniformMatrices, NULL},
    {NULL, NULL, NULL}
};