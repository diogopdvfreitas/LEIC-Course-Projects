/** @version $Id: RemoveSection.java,v 1.5 2015/11/29 18:45:01 ist180996 Exp $ */
package edt.textui.section;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.DialogException;

import java.io.IOException;

/* FIXME: import core classes here */
import edt.editor.Section;
import edt.editor.Document;

/**
 * §2.2.7.
 */
public class RemoveSection extends SectionCommand {
  public RemoveSection(Section section, Document document) {
    super(MenuEntry.REMOVE_SECTION, section, document);
  }

  @Override
  public final void execute() throws DialogException, IOException {
    int localId = IO.readInteger(Message.requestSectionId());

    if((localId >= 0) && (localId < _receiver.getSubSectionsSize())){
    	_receiver.removeSection(localId, _receiver2);
    }
    else
    	IO.println(Message.noSuchSection(localId));
  }
  
}
