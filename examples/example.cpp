#include <QApplication>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QStyleFactory>
#include <QVBoxLayout>
#include <QWindow>

#include "DoubleSlider.h"
#include "FilterIntegers.h"
#include "FilterDoubles.h"
#include "FilterDates.h"
#include "FilterStrings.h"
#include "ProgressBar.h"

static const double MIN {3};
static const double MAX {56};

static DoubleSlider* createDoubleSlider(QLabel* infoLabel)
{
    auto slider = new DoubleSlider(MIN, MAX);

    QObject::connect(slider,
                     &DoubleSlider::currentMinChanged,
                     infoLabel,
                     [ = ](double min)
    {
        infoLabel->setText("Double Slider: min = " + QString::number(min));
    });

    QObject::connect(slider,
                     &DoubleSlider::currentMaxChanged,
                     infoLabel,
                     [ = ](double max)
    {
        infoLabel->setText("Double Slider: max = " + QString::number(max));
    });

    return slider;
}

static FilterNumbers* createFilterIntegers(QLabel* infoLabel)
{
    auto filterNumbers = new FilterIntegers("Integers Filter", MIN, MAX);
    QObject::connect(filterNumbers,
                     &FilterIntegers::newNumericFilter,
                     infoLabel,
                     [ = ](int min, int max)
    {
        infoLabel->setText("Integers Filter: " + QString::number(min) + " | " +
                           QString::number(max));
    });

    filterNumbers->setCheckable(true);
    return filterNumbers;
}

static FilterNumbers* createFilterDoubles(QLabel* infoLabel)
{
    auto filterNumbers = new FilterDoubles("Doubles Filter", MIN, MAX);
    QObject::connect(filterNumbers,
                     &FilterDoubles::newNumericFilter,
                     infoLabel,
                     [ = ](double min, double max)
    {
        infoLabel->setText("Doubles Filter: " + QString::number(min) + " | " +
                           QString::number(max));
    });

    filterNumbers->setCheckable(true);
    return filterNumbers;
}

static FilterDates* createFilterDates(QLabel* infoLabel)
{
    auto filterDates = new FilterDates("Dates Filter",
                                       QDate(2010, 9, 21),
                                       QDate(2012, 2, 25),
                                       true);
    QObject::connect(filterDates,
                     &FilterDates::newDateFilter,
                     infoLabel,
                     [ = ](QDate from, QDate to, bool filterEmptyDates)
    {
        infoLabel->setText("Dates Filter: " + from.toString() + " | " +
                           to.toString() + " | " +
                           (filterEmptyDates ? "yes" : "no"));
    });

    filterDates->setCheckable(true);
    return filterDates;
}

static FilterStrings* createFilterStrings(QLabel* infoLabel)
{
    auto filterNames =
        new FilterStrings("Names Filter", QStringList{"a", "b", "c", "d"});
    QObject::connect(filterNames,
                     &FilterStrings::newStringFilter,
                     infoLabel,
                     [ = ](QStringList bannedItems)
    {
        infoLabel->setText("Names Filter: " + bannedItems.join(","));
    });

    filterNames->setCheckable(true);
    return filterNames;
}

static QVBoxLayout* createLeftWidgetColumn(QLabel* infoLabel)
{
    QVBoxLayout* leftLayout = new QVBoxLayout();
    leftLayout->setSpacing(10);
    auto* groupBox = new QGroupBox(QStringLiteral("Double Slider"));
    auto* layout = new QVBoxLayout(groupBox);
    layout->addWidget(createDoubleSlider(infoLabel));
    groupBox->setLayout(layout);
    leftLayout->addWidget(groupBox);
    leftLayout->addWidget(createFilterIntegers(infoLabel));
    leftLayout->addWidget(createFilterDoubles(infoLabel));
    leftLayout->addWidget(createFilterDates(infoLabel));
    leftLayout->addWidget(createFilterStrings(infoLabel));
    leftLayout->addWidget(infoLabel);
    leftLayout->addStretch();
    return leftLayout;
}

static QVBoxLayout* createRightWidgetColumn()
{
    QVBoxLayout* rightLayout = new QVBoxLayout();
    rightLayout->setSpacing(10);
    auto groupBox = new QGroupBox(QStringLiteral("Infinite progress bar"));
    auto* progressBar = new ProgressBar("Test", 0, groupBox);
    auto* layout = new QVBoxLayout();
    layout->addWidget(progressBar);
    auto* startStopButton = new QPushButton("start");
    QObject::connect(startStopButton, &QPushButton::clicked, progressBar,
                     [ = ]()
    {
        bool running = progressBar->isRunning();

        if (running)
            progressBar->stop();
        else
            progressBar->start();
        startStopButton->setText((running ? "start" : "stop"));

    });
    layout->addWidget(startStopButton);
    groupBox->setLayout(layout);
    rightLayout->addWidget(groupBox);
    rightLayout->addStretch();
    return rightLayout;
}

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    QApplication::setStyle(QStyleFactory::create("Fusion"));

    QWidget widget;
    auto infoLabel = new QLabel("Status");
    QHBoxLayout widgetLayout(&widget);
    QVBoxLayout* leftWidgetColumn = createLeftWidgetColumn(infoLabel);
    widgetLayout.addLayout(leftWidgetColumn);
    QVBoxLayout* rightWidgetColumn = createRightWidgetColumn();
    widgetLayout.addLayout(rightWidgetColumn);
    widget.setLayout(&widgetLayout);
    widget.show();

    return QApplication::exec();
}
