package edt.editor;

public class Paragraph extends TextElement{
	private String _content = "";

	public Paragraph(String content){
		super("");
		_content = content;
	}

	public Paragraph(String iD, String content){
		super(iD);
		_content = content;
	}

	public String getContent(){
		return _content;
	}

	public void setContent(String content){
		_content = content;
	}

	public int getParagraphSize(){
		return _content.length();
	}

	public void accept(Visitor v){
		v.visitParagraph(this);
	}
	
}