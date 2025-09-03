#include "interactivetimer.h"

InteractiveTimer::InteractiveTimer(QObject *parent) : QObject(parent)
{
    timer.setInterval(10);
    connect(&timer, &QTimer::timeout, this, &InteractiveTimer::onTimeout);
    typeCount = TypeCount::countDown;
    seconds = 0;
    mseconds = 0;
    msCounter = 0;
}

void InteractiveTimer::startTimer(int seconds)
{
    //проверка на первый запуск (или после сброса)
    if (this->seconds == 0) {
        //установка первичных значений
        secondStart = seconds;
        this->seconds = seconds;

       //установка заднего фона: если отсчет вверх - рандомный цвет, если вниз - зеленый
        if (typeCount == TypeCount::countUp)
        {
            int r = QRandomGenerator::global()->bounded(256);
            int g = QRandomGenerator::global()->bounded(256);
            int b = QRandomGenerator::global()->bounded(256);
            backgroundColor = QColor(r, g, b);
        }
        else {
            backgroundColor = QColor(0, 255, 0);
        }
    }
    //отображение и запуск
    emit signalShow();
    timer.start();
}

void InteractiveTimer::pauseTimer() { timer.stop(); }

void InteractiveTimer::resetTimer()
{
    timer.stop();
    seconds = 0;
    mseconds = 0;
    msCounter = 0;
    secondStart = 0;
    emit signalShow();
}
void InteractiveTimer::setTypeCountDown() { typeCount = TypeCount::countDown; }

void InteractiveTimer::setTypeCountUp() { typeCount = TypeCount::countUp; }

void InteractiveTimer::onTimeout()
{
    //счетчики 10мс
    msCounter++;
    mseconds++;

    //плавное изменение цвета при обычном режиме с интерполяцией от зеленого к красному (используется интервал 10мс)
    if (typeCount == TypeCount::countDown) {
        if (secondStart <= 0) return; // защита от деления на 0

        //расчет прогресса таймера где 0 - зеленый, 1 - красный
        double progress = 1.0 - (double)(secondStart * 100 - mseconds) / (secondStart * 100);

        //защита от погрешностей на границах
        if (progress < 0) progress = 0;
        if (progress > 1) progress = 1;

        //установка цвета для заднего фона
        int r = static_cast<int>(255 * progress);
        int g = static_cast<int>(255 * (1.0 - progress));
        int b = 0;
        backgroundColor = QColor(r, g, b);
        emit signalBackground();
    }

    //ограничитель что бы следующий код выполнялся каждые 100 * 10мс, т.е. 1 сек
    if (msCounter < 100) return;
    msCounter -= 100;

    //счетчик секунд в зависимости от режима и рандом фона при секретном режиме
    if (typeCount == TypeCount::countUp)
    {
        seconds++;
        int r = QRandomGenerator::global()->bounded(256);
        int g = QRandomGenerator::global()->bounded(256);
        int b = QRandomGenerator::global()->bounded(256);
        backgroundColor = QColor(r, g, b);
    }
    else seconds--;

    //отображение и финиш со сбросом данных
    emit signalShow();
    if (seconds == 0) {
        resetTimer();
        emit signalFinish();
    }
}

int InteractiveTimer::getTime() { return seconds; }

int InteractiveTimer::getPercent() {
    if (secondStart == 0) // проверка делителя на 0
        return 0;
    if (typeCount == TypeCount::countUp) //цикличное заполнение прогресс-бара при секретном режиме
        return ((seconds - secondStart) % TIMER_LOOP_SEC)/(float)TIMER_LOOP_SEC * 100;
    return seconds / (float)secondStart * 100; // при стандартном режиме
}

QColor InteractiveTimer::getBackgroundColor() { return backgroundColor; }
