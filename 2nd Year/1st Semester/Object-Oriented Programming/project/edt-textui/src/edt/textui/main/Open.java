/** @version $Id: Open.java,v 1.5 2015/11/16 02:36:57 ist180996 Exp $ */
package edt.textui.main;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.Command;
import ist.po.ui.DialogException;

import java.io.IOException;
import java.io.FileNotFoundException;

import edt.editor.Editor;

/**
 * Open existing document.
 */

public class Open extends Command<Editor> {
	public Open(Editor receiver) {
		super(MenuEntry.OPEN, receiver);
	}

	@Override
	public final void execute() throws DialogException, IOException {
		String line = IO.readString(Message.openFile());
		while(line.equals(""))
			line = IO.readString(Message.openFile());
		try{
			_receiver.open(line);
		}
		catch(FileNotFoundException e2){
			IO.println(Message.fileNotFound(line));
		}
	}

}
