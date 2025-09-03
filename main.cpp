#include "timerwindow.h"
#include "interactivetimer.h"

#include <QApplication>

//точка входа в программу. Принимает аргументы извне (например bash/cmd)
int main(int argc, char *argv[])
{
    QApplication a(argc, argv); //объект, управляющий циклом событий в Qt приложении (обработка событий от ОС)
    TimerWindow w;
    w.show();
    return a.exec(); //запускает главный цикл в котором живёт w до закрытия окна, возвращает код выхода из приложения
}
