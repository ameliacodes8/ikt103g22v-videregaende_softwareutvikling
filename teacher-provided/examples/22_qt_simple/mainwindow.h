#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Slots can be connected to signals to handle events
protected slots:
    void buttonClicked();
    void textEdited(const QString &text);

protected:
    // Widgets for the window
    QHBoxLayout *layout;
    QPushButton *pushButton;
    QLabel *label;
    QLineEdit *lineEdit;
};
#endif // MAINWINDOW_H
