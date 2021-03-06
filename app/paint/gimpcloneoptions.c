/* GIMP - The GNU Image Manipulation Program
 * Copyright (C) 1995 Spencer Kimball and Peter Mattis
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "config.h"

#include <string.h>

#include <glib-object.h>

#include "libgimpconfig/gimpconfig.h"

#include "paint-types.h"

#include "gimpcloneoptions.h"


enum
{
  PROP_0,
  PROP_CLONE_TYPE
};


static void   gimp_clone_options_set_property (GObject      *object,
                                               guint         property_id,
                                               const GValue *value,
                                               GParamSpec   *pspec);
static void   gimp_clone_options_get_property (GObject      *object,
                                               guint         property_id,
                                               GValue       *value,
                                               GParamSpec   *pspec);
static void   gimp_clone_options_notify       (GObject      *object,
                                               GParamSpec   *pspec);


G_DEFINE_TYPE (GimpCloneOptions, gimp_clone_options, GIMP_TYPE_SOURCE_OPTIONS)

#define parent_class gimp_clone_options_parent_class


static void
gimp_clone_options_class_init (GimpCloneOptionsClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->set_property = gimp_clone_options_set_property;
  object_class->get_property = gimp_clone_options_get_property;
  object_class->notify       = gimp_clone_options_notify;

  GIMP_CONFIG_INSTALL_PROP_ENUM (object_class, PROP_CLONE_TYPE,
                                 "clone-type", NULL,
                                 GIMP_TYPE_CLONE_TYPE,
                                 GIMP_IMAGE_CLONE,
                                 GIMP_PARAM_STATIC_STRINGS);
}

static void
gimp_clone_options_init (GimpCloneOptions *options)
{
}

static void
gimp_clone_options_set_property (GObject      *object,
                                 guint         property_id,
                                 const GValue *value,
                                 GParamSpec   *pspec)
{
  GimpCloneOptions *options = GIMP_CLONE_OPTIONS (object);

  switch (property_id)
    {
    case PROP_CLONE_TYPE:
      options->clone_type = g_value_get_enum (value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static void
gimp_clone_options_get_property (GObject    *object,
                                 guint       property_id,
                                 GValue     *value,
                                 GParamSpec *pspec)
{
  GimpCloneOptions *options = GIMP_CLONE_OPTIONS (object);

  switch (property_id)
    {
    case PROP_CLONE_TYPE:
      g_value_set_enum (value, options->clone_type);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static void
gimp_clone_options_notify (GObject    *object,
                           GParamSpec *pspec)
{
  if (G_OBJECT_CLASS (parent_class)->notify)
    G_OBJECT_CLASS (parent_class)->notify (object, pspec);

  if (! strcmp ("clone-type", g_param_spec_get_name (pspec)))
    GIMP_SOURCE_OPTIONS (object)->use_source =
      (GIMP_CLONE_OPTIONS (object)->clone_type == GIMP_IMAGE_CLONE);
}
