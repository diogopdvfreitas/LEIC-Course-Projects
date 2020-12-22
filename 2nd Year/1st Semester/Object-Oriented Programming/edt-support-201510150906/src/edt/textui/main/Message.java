package edt.textui.main;

/**
 * Messages for main menu interactions.
 */
@SuppressWarnings("nls")
public class Message {

  /**
   * @return string with prompt for filename to open.
   */
  public static final String openFile() {
    return "Ficheiro a abrir: ";
  }

  /**
   * @return string with "file not found" message.
   */
  public static final String fileNotFound() {
    return "O ficheiro não existe.";
  }

  /**
   * @param filename
   * @return string with "file not found" message (more elaborate).
   */
  public static final String fileNotFound(String filename) {
    return "O ficheiro '" + filename + "' não existe.";
  }

  /**
   * @return string with a warning and a question.
   */
  public static final String newSaveAs() {
    return "Ficheiro sem nome. " + saveAs();
  }

  /**
   * @return string asking for a filename.
   */
  public static final String saveAs() {
    return "Guardar ficheiro como: ";
  }

  /**
   * @return string confirming that user wants to save.
   */
  public static final String saveBeforeExit() {
    return "Guardar antes de fechar? ";
  }

  /**
   * @param documentTitle
   * @return string for presenting the document's title
   */
  public static String documentTitle(String documentTitle) {
    return "Título: " + documentTitle;
  }

  /**
   * @param name
   * @param email
   * @return string for presenting author information
   */
  public static String author(String name, String email) {
    return "Autor: " + name + "/" + email;
  }

  /**
   * @param numberOfTopLevelSections
   * @return string for presenting document sections
   */
  public static String documentSections(int numberOfTopLevelSections) {
    return "Secções de topo: " + numberOfTopLevelSections;
  }

  /**
   * @param size
   * @return string for presenting document size in bytes
   */
  public static String documentBytes(int size) {
    return "Dimensão do documento (bytes): " + size;
  }

  /**
   * @param name
   * @param title
   * @return string for presenting section index entry
   */
  public static String sectionIndexEntry(String name, String title) {
    return "[" + name + "] {" + title + "}";
  }

  /**
   * @return prompt for author name
   */
  public static String requestAuthorName() {
    return "Nome do autor: ";
  }

  /**
   * @return prompt for author email
   */
  public static String requestEmail() {
    return "Email do autor: ";
  }

  /**
   * @param name
   * @return status message for duplicate author
   */
  public static String duplicateAuthor(String name) {
    return "O autor '" + name + "' já existe.";
  }

  /**
   * @param nIdentifiers
   * @return string for presenting number of identifiers in document
   */
  public static String documentIdentifiers(int nIdentifiers) {
    return "Identificadores únicos: " + nIdentifiers;
  }

  /**
   * @return prompt for text element name
   */
  public static String requestElementId() {
    return "Identificador do elemento de texto: ";
  }

  /**
   * @param id
   * @return status message for missing id
   */
  public static String noSuchTextElement(String id) {
    return "O elemento de texto '" + id + "' não existe.";
  }

}