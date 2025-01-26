/**************************************************************************/
/*  resource_saver_sqlite.cpp                                             */
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

#include "resource_saver_sqlite.h"

#include "core/io/file_access.h"
#include "godot_sqlite.h"
#include "resource_sqlite.h"

Error ResourceFormatSaverSQLite::save(const Ref<Resource> &p_resource, const String &p_path, uint32_t p_flags) {
	Ref<SQLiteDatabase> database = p_resource;
	ERR_FAIL_COND_V(database.is_null(), ERR_INVALID_PARAMETER);
	if (!database->get_sqlite()->backup(p_path)) {
		return ERR_CANT_CREATE;
	}
	return OK;
}

void ResourceFormatSaverSQLite::get_recognized_extensions(const Ref<Resource> &p_resource, List<String> *p_extensions) const {
	if (Object::cast_to<SQLiteDatabase>(p_resource.ptr())) {
		p_extensions->push_back("sqlite");
	}
}

bool ResourceFormatSaverSQLite::recognize(const Ref<Resource> &p_resource) const {
	return Object::cast_to<SQLiteDatabase>(p_resource.ptr()) != nullptr;
}
