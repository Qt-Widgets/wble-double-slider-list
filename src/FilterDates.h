#ifndef FILTERDATES_H
#define FILTERDATES_H

#include <QWidget>
#include <QDate>
#include <QCalendarWidget>

#include "Filter.h"
#include "wble_global.h"

namespace Ui
{
class FilterDates;
} // namespace Ui

/**
 * @brief filter for date type columns in model.
 */
class WBLE_EXPORT FilterDates : public Filter
{
    Q_OBJECT
public:
    FilterDates(const QString& name,
                QDate min, QDate max,
                bool emptyDates,
                QWidget* parent = nullptr);

    ~FilterDates() override;

    FilterDates& operator=(const FilterDates& other) = delete;
    FilterDates(const FilterDates& other) = delete;

    FilterDates& operator=(FilterDates&& other) = delete;
    FilterDates(FilterDates&& other) = delete;

private:
    ///Initial filter minimum date.
    const QDate minOnInit_;

    ///Initial filter maximum date.
    const QDate maxOnInit_;

    Ui::FilterDates* ui;

    QCalendarWidget calendarLeft_;

    QCalendarWidget calendarRight_;

    ///Flag indicating there were wmpty dates in column.
    const bool emptyDates_;

private Q_SLOTS:
    void setChecked(bool checked);

    /**
     * Trigerred on change of date in left date edit.
     * @param newDate new value.
     */
    void lowerDateChanged(QDate newDate);

    /**
     * Trigerred on change of date in right date edit.
     * @param newDate new value.
     */
    void higherDateChanged(QDate newDate);

    /**
     * Trigerred when empty dates checkbox state change.
     * @param checked flag.
     */
    void emptyDatesToggled(bool checked);

Q_SIGNALS:
    void newDateFilter(QDate from, QDate to, bool filterEmptyDates);
};

#endif // FILTERDATES_H
