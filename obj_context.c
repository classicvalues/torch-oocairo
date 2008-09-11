static int
context_create (lua_State *L) {
    cairo_surface_t **surface = luaL_checkudata(L, 1, MT_NAME_SURFACE);
    cairo_t **obj;
    obj = lua_newuserdata(L, sizeof(cairo_t *));
    *obj = 0;
    luaL_getmetatable(L, MT_NAME_CONTEXT);
    lua_setmetatable(L, -2);
    *obj = cairo_create(*surface);
    return 1;
}

static int
cr_gc (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_destroy(*obj);
    *obj = 0;
    return 0;
}

static int
cr_append_path (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_path_t **path = luaL_checkudata(L, 2, MT_NAME_PATH);
    cairo_append_path(*obj, *path);
    return 0;
}

static int
cr_arc (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_arc(*obj, luaL_checknumber(L, 2), luaL_checknumber(L, 3),
              luaL_checknumber(L, 4), luaL_checknumber(L, 5),
              luaL_checknumber(L, 6));
    return 0;
}

static int
cr_arc_negative (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_arc_negative(*obj, luaL_checknumber(L, 2), luaL_checknumber(L, 3),
                       luaL_checknumber(L, 4), luaL_checknumber(L, 5),
                       luaL_checknumber(L, 6));
    return 0;
}

static int
cr_clip (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_clip(*obj);
    return 0;
}

static int
cr_clip_extents (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    double x1, y1, x2, y2;
    cairo_clip_extents(*obj, &x1, &y1, &x2, &y2);
    lua_pushnumber(L, x1);
    lua_pushnumber(L, y1);
    lua_pushnumber(L, x2);
    lua_pushnumber(L, y2);
    return 4;
}

static int
cr_clip_preserve (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_clip_preserve(*obj);
    return 0;
}

static int
cr_close_path (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_close_path(*obj);
    return 0;
}

static int
cr_copy_path (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_path_t **path = lua_newuserdata(L, sizeof(cairo_path_t *));
    *path = 0;
    luaL_getmetatable(L, MT_NAME_PATH);
    lua_setmetatable(L, -2);
    *path = cairo_copy_path(*obj);
    return 1;
}

static int
cr_copy_path_flat (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_path_t **path = lua_newuserdata(L, sizeof(cairo_path_t *));
    *path = 0;
    luaL_getmetatable(L, MT_NAME_PATH);
    lua_setmetatable(L, -2);
    *path = cairo_copy_path_flat(*obj);
    return 1;
}

static int
cr_curve_to (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_curve_to(*obj, luaL_checknumber(L, 2), luaL_checknumber(L, 3),
                   luaL_checknumber(L, 4), luaL_checknumber(L, 5),
                   luaL_checknumber(L, 6), luaL_checknumber(L, 7));
    return 0;
}

static int
cr_device_to_user (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    double x = luaL_checknumber(L, 2), y = luaL_checknumber(L, 3);
    cairo_device_to_user(*obj, &x, &y);
    lua_pushnumber(L, x);
    lua_pushnumber(L, y);
    return 2;
}

static int
cr_device_to_user_distance (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    double x = luaL_checknumber(L, 2), y = luaL_checknumber(L, 3);
    cairo_device_to_user_distance(*obj, &x, &y);
    lua_pushnumber(L, x);
    lua_pushnumber(L, y);
    return 2;
}

static int
cr_fill (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_fill(*obj);
    return 0;
}

static int
cr_fill_extents (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    double x1, y1, x2, y2;
    cairo_fill_extents(*obj, &x1, &y1, &x2, &y2);
    lua_pushnumber(L, x1);
    lua_pushnumber(L, y1);
    lua_pushnumber(L, x2);
    lua_pushnumber(L, y2);
    return 4;
}

static int
cr_fill_preserve (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_fill_preserve(*obj);
    return 0;
}

static int
cr_font_extents (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_font_extents_t extents;
    cairo_font_extents(*obj, &extents);
    create_lua_font_extents(L, &extents);
    return 1;
}

static int
cr_get_antialias (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    switch (cairo_get_antialias(*obj)) {
        case CAIRO_ANTIALIAS_DEFAULT:  lua_pushliteral(L, "default");   break;
        case CAIRO_ANTIALIAS_NONE:     lua_pushliteral(L, "none");      break;
        case CAIRO_ANTIALIAS_GRAY:     lua_pushliteral(L, "gray");      break;
        case CAIRO_ANTIALIAS_SUBPIXEL: lua_pushliteral(L, "subpixel");  break;
        default:                       lua_pushliteral(L, "<invalid>");
    }
    return 1;
}

static int
cr_get_current_point (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    double x, y;
    if (!cairo_has_current_point(*obj))
        return 0;
    cairo_get_current_point(*obj, &x, &y);
    lua_pushnumber(L, x);
    lua_pushnumber(L, y);
    return 2;
}

static int
cr_get_dash (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    int cnt, i;
    double *dashes = 0, offset;

    cnt = cairo_get_dash_count(*obj);
    if (cnt > 0) {
        dashes = malloc(sizeof(double) * cnt);
        assert(dashes);
    }

    cairo_get_dash(*obj, dashes, &offset);

    lua_createtable(L, cnt, 0);
    for (i = 0; i < cnt; ++i) {
        lua_pushnumber(L, dashes[i]);
        lua_rawseti(L, -2, i + 1);
    }
    lua_pushnumber(L, offset);

    if (cnt > 0)
        free(dashes);
    return 2;
}

static int
cr_get_fill_rule (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    switch (cairo_get_fill_rule(*obj)) {
        case CAIRO_FILL_RULE_WINDING:  lua_pushliteral(L, "winding");   break;
        case CAIRO_FILL_RULE_EVEN_ODD: lua_pushliteral(L, "even-odd");  break;
        default:                       lua_pushliteral(L, "<invalid>");
    }
    return 1;
}

static int
cr_get_font_face (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_font_face_t **face = lua_newuserdata(L, sizeof(cairo_font_face_t *));
    *face = 0;
    luaL_getmetatable(L, MT_NAME_FONTFACE);
    lua_setmetatable(L, -2);
    *face = cairo_get_font_face(*obj);
    cairo_font_face_reference(*face);
    return 1;
}

static int
cr_get_font_matrix (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_matrix_t mat;
    cairo_get_font_matrix(*obj, &mat);
    create_lua_matrix(L, &mat);
    return 1;
}

static int
cr_get_group_target (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_surface_t **surface = lua_newuserdata(L, sizeof(cairo_surface_t *));
    *surface = 0;
    luaL_getmetatable(L, MT_NAME_SURFACE);
    lua_setmetatable(L, -2);
    *surface = cairo_get_group_target(*obj);
    cairo_surface_reference(*surface);
    return 1;
}

static int
cr_get_line_cap (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    switch (cairo_get_line_cap(*obj)) {
        case CAIRO_LINE_CAP_BUTT:   lua_pushliteral(L, "butt");      break;
        case CAIRO_LINE_CAP_ROUND:  lua_pushliteral(L, "round");     break;
        case CAIRO_LINE_CAP_SQUARE: lua_pushliteral(L, "square");    break;
        default:                    lua_pushliteral(L, "<invalid>");
    }
    return 1;
}

static int
cr_get_line_join (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    switch (cairo_get_line_join(*obj)) {
        case CAIRO_LINE_JOIN_MITER: lua_pushliteral(L, "miter");     break;
        case CAIRO_LINE_JOIN_ROUND: lua_pushliteral(L, "round");     break;
        case CAIRO_LINE_JOIN_BEVEL: lua_pushliteral(L, "bevel");     break;
        default:                    lua_pushliteral(L, "<invalid>");
    }
    return 1;
}

static int
cr_get_line_width (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    lua_pushnumber(L, cairo_get_line_width(*obj));
    return 1;
}

static int
cr_get_matrix (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_matrix_t mat;
    cairo_get_matrix(*obj, &mat);
    create_lua_matrix(L, &mat);
    return 1;
}

static int
cr_get_miter_limit (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    lua_pushnumber(L, cairo_get_miter_limit(*obj));
    return 1;
}

static int
cr_get_operator (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    switch (cairo_get_operator(*obj)) {
        case CAIRO_OPERATOR_CLEAR:     lua_pushliteral(L, "clear");     break;
        case CAIRO_OPERATOR_SOURCE:    lua_pushliteral(L, "source");    break;
        case CAIRO_OPERATOR_OVER:      lua_pushliteral(L, "over");      break;
        case CAIRO_OPERATOR_IN:        lua_pushliteral(L, "in");        break;
        case CAIRO_OPERATOR_OUT:       lua_pushliteral(L, "out");       break;
        case CAIRO_OPERATOR_ATOP:      lua_pushliteral(L, "atop");      break;
        case CAIRO_OPERATOR_DEST:      lua_pushliteral(L, "dest");      break;
        case CAIRO_OPERATOR_DEST_OVER: lua_pushliteral(L, "dest-over"); break;
        case CAIRO_OPERATOR_DEST_IN:   lua_pushliteral(L, "dest-in");   break;
        case CAIRO_OPERATOR_DEST_OUT:  lua_pushliteral(L, "dest-out");  break;
        case CAIRO_OPERATOR_DEST_ATOP: lua_pushliteral(L, "dest-atop"); break;
        case CAIRO_OPERATOR_XOR:       lua_pushliteral(L, "xor");       break;
        case CAIRO_OPERATOR_ADD:       lua_pushliteral(L, "add");       break;
        case CAIRO_OPERATOR_SATURATE:  lua_pushliteral(L, "saturate");  break;
        default:                       lua_pushliteral(L, "<invalid>");
    }
    return 1;
}

static int
cr_get_source (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_pattern_t **pat = lua_newuserdata(L, sizeof(cairo_pattern_t *));
    *pat = 0;
    luaL_getmetatable(L, MT_NAME_PATTERN);
    lua_setmetatable(L, -2);
    *pat = cairo_get_source(*obj);
    cairo_pattern_reference(*pat);
    return 1;
}

static int
cr_get_target (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_surface_t **surface = lua_newuserdata(L, sizeof(cairo_surface_t *));
    *surface = 0;
    luaL_getmetatable(L, MT_NAME_SURFACE);
    lua_setmetatable(L, -2);
    *surface = cairo_get_target(*obj);
    cairo_surface_reference(*surface);
    return 1;
}

static int
cr_get_tolerance (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    lua_pushnumber(L, cairo_get_tolerance(*obj));
    return 1;
}

static int
cr_glyph_extents (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_glyph_t *glyphs;
    int num_glyphs;
    cairo_text_extents_t extents;
    from_lua_glyph_array(L, &glyphs, &num_glyphs, 2);
    cairo_glyph_extents(*obj, glyphs, num_glyphs, &extents);
    create_lua_text_extents(L, &extents);
    return 1;
}

static int
cr_glyph_path (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_glyph_t *glyphs;
    int num_glyphs;
    from_lua_glyph_array(L, &glyphs, &num_glyphs, 2);
    cairo_glyph_path(*obj, glyphs, num_glyphs);
    return 1;
}

static int
cr_has_current_point (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    lua_pushboolean(L, cairo_has_current_point(*obj));
    return 1;
}

static int
cr_identity_matrix (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_identity_matrix(*obj);
    return 0;
}

static int
cr_in_fill (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    lua_pushboolean(L,
        cairo_in_fill(*obj, luaL_checknumber(L, 2), luaL_checknumber(L, 3)));
    return 1;
}

static int
cr_in_stroke (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    lua_pushboolean(L,
        cairo_in_stroke(*obj, luaL_checknumber(L, 2), luaL_checknumber(L, 3)));
    return 1;
}

static int
cr_line_to (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_line_to(*obj, luaL_checknumber(L, 2), luaL_checknumber(L, 3));
    return 0;
}

static int
cr_move_to (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_move_to(*obj, luaL_checknumber(L, 2), luaL_checknumber(L, 3));
    return 0;
}

static int
cr_mask (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    void *p;
    cairo_pattern_t **pattern;
    cairo_surface_t **surface;

    /* This is needed to make sure the stack positions for the optional
     * arguments stay nil after we start pushing other things on. */
    lua_settop(L, 4);

    if ((p = lua_touserdata(L, 2))) {
        if (lua_getmetatable(L, 2)) {
            lua_getfield(L, LUA_REGISTRYINDEX, MT_NAME_PATTERN);
            if (lua_rawequal(L, -1, -2)) {
                pattern = p;
                cairo_mask(*obj, *pattern);
                return 0;
            }
            lua_pop(L, 1);

            lua_getfield(L, LUA_REGISTRYINDEX, MT_NAME_SURFACE);
            if (lua_rawequal(L, -1, -2)) {
                surface = p;
                cairo_mask_surface(*obj, *surface,
                                   luaL_optnumber(L, 3, 0),
                                   luaL_optnumber(L, 4, 0));
                return 0;
            }
            lua_pop(L, 2);
        }
    }

    return luaL_typerror(L, 2, "Cairo pattern or surface object");
}

static int
cr_new_path (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_new_path(*obj);
    return 0;
}

static int
cr_new_sub_path (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_new_sub_path(*obj);
    return 0;
}

static int
cr_paint (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_paint(*obj);
    return 0;
}

static int
cr_paint_with_alpha (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_paint_with_alpha(*obj, luaL_checknumber(L, 2));
    return 0;
}

static int
cr_path_extents (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    double x1, y1, x2, y2;
    cairo_path_extents(*obj, &x1, &y1, &x2, &y2);
    lua_pushnumber(L, x1);
    lua_pushnumber(L, y1);
    lua_pushnumber(L, x2);
    lua_pushnumber(L, y2);
    return 4;
}

static int
cr_pop_group (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_pattern_t **pattern = lua_newuserdata(L, sizeof(cairo_pattern_t *));
    *pattern = 0;
    luaL_getmetatable(L, MT_NAME_PATTERN);
    lua_setmetatable(L, -2);
    *pattern = cairo_pop_group(*obj);
    return 1;
}

static int
cr_pop_group_to_source (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_pop_group_to_source(*obj);
    return 0;
}

static int
cr_push_group (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_content_t content = CAIRO_CONTENT_COLOR_ALPHA;
    if (!lua_isnoneornil(L, 2))
        content = content_values[luaL_checkoption(L, 2, 0, content_names)];
    cairo_push_group_with_content(*obj, content);
    return 0;
}

static int
cr_rectangle (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_rectangle(*obj, luaL_checknumber(L, 2), luaL_checknumber(L, 3),
                    luaL_checknumber(L, 4), luaL_checknumber(L, 5));
    return 0;
}

static int
cr_rel_curve_to (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_rel_curve_to(*obj, luaL_checknumber(L, 2), luaL_checknumber(L, 3),
                       luaL_checknumber(L, 4), luaL_checknumber(L, 5),
                       luaL_checknumber(L, 6), luaL_checknumber(L, 7));
    return 0;
}

static int
cr_rel_line_to (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_rel_line_to(*obj, luaL_checknumber(L, 2), luaL_checknumber(L, 3));
    return 0;
}

static int
cr_rel_move_to (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_rel_move_to(*obj, luaL_checknumber(L, 2), luaL_checknumber(L, 3));
    return 0;
}

static int
cr_reset_clip (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_reset_clip(*obj);
    return 0;
}

static int
cr_restore (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_restore(*obj);
    return 0;
}

static int
cr_rotate (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_rotate(*obj, luaL_checknumber(L, 2));
    return 0;
}

static int
cr_save (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_save(*obj);
    return 0;
}

static int
cr_scale (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_scale(*obj, luaL_checknumber(L, 2), luaL_checknumber(L, 3));
    return 0;
}

static int
cr_select_font_face (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_select_font_face(*obj, luaL_checkstring(L, 2),
            font_slant_values[luaL_checkoption(L, 3, "normal",
                                               font_slant_names)],
            font_weight_values[luaL_checkoption(L, 4, "normal",
                                                font_weight_names)]);
    return 0;
}

static int
cr_set_antialias (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_antialias_t aa;
    if (lua_isboolean(L, 2)) {
        /* A boolean value is interpreted as a signal to turn AA on or off. */
        aa = lua_toboolean(L, 2) ? CAIRO_ANTIALIAS_DEFAULT
                                 : CAIRO_ANTIALIAS_NONE;
    }
    else
        aa = antialias_values[luaL_checkoption(L, 2, 0, antialias_names)];
    cairo_set_antialias(*obj, aa);
    return 0;
}

static int
cr_set_dash (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    int num_dashes, i;
    double *dashes = 0, offset, n, dashtotal;

    luaL_checktype(L, 2, LUA_TTABLE);
    offset = luaL_checknumber(L, 3);

    num_dashes = lua_objlen(L, 2);
    if (num_dashes > 0) {
        dashes = malloc(sizeof(double) * num_dashes);
        assert(dashes);
        dashtotal = 0;

        for (i = 0; i < num_dashes; ++i) {
            lua_rawgeti(L, 2, i + 1);
            if (!lua_isnumber(L, -1)) {
                free(dashes);
                return luaL_error(L, "bad dash pattern, dash value %d isn't"
                                  " a number", i + 1);
            }
            n = lua_tonumber(L, -1);
            if (n < 0) {
                free(dashes);
                return luaL_error(L, "bad dash pattern, dash value %d is"
                                  " negative", i + 1);
            }
            dashes[i] = n;
            dashtotal += n;
            lua_pop(L, 1);
        }

        if (dashtotal == 0) {
            free(dashes);
            return luaL_error(L, "bad dash pattern, all values are zero");
        }
    }

    cairo_set_dash(*obj, dashes, num_dashes, offset);

    if (num_dashes > 0)
        free(dashes);
    return 0;
}

static int
cr_set_fill_rule (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_set_fill_rule(*obj,
            fillrule_values[luaL_checkoption(L, 2, 0, fillrule_names)]);
    return 0;
}

static int
cr_set_font_matrix (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_matrix_t mat;
    from_lua_matrix(L, &mat, 2);
    cairo_set_font_matrix(*obj, &mat);
    return 0;
}

static int
cr_set_font_size (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_set_font_size(*obj, luaL_checknumber(L, 2));
    return 0;
}

static int
cr_set_line_cap (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_set_line_cap(*obj,
            linecap_values[luaL_checkoption(L, 2, 0, linecap_names)]);
    return 0;
}

static int
cr_set_line_join (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_set_line_join(*obj,
            linejoin_values[luaL_checkoption(L, 2, 0, linejoin_names)]);
    return 0;
}

static int
cr_set_line_width (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    double n = luaL_checknumber(L, 2);
    luaL_argcheck(L, n >= 0, 2, "line width cannot be negative");
    cairo_set_line_width(*obj, n);
    return 0;
}

static int
cr_set_matrix (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_matrix_t mat;
    from_lua_matrix(L, &mat, 2);
    cairo_set_matrix(*obj, &mat);
    return 0;
}

static int
cr_set_miter_limit (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_set_miter_limit(*obj, luaL_checknumber(L, 2));
    return 0;
}

static int
cr_set_operator (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_set_operator(*obj,
            operator_values[luaL_checkoption(L, 2, 0, operator_names)]);
    return 0;
}

static int
cr_set_source (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    void *p;
    cairo_pattern_t **pattern;
    cairo_surface_t **surface;

    /* This is needed to make sure the stack positions for the optional
     * arguments stay nil after we start pushing other things on. */
    lua_settop(L, 4);

    if ((p = lua_touserdata(L, 2))) {
        if (lua_getmetatable(L, 2)) {
            lua_getfield(L, LUA_REGISTRYINDEX, MT_NAME_PATTERN);
            if (lua_rawequal(L, -1, -2)) {
                pattern = p;
                cairo_set_source(*obj, *pattern);
                return 0;
            }
            lua_pop(L, 1);

            lua_getfield(L, LUA_REGISTRYINDEX, MT_NAME_SURFACE);
            if (lua_rawequal(L, -1, -2)) {
                surface = p;
                cairo_set_source_surface(*obj, *surface,
                                         luaL_optnumber(L, 3, 0),
                                         luaL_optnumber(L, 4, 0));
                return 0;
            }
            lua_pop(L, 2);
        }
    }

    return luaL_typerror(L, 2, "Cairo pattern or surface object");
}

static int
cr_set_source_rgb (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_set_source_rgb(*obj, luaL_checknumber(L, 2), luaL_checknumber(L, 3),
                         luaL_checknumber(L, 4));
    return 0;
}

static int
cr_set_source_rgba (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_set_source_rgba(*obj, luaL_checknumber(L, 2), luaL_checknumber(L, 3),
                          luaL_checknumber(L, 4), luaL_checknumber(L, 5));
    return 0;
}

static int
cr_set_tolerance (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_set_tolerance(*obj, luaL_checknumber(L, 2));
    return 0;
}

static int
cr_show_glyphs (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_glyph_t *glyphs;
    int num_glyphs;
    from_lua_glyph_array(L, &glyphs, &num_glyphs, 2);
    cairo_show_glyphs(*obj, glyphs, num_glyphs);
    free(glyphs);
    return 0;
}

static int
cr_show_text (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_show_text(*obj, luaL_checkstring(L, 2));
    return 0;
}

static int
cr_stroke (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_stroke(*obj);
    return 0;
}

static int
cr_stroke_extents (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    double x1, y1, x2, y2;
    cairo_stroke_extents(*obj, &x1, &y1, &x2, &y2);
    lua_pushnumber(L, x1);
    lua_pushnumber(L, y1);
    lua_pushnumber(L, x2);
    lua_pushnumber(L, y2);
    return 4;
}

static int
cr_stroke_preserve (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_stroke_preserve(*obj);
    return 0;
}

static int
cr_text_extents (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_text_extents_t extents;
    cairo_text_extents(*obj, luaL_checkstring(L, 2), &extents);
    create_lua_text_extents(L, &extents);
    return 1;
}

static int
cr_text_path (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_text_path(*obj, luaL_checkstring(L, 2));
    return 0;
}

static int
cr_transform (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_matrix_t mat;
    from_lua_matrix(L, &mat, 2);
    cairo_transform(*obj, &mat);
    return 0;
}

static int
cr_translate (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_translate(*obj, luaL_checknumber(L, 2), luaL_checknumber(L, 3));
    return 0;
}

static int
cr_user_to_device (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    double x = luaL_checknumber(L, 2), y = luaL_checknumber(L, 3);
    cairo_user_to_device(*obj, &x, &y);
    lua_pushnumber(L, x);
    lua_pushnumber(L, y);
    return 2;
}

static int
cr_user_to_device_distance (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    double x = luaL_checknumber(L, 2), y = luaL_checknumber(L, 3);
    cairo_user_to_device_distance(*obj, &x, &y);
    lua_pushnumber(L, x);
    lua_pushnumber(L, y);
    return 2;
}

static const luaL_Reg
context_methods[] = {
    { "__gc", cr_gc },
    { "append_path", cr_append_path },
    { "arc", cr_arc },
    { "arc_negative", cr_arc_negative },
    { "clip", cr_clip },
    { "clip_extents", cr_clip_extents },
    { "clip_preserve", cr_clip_preserve },
    { "close_path", cr_close_path },
    { "copy_path", cr_copy_path },
    { "copy_path_flat", cr_copy_path_flat },
    { "curve_to", cr_curve_to },
    { "device_to_user", cr_device_to_user },
    { "device_to_user_distance", cr_device_to_user_distance },
    { "fill", cr_fill },
    { "fill_extents", cr_fill_extents },
    { "fill_preserve", cr_fill_preserve },
    { "font_extents", cr_font_extents },
    { "get_antialias", cr_get_antialias },
    { "get_current_point", cr_get_current_point },
    { "get_dash", cr_get_dash },
    { "get_fill_rule", cr_get_fill_rule },
    { "get_font_face", cr_get_font_face },
    { "get_font_matrix", cr_get_font_matrix },
    { "get_group_target", cr_get_group_target },
    { "get_line_cap", cr_get_line_cap },
    { "get_line_join", cr_get_line_join },
    { "get_line_width", cr_get_line_width },
    { "get_matrix", cr_get_matrix },
    { "get_miter_limit", cr_get_miter_limit },
    { "get_operator", cr_get_operator },
    { "get_source", cr_get_source },
    { "get_target", cr_get_target },
    { "get_tolerance", cr_get_tolerance },
    { "glyph_extents", cr_glyph_extents },
    { "glyph_path", cr_glyph_path },
    { "has_current_point", cr_has_current_point },
    { "identity_matrix", cr_identity_matrix },
    { "in_fill", cr_in_fill },
    { "in_stroke", cr_in_stroke },
    { "line_to", cr_line_to },
    { "move_to", cr_move_to },
    { "mask", cr_mask },
    { "new_path", cr_new_path },
    { "new_sub_path", cr_new_sub_path },
    { "paint", cr_paint },
    { "paint_with_alpha", cr_paint_with_alpha },
    { "path_extents", cr_path_extents },
    { "pop_group", cr_pop_group },
    { "pop_group_to_source", cr_pop_group_to_source },
    { "push_group", cr_push_group },
    { "rectangle", cr_rectangle },
    { "rel_curve_to", cr_rel_curve_to },
    { "rel_line_to", cr_rel_line_to },
    { "rel_move_to", cr_rel_move_to },
    { "reset_clip", cr_reset_clip },
    { "restore", cr_restore },
    { "rotate", cr_rotate },
    { "save", cr_save },
    { "scale", cr_scale },
    { "select_font_face", cr_select_font_face },
    { "set_antialias", cr_set_antialias },
    { "set_dash", cr_set_dash },
    { "set_fill_rule", cr_set_fill_rule },
    { "set_font_matrix", cr_set_font_matrix },
    { "set_font_size", cr_set_font_size },
    { "set_line_cap", cr_set_line_cap },
    { "set_line_join", cr_set_line_join },
    { "set_line_width", cr_set_line_width },
    { "set_matrix", cr_set_matrix },
    { "set_miter_limit", cr_set_miter_limit },
    { "set_operator", cr_set_operator },
    { "set_source", cr_set_source },
    { "set_source_rgb", cr_set_source_rgb },
    { "set_source_rgba", cr_set_source_rgba },
    { "set_tolerance", cr_set_tolerance },
    { "show_glyphs", cr_show_glyphs },
    { "show_text", cr_show_text },
    { "stroke", cr_stroke },
    { "stroke_extents", cr_stroke_extents },
    { "stroke_preserve", cr_stroke_preserve },
    { "text_extents", cr_text_extents },
    { "text_path", cr_text_path },
    { "transform", cr_transform },
    { "translate", cr_translate },
    { "user_to_device", cr_user_to_device },
    { "user_to_device_distance", cr_user_to_device_distance },
    { 0, 0 }
};

/* vi:set ts=4 sw=4 expandtab: */
