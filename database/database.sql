CREATE DATABASE new_database;
CREATE TABLE users(
    login TEXT PRIMARY KEY NOT NULL,
    password TEXT NOT NULL,
    name TEXT NOT NULL
);
CREATE TABLE control_examples(
	id integer PRIMARY KEY NOT NULL,
	input TEXT NOT NULL,
	output TEXT NOT NULL
);
CREATE TABLE tasks(
	name TEXT PRIMARY KEY NOT NULL,
	condition TEXT NOT NULL,
	difficulty integer NOT NULL
);
CREATE TABLE solves(
	id integer PRIMARY KEY NOT NULL,
	programm TEXT NOT NULL,
	status TEXT NOT NULL
);
CREATE TABLE tests(
	name TEXT PRIMARY KEY NOT NULL
);
CREATE TABLE control_examples_tasks(
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
CREATE TABLE tests_users (
	name_tests TEXT NOT NULL,
	login_users TEXT NOT NULL,
    FOREIGN KEY(name_tests) REFERENCES tests(name) ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY(login_users) REFERENCES users(login) ON DELETE CASCADE ON UPDATE CASCADE
);
CREATE TABLE users_solves (
	login_users TEXT NOT NULL,
	id_solves integer NOT NULL,
    FOREIGN KEY(login_users) REFERENCES users(login) ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY(id_solves) REFERENCES solves(id) ON DELETE CASCADE ON UPDATE CASCADE
);
