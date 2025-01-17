#include <QApplication>
#include <QPushButton>
#include <QMessageBox>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Создаем окно с кнопкой
    QPushButton button("Click Me!");
    button.resize(200, 100);
    button.show();

    // Обработка нажатия кнопки
    QObject::connect(&button, &QPushButton::clicked, [&]() {
        QMessageBox::information(nullptr, "Message", "Hello, Qt with X-server!");
    });

    return app.exec();
}