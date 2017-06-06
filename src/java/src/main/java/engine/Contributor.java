package engine;

public class Contributor {
    Long id;
    String username;
    int nContribuicoes;

    public Contributor(Long id, String username) {
        this.username = username;
        this.id = id;
        nContribuicoes = 0;
    }

    public Contributor setAttr(String username, boolean inc) {
        this.username = username;
        if (inc) {
            nContribuicoes += 1;
        }

        return this;
    }

    @Override
    public String toString() {
        return "Contributor{" +
                "username='" + username + '\'' +
                ", id=" + id +
                ", nContribuicoes=" + nContribuicoes +
                '}';
    }

    public String getUsername() {
        return username;
    }
    public long getId() {
        return id;
    }
    public int getnContribuicoes() {
        return nContribuicoes;
    }

}
