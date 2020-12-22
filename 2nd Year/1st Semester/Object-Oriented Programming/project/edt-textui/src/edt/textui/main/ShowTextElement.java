/** @version $Id: ShowTextElement.java,v 1.6 2015/11/29 21:19:53 ist180996 Exp $ */
package edt.textui.main;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.Command;
import ist.po.ui.DialogException;

import java.io.IOException;

import edt.editor.Editor;

import edt.editor.Visitor;

import edt.textui.ShowTextElementVisitor;
import java.util.Map;
import java.util.TreeMap;


/**
 * §2.1.5.
 */
public class ShowTextElement extends Command<Editor> {
  public ShowTextElement(Editor receiver) {
    super(MenuEntry.SHOW_TEXT_ELEMENT, receiver);
  }

  @Override
  public final void execute() throws DialogException, IOException {
    String id = IO.readString(Message.requestElementId());

    Visitor v = new ShowTextElementVisitor();
    
    if(_receiver.acceptTextElement(v, id))
    	IO.println(v.getContent());
    else
    	IO.println(Message.noSuchTextElement(id));
  }
}
