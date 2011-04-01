
#include <libappindicator/app-indicator.h> 

#include <ruby.h>
#include <rbgobject.h>
#include <rbgtk.h>


/*
 * This macro helps to define every setter method with one argument since
 * the only difference between them is the method name and the cast
 */
#define APP_INDICATOR_SETTER1(suffix, cast) \
static VALUE ai_set_##suffix(VALUE self, VALUE val) { \
	VALUE rAI = rb_iv_get(self,"@ai_instance"); \
	app_indicator_set_##suffix(RVAL2GOBJ(rAI), cast(val)); \
	return Qnil; \
}

/*
 * This macro helps to define every setter method with two arguments since
 * the only difference between them is the method name and the cast
 */
#define APP_INDICATOR_SETTER2(suffix, cast1, cast2) \
static VALUE ai_set_##suffix(VALUE self, VALUE val1, VALUE val2) { \
	VALUE rAI = rb_iv_get(self,"@ai_instance"); \
	app_indicator_set_##suffix(RVAL2GOBJ(rAI), cast1(val1), cast2(val2)); \
	return Qnil; \
}

/*
 * This macro helps to define *every* getter method of the object since
 * the only difference between them is the method name and the cast
 */
#define APP_INDICATOR_GETTER(suffix, cast) \
static VALUE ai_get_##suffix(VALUE self) { \
	VALUE rAppIndicator = rb_iv_get(self,"@ai_instance"); \
	return cast(app_indicator_get_##suffix(RVAL2GOBJ(rAppIndicator))); \
}

static VALUE ai_initialize(int argc, VALUE* argv, VALUE self) {
	VALUE id, icon_name, category, icon_theme_path;

	rb_scan_args(argc, argv, "31", &id, &icon_name, &category, &icon_theme_path);

	AppIndicator* pAI;
	if(NIL_P(icon_theme_path))
		pAI = app_indicator_new(RVAL2CSTR(id), RVAL2CSTR(icon_name), NUM2INT(category));
	else
		pAI = app_indicator_new_with_path(RVAL2CSTR(id), RVAL2CSTR(icon_name), NUM2INT(category), RVAL2CSTR(icon_theme_path));

	rb_iv_set(self, "@ai_instance", GOBJ2RVAL(pAI));
	return self;
}

APP_INDICATOR_SETTER1(status, NUM2INT);
APP_INDICATOR_SETTER1(attention_icon, RVAL2CSTR);
APP_INDICATOR_SETTER2(attention_icon_full, RVAL2CSTR, RVAL2CSTR);
APP_INDICATOR_SETTER1(menu, RVAL2GOBJ);
APP_INDICATOR_SETTER1(icon, RVAL2CSTR);
APP_INDICATOR_SETTER2(icon_full, RVAL2CSTR, RVAL2CSTR);
APP_INDICATOR_SETTER2(label, RVAL2CSTR, RVAL2CSTR);
APP_INDICATOR_SETTER1(icon_theme_path, RVAL2CSTR);
APP_INDICATOR_SETTER1(ordering_index, NUM2UINT);

APP_INDICATOR_GETTER(id, CSTR2RVAL)
APP_INDICATOR_GETTER(category, INT2NUM)
APP_INDICATOR_GETTER(status, INT2NUM)
APP_INDICATOR_GETTER(icon, CSTR2RVAL)
APP_INDICATOR_GETTER(icon_desc, CSTR2RVAL)
APP_INDICATOR_GETTER(icon_theme_path, CSTR2RVAL)
APP_INDICATOR_GETTER(attention_icon, CSTR2RVAL)
APP_INDICATOR_GETTER(attention_icon_desc, CSTR2RVAL)
APP_INDICATOR_GETTER(menu, GOBJ2RVAL)
APP_INDICATOR_GETTER(label, CSTR2RVAL)
APP_INDICATOR_GETTER(label_guide, CSTR2RVAL)
APP_INDICATOR_GETTER(ordering_index, UINT2NUM)

static VALUE ai_build_menu_from_desktop(VALUE self, VALUE desktop_file, VALUE desktop_profile) {
	VALUE rAppIndicator = rb_iv_get(self,"@ai_instance");
	app_indicator_build_menu_from_desktop(RVAL2GOBJ(rAppIndicator), RVAL2CSTR(desktop_file), RVAL2CSTR(desktop_profile));
	return Qnil;
}


Init_appindicator() {
	VALUE mAppIndicator = rb_define_module("AppIndicator");

	VALUE cStatus = rb_define_class_under(mAppIndicator, "Status", rb_cObject);
	rb_define_const(cStatus, "PASSIVE", INT2FIX(APP_INDICATOR_STATUS_PASSIVE));
	rb_define_const(cStatus, "ACTIVE", INT2FIX(APP_INDICATOR_STATUS_ACTIVE));
	rb_define_const(cStatus, "ATTENTION", INT2FIX(APP_INDICATOR_STATUS_ATTENTION));

	VALUE cCategory = rb_define_class_under(mAppIndicator, "Category", rb_cObject);
	rb_define_const(cCategory, "APPLICATION_STATUS", INT2FIX(APP_INDICATOR_CATEGORY_APPLICATION_STATUS));
	rb_define_const(cCategory, "COMMUNICATIONS", INT2FIX(APP_INDICATOR_CATEGORY_COMMUNICATIONS));
	rb_define_const(cCategory, "SYSTEM_SERVICES", INT2FIX(APP_INDICATOR_CATEGORY_SYSTEM_SERVICES));
	rb_define_const(cCategory, "HARDWARE", INT2FIX(APP_INDICATOR_CATEGORY_HARDWARE));
	rb_define_const(cCategory, "OTHER", INT2FIX(APP_INDICATOR_CATEGORY_OTHER));

	VALUE cAppIndicator = rb_define_class_under(mAppIndicator, "AppIndicator", rb_cObject);
	rb_define_method(cAppIndicator, "initialize", ai_initialize, -1);

	rb_define_method(cAppIndicator, "set_status", ai_set_status, 1);
	rb_define_method(cAppIndicator, "set_attention_icon", ai_set_attention_icon, 1);
	rb_define_method(cAppIndicator, "set_attention_icon_full", ai_set_attention_icon_full, 2);
	rb_define_method(cAppIndicator, "set_menu", ai_set_menu, 1);
	rb_define_method(cAppIndicator, "set_icon", ai_set_icon, 1);
	rb_define_method(cAppIndicator, "set_icon_full", ai_set_icon_full, 2);
	rb_define_method(cAppIndicator, "set_label", ai_set_label, 2);
	rb_define_method(cAppIndicator, "set_icon_theme_path", ai_set_icon_theme_path, 1);
	rb_define_method(cAppIndicator, "set_ordering_index", ai_set_ordering_index, 1);

	rb_define_method(cAppIndicator, "get_id", ai_get_id, 0);
	rb_define_method(cAppIndicator, "get_category", ai_get_category, 0);
	rb_define_method(cAppIndicator, "get_status", ai_get_status, 0);
	rb_define_method(cAppIndicator, "get_icon", ai_get_icon, 0);
	rb_define_method(cAppIndicator, "get_icon_desc", ai_get_icon_desc, 0);
	rb_define_method(cAppIndicator, "get_icon_theme_path", ai_get_icon_theme_path, 0);
	rb_define_method(cAppIndicator, "get_attention_icon", ai_get_attention_icon, 0);
	rb_define_method(cAppIndicator, "get_attention_icon_desc", ai_get_attention_icon_desc, 0);
	rb_define_method(cAppIndicator, "get_menu", ai_get_menu, 0);
	rb_define_method(cAppIndicator, "get_label", ai_get_label, 0);
	rb_define_method(cAppIndicator, "get_label_guide", ai_get_label_guide, 0);
	rb_define_method(cAppIndicator, "get_ordering_index", ai_get_ordering_index, 0);

	rb_define_method(cAppIndicator, "build_menu_from_desktop", ai_build_menu_from_desktop, 2);
}
