/** @version $Id: Save.java,v 1.5 2015/11/16 02:36:57 ist180996 Exp $ */
package edt.textui.main;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.Command;
import ist.po.ui.DialogException;

import java.io.IOException;
import java.io.FileNotFoundException;

import edt.editor.Editor;

/**
 * Save to file under current name (if unnamed, query for name).
 */

public class Save extends Command<Editor> {
	public Save(Editor receiver) {
		super(MenuEntry.SAVE, receiver);
	}

	@Override
	public final void execute() throws DialogException, IOException {
		try{
			if(_receiver.getFileName() == null){
				String filename = IO.readString(Message.newSaveAs());
				while(filename.equals(""))
					filename = IO.readString(Message.newSaveAs());
				_receiver.save(filename);
			}
			else{
				_receiver.save(_receiver.getFileName());
			}
		}
		catch(FileNotFoundException e){}
	}
}
