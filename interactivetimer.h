#ifndef INTERACTIVETIMER_H
#define INTERACTIVETIMER_H

#include <QObject>
#include <QColor>
#include <QRandomGenerator>
#include <QTimer>
#include <QDebug>

#include <constants.h>

/**
 * @brief Интерактивный таймер
 *
 * Класс реализует логику работы таймера: запуск, пауза, сброс,
 * а также выбор режима работы: стандартный и "секретный". Использует внутренний QTimer
 * для генерации события каждую секунду, хранит прогресс таймера и цвет для фона окна
 */
class InteractiveTimer : public QObject
{
    Q_OBJECT
public:
    explicit InteractiveTimer(QObject *parent = nullptr);

    /**
     * @brief Запуск таймера
     * @param Количество секунд для таймера
     */
    void startTimer(int seconds);
    /**
     * @brief Остановка таймера на паузу
     */
    void pauseTimer();
    /**
     * @brief Сброс счетчика таймера
     */
    void resetTimer();
    /**
     * @brief Установка стандартного режима работы
     */
    void setTypeCountDown();
    /**
     * @brief Установка "секретного" режима работы
     */
    void setTypeCountUp();
    /**
     * @brief Получение времени таймера
     * @return Секунды
     */
    int getTime();
    /**
     * @brief Получение прогресса таймера для прогресс-бара
     * @return Значение прогресса в процентах
     */
    int getPercent();
    /**
     * @brief Получение цвета фона для главного окна
     * @return Цвет, соответствующий данному состоянию таймера
     */
    QColor getBackgroundColor();
private:
    ///Таймер
    QTimer timer;
    ///Класс режимов работы таймера
    enum class TypeCount {
        countUp, ///< "Секретный" режим работы, увеличивает
        countDown ///< Стандартный режим работы, уменьшает
    };
    ///Режим работы таймера
    TypeCount typeCount;
    ///Основной счётчик секунд, сек
    int seconds,
    ///Вводимое время таймера, сек
    secondStart,
    ///Счетчик 10мс для плавного изменения цвета, 10мс
    mseconds;
    ///Счётчик-ограничитель 10мс для секундных тиков, 10мс
    int msCounter;
    ///Цвет фона
    QColor backgroundColor;

signals:
    /**
     * @brief Сигнал для отображения данных таймера каждый тик
     */
    void signalShow();
    /**
     * @brief Сигнал для отображения плавного фона каждые 10мс
     */
    void signalBackground();
    /**
     * @brief Сигнал о завершении таймера
     */
    void signalFinish();

private slots:
    ///Тик таймера каждые 10мс
    void onTimeout();
};

#endif // INTERACTIVETIMER_H
