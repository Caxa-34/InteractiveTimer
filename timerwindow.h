#ifndef TIMERWINDOW_H //если этот маркер для предпроцессора был ранее определен, то код до #endif игнорируется (то есть если этот заголовочный файл уже включен в исходник)
#define TIMERWINDOW_H //если не был определен, то определяет пустой маркер TIMERWINDOW_H, код до #endif включается в исходник

#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QChar>
#include <QSoundEffect>

#include <interactivetimer.h>
#include <constants.h>

//класс TimerWindow в пространстве имен Ui создается с помощью uic в ui_.h, ниже он просто объявляется для использования в классе окна
//само пространство имен тут нужно что бы не было конфликта имен классов
QT_BEGIN_NAMESPACE
namespace Ui { class TimerWindow; }
QT_END_NAMESPACE

//идентификатор доступа определяет видимость функций/переменных переданных при наследии у потомка (public оставляет как указаны у родителя)
class TimerWindow : public QMainWindow
{
    Q_OBJECT //макрос qt который помечает класс для генерации файла moc_.cpp с помощью moc

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
#endif // TIMERWINDOW_H (для #ifndef)
