#include "timerwindow.h"
#include "./ui_timerwindow.h"

TimerWindow::TimerWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TimerWindow)
{
    //создает и настраивает элементы интерфейса, прописывает коннекты. Работает с окном из заголовочного файла .h, который генерируется из .ui через uic
    ui->setupUi(this);

    //стили для кнопки старт/пауза
    startStyle =
        "QPushButton {"
        "   background: green;"
        "   color: black;"
        "   border-radius: 4px;"
        "}";
    pauseStyle =
        "QPushButton {"
        "   background: lightcoral;"
        "   color: black;"
        "   border-radius: 4px;"
        "}";

    QRegularExpression mask("^\\d{1,2}$");
    ui->leInputSec->setValidator(new QRegularExpressionValidator(mask, ui->leInputSec));

    //установка текста с учетом констант
    QString textInputLabel = QString("Задайте время таймера (%1-%2 сек):").arg(TIMER_MIN_SEC).arg(TIMER_MAX_SEC);
    ui->labelInput->setText(textInputLabel);

    //настройка кнопки (true - запущено, false - на паузе)
    ui->btnStartPause->setCheckable(true);
    ui->btnStartPause->setChecked(false);
    ui->btnStartPause->setStyleSheet(startStyle);

    //создание таймера и подключение слотов
    interactiveTimer = new InteractiveTimer(this);
    connect(interactiveTimer, &InteractiveTimer::signalShow, this, &TimerWindow::showTimer);
    connect(interactiveTimer, &InteractiveTimer::signalFinish, this, &TimerWindow::finishTimer);
    connect(interactiveTimer, &InteractiveTimer::signalBackground, this, &TimerWindow::showBackground);

    //создание палитры
    pal = this->palette();
    this->setAutoFillBackground(true);
}

TimerWindow::~TimerWindow()
{
    delete ui;
}

void TimerWindow::on_btnStartPause_clicked()
{
    if (ui->btnStartPause->isChecked()) {
        startTimer();
    } else {
        pauseTimer();
    }
}

void TimerWindow::startTimer()
{
    //проверка входных данных на корректность
    bool resConvert;
    int inputNum = ui->leInputSec->text().toInt(&resConvert);
    if (!resConvert) {
        QMessageBox::warning(this, "Ошибка", "Введите корректное число!");
        ui->btnStartPause->setChecked(false);
        return;
    }
    if (inputNum > TIMER_MAX_SEC || inputNum < TIMER_MIN_SEC) {
        QMessageBox::warning(this, "Ошибка", QString("Введите число от %1 до %2!").arg(TIMER_MIN_SEC).arg(TIMER_MAX_SEC));
        ui->btnStartPause->setChecked(false);
        return;
    }
    //определение режима таймера и запуск
    if (inputNum == SECRET_NUMBER) interactiveTimer->setTypeCountUp();
    else interactiveTimer->setTypeCountDown();
    interactiveTimer->startTimer(inputNum);

    ui->btnStartPause->setText("Пауза");
    ui->btnStartPause->setStyleSheet(pauseStyle);
    ui->leInputSec->setEnabled(false);

}

void TimerWindow::pauseTimer()
{
    interactiveTimer->pauseTimer();

    ui->btnStartPause->setText("Старт");
    ui->btnStartPause->setStyleSheet(startStyle);
}

void TimerWindow::showTimer()
{
    //форматирование и отображения времени таймера
    int sec = interactiveTimer->getTime();
    int min = sec / 60;
    ui->leInputSec->setText(QString::number(sec));
    sec = sec % 60;
    ui->txtOutputTimer->setText(QString("%1:%2").arg(min, 2, 10, QChar('0')).arg(sec, 2, 10, QChar('0')));

    ui->prbarTimer->setValue(interactiveTimer->getPercent());

    pal.setColor(QPalette::Window, interactiveTimer->getBackgroundColor());
    this->setPalette(pal);
}
void TimerWindow::showBackground() {
    pal.setColor(QPalette::Window, interactiveTimer->getBackgroundColor());
    this->setPalette(pal);
}

void TimerWindow::finishTimer()
{
    //проверка и вывод в дебаг исключения
    QSoundEffect sound;
    sound.setSource(QUrl("qrc:music/end_timer.wav"));
    sound.setLoopCount(1);
    connect(&sound, &QSoundEffect::statusChanged, [&sound] {
         if (sound.status() == QSoundEffect::Error) qDebug() << "Ошибка воспроизведения трека!";
         if (sound.status() == QSoundEffect::Ready) sound.play();

    });

    QMessageBox::information(this, "Таймер", "Время вышло!");
    emit on_btnReset_clicked();
}

void TimerWindow::on_btnReset_clicked()
{
    if (ui->btnStartPause->isChecked()){
        ui->btnStartPause->setChecked(false);
        ui->btnStartPause->setText("Старт");
        ui->btnStartPause->setStyleSheet(startStyle);
    }

    interactiveTimer->setTypeCountDown();
    interactiveTimer->resetTimer();
    this->setPalette(QPalette());
    ui->leInputSec->setText("");
    ui->leInputSec->setEnabled(true);
}
