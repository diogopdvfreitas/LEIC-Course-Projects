package edt.textui.main;

import edt.textui.main.Message;

import edt.editor.Document;
import edt.editor.Section;
import edt.editor.Visitor;
import edt.editor.Paragraph;


public class ShowTopSectionsVisitor implements Visitor{
	private String x = "";

	public String getContent(){
		return x.substring(0, x.length() - 1);
	}

	public void visitDocument(Document document){
  		x += "{" + document.getTitle() + "}" + "\n";
  		for(Section s : document.getSubSections())
   			x += Message.sectionIndexEntry(s.getId(), s.getTitle()) + "\n";
 	}

 	public void visitSection(Section section){}

	public void visitParagraph(Paragraph paragraph){}
 }