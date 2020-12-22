/** @version $Id: ShowMetadata.java,v 1.7 2015/11/29 21:19:53 ist180996 Exp $ */
package edt.textui.main;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.Command;
import ist.po.ui.DialogException;

import java.io.IOException;

import edt.editor.Editor;
import edt.editor.Visitor;
import edt.textui.main.ShowMetaDataVisitor;

/**
 * §2.1.2.
 */
public class ShowMetadata extends Command<Editor> {
	public ShowMetadata(Editor receiver) {
		super(MenuEntry.SHOW_METADATA, receiver);
	}

	@Override
	public final void execute() throws DialogException, IOException {
		Visitor v = new ShowMetaDataVisitor();
		_receiver.acceptDocument(v);
		IO.println(v.getContent());
	}
}
