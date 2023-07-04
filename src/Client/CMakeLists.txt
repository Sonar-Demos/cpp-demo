if(APPLE)
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt5")
set(POPPLER_INCLUDE_DIR "/opt/homebrew/opt/poppler-qt5/include")
link_directories("/opt/homebrew/opt/poppler-qt5/lib")
else()
set(POPPLER_INCLUDE_DIR)
endif()

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(client
    main.cpp
    createaccount.cpp
    documentwidget.cpp
    mainwindow.cpp
    pdfviewer.cpp
    readwindow.cpp
    settingswindow.cpp)

target_include_directories(client PRIVATE
    ${POPPLER_INCLUDE_DIR})

target_link_libraries(client
    Qt5::Widgets
    poppler-qt5)

set_target_properties(
    client
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
