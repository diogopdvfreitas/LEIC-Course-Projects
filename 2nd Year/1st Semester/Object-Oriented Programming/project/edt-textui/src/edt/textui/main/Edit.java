/** @version $Id: Edit.java,v 1.4 2015/11/25 19:03:11 ist180996 Exp $ */
package edt.textui.main;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.Command;
import ist.po.ui.DialogException;

import java.io.IOException;

import edt.editor.Editor;

/**
 * §2.3.1.
 */
public class Edit extends Command<Editor> {
  public Edit(Editor receiver) {
    super(MenuEntry.OPEN_DOCUMENT_EDITOR, receiver);
  }

  @Override
  public final void execute() throws DialogException, IOException {
    edt.textui.section.MenuBuilder.menuFor(_receiver.getDocument(), _receiver.getDocument());
  }

}
