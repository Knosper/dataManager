#include <iostream>
#include <pqxx/pqxx>
#include <cstdlib>
#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[]) {
    // Initialize Qt Application
    QApplication app(argc, argv);

    // Create a QWidget, which will be our main window
    QWidget window;

    // Set some properties for the window
    window.resize(250, 150);
    window.setWindowTitle("Simple Qt Application");

    // Display the window
    window.show();

    // Start the Qt event loop
    return app.exec();
}
