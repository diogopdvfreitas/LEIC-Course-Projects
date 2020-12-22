/** @version $Id: New.java,v 1.4 2015/11/16 00:29:40 ist180996 Exp $ */
package edt.textui.main;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.Command;
import ist.po.ui.DialogException;

import java.io.IOException;

/* FIXME: import core classes here */
import edt.editor.Editor;

/**
 * Open a new document.
 */
public class New extends Command<Editor> {
	public New(Editor receiver) {
		super(MenuEntry.NEW, receiver);
	}

	@Override
	public final void execute() throws DialogException, IOException {
		_receiver.create();
	}

}
