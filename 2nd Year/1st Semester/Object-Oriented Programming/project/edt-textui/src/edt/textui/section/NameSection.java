/** @version $Id: NameSection.java,v 1.6 2015/11/29 21:19:53 ist180996 Exp $ */
package edt.textui.section;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.DialogException;

import java.io.IOException;

/* FIXME: import core classes here */
import edt.editor.Section;
import edt.editor.Document;

/**
 * §2.2.6.
 */
public class NameSection extends SectionCommand {
  public NameSection(Section section, Document document) {
    super(MenuEntry.NAME_SECTION, section, document);
  }

  @Override
  public final void execute() throws DialogException, IOException {
    	int localId = IO.readInteger(Message.requestSectionId());
      String uniqueId = IO.readString(Message.requestUniqueId());
    	
      if((localId >= 0) && (localId < _receiver.getSubSectionsSize())){
         if(_receiver2.nameTextElement(_receiver, uniqueId, localId, true))
            IO.println(Message.sectionNameChanged());
      }
    	else
    		IO.println(Message.noSuchSection(localId));


  }
}
