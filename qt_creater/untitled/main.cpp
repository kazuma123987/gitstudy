#include <QApplication>
#include <QComboBox>
#include <QVBoxLayout>
#include <QWidget>
#include <QtSerialPort/QSerialPortInfo>
#include <QLabel>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Serial Port Selector");

    QVBoxLayout *layout = new QVBoxLayout(&window);

    QLabel *label = new QLabel("Select a Serial Port:");
    layout->addWidget(label);

    QComboBox *comboBox = new QComboBox();
    layout->addWidget(comboBox);

    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : serialPortInfos) {
        comboBox->addItem(info.portName());
    }

    QObject::connect(comboBox, &QComboBox::currentTextChanged, [](const QString &portName) {
        qDebug() << "Selected port:" << portName;
    });

    window.setLayout(layout);
    window.resize(300, 100);
    window.show();

    return app.exec();
}
