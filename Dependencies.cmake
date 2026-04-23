include(FetchContent)

FetchContent_Declare(
    gaven
    GIT_REPOSITORY https://github.com/iGhaithSquare/Gaven
    GIT_TAG main
)
FetchContent_MakeAvailable(gaven)
target_compile_options(gaven PRIVATE
    -w
)

