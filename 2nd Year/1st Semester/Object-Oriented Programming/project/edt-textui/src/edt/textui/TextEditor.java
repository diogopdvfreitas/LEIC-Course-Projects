/** @version $Id: TextEditor.java,v 1.6 2015/11/16 02:36:57 ist180996 Exp $ */
package edt.textui;

import static ist.po.ui.Dialog.IO;

import java.io.IOException;

import edt.editor.Editor;

/**
 * Class that starts the application's textual interface.
 */

public class TextEditor {
	public static void main(String[] args) throws Exception{
		Editor editor = new Editor();
		editor.create();
		String datafile = System.getProperty("import"); 
		if (datafile != null) {
			try{
				editor.importData(datafile);
			}
			catch(IOException e){
				e.printStackTrace();
			}

		}
		edt.textui.main.MenuBuilder.menuFor(editor);
		IO.closeDown();
	}
}





