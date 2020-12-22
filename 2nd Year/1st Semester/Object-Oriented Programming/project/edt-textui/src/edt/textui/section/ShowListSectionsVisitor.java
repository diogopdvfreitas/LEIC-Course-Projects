package edt.textui.section;

import edt.textui.section.Message;

import edt.editor.Section;
import edt.editor.Document;
import edt.editor.Visitor;
import edt.editor.Paragraph;


public class ShowListSectionsVisitor implements Visitor{
	private String x = "";
	
	public String getContent(){
		if(x.equals(""))
			return x;
		return x.substring(0, x.length()-1);
	}

	public void visitSection(Section section){
		for(Section s : section.getSubSections()){
			x += Message.sectionIndexEntry(s.getId(), s.getTitle()) + "\n";
			s.accept(this);
		}
	}

	public void visitDocument(Document document){
		for(Section s : document.getSubSections()){
			x += Message.sectionIndexEntry(s.getId(), s.getTitle()) + "\n";
			s.accept(this);
		}
	}

	public void visitParagraph(Paragraph paragraph){}

	
}