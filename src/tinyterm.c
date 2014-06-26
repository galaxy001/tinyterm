/* tinyterm.c
 *
 * Copyright (C) 2009 Sebastian Linke
 *
 * This is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Library General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <gdk/gdkkeysyms.h>
#include <vte/vte.h>
#include <wordexp.h>

#define TINYTERM_FONT              "Terminus Regular 10" 
#define TINYTERM_SCROLLBACK_LINES  10000
#define TINYTERM_WORD_CHARS        "-A-Za-z0-9:./?%&#_=+@~"

static gboolean
on_key_press (GtkWidget *terminal, GdkEventKey *event)
{
    if (event->state == (GDK_CONTROL_MASK | GDK_SHIFT_MASK )) {
        switch (event->keyval) {
            case GDK_C:
                vte_terminal_copy_clipboard (VTE_TERMINAL (terminal));
                return TRUE;
            case GDK_V:
                vte_terminal_paste_clipboard (VTE_TERMINAL (terminal));
                return TRUE;
        }
    }
    return FALSE;
}

int
main (int argc, char *argv[])
{
    GtkWidget *window, *terminal, *design;
    GdkGeometry geo_hints;

    /* Init gtk and all widgets */
    gtk_init (&argc, &argv);
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    terminal = vte_terminal_new ();
    design = gtk_hbox_new (FALSE, 0);

    /* Terminal font*/
    PangoFontDescription * font = pango_font_description_from_string( TINYTERM_FONT);
    vte_terminal_set_font ( (VteTerminal *)terminal, font);

    /* Set window title */
    gtk_window_set_title (GTK_WINDOW (window), "TinyTerm");

    /* Terminal size */
    vte_terminal_set_size ( VTE_TERMINAL (terminal), (glong) 82, (glong) 25);

    /* Set scrollback lines */
    vte_terminal_set_scrollback_lines (VTE_TERMINAL (terminal), TINYTERM_SCROLLBACK_LINES);

    /* Apply geometry hints to handle terminal resizing */
    geo_hints.base_width  = VTE_TERMINAL (terminal)->char_width;
    geo_hints.base_height = VTE_TERMINAL (terminal)->char_height;
    geo_hints.min_width   = VTE_TERMINAL (terminal)->char_width;
    geo_hints.min_height  = VTE_TERMINAL (terminal)->char_height;
    geo_hints.width_inc   = VTE_TERMINAL (terminal)->char_width;
    geo_hints.height_inc  = VTE_TERMINAL (terminal)->char_height;
    gtk_window_set_geometry_hints (GTK_WINDOW (window), terminal, &geo_hints,
                                   GDK_HINT_RESIZE_INC | GDK_HINT_MIN_SIZE | GDK_HINT_BASE_SIZE);

    /* Open a standard shell */
    vte_terminal_fork_command(VTE_TERMINAL (terminal),
                               NULL,  
                               NULL,  
                               NULL,  
                               NULL,
                               FALSE,  
                               FALSE,
                               FALSE); 

    /* Connect signals */
    g_signal_connect (window, "delete-event", gtk_main_quit, NULL);
    g_signal_connect (terminal, "child-exited", gtk_main_quit, NULL);
    g_signal_connect (terminal, "key-press-event", G_CALLBACK (on_key_press), NULL);

    /* Set selection behavior for double-clicks */
    vte_terminal_set_word_chars (VTE_TERMINAL (terminal), TINYTERM_WORD_CHARS);

    /* Put all widgets together and show the result */
    gtk_box_pack_start (GTK_BOX (design), terminal, TRUE, TRUE, 0);
    gtk_container_add (GTK_CONTAINER (window), design);
    gtk_widget_show_all (window);
    gtk_main ();

    return 0;
}
