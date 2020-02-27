#ifndef FILTERNAMESTEST_H
#define FILTERNAMESTEST_H

#include <QObject>
#include <QStringList>

class FilterNamesTest : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();

    void testToggling();

    void testSelectAllToggling();

    void testListItemChecking();

private:
    QStringList testEntriesList_;

    static constexpr int NO_SIGNAL {0};
    static constexpr int SIGNAL_RECEIVED {1};
};

#endif // FILTERNAMESTEST_H
