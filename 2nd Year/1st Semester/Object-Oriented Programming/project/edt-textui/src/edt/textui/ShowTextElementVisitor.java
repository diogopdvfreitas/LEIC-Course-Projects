package edt.textui;

import edt.textui.main.Message;

import edt.editor.Section;
import edt.editor.Paragraph;
import edt.editor.Document;
import edt.editor.Visitor;

public class ShowTextElementVisitor implements Visitor{
	private String x = "";

	public String getContent(){
		return x.substring(0, x.length()-1);
	}

	public void visitParagraph(Paragraph paragraph){
		x += paragraph.getContent() + "\n";
	}

	public void visitSection(Section section){
		x += Message.sectionIndexEntry(section.getId(), section.getTitle()) + "\n";

		for(Paragraph p : section.getParagraphs())
			p.accept(this);
		
		for(Section s : section.getSubSections()){
			s.accept(this);
		}
	}

	public void visitDocument(Document document){
		x += "{" + document.getTitle() + "}" + "\n";
		for(Paragraph p : document.getParagraphs())
			p.accept(this);
		
		for(Section s : document.getSubSections()){
			s.accept(this);
		}
	}
}