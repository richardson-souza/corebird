/*  This file is part of corebird, a Gtk+ linux Twitter client.
 *  Copyright (C) 2016 Timm Bäder
 *
 *  corebird is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  corebird is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with corebird.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __TYPES_H
#define __TYPES_H

#include <glib-object.h>
#include <json-glib/json-glib.h>
#include "CbMedia.h"

struct _CbUserIdentity
{
  gint64  id;
  char   *screen_name;
  char   *user_name;
};
typedef struct _CbUserIdentity CbUserIdentity;
void cb_user_identity_free (CbUserIdentity *id);
void cb_user_identity_copy (CbUserIdentity *id, CbUserIdentity *id2);
void cb_user_identity_parse (CbUserIdentity *id, JsonObject *user_obj);
GVariant *cb_user_identity_serialize (const CbUserIdentity *id);
void cb_user_identity_deserialize (GVariant       *variant,
                                   CbUserIdentity *result);

struct _CbTextEntity
{
  guint  from;
  guint  to;
  guint  info : 1;
  char  *display_text;
  char  *tooltip_text;
  char  *target;
};
typedef struct _CbTextEntity CbTextEntity;
void cb_text_entity_free (CbTextEntity *e);
void cb_text_entity_copy (CbTextEntity *e1, CbTextEntity *e2);
GVariant *cb_text_entity_serialize (const CbTextEntity *e);
void cb_text_entity_deserialize (GVariant     *variant,
                                 CbTextEntity *result);


struct _CbMiniTweet
{
  gint64 id;
  gint64 created_at;
  CbUserIdentity author;
  char *text;
  CbTextEntity *entities;
  guint n_entities;
  CbMedia **medias;
  guint n_medias;
  guint display_range_start;
};
typedef struct _CbMiniTweet CbMiniTweet;
void cb_mini_tweet_free (CbMiniTweet *tweet);
void cb_mini_tweet_copy (CbMiniTweet *t1, CbMiniTweet *t2);
void cb_mini_tweet_init (CbMiniTweet *t);
void cb_mini_tweet_parse (CbMiniTweet *t, JsonObject *obj);
void cb_mini_tweet_parse_entities (CbMiniTweet *t, JsonObject *obj);
GVariant *cb_mini_tweet_serialize (const CbMiniTweet *t);
CbMiniTweet *cb_mini_tweet_deserialize (const GVariant *variant);

char *escape_ampersand (const char *in);

#endif
