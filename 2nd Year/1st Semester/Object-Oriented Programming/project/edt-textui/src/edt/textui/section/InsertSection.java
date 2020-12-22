/** @version $Id: InsertSection.java,v 1.6 2015/11/27 01:50:58 ist180996 Exp $ */
package edt.textui.section;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.DialogException;

import java.io.IOException;

/* FIXME: import core classes here */
import edt.editor.Section;
import edt.editor.Document;

/**
 * §2.2.5.
 */
public class InsertSection extends SectionCommand {
  public InsertSection(Section section, Document document) {
    super(MenuEntry.INSERT_SECTION, section, document);
  }

  @Override
  public final void execute() throws DialogException, IOException {
    int localId = IO.readInteger(Message.requestSectionId());
		String title = IO.readString(Message.requestSectionTitle());
		
		_receiver.insertSection(localId, "", title);
  }
}
