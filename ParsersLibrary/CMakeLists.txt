add_library(ParsersLibrary SHARED Grammar.cpp EarlyAlgorithm.cpp)

install(
        TARGETS ParsersLibrary
        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin
        LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/bin
)