#include "scoremanager.hpp"

ScoreManager::ScoreManager()
{
    myDb = QSqlDatabase::addDatabase(DATABASE_TYPE);
    myDb.setDatabaseName(DATABASE_NAME);
    if(myDb.open())
    {
        QSqlQuery queryCreation{myDb};
        queryCreation.exec("CREATE TABLE IF NOT EXISTS Scores ( Id INTEGER PRIMARY KEY AUTOINCREMENT,Score INTEGER);");
    }
}

// Load all the scores in a list.
QList<int> ScoreManager::selectAll()
{
    QList<int> scoresLoaded{};
    auto queryAll = myDb.exec("SELECT Score FROM Scores");
    while(queryAll.next())
    {
        scoresLoaded.push_back(queryAll.value(0).toInt());
    }
    return scoresLoaded;
}

// Select the highest score in he database.
int ScoreManager::selectBestScore()
{
    auto queryBest = myDb.exec("SELECT MAX(Score) FROM Scores");
    auto const best{queryBest.value(0).toInt()};
    return best;
}

// Insert a new score in the database
void ScoreManager::insertScore(const int score)
{
    QSqlQuery insertQuery{myDb};
    insertQuery.prepare("INSERT INTO Scores(Score)"
                        "VALUES (:score)");
    insertQuery.bindValue(":score",score);
    insertQuery.exec();
}

ScoreManager::~ScoreManager()
{
    myDb.close();
}
