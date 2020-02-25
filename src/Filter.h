#ifndef FILTER_H
#define FILTER_H

#include <QGroupBox>

#include "wble_global.h"

/**
 * @brief Filters base class.
 */
class WBLE_EXPORT Filter : public QGroupBox
{
    Q_OBJECT
public:
    explicit Filter(const QString& title, QWidget* parent = nullptr);

    ~Filter() override = default;

    Filter& operator=(const Filter& other) = delete;
    Filter(const Filter& other) = delete;

    Filter& operator=(Filter&& other) = delete;
    Filter(Filter&& other) = delete;
};

#endif // FILTER_H
