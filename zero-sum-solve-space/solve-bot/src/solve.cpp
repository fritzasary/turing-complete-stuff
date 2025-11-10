#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <climits>
#include <memory>
#include <cstring>
#include <functional>
//#include <pybind11/stl.h>  for std::vector<std::tuple> exposure
#include <sqlite3.h>
#include <openssl/sha.h>
#include "game.h"
#include "tictactoe.h"
#include "solve.h"


enum boundFlag { EXACT, LOWER, UPPER };

struct ttFlag {
	gameResult value;
	boundFlag flag;
};

std::unordered_map<std::string, ttFlag> memo;


// DB START
sqlite3* db;


// This initializes the database
void init_db(const std::string& path) {
    if (sqlite3_open(path.c_str(), &db) != SQLITE_OK)
        throw std::runtime_error("DB open failed");
    const char* sql = "CREATE TABLE IF NOT EXISTS memo (hash TEXT PRIMARY KEY, value INTEGER)";    sqlite3_exec(db, sql, nullptr, nullptr, nullptr);
}


// This gets the result from the database
bool get_db(const std::string& hash, int& outVal) {
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, "SELECT value FROM memo WHERE hash=?", -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, hash.c_str(), -1, SQLITE_STATIC);
    bool found = false;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        outVal = sqlite3_column_int(stmt, 0);
        found = true;
    }
    sqlite3_finalize(stmt);
    return found;
}


// --- write to DB ---
void set_db(const std::string& hash, int val) {
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, "INSERT OR REPLACE INTO memo VALUES (?, ?)", -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, hash.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, val);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}


//// DB END


std::string hashBoard(const board& b) {
    std::string serialized = b.serialize();
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(serialized.data()),
           serialized.size(), digest);
    // convert to hex string (example)
    char hex[2*SHA256_DIGEST_LENGTH + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        sprintf(hex + i*2, "%02x", digest[i]);
    hex[2*SHA256_DIGEST_LENGTH] = '\0';
    return std::string(hex);
}


int solve(game* position, int alpha, int beta, bool maxingPlayer) {
    std::unique_ptr<board> boardPtr = position->getBoard();
    const board& b = *boardPtr;
    std::string id = hashBoard(b);
    int dbVal;
    bool cache = true;

    int origAlpha = alpha;
    int origBeta = beta;

    // ---- Lookup in-memory ----
    if (!id.empty() && memo.count(id)) {
        const ttFlag& entry = memo[id];
        if (entry.flag == EXACT) return entry.value;
        if (entry.flag == LOWER) alpha = std::max(alpha, static_cast<int>(entry.value));
        if (entry.flag == UPPER) beta = std::min(beta, static_cast<int>(entry.value));
        if (alpha >= beta) return entry.value;
    }

    // ---- Lookup persistent DB ----
    if (get_db(id, dbVal) && cache) {
        memo[id] = {static_cast<gameResult>(dbVal), EXACT};
        return dbVal;
    }

    // ---- Base case ----
    int value = position->primitiveValue();
    if (value != UNDECIDED) {
        memo[id] = {static_cast<gameResult>(value), EXACT};
        if (cache) set_db(id, value);
        return value;
    }

    // ---- Recursive search ----
    int best = maxingPlayer ? INT_MIN : INT_MAX;

    for (const auto& move : position->generateMoves()) {
        std::unique_ptr<game> next(position->doMove(move));
        int result = solve(next.get(), alpha, beta, !maxingPlayer);

        if (maxingPlayer) {
            best = std::max(best, result);
            alpha = std::max(alpha, best);
        } else {
            best = std::min(best, result);
            beta = std::min(beta, best);
        }
        if (alpha >= beta) break;
    }

    // ---- Determine bound type ----
    boundFlag flag;
    if (best <= origAlpha) flag = UPPER; // fail-low
    else if (best >= origBeta) flag = LOWER; // fail-high
    else flag = EXACT;

    // ---- Store result ----
    memo[id] = {static_cast<gameResult>(best), flag};
    if ((flag == EXACT) && cache)
        set_db(id, best);

    return best;
}

