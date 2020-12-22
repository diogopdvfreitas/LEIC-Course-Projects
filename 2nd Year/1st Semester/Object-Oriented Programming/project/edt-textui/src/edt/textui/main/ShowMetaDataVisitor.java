package edt.textui.main;

import edt.textui.main.Message;

import edt.editor.Document;
import edt.editor.Section;
import edt.editor.Visitor;
import edt.editor.Author;
import edt.editor.Paragraph;


public class ShowMetaDataVisitor implements Visitor{
	private String x = "";

	public String getContent(){
		return x.substring(0, x.length() - 1);
	}

	public void visitDocument(Document document){
		x += Message.documentTitle(document.getTitle()) + "\n";
  		
		for(Author a : document.getAuthors())
			x += Message.author(a.getName(), a.getEmail()) + "\n";

  		x += Message.documentSections(document.getSubSectionsSize()) + "\n";
		
		x += Message.documentBytes(document.getTotalSize()) + "\n";
		
		x += Message.documentIdentifiers(document.getTextElementsSize()) + "\n";
 	}

 	public void visitSection(Section section){}

	public void visitParagraph(Paragraph paragraph){}

}