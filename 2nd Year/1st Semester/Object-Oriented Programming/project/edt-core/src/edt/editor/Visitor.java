package edt.editor;

public interface Visitor{
	public String getContent();
	
	public void visitSection(Section section);

	public void visitParagraph(Paragraph paragraph);

	public void visitDocument(Document document);

}