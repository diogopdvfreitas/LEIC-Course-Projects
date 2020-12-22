package edt.editor;

import java.util.List;
import java.util.ArrayList;

/**
 * Sections have subsections and paragraphs
 * 
 */

public class Section extends TextElement{

	/** Section Title. */
	private String _title;

	/** Paragraphs. */
	private List<Paragraph> _paragraphs = new ArrayList<Paragraph>();

	/** Subsections. */
	private List<Section> _subSections = new ArrayList<Section>();
	
	/**
	 * @param title
	 *            section name.
	 */
	public Section(String title){
		super("");
		_title = title;
	}

	/**
	 * @param iD
	 * 			  section unique iD.           
	 * @param title
	 *			  section name.
	 */
	public Section(String iD, String title){
		super(iD);
		_title = title;
	}

	/**
	 * @return the title of the section.
	 */

	public String getTitle(){
		return _title;
	}

	/**
	 * @param title
	 *            the title of the section.
	 */

	public void setTitle(String title){
		_title = title;
	}

	//Subsections Operations.

	/**
	 * @return the list of subsections.       
	 */

	public List<Section> getSubSections(){
		return _subSections;
	}

	/**
	 * @return the number of subsections of the current section.       
	 */

	public int getSubSectionsSize(){
		return _subSections.size();
	}

	/**
	* @param local id
	*
	* @return the section of the list of subsections
	*/

	public Section getSpecificSection(int localID){
		return _subSections.get(localID);
	}

		/**
	* @return a list with all the existing sections id's and titles. 
	*/

	public List<String> listSubSections(){
		List<String> sections = new ArrayList<String>();
		for (Section s : _subSections){
			sections.add(s.getId());
			sections.add(s.getTitle());
			sections.addAll(s.listSubSections());			
		}
		return sections;
	}

	/**
	 * Add a section in a specific position of the list of subsections.
	 *
	 * @param localID
	 * 				reference(position) in the list of subsections to put the section. 
	 * @param section
	 *				section to add.	       
	 */

	public Section insertSection(int localID, String uniqueID, String title){
		Section s = new Section(uniqueID, title);
		if((localID <= -1) || (localID >= _subSections.size()))
			_subSections.add(s);
		else
			_subSections.add(localID, s);
		return s;
	}

	/**
	*Remove a section of the list of subsection.
	*
	* @param localID
	*				reference(position) in the list of subsections.
	*/

	public void removeSection(int localId, Document document){
		Section x = _subSections.get(localId);
		String uniqueId = "";
		
		//Removes the subsections of the section from the list and in case the have an unique Id, removes them form _telements
		for(Section s : x.getSubSections()){
			uniqueId = s.getId();
			if(!uniqueId.equals(""))
				document.removeTextElement(uniqueId);
			s.removeSection(localId ,document);
		}
		//Removes the paragraphs of the section from _telements in case they have an unique Id
		for(Paragraph p : x.getParagraphs()){
			uniqueId = p.getId();
			if(!p.getId().equals(""))
				document.removeTextElement(uniqueId);
		}
		//Remove a seccao da lista e caso tenha uniqueId remove a do _telements
		//Removes the section from the list and in case it has an unique Id, removes it from _telements
		uniqueId = x.getId();
		if(!uniqueId.equals(""))
			document.removeTextElement(uniqueId);
		_subSections.remove(localId);
	}	

	/**
	 * @return the list of paragraphs.       
	 */

	//Paragraphs Operations.

	public List<Paragraph> getParagraphs(){
		return _paragraphs;
	}

	/**
	* @return the number of paragraphs of the current section
	*/

	public int getParagraphsSize(){
		return _paragraphs.size();
	}

	/**
	* @param local id
	*
	* @return the paragraph of the list of paragraphs
	*/

	public Paragraph getSpecificParagraph(int localID){
		return _paragraphs.get(localID);
	}

		/**
	*Add a paragraph in a specific position of the list of paragraphs.
	*
	* @param localID
	*				reference(position) in the list of paragraphs.
	* @param content
	*				of the new paragraph.
	*/

	public void addParagraph(int localID, String content){
		Paragraph p = new Paragraph(content);
		if((localID <= -1) || (localID >= _paragraphs.size()))
			_paragraphs.add(p);
		else
			_paragraphs.add(localID, p);
	}

	/**
	*Remove a paragraph of the list of paragraphs.
	*
	* @param localID
	*				reference(position) in the list of paragraphs.
	*/

	public void removeParagraph(int localId, Document document){
		String uniqueId = getSpecificParagraph(localId).getId();
		if(!uniqueId.equals(""))
      		document.removeTextElement(uniqueId);
 		_paragraphs.remove(localId);
	}

	/**
	*Change the content of a paragraph.
	*
	* @param localID
	*				reference(position) in the list of subsections.
	* @param content
	*				new content. 
	*/

	public void editParagraph(int localID, String content){
		_paragraphs.get(localID).setContent(content);
	}

	/**
	 * @return the size of all subsections(number of characters) of the section.       
	 */

	public int getTotalSize(){
		int total = _title.length();
		for(Paragraph p : _paragraphs)
			total += p.getParagraphSize();
		for(Section s : _subSections)
			total += s.getTotalSize();
		return total; 
	}

	/**
	*Accept a visitor and visit a section.
	*
	* @param v
	*				Visitor to visit a section.
	*/

	public void accept(Visitor v){
		v.visitSection(this);
	}
}