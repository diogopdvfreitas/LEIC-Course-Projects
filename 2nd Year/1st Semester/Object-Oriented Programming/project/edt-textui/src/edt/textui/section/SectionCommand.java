/** @version $Id: SectionCommand.java,v 1.6 2015/11/29 21:19:53 ist180996 Exp $ */
package edt.textui.section;

import ist.po.ui.Command;

import edt.editor.Section;
import edt.editor.Document;

/**
 * Superclass of all section-context commands.
 */
public abstract class SectionCommand extends Command<Section> {
  	Document _receiver2;
  
	public SectionCommand(String title, Section receiver, Document receiver2) {
		super(title, receiver);
		_receiver2 = receiver2;
	}

}
