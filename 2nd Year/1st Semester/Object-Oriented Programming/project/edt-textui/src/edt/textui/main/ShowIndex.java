/** @version $Id: ShowIndex.java,v 1.10 2015/11/29 21:19:53 ist180996 Exp $ */
package edt.textui.main;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.Command;
import ist.po.ui.DialogException;

import java.io.IOException;
import java.util.List;

import edt.editor.Editor;
import edt.editor.Visitor;
import edt.textui.main.ShowTopSectionsVisitor;

/**
 * §2.1.4.
 */
public class ShowIndex extends Command<Editor> {
	public ShowIndex(Editor receiver) {
		super(MenuEntry.SHOW_INDEX, receiver);
	}

	@Override
	public final void execute() throws DialogException, IOException {
		Visitor v = new ShowTopSectionsVisitor();
		_receiver.acceptDocument(v);
		IO.println(v.getContent());
	}
}
