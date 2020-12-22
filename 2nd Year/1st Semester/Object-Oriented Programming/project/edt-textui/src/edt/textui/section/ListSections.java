/** @version $Id: ListSections.java,v 1.9 2015/11/29 21:19:53 ist180996 Exp $ */
package edt.textui.section;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.DialogException;

import java.io.IOException;
import java.util.List;

/* FIXME: import core classes here */
import edt.editor.Section;
import edt.editor.Document;
import edt.editor.Visitor;

import edt.textui.section.ShowListSectionsVisitor;

/**
 * §2.2.2.
 */
public class ListSections extends SectionCommand {
	public ListSections(Section section, Document document) {
		super(MenuEntry.LIST_SECTIONS, section, document);
	}

	@Override
	public final void execute() throws DialogException, IOException {
		Visitor v = new ShowListSectionsVisitor();
		_receiver.accept(v);
		if(!v.getContent().equals(""))
			IO.println(v.getContent());	
	}
}
