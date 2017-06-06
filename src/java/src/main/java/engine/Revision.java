package engine;

public class Revision {

    private Long id;
    private String timestamp;

    public Revision(Long id, String timestamp) {
        this.id = id;
        this.timestamp = timestamp;
    }

    public Revision setAttr(String timestamp){
        this.timestamp = timestamp;
        return this;
    }

    public String getTimestamp() {
        return timestamp;
    }
}
