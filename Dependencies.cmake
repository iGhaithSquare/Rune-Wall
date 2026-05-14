include(FetchContent)
set (GAVEN_LOG_TO_CMD OFF CACHE BOOL "Force disable gaven log to cmd" FORCE)
FetchContent_Declare(
    gaven
    GIT_REPOSITORY https://github.com/iGhaithSquare/Gaven
    GIT_TAG c99cc2ce8f502dc6dff763804b6f40b33859d9f1
)
FetchContent_MakeAvailable(gaven)
target_compile_options(gaven PRIVATE
    -w
)

