package edt.textui.section;

/** Messages for user management menu interactions. */
@SuppressWarnings("nls")
public class Message {

  /**
   * @param name
   * @param title
   * @return string for presenting section index entry
   */
  public static String sectionIndexEntry(String name, String title) {
    return "[" + name + "] {" + title + "}";
  }

  /**
   * @return prompt for section identifier
   */
  public static String requestSectionId() {
    return "Identificador da secção: ";
  }

  /**
   * @param localId
   * @return status message for new section.
   */
  public static String newActiveSection(int localId) {
    return "Nova secção activa: '" + localId + "'.";
  }

  /**
   * @return prompt for section title.
   */
  public static String requestSectionTitle() {
    return "Título da secção: ";
  }

  /**
   * @param name
   * @return return error message for unknown section
   */
  public static String noSuchSection(int name) {
    return "A secção '" + name + "' não existe.";
  }

  /**
   * @param name
   * @return return error message for unknown section
   */
  public static String noSuchSection(String name) {
    return "A secção '" + name + "' não existe.";
  }

  /**
   * @param name
   * @return status message for duplicate section
   */
  public static String duplicateSectionName(String name) {
    return "A secção '" + name + "' já existe.";
  }

  /**
   * @return prompt for paragraph identifier
   */
  public static String requestParagraphId() {
    return "Número do parágrafo: ";
  }

  /**
   * @return prompt for paragraph content
   */
  public static String requestParagraphContent() {
    return "Conteúdo do parágrafo: ";
  }

  /**
   * @param pix
   * @return error message for unknown paragraph
   */
  public static String noSuchParagraph(int pix) {
    return "O parágrafo '" + pix + "' não existe.";
  }

  /**
   * @return prompt for a format B(old) I(talic) N(ormal)
   */
  public static String requestParagraphFormat() {
    return "Formato a aplicar? (B - negrito, I - itálico, N - normal) ";
  }

  /**
   * @return status message for section naming.
   */
  public static String sectionNameChanged() {
    return "O nome da secção foi alterado.";
  }

  /**
   * @return status message for section naming.
   */
  public static String paragraphNameChanged() {
    return "O nome do parágrafo foi alterado.";
  }

  /**
   * @return prompt for unique identifier
   */
  public static String requestUniqueId() {
    return "Identificador único: ";
  }

}
