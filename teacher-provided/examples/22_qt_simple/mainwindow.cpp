#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Create widgets
    pushButton = new QPushButton(QString("&Push me!"));   
    label = new QLabel(QString("Label text"));
    lineEdit = new QLineEdit();

    // Connect the push button's clicked() signal to the window's buttonClicked() slot
    connect(pushButton, SIGNAL(clicked()), this, SLOT(buttonClicked()));

    // Connect the line edit's textEdited() signal to the window's textEdited() slot
    connect(lineEdit, SIGNAL(textEdited(QString)), this, SLOT(textEdited(QString)));

    // Create a vertical layout and put the widgets in it
    QHBoxLayout *layout = new QHBoxLayout();

    layout->addWidget(pushButton);
    layout->addWidget(label);
    layout->addWidget(lineEdit);

    // Create a widget and set the layout to our vertical layout
    QWidget *widget = new QWidget();
    widget->setLayout(layout);

    // Set the new widget as the central widget of the window
    this->setCentralWidget(widget);

    // Resize the window
    this->resize(300, 150);
}

MainWindow::~MainWindow()
{
}

// button clicked signal handler
void MainWindow::buttonClicked()
{
    // Update the text of the label widget
    label->setText(QString("Button was pressed!"));
}

void MainWindow::textEdited(const QString &string)
{
    label->setText(string);
}
