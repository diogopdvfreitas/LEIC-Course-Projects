/** @version $Id: AddAuthor.java,v 1.5 2015/11/29 21:19:53 ist180996 Exp $ */
package edt.textui.main;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.Command;
import ist.po.ui.DialogException;

import java.io.IOException;

import edt.editor.Editor;

/**
 * §2.1.3.
 */
public class AddAuthor extends Command<Editor> {
	public AddAuthor(Editor receiver) {
		super(MenuEntry.ADD_AUTHOR, receiver);
	}

	@Override
	public final void execute() throws DialogException, IOException {
	  	String name = IO.readString(Message.requestAuthorName());
	  	String email = IO.readString(Message.requestEmail());

		if(!_receiver.addDocumentAuthor(name, email))
			IO.println(Message.duplicateAuthor(name));	
	}
}
