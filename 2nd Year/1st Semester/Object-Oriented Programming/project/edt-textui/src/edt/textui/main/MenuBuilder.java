/** @version $Id: MenuBuilder.java,v 1.9 2015/11/29 19:25:48 ist180996 Exp $ */
package edt.textui.main;

import ist.po.ui.Command;
import ist.po.ui.Menu;

/* FIXME: import core classes here */
import edt.editor.Editor;
import edt.editor.Document;

public abstract class MenuBuilder {
  public static void menuFor(Editor editor) {
    Menu menu = new Menu(MenuEntry.TITLE,
        new Command<?>[] { //
            new New(editor), //
            new Open(editor), //
            new Save(editor), //
            new ShowMetadata(editor), //
            new AddAuthor(editor), //
            new ShowIndex(editor), //
            new ShowTextElement(editor), //
            new Edit(editor), //
    });
    menu.open();
  }
}
