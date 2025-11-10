import sqlite3
import os
import solver
import hashlib

def hash_board(board):
    serialized = board.getBoard().serialize()  # must match C++ serialization *exactly*
    h = hashlib.sha256(serialized.encode('utf-8')).hexdigest()
    return h.lower()  # OpenSSL’s sprintf("%02x") produces lowercase hex

def getCached(cur, hash_value):
    """Check for cached result using the same cursor."""
    cur.execute("SELECT value FROM memo WHERE hash=?", (hash_value,))
    row = cur.fetchone()
    # print("CACHE MISS: ", hash_value) if row is None else print("CACHE HIT:", hash_value, "->", row[0])
    return row[0] if row else None



def traverse_orig(game, board, db_path):
    return solver.solve(game, board)

def traverse(game, board, db_path):
    # Always resolve full absolute path
    db_path = os.path.abspath(db_path)
    # print(f"Using database: {db_path}")

    conn = sqlite3.connect(db_path)
    cur = conn.cursor()

    # Confirm table exists in *this connection*
    cur.execute("SELECT name FROM sqlite_master WHERE type='table';")
    # print("Tables in DB:", cur.fetchall())

    # Compute hash
    h = hash_board(board)

    # Get from cache
    cached = getCached(cur, h)
    if cached is not None:
        #print("Accessing cached result")
        conn.close()
        return cached

    # Compute result via solver
    result = solver.solve(game, board)
    #print("Computed value...", result)

    # Insert new result
    cur.execute("INSERT OR REPLACE INTO memo (hash, value) VALUES (?, ?)", (h, result))
    conn.commit()
    conn.close()
    return result
