package edt.editor;

import java.io.IOException;
import java.io.FileNotFoundException;

import java.io.BufferedReader;
import java.io.FileReader;

import java.io.ObjectOutputStream;
import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
 
import java.io.ObjectInputStream;
import java.io.BufferedInputStream;
import java.io.FileInputStream;

import java.util.Map;
import java.util.List;
import java.util.ArrayList;

public class Editor{
	private Document _doc;
	private String _filename;

	public Document getDocument(){
		return _doc;
	}

	public String getFileName(){
		return	_filename;
	}

	public boolean addDocumentAuthor(String name, String email){
		return _doc.addAuthor(name, email);
	}

	public void acceptDocument(Visitor v){
		_doc.accept(v);
	}

	public boolean acceptTextElement(Visitor v, String id){
		TextElement t = _doc.getSpecificTextElement(id);
		if(t != null){
			t.accept(v);
			return true;
		}
		return false;
	}

	public void create(){
		_doc = new Document();
		_filename = null;
	}

	public void open(String filename) throws IOException, FileNotFoundException{
		//Reads the document from memory
		try{
			ObjectInputStream ois = new ObjectInputStream(new BufferedInputStream(new FileInputStream(filename)));
			_doc = (Document)ois.readObject();
			_filename = filename;
			ois.close();
		}
		catch(ClassNotFoundException e){
			e.printStackTrace();
		}
	}

	public void save(String filename) throws IOException, FileNotFoundException{
	    //Saves the document in memory
		ObjectOutputStream oos = new ObjectOutputStream(new BufferedOutputStream(new FileOutputStream(filename)));
	    _filename = filename;
	    oos.writeObject(_doc);
	    oos.close();
	}

	public void importData(String filename) throws IOException{
		
		BufferedReader reader = new BufferedReader(new FileReader(filename));
		
		//Add Title
		_doc.setTitle(reader.readLine());

		//Add authors
		String authors = reader.readLine();
		for(String author : authors.split("\\|")){
			String [] str = author.split("\\/");
			_doc.addAuthor(str[0], str[1]);
		}

		//Set Content
		String line;
		String uniqueId = null;
		while((line = reader.readLine()) != null){
			String[] content = line.split("\\|");
			Section sec;
			switch(content[0]){
				case "SECTION":
					uniqueId = content[1];
					sec = _doc.insertSection(-1, uniqueId, content[2]);
					if(!uniqueId.equals(""))
						_doc.addTextElement(uniqueId, sec);
					break;

				case "PARAGRAPH":
					if (uniqueId != null){
						sec = _doc.getSection(uniqueId);
						sec.addParagraph(-1, content[1]);
					}
					else{
						_doc.addParagraph(-1, content[1]);
					}
					break;

				default:
					System.err.println("Error importing content");//????
			}
		}
	}
}