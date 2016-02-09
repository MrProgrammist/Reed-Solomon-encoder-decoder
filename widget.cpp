#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

//    Заполняем таблицу соответствия входным комбинациям G(x)
//    выходых комбинаций F(x). По данной таблице кодер определяет
//    выходную кодовую комбинацию F(x) по входным данным G(x), а декодер -
//    выходные данные G'(x) по кодовой комбинации H(x), полученной из канала связи
//    таблица представляет собой двумерный массив 16-разрядных ячеек, идущих парами
//    в первых ячейках пар хранятся все варианты 5-разрядных кодовых слов, которые могут
//    поступить от ООД, а во вторых ячейках пар, - соответствующие им 15-разрядные кодовые
//    комбинации
    checkTable[0][0] = 0b00000;
    checkTable[0][1] = 0b000000000000000;
    checkTable[1][0] = 0b10000;
    checkTable[1][1] = 0b100001101100001;
    checkTable[2][0] = 0b01000;
    checkTable[2][1] = 0b010001110001000;
    checkTable[3][0] = 0b00100;
    checkTable[3][1] = 0b001000111000100;
    checkTable[4][0] = 0b00010;
    checkTable[4][1] = 0b000100011100010;
    checkTable[5][0] = 0b00001;
    checkTable[5][1] = 0b000010001110001;
    checkTable[6][0] = 0b11000;
    checkTable[6][1] = 0b110000011101001;
    checkTable[7][0] = 0b10100;
    checkTable[7][1] = 0b101001010100101;
    checkTable[8][0] = 0b10010;
    checkTable[8][1] = 0b100101110000011;
    checkTable[9][0] = 0b10001;
    checkTable[9][1] = 0b100011100010000;
    checkTable[10][0] = 0b01100;
    checkTable[10][1] = 0b011001001001100;
    checkTable[11][0] = 0b01010;
    checkTable[11][1] = 0b010101101101010;
    checkTable[12][0] = 0b01001;
    checkTable[12][1] = 0b010011111111001;
    checkTable[13][0] = 0b00110;
    checkTable[13][1] = 0b001100100100110;
    checkTable[14][0] = 0b00101;
    checkTable[14][1] = 0b001010110110101;
    checkTable[15][0] = 0b00011;
    checkTable[15][1] = 0b000110010010011;
    checkTable[16][0] = 0b11100;
    checkTable[16][1] = 0b111000100101101;
    checkTable[17][0] = 0b11010;
    checkTable[17][1] = 0b110100000001011;
    checkTable[18][0] = 0b11001;
    checkTable[18][1] = 0b110010010011000;
    checkTable[19][0] = 0b10110;
    checkTable[19][1] = 0b101101001000111;
    checkTable[20][0] = 0b10101;
    checkTable[20][1] = 0b101011001010100;
    checkTable[21][0] = 0b10011;
    checkTable[21][1] = 0b100111111110010;
    checkTable[22][0] = 0b01110;
    checkTable[22][1] = 0b011101010101110;
    checkTable[23][0] = 0b01101;
    checkTable[23][1] = 0b011011000111101;
    checkTable[24][0] = 0b01011;
    checkTable[24][1] = 0b010111100011011;
    checkTable[25][0] = 0b00111;
    checkTable[25][1] = 0b001110101010111;
    checkTable[26][0] = 0b11110;
    checkTable[26][1] = 0b111100111001111;
    checkTable[27][0] = 0b11101;
    checkTable[27][1] = 0b111010101011100;
    checkTable[28][0] = 0b11011;
    checkTable[28][1] = 0b110110001111010;
    checkTable[29][0] = 0b10111;
    checkTable[29][1] = 0b101111010110110;
    checkTable[30][0] = 0b01111;
    checkTable[30][1] = 0b011111011011111;
    checkTable[31][0] = 0b11111;
    checkTable[31][1] = 0b111110110111110;

//    Производим начальную инициализацию полей формы и значений переменных
//    для корректной работы программы. Избыточные биты в кодах маркируются
//    зеленым цветом

    ui->labelCoder->setText("00000<font color=\"green\">0000000000<\font>");
    ui->labelDecoder->setText("00000<font color=\"green\">0000000000<\font>");
    ui->labelDTE->setText("00000");
    userData = 0;
    dataAfterCoder = 0;
    dataAfterDecoder = 0;
    dataAfterDistortion = 0;

//    Подключаем события нажатия на кнопки, соответствующие битам G(x) и E(x)
//    к функции-обработчику данных событий

    connect(ui->buttonG0, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    connect(ui->buttonG1, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    connect(ui->buttonG2, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    connect(ui->buttonG3, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    connect(ui->buttonG4, SIGNAL(clicked()), this, SLOT(buttonClicked()));

    connect(ui->buttonE0, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    connect(ui->buttonE1, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    connect(ui->buttonE2, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    connect(ui->buttonE3, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    connect(ui->buttonE4, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    connect(ui->buttonE5, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    connect(ui->buttonE6, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    connect(ui->buttonE7, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    connect(ui->buttonE8, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    connect(ui->buttonE9, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    connect(ui->buttonE10, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    connect(ui->buttonE11, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    connect(ui->buttonE12, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    connect(ui->buttonE13, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    connect(ui->buttonE14, SIGNAL(clicked()), this, SLOT(buttonClicked()));
}

Widget::~Widget()
{
    delete ui;
}

//buttonClicked() - функция-обработчик событий нажатия на кнопки, соответствующие битам G(x) и E(x)
//В функции, с помощью процедуры динамического приведения типов(dynamic_cast), получается указатель на объект кнопки
//которая была нажата. С помощью данного указателя можем получать информацию о кнопке. Далее считывается текущее
//название кнопки ("0" или "1") и изменяется на противоположное. Таким образом создается переключение битов из 1 в 0
//и наоборот. После этого последовательно вызываются функции coding(), distortion(), decoding(), showResult().
//Таким образом, при нажатии любой из кнопок, соответствующих битам G(x) и E(x), выполняется процедура
//кодирования/декодирования
void Widget::buttonClicked()
{
    QPushButton *button = dynamic_cast<QPushButton *>(sender());

    if(button == NULL)
        return;

    if (button->text() == "1")
        button->setText("0");
    else
        button->setText("1");

    coding();
    distortion();
    decoding();
    showResult();
}

//coding() - функция, отвечающая за кодирование набранной кнопками комбинации G(x) с помощью табличного метода
//функция считывает значения кнопок, соответствующих 5-разрядному слову, кторое нужно закодирывать и преобразует
//эти значения в 16-разрядную переменную userData. Таким образом, значение переменной userData соответствует числу,
//набранному кнопками. Далее это число прогоняется по таблице checkTable. Как уже упоминалось выше, вся таблица
//состоит из пар чисел. Первое число в каждой паре, - один из вариантов данных, пришедших от пользователя,
//второе число - соответствующая этим данным кодовая комбинация. Найдя пару, в которой первое число совпадает
//с данными, полученными от пользователя, кодер берет значение второго числа пары и выдает его на выход
//Это и есть код F(x). Данное значение записывается в переменную dataAfterCoder
void Widget::coding()
{
    userData = 0;

    if(ui->buttonG4->text() == "1")
        userData |= 1 << 4;
    if(ui->buttonG3->text() == "1")
        userData |= 1 << 3;
    if(ui->buttonG2->text() == "1")
        userData |= 1 << 2;
    if(ui->buttonG1->text() == "1")
        userData |= 1 << 1;
    if(ui->buttonG0->text() == "1")
        userData |= 1;

    for(int i = 0; i < 32; i++)
    {
        if(checkTable[i][0] == userData)
        {
            dataAfterCoder = checkTable[i][1];
            break;
        }
    }
}

//distortion() - функция, которая вносит искажения E(x) в кодовую комбинацию F(x) и выдает
//искаженную кодовую комбинацию H(x) на декодер. Функция последовательно проверяет значения
//кнопок, соответствующих поиному искажения E(x), вносимого каналом связи. Каждая кнопка отвечает
//за искажение в одном из 15 разрядов кодовой комбинации F(x). Если значение кнопки соответствует
//"1" (есть искажение),соответствующий этой кнопк бит кодовой комбинации F(x), сохраненной в переменной
//dataAfterCoder, инвертируется операцией "сложение по модулю 2". Полученная таким образом искаженная
//кодовая комбинация H(x) сохраняется в переменной dataAfterDistortion
void Widget::distortion()
{
    quint16 distortedData = dataAfterCoder;

    if(ui->buttonE14->text() == "1")
        distortedData ^= 1 << 14;

    if(ui->buttonE13->text() == "1")
        distortedData ^= 1 << 13;

    if(ui->buttonE12->text() == "1")
        distortedData ^= 1 << 12;

    if(ui->buttonE11->text() == "1")
        distortedData ^= 1 << 11;

    if(ui->buttonE10->text() == "1")
        distortedData ^= 1 << 10;

    if(ui->buttonE9->text() == "1")
        distortedData ^= 1 << 9;

    if(ui->buttonE8->text() == "1")
        distortedData ^= 1 << 8;

    if(ui->buttonE7->text() == "1")
        distortedData ^= 1 << 7;

    if(ui->buttonE6->text() == "1")
        distortedData ^= 1 << 6;

    if(ui->buttonE5->text() == "1")
        distortedData ^= 1 << 5;

    if(ui->buttonE4->text() == "1")
        distortedData ^= 1 << 4;

    if(ui->buttonE3->text() == "1")
        distortedData ^= 1 << 3;

    if(ui->buttonE2->text() == "1")
        distortedData ^= 1 << 2;

    if(ui->buttonE1->text() == "1")
        distortedData ^= 1 << 1;

    if(ui->buttonE0->text() == "1")
        distortedData ^= 1;

    dataAfterDistortion = distortedData;
}

//decoding() - функция, осуществляющая декодирование, то есть преобразование принятой из
//канала связи кодовой комбинации H(x) в блок данных G'(x), соответствующий передаваемым с удаленного
//конца данным G(x). Функция извлекает значение переменной dataAfterDistortion, соответствующей
//кодовой информации, принятой из канала связи и по нему осуществляет декодирование табличным способом.
//Процедура декодирования очень похожа на процедуру кодирования, за исключением некоторых особенностей.
//Получив данные из канала связи, функция обращается к парам данных проверочной таблицы. В каждой паре
//первое число - одна из возможных комбинаций пользовательских данных, второе - соответствующая ей кодовая
//комбинация, образованная кодом (15, 5). Пробегая по всем парам таблицы, функция сравнивает принятую
//кодовую комбинацию с значением второго числа пары. Процедура сравнения заключается в определении количества
//разрядов, в которых принятая кодовая комбинация отличается от кодовой комбинации, записанной в таблице и
//представленной соответствующей парой данные-код. Во время просмотра всей таблицы функция декодирования
//находит ту пару чисел, в которой второе число имеет минимальное число разрядов, отличных от приятой
//кодовой комбинации H(x). Первое число в данной паре есть ни что иное, как декодированные данные, которые
//необходимо передать пользователю. Эти данные сохраняются в переменной dataAfterDecoder
void Widget::decoding()
{
    quint16 data = 0;
    quint16 different = 0;
    int curDelta;
    int prevDelta = 17;
    int resultIndex;

    data = dataAfterDistortion;

    for(int i = 0; i < 32; i++)
    {
        different = checkTable[i][1] ^ data;
        curDelta = 0;

        for(int j = 0; j < 16; j++)
        {
            if(different & (1 << j))
                curDelta++;
        }

        if(curDelta < prevDelta)
        {
            prevDelta = curDelta;
            resultIndex = i;
        }
    }

    dataAfterDecoder =  checkTable[resultIndex][0];
}

//showResult() - функция, отвечающее за отображение данных^ полученных в ходе рассчетов
//функциями coding(), distortion() и decoding(), на форме приложения
//Функция подсвечивает избыточные данные, добавляемые кодером, зеленым цветом.
//Так же функция подсвечивает красным цветом искаженные биты в кодовой комбинации H(x),
//получаемой из канала связи и ошибочные биты данных G'(x), получпемых на выходе декодера в случае,
//если последний не смог исправить все ошибки в принятой из канала связи кодовой комбинации
void Widget::showResult()
{
    QString strDataAfterCoder = QString::number(dataAfterCoder, 2);
    QString strDataAfterDistortion = QString::number(dataAfterDistortion, 2);
    QString strDataAfterDecoder = QString::number(dataAfterDecoder, 2);
    QString fColor[15];
    QString hColor[15];
    QString gColor[5];
    int count;

    if(strDataAfterCoder.size() < 15)
    {
        count = 15 - strDataAfterCoder.size();
        for(int i = 0; i < count; i++)
            strDataAfterCoder.prepend("0");
    }

    for(int i = 0; i < 15; i++)
    {
        if(i < 10)
            fColor[i] = "green";
        else
            fColor[i] = "black";
    }

    if(strDataAfterDistortion.size() < 15)
    {
        count = 15 - strDataAfterDistortion.size();
        for(int i = 0; i < count; i++)
            strDataAfterDistortion.prepend("0");
    }

    if(strDataAfterDecoder.size() < 5)
    {
        count = 5 - strDataAfterDecoder.size();
        for(int i = 0; i < count; i++)
            strDataAfterDecoder.prepend("0");
    }

    quint16 codeDifferent = dataAfterCoder ^ dataAfterDistortion;

    for(int i = 0; i < 15; i++)
    {
        if(i < 10)
            hColor[i] = "green";
        if(codeDifferent & (1 << i))
            hColor[i] = "red";
        else if(i > 9)
            hColor[i] = "black";
    }

    codeDifferent = userData ^ dataAfterDecoder;

    for(int i = 0; i < 5; i++)
    {
        if(codeDifferent & (1 << i))
            gColor[i] = "red";
        else
            gColor[i] = "black";
    }

    QString coloredData;

    for(int i = 14, j = 0; i >= 0; i--, j++)
        coloredData.operator +=("<font color=" + fColor[i] + ">" +strDataAfterCoder.operator [](j) + "</font>");

    ui->labelCoder->setText(coloredData);
    coloredData.clear();

    for(int i = 14, j = 0; i >= 0; i--, j++)
        coloredData.operator +=("<font color=" + hColor[i] + ">" +strDataAfterDistortion.operator [](j) + "</font>");

    ui->labelDecoder->setText(coloredData);
    coloredData.clear();

    for(int i = 4, j = 0; i >= 0; i--, j++)
        coloredData.operator +=("<font color=" + gColor[i] + ">" +strDataAfterDecoder.operator [](j) + "</font>");

    ui->labelDTE->setText(coloredData);
}
