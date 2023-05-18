CREATE DATABASE new_database;
CREATE TABLE users(
	name TEXT PRIMARY KEY,
	password TEXT NOT NULL
);
CREATE TABLE control_examples(
	id integer PRIMARY KEY,
	input TEXT NOT NULL,
	output TEXT NOT NULL
);
CREATE TABLE tasks(
	name TEXT PRIMARY KEY,
	condition TEXT NOT NULL,
	difficulty integer NOT NULL
);
CREATE TABLE solves(
	id integer PRIMARY KEY,
	programm TEXT NOT NULL,
	status TEXT NOT NULL
);
CREATE TABLE tests(
	name TEXT PRIMARY KEY
);
CREATE TABLE control_examples_solves(
	id_control_examples integer NOT NULL,
	name_tasks TEXT NOT NULL,
    FOREIGN KEY(id_control_examples) REFERENCES control_examples(id) ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY(name_tasks) REFERENCES tasks(name) ON DELETE CASCADE ON UPDATE CASCADE
);
CREATE TABLE solves_tasks(
	id_solves integer NOT NULL,
	name_tasks TEXT NOT NULL,
    FOREIGN KEY(id_solves) REFERENCES solves(id) ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY(name_tasks) REFERENCES tasks(name) ON DELETE CASCADE ON UPDATE CASCADE
);
CREATE TABLE tasks_tests(
	name_tasks TEXT NOT NULL,
	name_tests TEXT NOT NULL,
    FOREIGN KEY(name_tasks) REFERENCES tasks(name) ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY(name_tests) REFERENCES tests(name) ON DELETE CASCADE ON UPDATE CASCADE
);
CREATE TABLE many_tests_has_many_users (
	name_tests TEXT NOT NULL,
	name_users TEXT NOT NULL,
    FOREIGN KEY(name_tests) REFERENCES tests(name) ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY(name_users) REFERENCES users(name) ON DELETE CASCADE ON UPDATE CASCADE
);
CREATE TABLE many_users_has_many_Solves (
	name_users TEXT NOT NULL,
	id_solves integer NOT NULL,
    FOREIGN KEY(name_users) REFERENCES users(name) ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY(id_solves) REFERENCES solves(id) ON DELETE CASCADE ON UPDATE CASCADE
);
