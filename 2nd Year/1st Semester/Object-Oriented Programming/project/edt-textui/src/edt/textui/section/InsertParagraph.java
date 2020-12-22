/** @version $Id: InsertParagraph.java,v 1.7 2015/11/29 21:19:53 ist180996 Exp $ */
package edt.textui.section;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.DialogException;

import java.io.IOException;

/* FIXME: import core classes here */
import edt.editor.Section;
import edt.editor.Document;
/**
 * §2.2.8.
 */
public class InsertParagraph extends SectionCommand {
	public InsertParagraph(Section section, Document document) {
		super(MenuEntry.INSERT_PARAGRAPH, section, document);
	}

	@Override
	public final void execute() throws DialogException, IOException {
		int localId = IO.readInteger(Message.requestParagraphId());
		String content = IO.readString(Message.requestParagraphContent());
		
		_receiver.addParagraph(localId, content);
	}
}
