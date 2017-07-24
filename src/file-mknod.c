/*
** file-mknod.c - File class with mknod method
**
** Copyright (c) Uchio Kondo 2017
**
** See Copyright Notice in LICENSE
*/

#define _BSD_SOURCE

#include <mruby.h>
#include <mruby/data.h>
#include <mruby/error.h>
#include <mruby/hash.h>
#include <mruby/value.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "mrb_file.h"

#define DONE mrb_gc_arena_restore(mrb, 0);

#define mrb_mknod_symbol_p(type, expected) (type == mrb_intern_lit(mrb, expected))
#define mrb_mknod_make_sym(name) mrb_symbol_value(mrb_intern_lit(mrb, name))

static mrb_value mrb_file_mknod(mrb_state *mrb, mrb_value self)
{
  char *path;
  mode_t mode = 0644;
  int major, minor;
  dev_t dev;
  mrb_sym type;
  mrb_get_args(mrb, "nzii|i", &type, &path, &major, &minor, &mode);

  dev = makedev(major, minor);

  if (mrb_mknod_symbol_p(type, "block")) {
    mode = S_IFBLK | mode;
  } else if (mrb_mknod_symbol_p(type, "char")) {
    mode = S_IFCHR | mode;
  } else if (mrb_mknod_symbol_p(type, "regular")) {
    mode = S_IFREG | mode;
  } else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Invalid device type");
  }

  if (mknod(path, mode, dev) < 0) {
    mrb_sys_fail(mrb, "mknod failed");
  }

  return mrb_true_value();
}

static mrb_value mrb_file_get_filetype(mrb_state *mrb, mode_t mode)
{
  if (S_ISCHR(mode)) {
    return mrb_mknod_make_sym("char");
  } else if (S_ISBLK(mode)) {
    return mrb_mknod_make_sym("block");
  } else if (S_ISREG(mode) && S_ISDIR(mode)) {
    return mrb_mknod_make_sym("regular");
  } else {
    return mrb_mknod_make_sym("unknown");
  }
}

static mrb_value mrb_file_majorminor(mrb_state *mrb, mrb_value self)
{
  char *path;
  struct stat s;
  mrb_value ha;
  mrb_get_args(mrb, "z", &path);

  if (stat(path, &s) < 0) {
    mrb_sys_fail(mrb, "stat");
  }

  ha = mrb_hash_new_capa(mrb, 3);
  mrb_hash_set(mrb, ha, mrb_mknod_make_sym("major"), mrb_fixnum_value(major(s.st_rdev)));
  mrb_hash_set(mrb, ha, mrb_mknod_make_sym("minor"), mrb_fixnum_value(minor(s.st_rdev)));
  mrb_hash_set(mrb, ha, mrb_mknod_make_sym("filetype"), mrb_file_get_filetype(mrb, s.st_mode));

  return ha;
}

void mrb_mruby_io_gem_init(mrb_state *mrb);

void mrb_mruby_file_mknod_gem_init(mrb_state *mrb)
{
  mrb_mruby_io_gem_init(mrb);

  struct RClass *file;
  file = mrb_class_get(mrb, "File");

  mrb_define_class_method(mrb, file, "mknod", mrb_file_mknod, MRB_ARGS_ARG(4, 1));
  mrb_define_class_method(mrb, file, "makedev", mrb_file_mknod, MRB_ARGS_ARG(4, 1));
  mrb_define_class_method(mrb, file, "majorminor", mrb_file_majorminor, MRB_ARGS_REQ(1));

  DONE;
}

void mrb_mruby_file_mknod_gem_final(mrb_state *mrb)
{
}
