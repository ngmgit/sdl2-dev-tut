
set(myengine_source_files
        Sprite.cpp
        Errors.cpp
        GLSLProgram.cpp
        ImageLoader.cpp
        IOManager.cpp
        picoPNG.cpp
        TextureCache.cpp
        ResourceManager.cpp
    )

add_library(myengine SHARED ${myengine_source_files})
target_link_libraries(myengine ${SDL_LINK_FLAGS} ${GLEW_LINK_FLAGS})
