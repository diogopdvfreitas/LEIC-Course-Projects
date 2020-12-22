/** @version $Id: SelectSection.java,v 1.7 2015/11/27 05:01:13 ist180996 Exp $ */
package edt.textui.section;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.DialogException;

import java.io.IOException;

/* FIXME: import core classes here */
import edt.editor.Section;
import edt.editor.Document;

/**
 * §2.2.4.
 */
public class SelectSection extends SectionCommand {
	public SelectSection(Section section, Document document) {
		super(MenuEntry.SELECT_SECTION, section, document);
	}

	@Override
	public final void execute() throws DialogException, IOException  {
	 	
	 	int localId = IO.readInteger(Message.requestSectionId());
	 	if ((localId >= 0) && (localId < _receiver.getSubSectionsSize())){
	 		IO.println(Message.newActiveSection(localId));
	 		edt.textui.section.MenuBuilder.menuFor(_receiver.getSpecificSection(localId), _receiver2);
		}
		else
			IO.println(Message.noSuchSection(localId));
	}
}
