package edt.editor;

import java.util.Map;
import java.util.TreeMap;
import java.util.List;
import java.util.ArrayList;

public class Document extends Section{
	private int _dimension; 
	private Map<String, Author> _authors = new TreeMap<String, Author>();
	private Map<String, TextElement> _tElements = new TreeMap<String, TextElement>();
	

	public Document(){
		super("");
		_dimension = 0;
	}
	
	public Document(String title){
		super(title);
		_dimension = 0;
	}

	//Authors Operations.

	public List<Author> getAuthors(){
		List<Author> authors = new ArrayList<Author>();

		for(Author a : _authors.values())
			authors.add(a);
		return authors;
	}

	public int getAuthorsSize(){
		return _authors.size();
	}

	public boolean addAuthor(String name, String email){
		if(_authors.get(name) == null){
			Author author = new Author(name, email);
			_authors.put(name, author);
			return true;
		}
		return false;
	}

	//TextElements Operations.

	public Section getSection(String iD){
		List<Section> subSection = getSubSections();
		for (Section s : subSection){
			if(s.getId() == iD)
				return s;
		}
		return null;
	}

	public TextElement getSpecificTextElement(String id){
		return _tElements.get(id);
	}

	public int getTextElementsSize(){
		return _tElements.size();
	}

	public void addTextElement(String iD, TextElement textelement){
		_tElements.put(iD, textelement);
	}

	public void removeTextElement(String id){
		_tElements.remove(id);
	}

	public boolean nameTextElement(Section s, String id, int localId, boolean type){
		TextElement t;
		//True if TextElement is a section.
		if(type == true) 
			t = s.getSpecificSection(localId);
		//False if TextElement is a paragraph.
		else 
			t = s.getSpecificParagraph(localId);
		if(!id.equals("")){
			//If the TextElement already exists in _telements
			if(_tElements.containsValue(t)){
				_tElements.remove(t.getId());
				t.setId(id);
				_tElements.put(id, t);
				return true;
			}
			else{
				//If the key already exists in _telements
				if(_tElements.containsKey(id)){
					_tElements.get(id).setId("");
					_tElements.remove(id);
					t.setId(id);
					_tElements.put(id, t);
				}
				//If neither the TextElement nor the key exist in _telements
				else{
					t.setId(id);
					_tElements.put(id, t);
				}
				return false;
			}
		}
		return false;
	}

	public void accept(Visitor v){
		v.visitDocument(this);
	}
}