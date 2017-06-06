package engine;

public class Page {

    private Long id;
    private String title;

    private long nBytes;
    private long nWords;

    public Page() {

    }

    public Page(Long id, String title, long nBytes, long nWords) {
        this.id = id;
        this.title = title;
        this.nBytes = nBytes;
        this.nWords = nWords;
    }

    public Page setAttr(String title, long nb, long nw){
        this.title = title;
        nBytes = Math.max(nBytes, nb);
        nWords = Math.max(nWords, nw);

        return this;
    }

    @Override
    public String toString() {
        return "Page{" +
                "id=" + id +
                ", title='" + title + '\'' +
                ", nBytes=" + nBytes +
                ", nWords=" + nWords +
                '}';
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public long getnBytes() {
        return nBytes;
    }

    public void setnBytes(int nBytes) {
        this.nBytes = nBytes;
    }

    public long getnWords() {
        return nWords;
    }

    public void setnWords(int nWords) {
        this.nWords = nWords;
    }
}
