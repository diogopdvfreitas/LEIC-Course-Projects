/** @version $Id: EditParagraph.java,v 1.7 2015/11/29 21:19:53 ist180996 Exp $ */
package edt.textui.section;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.DialogException;

import java.io.IOException;

/* FIXME: import core classes here */
import edt.editor.Section;
import edt.editor.Document;

/**
 * §2.2.10.
 */
public class EditParagraph extends SectionCommand {
	public EditParagraph(Section section, Document document) {
		super(MenuEntry.EDIT_PARAGRAPH, section, document);
	}

	@Override
	public final void execute() throws DialogException, IOException {
		int localId = IO.readInteger(Message.requestParagraphId());
		String content = IO.readString(Message.requestParagraphContent());
		
		if ((localId >= 0) && (localId < _receiver.getParagraphsSize()))
			_receiver.editParagraph(localId, content);
	  	else
	  		IO.println(Message.noSuchParagraph(localId));
	}

}
