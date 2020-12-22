/** @version $Id: ShowContent.java,v 1.5 2015/11/29 16:34:11 ist181586 Exp $ */
package edt.textui.section;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.DialogException;

import java.io.IOException;

/* FIXME: import core classes here */
import edt.editor.Section;
import edt.editor.Document;
import edt.editor.Visitor;

import edt.textui.ShowTextElementVisitor;

/**
 * §2.2.3.
 */
public class ShowContent extends SectionCommand {
	public ShowContent(Section section, Document document) {
		super(MenuEntry.SHOW_CONTENT, section, document);
	}

	@Override
	public final void execute() throws DialogException, IOException {
	  	Visitor v = new ShowTextElementVisitor();
		_receiver.accept(v);
		IO.println(v.getContent());
	}
}
