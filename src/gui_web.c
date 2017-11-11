/* vi:set ts=8 sts=4 sw=4:
 *
 * VIM - Vi IMproved		by Bram Moolenaar
 *                              Web port by Lu Wang
 *
 * Do ":help uganda"  in Vim to read copying and usage conditions.
 * Do ":help credits" in Vim to see a list of people who contributed.
 * See README.txt for an overview of the Vim source code.
 */

/*
 * gui_web.c 
 * gui functions for vim.js
 *
 * Copyright (c) 2013 Lu Wang <coolwanglu@gmail.com>
 */

#include "vim.h"

     void
gui_mch_mousehide(int hide)
{
}

/*
 * ------------------------------------------------------------
 * GUI_MCH functionality
 * ------------------------------------------------------------
 */

/*
 * Parse the GUI related command-line arguments.  Any arguments used are
 * deleted from argv, and *argc is decremented accordingly.  This is called
 * when vim is started, whether or not the GUI has been started.
 */
    void
gui_mch_prepare(int *argc, char **argv)
{
    // nothing to do
}



#ifndef ALWAYS_USE_GUI
/*
 * Check if the GUI can be started.  Called before gvimrc is sourced.
 * Return OK or FAIL.
 *
 * Not needed by vim.js
 */
    int
gui_mch_init_check(void)
{
    return OK;
}
#endif

/*
 * Initialise the GUI.  Create all the windows, set up all the call-backs
 * etc.
 */
    int
gui_mch_init(void)
{
    vimjs_init();
    gui.border_offset = 0;
    gui.border_width = 0;
    gui.scrollbar_width = 0;
    gui.scrollbar_height = 0;

    gui.back_pixel = gui_get_color((char_u*)"black");
    gui.norm_pixel = gui_get_color((char_u*)"white");

    set_normal_colors();
    gui_check_colors();

    gui.def_back_pixel = gui.back_pixel;
    gui.def_norm_pixel = gui.norm_pixel;

    gui.in_focus = TRUE; 

    Rows = vimjs_get_window_height() / vimjs_get_char_height();
    Columns = vimjs_get_window_width() / vimjs_get_char_width();

    // For clipboard
    clip_init(TRUE);

    return OK;
}


/*
 * Called when the foreground or background color has been changed.
 */
    void
gui_mch_new_colors(void)
{
    // Nothing to do
}

/*
 * Open the GUI window which was created by a call to gui_mch_init().
 */
    int
gui_mch_open(void)
{
    return OK;
}

    void
gui_mch_exit(int rc)
{
}

/*
 * Get the position of the top left corner of the window.
 */
    int
gui_mch_get_winpos(int *x, int *y)
{
    *x = *y = 0;
    return OK;
}

/*
 * Set the position of the top left corner of the window to the given
 * coordinates.
 */
    void
gui_mch_set_winpos(int x, int y)
{
    // Nothing to do
    // we never change winpos
}

    void
gui_mch_set_shellsize(
    int		width,
    int		height,
    int		min_width,
    int		min_height,
    int		base_width,
    int		base_height,
    int		direction)
{
    vimjs_resize(width, height);
}

/*
 * Get the screen dimensions.
 */
    void
gui_mch_get_screen_dimensions(int *screen_w, int *screen_h)
{
    *screen_w = vimjs_get_window_width();
    *screen_h = vimjs_get_window_height();
}

/*
 * Initialise vim to use the font with the given name.	Return FAIL if the font
 * could not be loaded, OK otherwise.
 */
    int
gui_mch_init_font(char_u *font_name, int fontset)
{
    vimjs_init_font((char*)font_name);

    gui.char_width = vimjs_get_char_width();
    gui.char_height = vimjs_get_char_height();
    gui.char_ascent = gui.char_height;

    char_u buf[100];

    gui.norm_font = vim_strsave(font_name);
        
    vim_strncpy(buf, "bold ", 99); // should report 1 less to vim_strncpy 
    vim_strcat(buf, font_name, 100);
    gui.bold_font = vim_strsave(buf);

    vim_strncpy(buf, "italic ", 99); // should report 1 less to vim_strncpy 
    vim_strcat(buf, font_name, 100);
    gui.ital_font = vim_strsave(buf);

    vim_strncpy(buf, "bold italic ", 99); // should report 1 less to vim_strncpy 
    vim_strcat(buf, font_name, 100);
    gui.boldital_font = vim_strsave(buf);

    int w,h;
    w = vimjs_get_window_width();
    h = vimjs_get_window_height();
    gui_resize_shell(w, h);

    return OK;
}

/*
 * Adjust gui.char_height (after 'linespace' was changed).
 */
    int
gui_mch_adjust_charheight(void)
{
    //TODO
    return FAIL;
}

/*
 * Get a font structure for highlighting.
 */
    GuiFont
gui_mch_get_font(char_u *name, int giveErrorIfMissing)
{
    if(vimjs_check_font((char*)name)) 
        return (char*)vim_strsave(name);

    if (giveErrorIfMissing)
        EMSG2(_(e_font), name);
    return NOFONT;
}

#if defined(FEAT_EVAL) || defined(PROTO)
/*
 * Return the name of font "font" in allocated memory.
 * Don't know how to get the actual name, thus use the provided name.
 */
    char_u *
gui_mch_get_fontname(GuiFont font, char_u *name)
{
    if (font != NOFONT)
    {
        return vim_strsave((char_u*)font);
    }
    return NULL;
}
#endif

/*
 * Set the current text font.
 */
    void
gui_mch_set_font(GuiFont font)
{
    vimjs_set_font(font);
}

/*
 * If a font is not going to be used, free its structure.
 */
    void
gui_mch_free_font(font)
    GuiFont	font;
{
    vim_free(font);
}

/*
 * Return the Pixel value (color) for the given color name.  
 * Return INVALCOLOR when failed.
 */
    guicolor_T
gui_mch_get_color(char_u *name)
{
    // html:  https://www.w3schools.com/colors/colors_hex.asp
    // x11:   http://vim.wikia.com/wiki/Xterm256_color_names_for_console_Vim
    // GuiVim runtime rgb.txt
    // dbg:   http://vim.wikia.com/wiki/View_all_colors_available_to_gvim 
    static const char* const vimnames[][2] = 
    {
        {"Black", "#000000"},
        {"Navy", "#000080"},
        {"DarkBlue", "#00008B"},
        {"MediumBlue", "#0000CD"},
        {"Blue", "#0000FF"},
        {"DarkGreen", "#006400"},
        {"Green", "#008000"},
        {"Teal", "#008080"},
        {"DarkCyan", "#008B8B"},
        {"DeepSkyBlue", "#00BFFF"},
        {"DarkTurquoise", "#00CED1"},
        {"MediumSpringGreen", "#00FA9A"},
        {"Lime", "#00FF00"},
        {"SpringGreen", "#00FF7F"},
        {"Aqua", "#00FFFF"},
        {"Cyan", "#00FFFF"},
        {"MidnightBlue", "#191970"},
        {"DodgerBlue", "#1E90FF"},
        {"LightSeaGreen", "#20B2AA"},
        {"ForestGreen", "#228B22"},
        {"SeaGreen", "#2E8B57"},
        {"DarkSlateGray", "#2F4F4F"},
        {"DarkSlateGrey", "#2F4F4F"},
        {"LimeGreen", "#32CD32"},
        {"MediumSeaGreen", "#3CB371"},
        {"Turquoise", "#40E0D0"},
        {"RoyalBlue", "#4169E1"},
        {"SteelBlue", "#4682B4"},
        {"DarkSlateBlue", "#483D8B"},
        {"MediumTurquoise", "#48D1CC"},
        {"Indigo", "#4B0082"},
        {"DarkOliveGreen", "#556B2F"},
        {"CadetBlue", "#5F9EA0"},
        {"CornflowerBlue", "#6495ED"},
        {"RebeccaPurple", "#663399"},
        {"MediumAquaMarine", "#66CDAA"},
        {"DimGray", "#696969"},
        {"DimGrey", "#696969"},
        {"SlateBlue", "#6A5ACD"},
        {"OliveDrab", "#6B8E23"},
        {"SlateGray", "#708090"},
        {"SlateGrey", "#708090"},
        {"LightSlateGray", "#778899"},
        {"LightSlateGrey", "#778899"},
        {"MediumSlateBlue", "#7B68EE"},
        {"LawnGreen", "#7CFC00"},
        {"Chartreuse", "#7FFF00"},
        {"Aquamarine", "#7FFFD4"},
        {"Maroon", "#800000"},
        {"Purple", "#800080"},
        {"Olive", "#808000"},
        {"Gray", "#808080"},
        {"Grey", "#808080"},
        {"SkyBlue", "#87CEEB"},
        {"LightSkyBlue", "#87CEFA"},
        {"BlueViolet", "#8A2BE2"},
        {"DarkRed", "#8B0000"},
        {"DarkMagenta", "#8B008B"},
        {"SaddleBrown", "#8B4513"},
        {"DarkSeaGreen", "#8FBC8F"},
        {"LightGreen", "#90EE90"},
        {"MediumPurple", "#9370DB"},
        {"DarkViolet", "#9400D3"},
        {"PaleGreen", "#98FB98"},
        {"DarkOrchid", "#9932CC"},
        {"YellowGreen", "#9ACD32"},
        {"Sienna", "#A0522D"},
        {"Brown", "#A52A2A"},
        {"DarkGray", "#A9A9A9"},
        {"DarkGrey", "#A9A9A9"},
        {"LightBlue", "#ADD8E6"},
        {"GreenYellow", "#ADFF2F"},
        {"PaleTurquoise", "#AFEEEE"},
        {"LightSteelBlue", "#B0C4DE"},
        {"PowderBlue", "#B0E0E6"},
        {"FireBrick", "#B22222"},
        {"DarkGoldenRod", "#B8860B"},
        {"MediumOrchid", "#BA55D3"},
        {"RosyBrown", "#BC8F8F"},
        {"DarkKhaki", "#BDB76B"},
        {"Silver", "#C0C0C0"},
        {"MediumVioletRed", "#C71585"},
        {"IndianRed", "#CD5C5C"},
        {"Peru", "#CD853F"},
        {"Chocolate", "#D2691E"},
        {"Tan", "#D2B48C"},
        {"LightGray", "#D3D3D3"},
        {"LightGrey", "#D3D3D3"},
        {"Thistle", "#D8BFD8"},
        {"Orchid", "#DA70D6"},
        {"GoldenRod", "#DAA520"},
        {"PaleVioletRed", "#DB7093"},
        {"Crimson", "#DC143C"},
        {"Gainsboro", "#DCDCDC"},
        {"Plum", "#DDA0DD"},
        {"BurlyWood", "#DEB887"},
        {"LightCyan", "#E0FFFF"},
        {"Lavender", "#E6E6FA"},
        {"DarkSalmon", "#E9967A"},
        {"Violet", "#EE82EE"},
        {"PaleGoldenRod", "#EEE8AA"},
        {"LightCoral", "#F08080"},
        {"Khaki", "#F0E68C"},
        {"AliceBlue", "#F0F8FF"},
        {"HoneyDew", "#F0FFF0"},
        {"Azure", "#F0FFFF"},
        {"SandyBrown", "#F4A460"},
        {"Wheat", "#F5DEB3"},
        {"Beige", "#F5F5DC"},
        {"WhiteSmoke", "#F5F5F5"},
        {"MintCream", "#F5FFFA"},
        {"GhostWhite", "#F8F8FF"},
        {"Salmon", "#FA8072"},
        {"AntiqueWhite", "#FAEBD7"},
        {"Linen", "#FAF0E6"},
        {"LightGoldenRodYellow", "#FAFAD2"},
        {"OldLace", "#FDF5E6"},
        {"Red", "#FF0000"},
        {"Fuchsia", "#FF00FF"},
        {"Magenta", "#FF00FF"},
        {"DeepPink", "#FF1493"},
        {"OrangeRed", "#FF4500"},
        {"Tomato", "#FF6347"},
        {"HotPink", "#FF69B4"},
        {"Coral", "#FF7F50"},
        {"DarkOrange", "#FF8C00"},
        {"LightSalmon", "#FFA07A"},
        {"Orange", "#FFA500"},
        {"LightPink", "#FFB6C1"},
        {"Pink", "#FFC0CB"},
        {"Gold", "#FFD700"},
        {"PeachPuff", "#FFDAB9"},
        {"NavajoWhite", "#FFDEAD"},
        {"Moccasin", "#FFE4B5"},
        {"Bisque", "#FFE4C4"},
        {"MistyRose", "#FFE4E1"},
        {"BlanchedAlmond", "#FFEBCD"},
        {"PapayaWhip", "#FFEFD5"},
        {"LavenderBlush", "#FFF0F5"},
        {"SeaShell", "#FFF5EE"},
        {"Cornsilk", "#FFF8DC"},
        {"LemonChiffon", "#FFFACD"},
        {"FloralWhite", "#FFFAF0"},
        {"Snow", "#FFFAFA"},
        {"Yellow", "#FFFF00"},
        {"LightYellow", "#FFFFE0"},
        {"Ivory", "#FFFFF0"},
        {"White", "#FFFFFF"},


        {"Grey0", "#000000"},
        {"NavyBlue", "#00005F"},
        {"DarkBlue", "#000087"},
        {"Blue3", "#0000AF"},
        {"Blue3", "#0000D7"},
        {"Blue1", "#0000FF"},
        {"DarkGreen", "#005F00"},
        {"DeepSkyBlue4", "#005F5F"},
        {"DeepSkyBlue4", "#005F87"},
        {"DeepSkyBlue4", "#005FAF"},
        {"DodgerBlue3", "#005FD7"},
        {"DodgerBlue2", "#005FFF"},
        {"Green4", "#008700"},
        {"SpringGreen4", "#00875F"},
        {"Turquoise4", "#008787"},
        {"DeepSkyBlue3", "#0087AF"},
        {"DeepSkyBlue3", "#0087D7"},
        {"DodgerBlue1", "#0087FF"},
        {"Green3", "#00AF00"},
        {"SpringGreen3", "#00AF5F"},
        {"DarkCyan", "#00AF87"},
        {"LightSeaGreen", "#00AFAF"},
        {"DeepSkyBlue2", "#00AFD7"},
        {"DeepSkyBlue1", "#00AFFF"},
        {"Green3", "#00D700"},
        {"SpringGreen3", "#00D75F"},
        {"SpringGreen2", "#00D787"},
        {"Cyan3", "#00D7AF"},
        {"DarkTurquoise", "#00D7D7"},
        {"Turquoise2", "#00D7FF"},
        {"Green1", "#00FF00"},
        {"SpringGreen2", "#00FF5F"},
        {"SpringGreen1", "#00FF87"},
        {"MediumSpringGreen", "#00FFAF"},
        {"Cyan2", "#00FFD7"},
        {"Cyan1", "#00FFFF"},
        {"DarkRed", "#5F0000"},
        {"DeepPink4", "#5F005F"},
        {"Purple4", "#5F0087"},
        {"Purple4", "#5F00AF"},
        {"Purple3", "#5F00D7"},
        {"BlueViolet", "#5F00FF"},
        {"Orange4", "#5F5F00"},
        {"Grey37", "#5F5F5F"},
        {"MediumPurple4", "#5F5F87"},
        {"SlateBlue3", "#5F5FAF"},
        {"SlateBlue3", "#5F5FD7"},
        {"RoyalBlue1", "#5F5FFF"},
        {"Chartreuse4", "#5F8700"},
        {"DarkSeaGreen4", "#5F875F"},
        {"PaleTurquoise4", "#5F8787"},
        {"SteelBlue", "#5F87AF"},
        {"SteelBlue3", "#5F87D7"},
        {"CornflowerBlue", "#5F87FF"},
        {"Chartreuse3", "#5FAF00"},
        {"DarkSeaGreen4", "#5FAF5F"},
        {"CadetBlue", "#5FAF87"},
        {"CadetBlue", "#5FAFAF"},
        {"SkyBlue3", "#5FAFD7"},
        {"SteelBlue1", "#5FAFFF"},
        {"Chartreuse3", "#5FD700"},
        {"PaleGreen3", "#5FD75F"},
        {"SeaGreen3", "#5FD787"},
        {"Aquamarine3", "#5FD7AF"},
        {"MediumTurquoise", "#5FD7D7"},
        {"SteelBlue1", "#5FD7FF"},
        {"Chartreuse2", "#5FFF00"},
        {"SeaGreen2", "#5FFF5F"},
        {"SeaGreen1", "#5FFF87"},
        {"SeaGreen1", "#5FFFAF"},
        {"Aquamarine1", "#5FFFD7"},
        {"DarkSlateGray2", "#5FFFFF"},
        {"DarkRed", "#870000"},
        {"DeepPink4", "#87005F"},
        {"DarkMagenta", "#870087"},
        {"DarkMagenta", "#8700AF"},
        {"DarkViolet", "#8700D7"},
        {"Purple", "#8700FF"},
        {"Orange4", "#875F00"},
        {"LightPink4", "#875F5F"},
        {"Plum4", "#875F87"},
        {"MediumPurple3", "#875FAF"},
        {"MediumPurple3", "#875FD7"},
        {"SlateBlue1", "#875FFF"},
        {"Yellow4", "#878700"},
        {"Wheat4", "#87875F"},
        {"Grey53", "#878787"},
        {"LightSlateGrey", "#8787AF"},
        {"MediumPurple", "#8787D7"},
        {"LightSlateBlue", "#8787FF"},
        {"Yellow4", "#87AF00"},
        {"DarkOliveGreen3", "#87AF5F"},
        {"DarkSeaGreen", "#87AF87"},
        {"LightSkyBlue3", "#87AFAF"},
        {"LightSkyBlue3", "#87AFD7"},
        {"SkyBlue2", "#87AFFF"},
        {"Chartreuse2", "#87D700"},
        {"DarkOliveGreen3", "#87D75F"},
        {"PaleGreen3", "#87D787"},
        {"DarkSeaGreen3", "#87D7AF"},
        {"DarkSlateGray3", "#87D7D7"},
        {"SkyBlue1", "#87D7FF"},
        {"Chartreuse1", "#87FF00"},
        {"LightGreen", "#87FF5F"},
        {"LightGreen", "#87FF87"},
        {"PaleGreen1", "#87FFAF"},
        {"Aquamarine1", "#87FFD7"},
        {"DarkSlateGray1", "#87FFFF"},
        {"Red3", "#AF0000"},
        {"DeepPink4", "#AF005F"},
        {"MediumVioletRed", "#AF0087"},
        {"Magenta3", "#AF00AF"},
        {"DarkViolet", "#AF00D7"},
        {"Purple", "#AF00FF"},
        {"DarkOrange3", "#AF5F00"},
        {"IndianRed", "#AF5F5F"},
        {"HotPink3", "#AF5F87"},
        {"MediumOrchid3", "#AF5FAF"},
        {"MediumOrchid", "#AF5FD7"},
        {"MediumPurple2", "#AF5FFF"},
        {"DarkGoldenrod", "#AF8700"},
        {"LightSalmon3", "#AF875F"},
        {"RosyBrown", "#AF8787"},
        {"Grey63", "#AF87AF"},
        {"MediumPurple2", "#AF87D7"},
        {"MediumPurple1", "#AF87FF"},
        {"Gold3", "#AFAF00"},
        {"DarkKhaki", "#AFAF5F"},
        {"NavajoWhite3", "#AFAF87"},
        {"Grey69", "#AFAFAF"},
        {"LightSteelBlue3", "#AFAFD7"},
        {"LightSteelBlue", "#AFAFFF"},
        {"Yellow3", "#AFD700"},
        {"DarkOliveGreen3", "#AFD75F"},
        {"DarkSeaGreen3", "#AFD787"},
        {"DarkSeaGreen2", "#AFD7AF"},
        {"LightCyan3", "#AFD7D7"},
        {"LightSkyBlue1", "#AFD7FF"},
        {"GreenYellow", "#AFFF00"},
        {"DarkOliveGreen2", "#AFFF5F"},
        {"PaleGreen1", "#AFFF87"},
        {"DarkSeaGreen2", "#AFFFAF"},
        {"DarkSeaGreen1", "#AFFFD7"},
        {"PaleTurquoise1", "#AFFFFF"},
        {"Red3", "#D70000"},
        {"DeepPink3", "#D7005F"},
        {"DeepPink3", "#D70087"},
        {"Magenta3", "#D700AF"},
        {"Magenta3", "#D700D7"},
        {"Magenta2", "#D700FF"},
        {"DarkOrange3", "#D75F00"},
        {"IndianRed", "#D75F5F"},
        {"HotPink3", "#D75F87"},
        {"HotPink2", "#D75FAF"},
        {"Orchid", "#D75FD7"},
        {"MediumOrchid1", "#D75FFF"},
        {"Orange3", "#D78700"},
        {"LightSalmon3", "#D7875F"},
        {"LightPink3", "#D78787"},
        {"Pink3", "#D787AF"},
        {"Plum3", "#D787D7"},
        {"Violet", "#D787FF"},
        {"Gold3", "#D7AF00"},
        {"LightGoldenrod3", "#D7AF5F"},
        {"Tan", "#D7AF87"},
        {"MistyRose3", "#D7AFAF"},
        {"Thistle3", "#D7AFD7"},
        {"Plum2", "#D7AFFF"},
        {"Yellow3", "#D7D700"},
        {"Khaki3", "#D7D75F"},
        {"LightGoldenrod2", "#D7D787"},
        {"LightYellow3", "#D7D7AF"},
        {"Grey84", "#D7D7D7"},
        {"LightSteelBlue1", "#D7D7FF"},
        {"Yellow2", "#D7FF00"},
        {"DarkOliveGreen1", "#D7FF5F"},
        {"DarkOliveGreen1", "#D7FF87"},
        {"DarkSeaGreen1", "#D7FFAF"},
        {"Honeydew2", "#D7FFD7"},
        {"LightCyan1", "#D7FFFF"},
        {"Red1", "#FF0000"},
        {"DeepPink2", "#FF005F"},
        {"DeepPink1", "#FF0087"},
        {"DeepPink1", "#FF00AF"},
        {"Magenta2", "#FF00D7"},
        {"Magenta1", "#FF00FF"},
        {"OrangeRed1", "#FF5F00"},
        {"IndianRed1", "#FF5F5F"},
        {"IndianRed1", "#FF5F87"},
        {"HotPink", "#FF5FAF"},
        {"HotPink", "#FF5FD7"},
        {"MediumOrchid1", "#FF5FFF"},
        {"DarkOrange", "#FF8700"},
        {"Salmon1", "#FF875F"},
        {"LightCoral", "#FF8787"},
        {"PaleVioletRed1", "#FF87AF"},
        {"Orchid2", "#FF87D7"},
        {"Orchid1", "#FF87FF"},
        {"Orange1", "#FFAF00"},
        {"SandyBrown", "#FFAF5F"},
        {"LightSalmon1", "#FFAF87"},
        {"LightPink1", "#FFAFAF"},
        {"Pink1", "#FFAFD7"},
        {"Plum1", "#FFAFFF"},
        {"Gold1", "#FFD700"},
        {"LightGoldenrod2", "#FFD75F"},
        {"LightGoldenrod2", "#FFD787"},
        {"NavajoWhite1", "#FFD7AF"},
        {"MistyRose1", "#FFD7D7"},
        {"Thistle1", "#FFD7FF"},
        {"Yellow1", "#FFFF00"},
        {"LightGoldenrod1", "#FFFF5F"},
        {"Khaki1", "#FFFF87"},
        {"Wheat1", "#FFFFAF"},
        {"Cornsilk1", "#FFFFD7"},
        {"Grey100", "#FFFFFF"},
        {"Grey3", "#080808"},
        {"Grey7", "#121212"},
        {"Grey11", "#1C1C1C"},
        {"Grey15", "#262626"},
        {"Grey19", "#303030"},
        {"Grey23", "#3A3A3A"},
        {"Grey27", "#444444"},
        {"Grey30", "#4E4E4E"},
        {"Grey35", "#585858"},
        {"Grey39", "#626262"},
        {"Grey42", "#6C6C6C"},
        {"Grey46", "#767676"},
        {"Grey50", "#808080"},
        {"Grey54", "#8A8A8A"},
        {"Grey58", "#949494"},
        {"Grey62", "#9E9E9E"},
        {"Grey66", "#A8A8A8"},
        {"Grey70", "#B2B2B2"},
        {"Grey74", "#BCBCBC"},
        {"Grey78", "#C6C6C6"},
        {"Grey82", "#D0D0D0"},
        {"Grey85", "#DADADA"},
        {"Grey89", "#E4E4E4"},
        {"Grey93", "#EEEEEE"},


        {"snow", "#FFFAFA"},
        {"ghost white", "#F8F8FF"},
        {"GhostWhite", "#F8F8FF"},
        {"white smoke", "#F5F5F5"},
        {"WhiteSmoke", "#F5F5F5"},
        {"gainsboro", "#DCDCDC"},
        {"floral white", "#FFFAF0"},
        {"FloralWhite", "#FFFAF0"},
        {"old lace", "#FDF5E6"},
        {"OldLace", "#FDF5E6"},
        {"linen", "#FAF0E6"},
        {"antique white", "#FAEBD7"},
        {"AntiqueWhite", "#FAEBD7"},
        {"papaya whip", "#FFEFD5"},
        {"PapayaWhip", "#FFEFD5"},
        {"blanched almond", "#FFEBCD"},
        {"BlanchedAlmond", "#FFEBCD"},
        {"bisque", "#FFE4C4"},
        {"peach puff", "#FFDAB9"},
        {"PeachPuff", "#FFDAB9"},
        {"navajo white", "#FFDEAD"},
        {"NavajoWhite", "#FFDEAD"},
        {"moccasin", "#FFE4B5"},
        {"cornsilk", "#FFF8DC"},
        {"ivory", "#FFFFF0"},
        {"lemon chiffon", "#FFFACD"},
        {"LemonChiffon", "#FFFACD"},
        {"seashell", "#FFF5EE"},
        {"honeydew", "#F0FFF0"},
        {"mint cream", "#F5FFFA"},
        {"MintCream", "#F5FFFA"},
        {"azure", "#F0FFFF"},
        {"alice blue", "#F0F8FF"},
        {"AliceBlue", "#F0F8FF"},
        {"lavender", "#E6E6FA"},
        {"lavender blush", "#FFF0F5"},
        {"LavenderBlush", "#FFF0F5"},
        {"misty rose", "#FFE4E1"},
        {"MistyRose", "#FFE4E1"},
        {"white", "#FFFFFF"},
        {"black", "#000000"},
        {"dark slate gray", "#004F4F"},
        {"DarkSlateGray", "#004F4F"},
        {"dark slate grey", "#004F4F"},
        {"DarkSlateGrey", "#004F4F"},
        {"dim gray", "#696969"},
        {"DimGray", "#696969"},
        {"dim grey", "#696969"},
        {"DimGrey", "#696969"},
        {"slate gray", "#708090"},
        {"SlateGray", "#708090"},
        {"slate grey", "#708090"},
        {"SlateGrey", "#708090"},
        {"light slate gray", "#778899"},
        {"LightSlateGray", "#778899"},
        {"light slate grey", "#778899"},
        {"LightSlateGrey", "#778899"},
        {"gray", "#BEBEBE"},
        {"grey", "#BEBEBE"},
        {"light grey", "#D3D3D3"},
        {"LightGrey", "#D3D3D3"},
        {"light gray", "#D3D3D3"},
        {"LightGray", "#D3D3D3"},
        {"midnight blue", "#001970"},
        {"MidnightBlue", "#001970"},
        {"navy", "#000080"},
        {"navy blue", "#000080"},
        {"NavyBlue", "#000080"},
        {"cornflower blue", "#6495ED"},
        {"CornflowerBlue", "#6495ED"},
        {"dark slate blue", "#003D8B"},
        {"DarkSlateBlue", "#003D8B"},
        {"slate blue", "#6A5ACD"},
        {"SlateBlue", "#6A5ACD"},
        {"medium slate blue", "#7B68EE"},
        {"MediumSlateBlue", "#7B68EE"},
        {"light slate blue", "#8470FF"},
        {"LightSlateBlue", "#8470FF"},
        {"medium blue", "#0000CD"},
        {"MediumBlue", "#0000CD"},
        {"royal blue", "#0069E1"},
        {"RoyalBlue", "#0069E1"},
        {"blue", "#0000FF"},
        {"dodger blue", "#0090FF"},
        {"DodgerBlue", "#0090FF"},
        {"deep sky blue", "#00BFFF"},
        {"DeepSkyBlue", "#00BFFF"},
        {"sky blue", "#87CEEB"},
        {"SkyBlue", "#87CEEB"},
        {"light sky blue", "#87CEFA"},
        {"LightSkyBlue", "#87CEFA"},
        {"steel blue", "#0082B4"},
        {"SteelBlue", "#0082B4"},
        {"light steel blue", "#B0C4DE"},
        {"LightSteelBlue", "#B0C4DE"},
        {"light blue", "#ADD8E6"},
        {"LightBlue", "#ADD8E6"},
        {"powder blue", "#B0E0E6"},
        {"PowderBlue", "#B0E0E6"},
        {"pale turquoise", "#AFEEEE"},
        {"PaleTurquoise", "#AFEEEE"},
        {"dark turquoise", "#00CED1"},
        {"DarkTurquoise", "#00CED1"},
        {"medium turquoise", "#00D1CC"},
        {"MediumTurquoise", "#00D1CC"},
        {"turquoise", "#00E0D0"},
        {"cyan", "#00FFFF"},
        {"light cyan", "#E0FFFF"},
        {"LightCyan", "#E0FFFF"},
        {"cadet blue", "#009EA0"},
        {"CadetBlue", "#009EA0"},
        {"medium aquamarine", "#66CDAA"},
        {"MediumAquamarine", "#66CDAA"},
        {"aquamarine", "#7FFFD4"},
        {"dark green", "#006400"},
        {"DarkGreen", "#006400"},
        {"dark olive green", "#006B2F"},
        {"DarkOliveGreen", "#006B2F"},
        {"dark sea green", "#8FBC8F"},
        {"DarkSeaGreen", "#8FBC8F"},
        {"sea green", "#008B57"},
        {"SeaGreen", "#008B57"},
        {"medium sea green", "#00B371"},
        {"MediumSeaGreen", "#00B371"},
        {"light sea green", "#00B2AA"},
        {"LightSeaGreen", "#00B2AA"},
        {"pale green", "#98FB98"},
        {"PaleGreen", "#98FB98"},
        {"spring green", "#00FF7F"},
        {"SpringGreen", "#00FF7F"},
        {"lawn green", "#7CFC00"},
        {"LawnGreen", "#7CFC00"},
        {"green", "#00FF00"},
        {"chartreuse", "#7FFF00"},
        {"medium spring green", "#00FA9A"},
        {"MediumSpringGreen", "#00FA9A"},
        {"green yellow", "#ADFF2F"},
        {"GreenYellow", "#ADFF2F"},
        {"lime green", "#00CD32"},
        {"LimeGreen", "#00CD32"},
        {"yellow green", "#9ACD32"},
        {"YellowGreen", "#9ACD32"},
        {"forest green", "#008B22"},
        {"ForestGreen", "#008B22"},
        {"olive drab", "#6B8E23"},
        {"OliveDrab", "#6B8E23"},
        {"dark khaki", "#BDB76B"},
        {"DarkKhaki", "#BDB76B"},
        {"khaki", "#F0E68C"},
        {"pale goldenrod", "#EEE8AA"},
        {"PaleGoldenrod", "#EEE8AA"},
        {"light goldenrod yellow", "#FAFAD2"},
        {"LightGoldenrodYellow", "#FAFAD2"},
        {"light yellow", "#FFFFE0"},
        {"LightYellow", "#FFFFE0"},
        {"yellow", "#FFFF00"},
        {"gold", "#FFD700"},
        {"light goldenrod", "#EEDD82"},
        {"LightGoldenrod", "#EEDD82"},
        {"goldenrod", "#DAA520"},
        {"dark goldenrod", "#B8860B"},
        {"DarkGoldenrod", "#B8860B"},
        {"rosy brown", "#BC8F8F"},
        {"RosyBrown", "#BC8F8F"},
        {"indian red", "#CD5C5C"},
        {"IndianRed", "#CD5C5C"},
        {"saddle brown", "#8B4513"},
        {"SaddleBrown", "#8B4513"},
        {"sienna", "#A0522D"},
        {"peru", "#CD853F"},
        {"burlywood", "#DEB887"},
        {"beige", "#F5F5DC"},
        {"wheat", "#F5DEB3"},
        {"sandy brown", "#F4A460"},
        {"SandyBrown", "#F4A460"},
        {"tan", "#D2B48C"},
        {"chocolate", "#D2691E"},
        {"firebrick", "#B22222"},
        {"brown", "#A52A2A"},
        {"dark salmon", "#E9967A"},
        {"DarkSalmon", "#E9967A"},
        {"salmon", "#FA8072"},
        {"light salmon", "#FFA07A"},
        {"LightSalmon", "#FFA07A"},
        {"orange", "#FFA500"},
        {"dark orange", "#FF8C00"},
        {"DarkOrange", "#FF8C00"},
        {"coral", "#FF7F50"},
        {"light coral", "#F08080"},
        {"LightCoral", "#F08080"},
        {"tomato", "#FF6347"},
        {"orange red", "#FF4500"},
        {"OrangeRed", "#FF4500"},
        {"red", "#FF0000"},
        {"hot pink", "#FF69B4"},
        {"HotPink", "#FF69B4"},
        {"deep pink", "#FF1493"},
        {"DeepPink", "#FF1493"},
        {"pink", "#FFC0CB"},
        {"light pink", "#FFB6C1"},
        {"LightPink", "#FFB6C1"},
        {"pale violet red", "#DB7093"},
        {"PaleVioletRed", "#DB7093"},
        {"maroon", "#B03060"},
        {"medium violet red", "#C71585"},
        {"MediumVioletRed", "#C71585"},
        {"violet red", "#D02090"},
        {"VioletRed", "#D02090"},
        {"magenta", "#FF00FF"},
        {"violet", "#EE82EE"},
        {"plum", "#DDA0DD"},
        {"orchid", "#DA70D6"},
        {"medium orchid", "#BA55D3"},
        {"MediumOrchid", "#BA55D3"},
        {"dark orchid", "#9932CC"},
        {"DarkOrchid", "#9932CC"},
        {"dark violet", "#9400D3"},
        {"DarkViolet", "#9400D3"},
        {"blue violet", "#8A2BE2"},
        {"BlueViolet", "#8A2BE2"},
        {"purple", "#A020F0"},
        {"medium purple", "#9370DB"},
        {"MediumPurple", "#9370DB"},
        {"thistle", "#D8BFD8"},
        {"snow1", "#FFFAFA"},
        {"snow2", "#EEE9E9"},
        {"snow3", "#CDC9C9"},
        {"snow4", "#8B8989"},
        {"seashell1", "#FFF5EE"},
        {"seashell2", "#EEE5DE"},
        {"seashell3", "#CDC5BF"},
        {"seashell4", "#8B8682"},
        {"AntiqueWhite1", "#FFEFDB"},
        {"AntiqueWhite2", "#EEDFCC"},
        {"AntiqueWhite3", "#CDC0B0"},
        {"AntiqueWhite4", "#8B8378"},
        {"bisque1", "#FFE4C4"},
        {"bisque2", "#EED5B7"},
        {"bisque3", "#CDB79E"},
        {"bisque4", "#8B7D6B"},
        {"PeachPuff1", "#FFDAB9"},
        {"PeachPuff2", "#EECBAD"},
        {"PeachPuff3", "#CDAF95"},
        {"PeachPuff4", "#8B7765"},
        {"NavajoWhite1", "#FFDEAD"},
        {"NavajoWhite2", "#EECFA1"},
        {"NavajoWhite3", "#CDB38B"},
        {"NavajoWhite4", "#8B795E"},
        {"LemonChiffon1", "#FFFACD"},
        {"LemonChiffon2", "#EEE9BF"},
        {"LemonChiffon3", "#CDC9A5"},
        {"LemonChiffon4", "#8B8970"},
        {"cornsilk1", "#FFF8DC"},
        {"cornsilk2", "#EEE8CD"},
        {"cornsilk3", "#CDC8B1"},
        {"cornsilk4", "#8B8878"},
        {"ivory1", "#FFFFF0"},
        {"ivory2", "#EEEEE0"},
        {"ivory3", "#CDCDC1"},
        {"ivory4", "#8B8B83"},
        {"honeydew1", "#F0FFF0"},
        {"honeydew2", "#E0EEE0"},
        {"honeydew3", "#C1CDC1"},
        {"honeydew4", "#838B83"},
        {"LavenderBlush1", "#FFF0F5"},
        {"LavenderBlush2", "#EEE0E5"},
        {"LavenderBlush3", "#CDC1C5"},
        {"LavenderBlush4", "#8B8386"},
        {"MistyRose1", "#FFE4E1"},
        {"MistyRose2", "#EED5D2"},
        {"MistyRose3", "#CDB7B5"},
        {"MistyRose4", "#8B7D7B"},
        {"azure1", "#F0FFFF"},
        {"azure2", "#E0EEEE"},
        {"azure3", "#C1CDCD"},
        {"azure4", "#838B8B"},
        {"SlateBlue1", "#836FFF"},
        {"SlateBlue2", "#7A67EE"},
        {"SlateBlue3", "#6959CD"},
        {"SlateBlue4", "#003C8B"},
        {"RoyalBlue1", "#0076FF"},
        {"RoyalBlue2", "#006EEE"},
        {"RoyalBlue3", "#005FCD"},
        {"RoyalBlue4", "#00408B"},
        {"blue1", "#0000FF"},
        {"blue2", "#0000EE"},
        {"blue3", "#0000CD"},
        {"blue4", "#00008B"},
        {"DodgerBlue1", "#0090FF"},
        {"DodgerBlue2", "#0086EE"},
        {"DodgerBlue3", "#0074CD"},
        {"DodgerBlue4", "#004E8B"},
        {"SteelBlue1", "#00B8FF"},
        {"SteelBlue2", "#00ACEE"},
        {"SteelBlue3", "#0094CD"},
        {"SteelBlue4", "#00648B"},
        {"DeepSkyBlue1", "#00BFFF"},
        {"DeepSkyBlue2", "#00B2EE"},
        {"DeepSkyBlue3", "#009ACD"},
        {"DeepSkyBlue4", "#00688B"},
        {"SkyBlue1", "#87CEFF"},
        {"SkyBlue2", "#7EC0EE"},
        {"SkyBlue3", "#6CA6CD"},
        {"SkyBlue4", "#00708B"},
        {"LightSkyBlue1", "#B0E2FF"},
        {"LightSkyBlue2", "#A4D3EE"},
        {"LightSkyBlue3", "#8DB6CD"},
        {"LightSkyBlue4", "#007B8B"},
        {"SlateGray1", "#C6E2FF"},
        {"SlateGray2", "#B9D3EE"},
        {"SlateGray3", "#9FB6CD"},
        {"SlateGray4", "#6C7B8B"},
        {"LightSteelBlue1", "#CAE1FF"},
        {"LightSteelBlue2", "#BCD2EE"},
        {"LightSteelBlue3", "#A2B5CD"},
        {"LightSteelBlue4", "#6E7B8B"},
        {"LightBlue1", "#BFEFFF"},
        {"LightBlue2", "#B2DFEE"},
        {"LightBlue3", "#9AC0CD"},
        {"LightBlue4", "#68838B"},
        {"LightCyan1", "#E0FFFF"},
        {"LightCyan2", "#D1EEEE"},
        {"LightCyan3", "#B4CDCD"},
        {"LightCyan4", "#7A8B8B"},
        {"PaleTurquoise1", "#BBFFFF"},
        {"PaleTurquoise2", "#AEEEEE"},
        {"PaleTurquoise3", "#96CDCD"},
        {"PaleTurquoise4", "#668B8B"},
        {"CadetBlue1", "#98F5FF"},
        {"CadetBlue2", "#8EE5EE"},
        {"CadetBlue3", "#7AC5CD"},
        {"CadetBlue4", "#00868B"},
        {"turquoise1", "#00F5FF"},
        {"turquoise2", "#00E5EE"},
        {"turquoise3", "#00C5CD"},
        {"turquoise4", "#00868B"},
        {"cyan1", "#00FFFF"},
        {"cyan2", "#00EEEE"},
        {"cyan3", "#00CDCD"},
        {"cyan4", "#008B8B"},
        {"DarkSlateGray1", "#97FFFF"},
        {"DarkSlateGray2", "#8DEEEE"},
        {"DarkSlateGray3", "#79CDCD"},
        {"DarkSlateGray4", "#008B8B"},
        {"aquamarine1", "#7FFFD4"},
        {"aquamarine2", "#76EEC6"},
        {"aquamarine3", "#66CDAA"},
        {"aquamarine4", "#008B74"},
        {"DarkSeaGreen1", "#C1FFC1"},
        {"DarkSeaGreen2", "#B4EEB4"},
        {"DarkSeaGreen3", "#9BCD9B"},
        {"DarkSeaGreen4", "#698B69"},
        {"SeaGreen1", "#00FF9F"},
        {"SeaGreen2", "#00EE94"},
        {"SeaGreen3", "#00CD80"},
        {"SeaGreen4", "#008B57"},
        {"PaleGreen1", "#9AFF9A"},
        {"PaleGreen2", "#90EE90"},
        {"PaleGreen3", "#7CCD7C"},
        {"PaleGreen4", "#008B54"},
        {"SpringGreen1", "#00FF7F"},
        {"SpringGreen2", "#00EE76"},
        {"SpringGreen3", "#00CD66"},
        {"SpringGreen4", "#008B45"},
        {"green1", "#00FF00"},
        {"green2", "#00EE00"},
        {"green3", "#00CD00"},
        {"green4", "#008B00"},
        {"chartreuse1", "#7FFF00"},
        {"chartreuse2", "#76EE00"},
        {"chartreuse3", "#66CD00"},
        {"chartreuse4", "#008B00"},
        {"OliveDrab1", "#C0FF3E"},
        {"OliveDrab2", "#B3EE3A"},
        {"OliveDrab3", "#9ACD32"},
        {"OliveDrab4", "#698B22"},
        {"DarkOliveGreen1", "#CAFF70"},
        {"DarkOliveGreen2", "#BCEE68"},
        {"DarkOliveGreen3", "#A2CD5A"},
        {"DarkOliveGreen4", "#6E8B3D"},
        {"khaki1", "#FFF68F"},
        {"khaki2", "#EEE685"},
        {"khaki3", "#CDC673"},
        {"khaki4", "#8B864E"},
        {"LightGoldenrod1", "#FFEC8B"},
        {"LightGoldenrod2", "#EEDC82"},
        {"LightGoldenrod3", "#CDBE70"},
        {"LightGoldenrod4", "#8B814C"},
        {"LightYellow1", "#FFFFE0"},
        {"LightYellow2", "#EEEED1"},
        {"LightYellow3", "#CDCDB4"},
        {"LightYellow4", "#8B8B7A"},
        {"yellow1", "#FFFF00"},
        {"yellow2", "#EEEE00"},
        {"yellow3", "#CDCD00"},
        {"yellow4", "#8B8B00"},
        {"gold1", "#FFD700"},
        {"gold2", "#EEC900"},
        {"gold3", "#CDAD00"},
        {"gold4", "#8B7500"},
        {"goldenrod1", "#FFC125"},
        {"goldenrod2", "#EEB422"},
        {"goldenrod3", "#CD9B1D"},
        {"goldenrod4", "#8B6914"},
        {"DarkGoldenrod1", "#FFB90F"},
        {"DarkGoldenrod2", "#EEAD0E"},
        {"DarkGoldenrod3", "#CD950C"},
        {"DarkGoldenrod4", "#8B6508"},
        {"RosyBrown1", "#FFC1C1"},
        {"RosyBrown2", "#EEB4B4"},
        {"RosyBrown3", "#CD9B9B"},
        {"RosyBrown4", "#8B6969"},
        {"IndianRed1", "#FF6A6A"},
        {"IndianRed2", "#EE6363"},
        {"IndianRed3", "#CD5555"},
        {"IndianRed4", "#8B3A3A"},
        {"sienna1", "#FF8247"},
        {"sienna2", "#EE7942"},
        {"sienna3", "#CD6839"},
        {"sienna4", "#8B4726"},
        {"burlywood1", "#FFD39B"},
        {"burlywood2", "#EEC591"},
        {"burlywood3", "#CDAA7D"},
        {"burlywood4", "#8B7355"},
        {"wheat1", "#FFE7BA"},
        {"wheat2", "#EED8AE"},
        {"wheat3", "#CDBA96"},
        {"wheat4", "#8B7E66"},
        {"tan1", "#FFA54F"},
        {"tan2", "#EE9A49"},
        {"tan3", "#CD853F"},
        {"tan4", "#8B5A2B"},
        {"chocolate1", "#FF7F24"},
        {"chocolate2", "#EE7621"},
        {"chocolate3", "#CD661D"},
        {"chocolate4", "#8B4513"},
        {"firebrick1", "#FF3030"},
        {"firebrick2", "#EE2C2C"},
        {"firebrick3", "#CD2626"},
        {"firebrick4", "#8B1A1A"},
        {"brown1", "#FF4040"},
        {"brown2", "#EE3B3B"},
        {"brown3", "#CD3333"},
        {"brown4", "#8B2323"},
        {"salmon1", "#FF8C69"},
        {"salmon2", "#EE8262"},
        {"salmon3", "#CD7054"},
        {"salmon4", "#8B4C39"},
        {"LightSalmon1", "#FFA07A"},
        {"LightSalmon2", "#EE9572"},
        {"LightSalmon3", "#CD8162"},
        {"LightSalmon4", "#8B5742"},
        {"orange1", "#FFA500"},
        {"orange2", "#EE9A00"},
        {"orange3", "#CD8500"},
        {"orange4", "#8B5A00"},
        {"DarkOrange1", "#FF7F00"},
        {"DarkOrange2", "#EE7600"},
        {"DarkOrange3", "#CD6600"},
        {"DarkOrange4", "#8B4500"},
        {"coral1", "#FF7256"},
        {"coral2", "#EE6A50"},
        {"coral3", "#CD5B45"},
        {"coral4", "#8B3E2F"},
        {"tomato1", "#FF6347"},
        {"tomato2", "#EE5C42"},
        {"tomato3", "#CD4F39"},
        {"tomato4", "#8B3626"},
        {"OrangeRed1", "#FF4500"},
        {"OrangeRed2", "#EE4000"},
        {"OrangeRed3", "#CD3700"},
        {"OrangeRed4", "#8B2500"},
        {"red1", "#FF0000"},
        {"red2", "#EE0000"},
        {"red3", "#CD0000"},
        {"red4", "#8B0000"},
        {"DeepPink1", "#FF1493"},
        {"DeepPink2", "#EE1289"},
        {"DeepPink3", "#CD1076"},
        {"DeepPink4", "#8B0A50"},
        {"HotPink1", "#FF6EB4"},
        {"HotPink2", "#EE6AA7"},
        {"HotPink3", "#CD6090"},
        {"HotPink4", "#8B3A62"},
        {"pink1", "#FFB5C5"},
        {"pink2", "#EEA9B8"},
        {"pink3", "#CD919E"},
        {"pink4", "#8B636C"},
        {"LightPink1", "#FFAEB9"},
        {"LightPink2", "#EEA2AD"},
        {"LightPink3", "#CD8C95"},
        {"LightPink4", "#8B5F65"},
        {"PaleVioletRed1", "#FF82AB"},
        {"PaleVioletRed2", "#EE799F"},
        {"PaleVioletRed3", "#CD6889"},
        {"PaleVioletRed4", "#8B475D"},
        {"maroon1", "#FF34B3"},
        {"maroon2", "#EE30A7"},
        {"maroon3", "#CD2990"},
        {"maroon4", "#8B1C62"},
        {"VioletRed1", "#FF3E96"},
        {"VioletRed2", "#EE3A8C"},
        {"VioletRed3", "#CD3278"},
        {"VioletRed4", "#8B2252"},
        {"magenta1", "#FF00FF"},
        {"magenta2", "#EE00EE"},
        {"magenta3", "#CD00CD"},
        {"magenta4", "#8B008B"},
        {"orchid1", "#FF83FA"},
        {"orchid2", "#EE7AE9"},
        {"orchid3", "#CD69C9"},
        {"orchid4", "#8B4789"},
        {"plum1", "#FFBBFF"},
        {"plum2", "#EEAEEE"},
        {"plum3", "#CD96CD"},
        {"plum4", "#8B668B"},
        {"MediumOrchid1", "#E066FF"},
        {"MediumOrchid2", "#D15FEE"},
        {"MediumOrchid3", "#B452CD"},
        {"MediumOrchid4", "#7A378B"},
        {"DarkOrchid1", "#BF3EFF"},
        {"DarkOrchid2", "#B23AEE"},
        {"DarkOrchid3", "#9A32CD"},
        {"DarkOrchid4", "#68228B"},
        {"purple1", "#9B30FF"},
        {"purple2", "#912CEE"},
        {"purple3", "#7D26CD"},
        {"purple4", "#001A8B"},
        {"MediumPurple1", "#AB82FF"},
        {"MediumPurple2", "#9F79EE"},
        {"MediumPurple3", "#8968CD"},
        {"MediumPurple4", "#00478B"},
        {"thistle1", "#FFE1FF"},
        {"thistle2", "#EED2EE"},
        {"thistle3", "#CDB5CD"},
        {"thistle4", "#8B7B8B"},
        {"gray0", "#000000"},
        {"grey0", "#000000"},
        {"gray1", "#000303"},
        {"grey1", "#000303"},
        {"gray2", "#000505"},
        {"grey2", "#000505"},
        {"gray3", "#000808"},
        {"grey3", "#000808"},
        {"gray4", "#000A0A"},
        {"grey4", "#000A0A"},
        {"gray5", "#000D0D"},
        {"grey5", "#000D0D"},
        {"gray6", "#000F0F"},
        {"grey6", "#000F0F"},
        {"gray7", "#001212"},
        {"grey7", "#001212"},
        {"gray8", "#001414"},
        {"grey8", "#001414"},
        {"gray9", "#001717"},
        {"grey9", "#001717"},
        {"gray10", "#001A1A"},
        {"grey10", "#001A1A"},
        {"gray11", "#001C1C"},
        {"grey11", "#001C1C"},
        {"gray12", "#001F1F"},
        {"grey12", "#001F1F"},
        {"gray13", "#002121"},
        {"grey13", "#002121"},
        {"gray14", "#002424"},
        {"grey14", "#002424"},
        {"gray15", "#002626"},
        {"grey15", "#002626"},
        {"gray16", "#002929"},
        {"grey16", "#002929"},
        {"gray17", "#002B2B"},
        {"grey17", "#002B2B"},
        {"gray18", "#002E2E"},
        {"grey18", "#002E2E"},
        {"gray19", "#003030"},
        {"grey19", "#003030"},
        {"gray20", "#003333"},
        {"grey20", "#003333"},
        {"gray21", "#003636"},
        {"grey21", "#003636"},
        {"gray22", "#003838"},
        {"grey22", "#003838"},
        {"gray23", "#003B3B"},
        {"grey23", "#003B3B"},
        {"gray24", "#003D3D"},
        {"grey24", "#003D3D"},
        {"gray25", "#004040"},
        {"grey25", "#004040"},
        {"gray26", "#004242"},
        {"grey26", "#004242"},
        {"gray27", "#004545"},
        {"grey27", "#004545"},
        {"gray28", "#004747"},
        {"grey28", "#004747"},
        {"gray29", "#004A4A"},
        {"grey29", "#004A4A"},
        {"gray30", "#004D4D"},
        {"grey30", "#004D4D"},
        {"gray31", "#004F4F"},
        {"grey31", "#004F4F"},
        {"gray32", "#005252"},
        {"grey32", "#005252"},
        {"gray33", "#005454"},
        {"grey33", "#005454"},
        {"gray34", "#005757"},
        {"grey34", "#005757"},
        {"gray35", "#005959"},
        {"grey35", "#005959"},
        {"gray36", "#005C5C"},
        {"grey36", "#005C5C"},
        {"gray37", "#005E5E"},
        {"grey37", "#005E5E"},
        {"gray38", "#006161"},
        {"grey38", "#006161"},
        {"gray39", "#006363"},
        {"grey39", "#006363"},
        {"gray40", "#666666"},
        {"grey40", "#666666"},
        {"gray41", "#696969"},
        {"grey41", "#696969"},
        {"gray42", "#6B6B6B"},
        {"grey42", "#6B6B6B"},
        {"gray43", "#6E6E6E"},
        {"grey43", "#6E6E6E"},
        {"gray44", "#707070"},
        {"grey44", "#707070"},
        {"gray45", "#737373"},
        {"grey45", "#737373"},
        {"gray46", "#757575"},
        {"grey46", "#757575"},
        {"gray47", "#787878"},
        {"grey47", "#787878"},
        {"gray48", "#7A7A7A"},
        {"grey48", "#7A7A7A"},
        {"gray49", "#7D7D7D"},
        {"grey49", "#7D7D7D"},
        {"gray50", "#7F7F7F"},
        {"grey50", "#7F7F7F"},
        {"gray51", "#828282"},
        {"grey51", "#828282"},
        {"gray52", "#858585"},
        {"grey52", "#858585"},
        {"gray53", "#878787"},
        {"grey53", "#878787"},
        {"gray54", "#8A8A8A"},
        {"grey54", "#8A8A8A"},
        {"gray55", "#8C8C8C"},
        {"grey55", "#8C8C8C"},
        {"gray56", "#8F8F8F"},
        {"grey56", "#8F8F8F"},
        {"gray57", "#919191"},
        {"grey57", "#919191"},
        {"gray58", "#949494"},
        {"grey58", "#949494"},
        {"gray59", "#969696"},
        {"grey59", "#969696"},
        {"gray60", "#999999"},
        {"grey60", "#999999"},
        {"gray61", "#9C9C9C"},
        {"grey61", "#9C9C9C"},
        {"gray62", "#9E9E9E"},
        {"grey62", "#9E9E9E"},
        {"gray63", "#A1A1A1"},
        {"grey63", "#A1A1A1"},
        {"gray64", "#A3A3A3"},
        {"grey64", "#A3A3A3"},
        {"gray65", "#A6A6A6"},
        {"grey65", "#A6A6A6"},
        {"gray66", "#A8A8A8"},
        {"grey66", "#A8A8A8"},
        {"gray67", "#ABABAB"},
        {"grey67", "#ABABAB"},
        {"gray68", "#ADADAD"},
        {"grey68", "#ADADAD"},
        {"gray69", "#B0B0B0"},
        {"grey69", "#B0B0B0"},
        {"gray70", "#B3B3B3"},
        {"grey70", "#B3B3B3"},
        {"gray71", "#B5B5B5"},
        {"grey71", "#B5B5B5"},
        {"gray72", "#B8B8B8"},
        {"grey72", "#B8B8B8"},
        {"gray73", "#BABABA"},
        {"grey73", "#BABABA"},
        {"gray74", "#BDBDBD"},
        {"grey74", "#BDBDBD"},
        {"gray75", "#BFBFBF"},
        {"grey75", "#BFBFBF"},
        {"gray76", "#C2C2C2"},
        {"grey76", "#C2C2C2"},
        {"gray77", "#C4C4C4"},
        {"grey77", "#C4C4C4"},
        {"gray78", "#C7C7C7"},
        {"grey78", "#C7C7C7"},
        {"gray79", "#C9C9C9"},
        {"grey79", "#C9C9C9"},
        {"gray80", "#CCCCCC"},
        {"grey80", "#CCCCCC"},
        {"gray81", "#CFCFCF"},
        {"grey81", "#CFCFCF"},
        {"gray82", "#D1D1D1"},
        {"grey82", "#D1D1D1"},
        {"gray83", "#D4D4D4"},
        {"grey83", "#D4D4D4"},
        {"gray84", "#D6D6D6"},
        {"grey84", "#D6D6D6"},
        {"gray85", "#D9D9D9"},
        {"grey85", "#D9D9D9"},
        {"gray86", "#DBDBDB"},
        {"grey86", "#DBDBDB"},
        {"gray87", "#DEDEDE"},
        {"grey87", "#DEDEDE"},
        {"gray88", "#E0E0E0"},
        {"grey88", "#E0E0E0"},
        {"gray89", "#E3E3E3"},
        {"grey89", "#E3E3E3"},
        {"gray90", "#E5E5E5"},
        {"grey90", "#E5E5E5"},
        {"gray91", "#E8E8E8"},
        {"grey91", "#E8E8E8"},
        {"gray92", "#EBEBEB"},
        {"grey92", "#EBEBEB"},
        {"gray93", "#EDEDED"},
        {"grey93", "#EDEDED"},
        {"gray94", "#F0F0F0"},
        {"grey94", "#F0F0F0"},
        {"gray95", "#F2F2F2"},
        {"grey95", "#F2F2F2"},
        {"gray96", "#F5F5F5"},
        {"grey96", "#F5F5F5"},
        {"gray97", "#F7F7F7"},
        {"grey97", "#F7F7F7"},
        {"gray98", "#FAFAFA"},
        {"grey98", "#FAFAFA"},
        {"gray99", "#FCFCFC"},
        {"grey99", "#FCFCFC"},
        {"gray100", "#FFFFFF"},
        {"grey100", "#FFFFFF"},
        {"dark grey", "#A9A9A9"},
        {"DarkGrey", "#A9A9A9"},
        {"dark gray", "#A9A9A9"},
        {"DarkGray", "#A9A9A9"},
        {"dark blue", "#00008B"},
        {"DarkBlue", "#00008B"},
        {"dark cyan", "#008B8B"},
        {"DarkCyan", "#008B8B"},
        {"dark magenta", "#8B008B"},
        {"DarkMagenta", "#8B008B"},
        {"dark red", "#8B0000"},
        {"DarkRed", "#8B0000"},
        {"light green", "#90EE90"},
        {"LightGreen", "#90EE90"},
    };

    /* add a few builtin names and try again */
    if (name[0] != '#'){
        for (int i = 0; ; ++i)
        {
            if (vimnames[i][0] == NULL)
            {
                name = NULL;
                break;
            }
            if (STRICMP(name, vimnames[i][0]) == 0)
            {
                name = (char_u *)vimnames[i][1];
                break;
            }
        }
    }

    if(vimjs_is_valid_color((char*)name)){
        return (guicolor_T)vimjs_get_rgb((char*)name);
    }


    return INVALCOLOR;
}

/*
 * Set the current text foreground color.
 */
    void
gui_mch_set_fg_color(guicolor_T color)
{
    vimjs_set_fg_color(color);
}

/*
 * Set the current text background color.
 */
    void
gui_mch_set_bg_color(guicolor_T color)
{
    vimjs_set_bg_color(color);
}

/*
 * Set the current text special color.
 */
    void
gui_mch_set_sp_color(guicolor_T color)
{
    vimjs_set_sp_color(color);
}

    void
gui_mch_draw_string(int row, int col, char_u *s, int len, int flags)
{
    vimjs_draw_string(row, col, s, len, flags);
}

/*
 * Return OK if the key with the termcap name "name" is supported.
 */
    int
gui_mch_haskey(char_u *name)
{
    return vimjs_haskey((char*)name) ? OK : FAIL;
}

    void
gui_mch_beep(void)
{
    vimjs_beep();
}

    void
gui_mch_flash(int msec)
{
    vimjs_flash(msec);
}

/*
 * Invert a rectangle from row r, column c, for nr rows and nc columns.
 */
    void
gui_mch_invert_rectangle(int r, int c, int nr, int nc)
{
    vimjs_invert_rectangle(r, c, nr, nc);
}

/*
 * Iconify the GUI window.
 */
    void
gui_mch_iconify(void)
{
}

#if defined(FEAT_EVAL) || defined(PROTO)
/*
 * Bring the Vim window to the foreground.
 */
    void
gui_mch_set_foreground(void)
{
    // Nothing to do
}
#endif

/*
 * Draw a cursor without focus.
 */
    void
gui_mch_draw_hollow_cursor(guicolor_T color)
{
    gui_mch_set_fg_color(color);
    vimjs_draw_hollow_cursor(gui.row, gui.col);
}

/*
 * Draw part of a cursor, only w pixels wide, and h pixels high.
 */
    void
gui_mch_draw_part_cursor(int w, int h, guicolor_T color)
{
    gui_mch_set_fg_color(color);
    vimjs_draw_part_cursor(gui.row, gui.col, w, h);
}



/*
 * Catch up with any queued X events.  This may put keyboard input into the
 * input buffer, call resize call-backs, trigger timers etc.  If there is
 * nothing in the X event queue (& no timers pending), then we return
 * immediately.
 */
    void
gui_mch_update(void)
{
    emscripten_sleep(1);
}

/*
 * GUI input routine called by gui_wait_for_chars().  Waits for a character
 * from the keyboard.
 *  wtime == -1	    Wait forever.
 *  wtime == 0	    This should never happen.
 *  wtime > 0	    Wait wtime milliseconds for a character.
 * Returns OK if a character was found to be available within the given time,
 * or FAIL otherwise.
 */
    int
gui_mch_wait_for_chars(int wtime)
{
    if(input_available())
        return OK;
    
    int t = 0;
    int step = 10;
    while(1)
    {
        emscripten_sleep(step);
        if(input_available())
            return OK;
        t += step;
        if((wtime > -1) && (t >= wtime))
            return FAIL;
    }
}


    void
gui_web_handle_key(int code, int modifiers, char_u special1, char_u special2)
{
    char_u buf[64];
    int buf_len = 0;
    int is_special = (special1 != 0);

    if(is_special) 
    {
        code = TO_SPECIAL(special1, special2);
        code = simplify_key(code, &modifiers);
    }
    else 
    {
        if(code == 'c' && (modifiers & MOD_MASK_CTRL))
            got_int = TRUE;
        if(!IS_SPECIAL(code))
        {
            code = simplify_key(code, &modifiers);
            code = extract_modifiers(code, &modifiers);
            if(code == CSI)
                code = K_CSI;
            if(IS_SPECIAL(code))
                is_special = TRUE;
        }
    }

    if(modifiers) 
    {
        buf[buf_len++] = CSI;
        buf[buf_len++] = KS_MODIFIER;
        buf[buf_len++] = modifiers;
    }

    if(is_special && IS_SPECIAL(code))
    {
        buf[buf_len++] = CSI;
        buf[buf_len++] = K_SECOND(code);
        buf[buf_len++] = K_THIRD(code);
    }
    else
    {
        // TODO: support Unicode
        buf[buf_len++] = code;
    }

    if(buf_len)
        add_to_input_buf(buf, buf_len);
}


/*
 * Output routines.
 */

/* Flush any output to the screen */
    void
gui_mch_flush(void)
{
    // Nothing to do
}

/*
 * Clear a rectangular region of the screen from text pos (row1, col1) to
 * (row2, col2) inclusive.
 */
    void
gui_mch_clear_block(int row1, int col1, int row2, int col2)
{
    gui_mch_set_bg_color(gui.back_pixel);
    vimjs_clear_block(row1, col1, row2, col2);
}

/*
 * Clear the whole text window.
 */
    void
gui_mch_clear_all(void)
{
    gui_mch_set_bg_color(gui.back_pixel);
    vimjs_clear_all();
}

/*
 * Delete the given number of lines from the given row, scrolling up any
 * text further down within the scroll region.
 */
    void
gui_mch_delete_lines(int row, int num_lines)
{
    gui_mch_set_bg_color(gui.back_pixel);
    vimjs_delete_lines(num_lines, row, gui.scroll_region_bot, gui.scroll_region_left, gui.scroll_region_right);
}

/*
 * Insert the given number of lines before the given row, scrolling down any
 * following text within the scroll region.
 */
    void
gui_mch_insert_lines(int row, int num_lines)
{
    gui_mch_set_bg_color(gui.back_pixel);
    vimjs_insert_lines(num_lines, row, gui.scroll_region_bot, gui.scroll_region_left, gui.scroll_region_right);
}


    void
gui_mch_set_text_area_pos(int x, int y, int w, int h)
{
    // Nothing to do
}


/*
 * Read the Windows clipboard text and put it in Vim's clipboard register.
 */
    void
clip_mch_request_selection(VimClipboard *cbd)
{
    // Copyed from windows (unix delay the work)
    // TODO missing open and close clipboad
    int		type = MAUTO;
    char_u	*pAllocated = NULL;
    char_u	*pClipText = NULL;
    long_u	size;


    if (cbd != &clip_plus){
        vimjs_log(3, "reg is different from +");
        return;
    }
    vimjs_log(3, "reg is +");

    if ((pAllocated = vimjs_clip_get()) != NULL)
    {
	pClipText = pAllocated;

	switch (*pClipText++)	/* after ++, pClipText points to text */
	{
	    default:
	    case 'L':	type = MLINE;	break;
	    case 'C':	type = MCHAR;	break;
#ifdef FEAT_VISUAL
	    case 'B':	type = MBLOCK;	break;
#endif
	}
    }


    /* Did we get anything? */
    if (pClipText == NULL){
	return;
    }


    /* Since the data may have been padded with trailing nulls,
     * determine the true string length. */
    size = STRLEN(pClipText);

    /* Copy the cleaned-up data over to Vim's clipboard "*" register. */
    clip_yank_selection(type, pClipText, size, cbd);

    /* Free the memory that Win16GetClipboardData() allocated. */
    vim_free(pAllocated);
}


    void
clip_mch_lose_selection(VimClipboard *cbd)
{
}

    int
clip_mch_own_selection(VimClipboard *cbd)
{
    return OK;
}

/*
 * Send the current selection to the clipboard.
 */
    void
clip_mch_set_selection(VimClipboard *cbd)
{

    char_u*	pClipData = NULL;
    char_u	*clip_data_buffer;
    long_u	clip_data_size;
    int		clip_data_type;

    /* If the '*' register isn't already filled in, fill it in now. */
    cbd->owned = TRUE;
    clip_get_selection(cbd);
    cbd->owned = FALSE;

    // Pass * register <- otherwise always prompted
    if (cbd != &clip_plus){
        vimjs_log(3, "reg is different from +");
        return;
    }
    vimjs_log(3, "reg is +");
    
    /*
     * clip_convert_selection() returns a pointer to a buffer containing
     * the text to send to the Windows clipboard, together with a count
     * of the number of characters (bytes) in the buffer.  The function's
     * return value is the 'type' of selection: MLINE, MCHAR, or MBLOCK;
     * or -1 for failure.
     */
    clip_data_type = clip_convert_selection(&pClipData, &clip_data_size, cbd);

    if (clip_data_type < 0)	    /* could not convert? */
	return;			    /* early exit */

    // Null terminate
    clip_data_buffer = (char_u *)lalloc(clip_data_size + 1, TRUE);
    *(clip_data_buffer + clip_data_size) = '\0';
    memcpy(clip_data_buffer, pClipData, clip_data_size);

    // TODO what is the format and the type 
    vimjs_clip_set(clip_data_buffer, clip_data_size);

    /* release memory allocated by clip_convert_selection() */
    vim_free(pClipData);
}


/*
 * Menu stuff.
 */

    void
gui_mch_enable_menu(int flag)
{
}

    void
gui_mch_set_menu_pos(int x, int y, int w, int h)
{
}

/*
 * Add a sub menu to the menu bar.
 */
    void
gui_mch_add_menu(vimmenu_T *menu, int idx)
{
}


/*
 * Add a menu item to a menu
 */
    void
gui_mch_add_menu_item(vimmenu_T *menu, int idx)
{
}


    void
gui_mch_toggle_tearoffs(int enable)
{
}

/*
 * Destroy the machine specific menu widget.
 */
    void
gui_mch_destroy_menu(vimmenu_T *menu)
{
}


/*
 * Make a menu either grey or not grey.
 */
    void
gui_mch_menu_grey(vimmenu_T *menu, int grey)
{
}


/*
 * Make menu item hidden or not hidden
 */
    void
gui_mch_menu_hidden(vimmenu_T *menu, int hidden)
{
}


/*
 * This is called after setting all the menus to grey/hidden or not.
 */
    void
gui_mch_draw_menubar(void)
{
}


/*
 * Scrollbar stuff.
 */

    void
gui_mch_enable_scrollbar(
	scrollbar_T	*sb,
	int		flag)
{
}

    void
gui_mch_set_scrollbar_thumb(
	scrollbar_T *sb,
	long val,
	long size,
	long max)
{
}

    void
gui_mch_set_scrollbar_pos(
	scrollbar_T *sb,
	int x,
	int y,
	int w,
	int h)
{
}

    void
gui_mch_create_scrollbar(
	scrollbar_T *sb,
	int orient)	/* SBAR_VERT or SBAR_HORIZ */
{
}


    void
gui_mch_destroy_scrollbar(scrollbar_T *sb)
{
}


/*
 * Cursor blink functions.
 *
 * This is a simple state machine:
 * BLINK_NONE	not blinking at all
 * BLINK_OFF	blinking, cursor is not shown
 * BLINK_ON blinking, cursor is shown
 */
    void
gui_mch_set_blinking(long wait, long on, long off)
{
}

/*
 * Stop the cursor blinking.  Show the cursor if it wasn't shown.
 */
    void
gui_mch_stop_blink(void)
{
    gui_update_cursor(TRUE, FALSE);
}

/*
 * Start the cursor blinking.  If it was already blinking, this restarts the
 * waiting time and shows the cursor.
 */
    void
gui_mch_start_blink(void)
{
    gui_update_cursor(TRUE, FALSE);
}

/*
 * Return the RGB value of a pixel as long.
 */
    long_u
gui_mch_get_rgb(guicolor_T pixel)
{
    return (long_u)pixel;
}



#ifdef FEAT_BROWSE
/*
 * Pop open a file browser and return the file selected, in allocated memory,
 * or NULL if Cancel is hit.
 *  saving  - TRUE if the file will be saved to, FALSE if it will be opened.
 *  title   - Title message for the file browser dialog.
 *  dflt    - Default name of file.
 *  ext     - Default extension to be added to files without extensions.
 *  initdir - directory in which to open the browser (NULL = current dir)
 *  filter  - Filter for matched files to choose from.
 *  Has a format like this:
 *  "C Files (*.c)\0*.c\0"
 *  "All Files\0*.*\0\0"
 *  If these two strings were concatenated, then a choice of two file
 *  filters will be selectable to the user.  Then only matching files will
 *  be shown in the browser.  If NULL, the default allows all files.
 *
 *  *NOTE* - the filter string must be terminated with TWO nulls.
 */
    char_u *
gui_mch_browse(
    int saving,
    char_u *title,
    char_u *dflt,
    char_u *ext,
    char_u *initdir,
    char_u *filter)
{
    char buf[4096];
    vimjs_browse(buf, 4096, saving, (char*)dflt, (char*)initdir);
    if(*buf == 0) {
        return NULL;
    }
    return vim_strsave((char_u*)buf);
}
#endif /* FEAT_BROWSE */

#ifdef FEAT_GUI_DIALOG
/*
 * Stuff for dialogues
 */

/*
 * Create a dialogue dynamically from the parameter strings.
 * type       = type of dialogue (question, alert, etc.)
 * title      = dialogue title. may be NULL for default title.
 * message    = text to display. Dialogue sizes to accommodate it.
 * buttons    = '\n' separated list of button captions, default first.
 * dfltbutton = number of default button.
 *
 * This routine returns 1 if the first button is pressed,
 *	    2 for the second, etc.
 *
 *	    0 indicates Esc was pressed.
 *	    -1 for unexpected error
 *
 * If stubbing out this fn, return 1.
 */

    int
gui_mch_dialog(
    int		type,
    char_u	*title,
    char_u	*message,
    char_u	*buttons,
    int		dfltbutton,
    char_u	*textfield,
    int		ex_cmd)
{
    return -1;
}
#endif /* FEAT_DIALOG_GUI */

/*
 * Get current mouse coordinates in text window.
 */
    void
gui_mch_getmouse(int *x, int *y)
{
    *x = *y = 0;
}

    void
gui_mch_setmouse(int x, int y)
{
}

    void
gui_mch_show_popupmenu(vimmenu_T *menu)
{
}


#ifdef FEAT_TITLE
/*
 * Set the window title and icon.
 */
    void
gui_mch_settitle(char_u *title, char_u *icon)
{
}
#endif

#if defined(FEAT_GUI_TABLINE)
/*
 * Show or hide the tabline.
 */
    void
gui_mch_show_tabline(int showit)
{
}

/*
 * Return TRUE when tabline is displayed.
 */
    int
gui_mch_showing_tabline(void)
{
    return FALSE;
}

/*
 * Update the labels of the tabline.
 */
    void
gui_mch_update_tabline(void)
{
}


/*
 * Set the current tab to "nr".  First tab is 1.
 */
    void
gui_mch_set_curtab(nr)
    int		nr;
{
}

#endif // FEAT_GUI_TABLINE
