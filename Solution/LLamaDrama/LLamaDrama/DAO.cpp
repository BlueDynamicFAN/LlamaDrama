#include "DAO.h"

DAO::DAO(void)
{
	int result = sqlite3_open("highscore.db", &highscoreDB);
	if (result != 0)
	{
		printf("Failed to open the database! Error code %d\n", result);
		return;
	}
	printf("Successfully opened the database!\n");

	const char* sql = "CREATE TABLE Player(Id INT PRIMARY KEY NOT NULL, Highscore INT NOT NULL);";
	result = sqlite3_exec(highscoreDB, sql, NULL, NULL, NULL);
}

DAO::~DAO(void)
{
	int result = sqlite3_close(highscoreDB);
	if (result != 0)
	{
		printf("Failed to close the entities database! Error code %d\n", result);
		return;
	}
	printf("Successfully closed the entities database!\n");
}

int ResultCallback(void* notUsed, int argc, char** argv, char** azColName)
{
	if (argc == 1 && argv) {
		*static_cast<int*>(notUsed) = atoi(argv[0]);
		return 0;
	}

	for (int i = 0; i < argc; i++)
	{
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		if (i == 1)
		{
			*static_cast<int*>(notUsed) = atoi(argv[1]);
		}
	}
	printf("\n");
	return 0;
}

int DAO::setHighScore(int id, int score)
{
	char* errMsg;
	int count = 0;

	std::string sqlStr = "SELECT count(*) FROM Player WHERE id = " + std::to_string(id) + ";";
	int result = sqlite3_exec(highscoreDB, sqlStr.c_str(), ResultCallback, &count, &errMsg);

	if (count == 0)
	{
		sqlStr = "INSERT INTO Player (id, score) VALUES(" + std::to_string(id) + ", " + std::to_string(score) + ");";
		int result = sqlite3_exec(highscoreDB, sqlStr.c_str(), ResultCallback, 0, &errMsg);
	}
	else
	{
		sqlStr = "SELECT * FROM Player WHERE id = " + std::to_string(id) + ";";
		int result = sqlite3_exec(highscoreDB, sqlStr.c_str(), ResultCallback, &count, &errMsg);

		sqlStr = "UPDATE Player SET score=" + std::to_string(count + score) + " WHERE id=" + std::to_string(id) + ";";
		result = sqlite3_exec(highscoreDB, sqlStr.c_str(), ResultCallback, 0, &errMsg);
	}
	return count + score;
}

const std::vector<Score>& DAO::getHighScore(int id)
{
	std::vector<Score> entities;
	char* errMsg;
	int score;

	std::string sqlStr = "SELECT * FROM Player WHERE id =(" + std::to_string(id) + ");";
	int result = sqlite3_exec(highscoreDB, sqlStr.c_str(), ResultCallback, &score, &errMsg);

	return entities;
}
