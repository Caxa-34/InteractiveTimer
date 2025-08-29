#ifndef TIMERWINDOW_H
#define TIMERWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QChar>
#include <interactivetimer.h>
#include <QSound>

QT_BEGIN_NAMESPACE
namespace Ui { class TimerWindow; }
QT_END_NAMESPACE

class TimerWindow : public QMainWindow
{
    Q_OBJECT

public:
    TimerWindow(QWidget *parent = nullptr);
    ~TimerWindow();

private slots:
    /**
     * @brief Запуск таймера
     */
    void on_btnStartPause_clicked();

    /**
     * @brief Отображение всех данных таймера при каждом тике
     */
    void showTimer();

    /**
     * @brief Завершение таймера
     */
    void finishTimer();

    /**
     * @brief Окрашивание фона (для частой плавной смены цвета)
     */
    void showBackground();

    /**
     * @brief Сборс таймера, очистка, возвращение стандартного вида элементов
     */
    void on_btnReset_clicked();

private:
    Ui::TimerWindow *ui;

    ///стили для смены вида кнопки старт/пауза
    QString startStyle, pauseStyle;

    /**
     * @brief Функция запуска таймера, валидация входных данных и проверка секретного режима
     */
    void startTimer();

    /**
     * @brief Функция паузы таймера
     */
    void pauseTimer();

    ///Таймер
    InteractiveTimer *interactiveTimer;
    ///Палитра главного окна
    QPalette pal;
};
#endif // TIMERWINDOW_H
