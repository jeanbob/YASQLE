/*
 * YASQLE
 * 
 * yasqle.h
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

#ifndef YASQLE_H
#define YASQLE_H

static void 
yasqle_menubar_addWidget(GtkUIManager *ui_manager, 
		  GtkWidget *widget, 
		  GtkContainer *container);

static void 
yasqle_menu_quit();

static void 
yasqle_show_about_dialog();

static void 
yasqle_mainWindow_OnDestroy(GtkWidget *pWidget, 
			    gpointer pData);


#endif
