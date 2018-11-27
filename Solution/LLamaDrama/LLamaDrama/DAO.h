#ifndef _DAO_HG
#define _DAO_HG

#include <vector>
#include <string>

#include "sqlite3.h"

struct Score {
	int id;
	int score;
};

class DAO
{
public:
	DAO(void);
	~DAO(void);

	int setHighScore(int id, int score);
	const std::vector<Score>& getHighScore(int id);

private:
	sqlite3* highscoreDB;
};

#endif
