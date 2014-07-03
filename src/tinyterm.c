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

#define TINYTERM_FONT              "Terminus Regular 10" 
#define TINYTERM_WORD_CHARS        "-A-Za-z0-9:./?%&#_=+@~"

int
main (int argc, char *argv[])
{
    GtkWidget *window, *terminal;
    GdkGeometry geo_hints;

    /* Init gtk and all widgets */
    gtk_init (&argc, &argv);
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    terminal = vte_terminal_new ();

    /* Terminal font*/
    PangoFontDescription * font = pango_font_description_from_string( TINYTERM_FONT);
    vte_terminal_set_font ( (VteTerminal *)terminal, font);

    /* Terminal size */
    vte_terminal_set_size ( VTE_TERMINAL (terminal), (glong) 82, (glong) 25);


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

    /* Set selection behavior for double-clicks */
    vte_terminal_set_word_chars (VTE_TERMINAL (terminal), TINYTERM_WORD_CHARS);

    /* Put all widgets together and show the result */
    gtk_container_add (GTK_CONTAINER (window), terminal);
    gtk_widget_show_all (window);
    gtk_main ();

    return 0;
}
