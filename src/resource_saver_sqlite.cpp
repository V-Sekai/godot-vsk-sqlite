#include "resource_saver_sqlite.h"
#include "resource_sqlite.h"
#include "godot_sqlite.h"
#include "core/io/file_access.h"

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
