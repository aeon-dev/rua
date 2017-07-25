include(Unittests)

add_unit_test_suite(
    NO_GTEST_MAIN
    TARGET test_common
    SOURCES
        main.cpp
        test_control_signals.cpp
    LIBRARIES common
    FOLDER rua/tests
)
