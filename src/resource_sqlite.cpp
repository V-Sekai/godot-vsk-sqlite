/**************************************************************************/
/*  resource_sqlite.cpp                                                   */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#include "resource_sqlite.h"
#include "core/io/file_access.h"

void SQLiteDatabase::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_sqlite"), &SQLiteDatabase::get_sqlite);
	ClassDB::bind_method(D_METHOD("set_resource", "path"), &SQLiteDatabase::set_resource);
	ClassDB::bind_static_method("SQLiteDatabase", D_METHOD("create"), &SQLiteDatabase::create);
}

Ref<SQLiteDatabase> SQLiteDatabase::create() {
	Ref<SQLite> db;
	db.instantiate();
	db->open_in_memory();
	Ref<SQLiteDatabase> sqlite_database;
	sqlite_database.instantiate();
	sqlite_database->db = db;
	sqlite_database->is_opened = true;
	return sqlite_database;
}

void SQLiteDatabase::set_resource(const String &p_path) {
	is_opened = db->open(p_path);
	emit_changed();
}

Ref<SQLite> SQLiteDatabase::get_sqlite() {
	return db;
}

SQLiteDatabase::SQLiteDatabase() {
	db.instantiate();
}

SQLiteDatabase::~SQLiteDatabase() {
	db.unref();
}
