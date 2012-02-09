/*
 * YASQLE
 * 
 * yasqle.c
 *
 * Copyright (C) 2012 Peter Fontaine (aka JeanBoB) <jeanbob@jeanbob.eu>, Tous 
 * droits réservés.
 *
 * Ce programme est un logiciel libre; vous pouvez le redistribuer ou le
 * modifier suivant les termes de la "GNU General Public Licence" telle ue
 * publiée par la Free Software Foundation : soit la version 3 de cette
 * licence, soit (à votre gré) toute version ultérieure.
 *
 * Ce programme est distribué dans l'espoir qu'il vous sera utile, mais SANS
 * AUCUNE GARANTIE : sans même la garantie implicite de COMMERCIALISABILITÉ
 * ni d'ADÉQUATION À UN OBJECTIF PARTICULIER. Consultez la Licence Générale
 * Publique GNU pour plus de détails.
 *
 * Vous devriez avoir reçu une copie de la Licence Générale Publique GNU avec
 * ce programme; si ce n'est pas le cas, consultez :
 * <http://www.gnu.org/licences/>.
 *
 */

#include <stdlib.h>
#include <gtk/gtk.h>
#include "yasqle.h"

int 
main(int argc,char **argv)
{ 
    /* Declaration des widgets */
    GtkWidget *mainWindow;
    GtkWidget *Label;
    GtkUIManager *menubar_manager;
    GtkWidget *toolbar;
    GtkWidget *statebar;
    GtkWidget *main_content;
    GtkActionGroup *actiongroup;
    GtkWidget *hpaned;
    GtkActionEntry entries[] = {
	 { "FichierMenuAction", NULL, "Fichier", NULL, NULL, NULL },
	 { "NouveauAction", GTK_STOCK_NEW, "Nouveau", "<Control>N", "Nouveau", NULL },
	 { "OuvrirAction", GTK_STOCK_OPEN, "Ouvrir", "<Control>O", "Ouvrir", NULL },
	 { "QuitterAction", GTK_STOCK_QUIT, "Quitter", "<Ctrl>Q", "Quitter", G_CALLBACK(yasqle_menu_quit) },
	 { "TableMenuAction", NULL, "Table", NULL, NULL, NULL },	 
	 { "NouvelleTableAction", NULL, "Nouvelle Table", "<Ctrl><Shift>N", "Nouvelle Table", NULL },
	 { "SupprimerTableAction", NULL, "Supprimer Table", "<Ctrl><Shift>D", "Supprimer la table", NULL },
	 { "ModifierTableAction", NULL, "Modifier Table", "<Ctrl><Shift>M", "Modifier la table", NULL },	 
	 { "AideMenuAction", NULL, "?", NULL, NULL, NULL },
	 { "AideAction", GTK_STOCK_HELP, "Aide", NULL, NULL, NULL },
	 { "AproposAction", GTK_STOCK_ABOUT, "A propos...", "<Control>F10", "A propos", G_CALLBACK(yasqle_show_about_dialog) }
    };
    
    gtk_init(&argc,&argv);

    /* Creation de la fenetre */
    mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    /* Connexion du signal "destroy" */
    g_signal_connect(G_OBJECT(mainWindow), "destroy", G_CALLBACK(yasqle_mainWindow_OnDestroy), NULL);

    /* Configuration de la fenetre */
    gtk_window_set_position(GTK_WINDOW(mainWindow), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(mainWindow), "YASQLE - Yet Another SQLite Explorer");
    gtk_window_set_icon_from_file(GTK_WINDOW(mainWindow), "../res/yasqle16.png", NULL);
    gtk_window_set_default_size(GTK_WINDOW(mainWindow), 800, 600);

    /* Configuration d'un conteneur principal */
    main_content = gtk_vbox_new(FALSE, 0);
    
    /* Insertion du conteneur principal dans la fenetre */
    gtk_container_add(GTK_CONTAINER(mainWindow), main_content);
    
    /* Creation de la barre de menu */
    menubar_manager = gtk_ui_manager_new();
    gtk_ui_manager_add_ui_from_file(menubar_manager, "ui.xml", NULL);
    g_signal_connect(menubar_manager, "add_widget", G_CALLBACK(yasqle_menubar_addWidget), GTK_CONTAINER(main_content));
    actiongroup = gtk_action_group_new("menuActionGroup");
    gtk_action_group_add_actions(actiongroup, entries, G_N_ELEMENTS(entries), NULL);
    gtk_ui_manager_insert_action_group(menubar_manager, actiongroup, 0);

    /* Création de la barre de status */
    GtkWidget *statusbar;
    statusbar = gtk_statusbar_new();
    guint welcomemess = gtk_statusbar_get_context_id(GTK_STATUSBAR(statusbar), "welkommess");
    gtk_box_pack_end(GTK_BOX(main_content), statusbar, FALSE, FALSE, 0);
    gtk_statusbar_push(GTK_STATUSBAR(statusbar), welcomemess, "Bienvenue dans YASQLE");
        
    /* Creation de l'arborescence et de la vue */
    hpaned = gtk_hpaned_new();
    gtk_paned_set_position(GTK_PANED(hpaned), 250);
    GtkWidget *label;
    label = gtk_label_new("coucou");
    gtk_paned_add1(GTK_PANED(hpaned), gtk_button_new_with_label("Coucou"));
    gtk_paned_add2(GTK_PANED(hpaned), label);
    gtk_box_pack_end(GTK_BOX(main_content), hpaned, TRUE, TRUE, 0);


    /* Affichage de la fenetre */
    gtk_widget_show_all(mainWindow);

    /* Demarrage de la boucle evenementielle */
    gtk_main();

    return EXIT_SUCCESS; 
}

static void 
yasqle_menu_quit()
{
     gtk_main_quit();
}


static void 
yasqle_mainWindow_OnDestroy(GtkWidget *pWidget, 
			    gpointer pData)
{
    /* Arret de la boucle evenementielle */
    yasqle_menu_quit();
}

static void 
yasqle_show_about_dialog()
{
    GtkWidget *aboutBox;
    GdkPixbuf *aboutlogo;
    
     /* Création AboutBox */
    
    gchar *authors[] = { "Peter Fontaine (aka Jeanbob)", NULL 
    };
    
    gchar *documenters[] = { "Peter Fontaine (aka Jeanbob)", NULL
    };
    
    aboutlogo = gdk_pixbuf_new_from_file("../res/logo.png", NULL);
            
    gtk_show_about_dialog(NULL, 
			  "program-name", "YASQLE",
			  "license", "YASQLE is released on GPLv3,\nsee http://yasqle.jeanbob.eu/Licence/",
			  "version", "version 0.1",
			  "website", "http://yasqle.jeanbob.eu",
			  "copyright", "Copyright 2012 (c) Peter Fontaine (aka Jeanbob)",
			  "logo", aboutlogo,
			  "authors", authors,
			  "documenters", documenters,
			  "comments", "Yet Another SQLite Explorer\nSQLite3 file manager.",
			  NULL);
}

static void 
yasqle_menubar_addWidget(GtkUIManager *ui_manager, 
			 GtkWidget *widget, 
			 GtkContainer *container)
{
     gtk_box_pack_start(GTK_BOX(container), widget, FALSE, FALSE, 0);
     gtk_widget_show(widget);
     return;
}
