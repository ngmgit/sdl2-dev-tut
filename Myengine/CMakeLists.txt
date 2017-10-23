
set(myengine_source_files
        Myengine.cpp
        Window.cpp
        Camera2D.cpp
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
