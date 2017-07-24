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

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "mrb_file.h"

#define DONE mrb_gc_arena_restore(mrb, 0);

#define mrb_mknod_symbol_p(type, expected) (type == mrb_intern_lit(mrb, expected))

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

void mrb_mruby_file_mknod_gem_init(mrb_state *mrb)
{
  struct RClass *file;
  if (mrb_class_defined(mrb, "File")) {
    file = mrb_class_get(mrb, "File");
  } else {
    file = mrb_define_class(mrb, "File", mrb->object_class);
  }

  mrb_define_class_method(mrb, file, "mknod", mrb_file_mknod, MRB_ARGS_ARG(4, 1));
  mrb_define_class_method(mrb, file, "makedev", mrb_file_mknod, MRB_ARGS_ARG(4, 1));

  DONE;
}

void mrb_mruby_file_mknod_gem_final(mrb_state *mrb)
{
}
