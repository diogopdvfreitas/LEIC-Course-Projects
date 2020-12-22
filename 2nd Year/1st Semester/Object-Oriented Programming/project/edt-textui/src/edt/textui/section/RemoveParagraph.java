/** @version $Id: RemoveParagraph.java,v 1.6 2015/11/29 21:19:53 ist180996 Exp $ */
package edt.textui.section;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.DialogException;

import java.io.IOException;

/* FIXME: import core classes here */
import edt.editor.Section;
import edt.editor.Document;

/**
 * §2.2.11.
 */
public class RemoveParagraph extends SectionCommand {
	public RemoveParagraph(Section section, Document document) {
		super(MenuEntry.REMOVE_PARAGRAPH, section, document);
	}

	@Override
	public final void execute() throws DialogException, IOException {
      	int localId = IO.readInteger(Message.requestParagraphId());
     	
      	if((localId >= 0) && (localId < _receiver.getParagraphsSize()))
      		_receiver.removeParagraph(localId, _receiver2);
		
		else
			IO.println(Message.noSuchParagraph(localId));
		

		
	}

}
