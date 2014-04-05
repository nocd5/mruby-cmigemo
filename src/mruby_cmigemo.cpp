#include "mruby.h"
#include "mruby/string.h"
#include "../cmigemo/src/migemo.h"
#include "stdio.h"

extern "C" {
    void mrb_mruby_cmigemo_gem_init(mrb_state* mrb);
    void mrb_mruby_cmigemo_gem_final(mrb_state* mrb);
}

static mrb_value
mrb_migemo_open(mrb_state *mrb, mrb_value self){
    mrb_value mrbv_dict;
    mrb_get_args(mrb, "S", &mrbv_dict);
    migemo *m = migemo_open(RSTRING_PTR(mrbv_dict));
    return mrb_obj_value(m);
}

static mrb_value
mrb_migemo_close(mrb_state *mrb, mrb_value self){
    mrb_value mrbv_migemo;
    mrb_get_args(mrb, "o", &mrbv_migemo);
    migemo *m = (migemo*)mrb_object(mrbv_migemo);
    migemo_close(m);
    return self;
}

static mrb_value
mrb_migemo_query(mrb_state *mrb, mrb_value self){
    mrb_value mrbv_query;
    mrb_value mrbv_migemo;
    mrb_get_args(mrb, "oS", &mrbv_migemo, &mrbv_query);
    migemo *m = (migemo*)mrb_object(mrbv_migemo);
    unsigned char* p =
        migemo_query(m, (const unsigned char*)RSTRING_PTR(mrbv_query));
    mrb_value result = mrb_str_new_cstr(mrb, (const char*)p);
    migemo_release(m, p);
    return result;
}

// migemo_release()ÇÕmrb_migemo_query()ì‡Ç≈åƒÇ‘ÇÃÇ≈ïsóv

static mrb_value
mrb_migemo_set_operator(mrb_state *mrb, mrb_value self){
    mrb_value mrbv_migemo;
    mrb_int mrbv_index;
    mrb_value mrbv_operator;
    mrb_get_args(mrb, "oiS", &mrbv_migemo, &mrbv_index, &mrbv_operator);
    migemo *m = (migemo*)mrb_object(mrbv_migemo);
    mrb_int result =
        migemo_set_operator(m, mrbv_index, (const unsigned char*)RSTRING_PTR(mrbv_operator));
    return mrb_fixnum_value(result);
}

static mrb_value
mrb_migemo_get_operator(mrb_state *mrb, mrb_value self){
    mrb_value mrbv_migemo;
    mrb_int mrbv_index;
    mrb_get_args(mrb, "oi", &mrbv_migemo, &mrbv_index);
    migemo *m = (migemo*)mrb_object(mrbv_migemo);
    const unsigned char* p = migemo_get_operator(m, mrbv_index);
    mrb_value result = mrb_str_new_cstr(mrb, (const char*)p);
    return result;
}

static mrb_value
mrb_migemo_load(mrb_state *mrb, mrb_value self){
    mrb_value mrbv_migemo;
    mrb_int mrbv_id;
    mrb_value mrbv_dict;
    mrb_get_args(mrb, "oiS", &mrbv_migemo, &mrbv_id, &mrbv_dict);
    migemo *m = (migemo*)mrb_object(mrbv_migemo);
    mrb_int result = migemo_load(m, mrbv_id, RSTRING_PTR(mrbv_dict));
    return mrb_fixnum_value(result);
}

static mrb_value
mrb_migemo_is_enable(mrb_state *mrb, mrb_value self){
    mrb_value mrbv_migemo;
    mrb_get_args(mrb, "o", &mrbv_migemo);
    migemo *m = (migemo*)mrb_object(mrbv_migemo);
    mrb_int result = migemo_is_enable(m);
    return mrb_fixnum_value(result);
}

void
mrb_mruby_cmigemo_gem_init(mrb_state* mrb){
    struct RClass *mod;
    mod = mrb_define_module(mrb, "Migemo");

    // ä÷êî
    mrb_define_module_function(mrb, mod, "migemo_open",         mrb_migemo_open,         ARGS_REQ(1));
    mrb_define_module_function(mrb, mod, "migemo_close",        mrb_migemo_close,        ARGS_REQ(1));
    mrb_define_module_function(mrb, mod, "migemo_query",        mrb_migemo_query,        ARGS_REQ(2));
    mrb_define_module_function(mrb, mod, "migemo_set_operator", mrb_migemo_set_operator, ARGS_REQ(3));
    mrb_define_module_function(mrb, mod, "migemo_get_operator", mrb_migemo_get_operator, ARGS_REQ(2));
    mrb_define_module_function(mrb, mod, "migemo_load",         mrb_migemo_load,         ARGS_REQ(3));
    mrb_define_module_function(mrb, mod, "migemo_is_enable",    mrb_migemo_is_enable,    ARGS_REQ(1));

    // íËêî
    /* for migemo_load() */
    mrb_define_const(mrb, mod, "MIGEMO_DICTID_INVALID",     mrb_fixnum_value(0));
    mrb_define_const(mrb, mod, "MIGEMO_DICTID_MIGEMO",      mrb_fixnum_value(1));
    mrb_define_const(mrb, mod, "MIGEMO_DICTID_ROMA2HIRA",   mrb_fixnum_value(2));
    mrb_define_const(mrb, mod, "MIGEMO_DICTID_HIRA2KATA",   mrb_fixnum_value(3));
    mrb_define_const(mrb, mod, "MIGEMO_DICTID_HAN2ZEN",     mrb_fixnum_value(4));
    mrb_define_const(mrb, mod, "MIGEMO_DICTID_ZEN2HAN",     mrb_fixnum_value(5));

    /* for migemo_set_operator()/migemo_get_operator().  see: rxgen.h */
    mrb_define_const(mrb, mod, "MIGEMO_OPINDEX_OR",         mrb_fixnum_value(0));
    mrb_define_const(mrb, mod, "MIGEMO_OPINDEX_NEST_IN",    mrb_fixnum_value(1));
    mrb_define_const(mrb, mod, "MIGEMO_OPINDEX_NEST_OUT",   mrb_fixnum_value(2));
    mrb_define_const(mrb, mod, "MIGEMO_OPINDEX_SELECT_IN",  mrb_fixnum_value(3));
    mrb_define_const(mrb, mod, "MIGEMO_OPINDEX_SELECT_OUT", mrb_fixnum_value(4));
    mrb_define_const(mrb, mod, "MIGEMO_OPINDEX_NEWLINE",    mrb_fixnum_value(5));
}

void
mrb_mruby_cmigemo_gem_final(mrb_state* mrb) { }

