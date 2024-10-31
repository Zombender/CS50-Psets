DROP TABLE IF EXISTS user;
DROP TABLE IF EXISTS logs;
DROP TABLE IF EXISTS users;

CREATE TABLE user (
    id INTEGER,
    username TEXT NOT NULL, hash TEXT NOT NULL,
    cash NUMERIC NOT NULL DEFAULT 10000.00,
    PRIMARY KEY(id)
);

CREATE UNIQUE INDEX username ON users (username);

CREATE TABLE logs(
    id_user INTEGER NOT NULL,
    transaction_id INTEGER PRIMARY KEY AUTOINCREMENT,
    symbol TEXT NOT NULL,
    name TEXT NOT NULL,
    shares INTEGER NOT NULL,
    price NUMERIC NOT NULL,
    transaction_date TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY(id_user) REFERENCES user(id)
);
