/** @version $Id: NameParagraph.java,v 1.5 2015/11/29 21:19:53 ist180996 Exp $ */
package edt.textui.section;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.DialogException;

import java.io.IOException;

/* FIXME: import core classes here */
import edt.editor.Section;
import edt.editor.Document;

/**
 * §2.2.9.
 */
public class NameParagraph extends SectionCommand {
  public NameParagraph(Section section, Document document) {
    super(MenuEntry.NAME_PARAGRAPH, section, document);
  }

  @Override
  public final void execute() throws DialogException, IOException {
    int localId = IO.readInteger(Message.requestParagraphId());
    String uniqueId = IO.readString(Message.requestUniqueId());
	
	if((localId >= 0) && (localId < _receiver.getParagraphsSize())) {
     	if(_receiver2.nameTextElement(_receiver, uniqueId, localId, false))
        	IO.println(Message.paragraphNameChanged());
  	}
  	else
		IO.println(Message.noSuchParagraph(localId));
  }
}
