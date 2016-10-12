#include <QGuiApplication>
#include <QSurfaceFormat>

#include <iostream>
#include <string>

#include "src/mainwaindow.h"

int main(int argc, char **argv)
{
    std::cout << "3D Model Builder " << std::endl;
    std::cout << "-----------------" << std::endl;
    std::cout << "Commands: hello  " << std::endl;
    std::cout << "          render " << std::endl;
    std::cout << "          quit   " << std::endl << std::endl;

    while (true) {

        // Prompt

        std::cout << "> ";
        std::string input;
        std::getline(std::cin, input);

        // Command processing
        //      Commands to affect variables
        //      to be passed into MainWindow constructor
        //      on "render" command

        if (input == "hello") {

            std::cout << "Hello" << std::endl;

        } else if (input == "render") {

            QGuiApplication app(argc, argv);

            QSurfaceFormat format;
            format.setSamples(16);

            MainWindow window;
            window.setFormat(format);
            window.resize(640, 480);
            window.show();

            app.setQuitOnLastWindowClosed(true);
            app.exec();

        } else if (input == "exit" || input == "quit") {

            return 0;

        }

        std::cout << std::endl;
    }
}
