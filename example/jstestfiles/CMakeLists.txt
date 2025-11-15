file(GLOB JS_FILES "*.js")

add_library(__IDE_HELPER_JS_DIR INTERFACE
    ${JS_FILES})
