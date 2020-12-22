/** @version $Id: MenuBuilder.java,v 1.4 2015/11/25 19:03:11 ist180996 Exp $ */
package edt.textui.section;

import ist.po.ui.Command;
import ist.po.ui.Menu;

/* FIXME: import core classes here */
import edt.editor.Document;
import edt.editor.Section;

/**
 * Menu builder for search operations.
 */
public class MenuBuilder {
  public static void menuFor(Section section, Document document) {
    Menu menu = new Menu(MenuEntry.TITLE,
        new Command<?>[] { //
            new ChangeTitle(section, document), //
            new ListSections(section, document), //
            new ShowContent(section, document), //
            new SelectSection(section, document), //
            new InsertSection(section, document), //
            new NameSection(section, document), //
            new RemoveSection(section, document), //
            new InsertParagraph(section, document), //
            new NameParagraph(section, document), //
            new EditParagraph(section, document), //
            new RemoveParagraph(section, document), //
    });
    menu.open();
  }
}
