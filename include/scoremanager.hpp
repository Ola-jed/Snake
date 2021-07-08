#ifndef SCOREMANAGER_HPP
#define SCOREMANAGER_HPP

#include <QList>
#include <QVariant>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlResult>
#include <QSqlDriver>
#include <QSqlDatabase>

class ScoreManager
{
    public:
        ScoreManager();
        ~ScoreManager();
        QList<int> selectAll();
        int selectBestScore();
        void insertScore(const int score);

    private:
        const QString DATABASE_TYPE{"QSQLITE"};
        const QString DATABASE_NAME{"Scores.db"};
        QSqlDatabase myDb;
};

#endif // SCOREMANAGER_HPP
