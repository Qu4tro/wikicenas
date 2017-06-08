package engine;

import java.util.*;
import java.util.stream.Collectors;

import static java.util.Comparator.comparingInt;
import static java.util.Comparator.comparingLong;


public class Result {

    private long pagesRead;
    private Map<Long, Page> pageHashMap;
    private Map<Long, Revision> revisionHashMap;
    private Map<Long, Contributor> contributorHashMap;
    private SortedSet<String> titlesByName;
    private SortedSet<Contributor> contributorsByContributions;
    private SortedSet<Page> pageByWords;
    private SortedSet<Page> pageByBytes;


    public Result(){
        pagesRead = 0;
        pageHashMap = new HashMap<>();
        revisionHashMap = new HashMap<>();
        contributorHashMap = new HashMap<>();

        titlesByName = new TreeSet<>();
        contributorsByContributions = new TreeSet<>(comparingInt(Contributor::getnContribuicoes).reversed());
        pageByWords = new TreeSet<>(comparingLong(Page::getnWords).reversed());
        pageByBytes = new TreeSet<>(comparingLong(Page::getnBytes).reversed());
    }

    public void addPage(Long id, String pTitle, long nb, long nw){
        Page p;
        p = Optional.ofNullable(pageHashMap.get(id))
                                           .map(in -> in.setAttr(pTitle, nb, nw))
                                           .orElse(new Page(id, pTitle, nb, nw));
        pageHashMap.put(id, p);
        pagesRead += 1;
    }
    public void addRevision(Long id, String timestamp){
        Revision r;
        r = Optional.ofNullable(revisionHashMap.get(id))
                                               .map(in -> in.setAttr(timestamp))
                                               .orElse(new Revision(id, timestamp));
        revisionHashMap.put(id, r);
    }
    public void addContributor(Long id, Long revision_id, String username){
        Contributor c;
        boolean increment = !revisionHashMap.containsKey(revision_id);
        c = Optional.ofNullable(contributorHashMap.get(id))
                                                  .map(in -> in.setAttr(username, increment))
                                                  .orElse(new Contributor(id, username));
        contributorHashMap.put(id, c);
    }

    public void postProcess(){
        pageByBytes.addAll(pageHashMap.values());
        pageByWords.addAll(pageHashMap.values());
        contributorsByContributions.addAll(contributorHashMap.values());
        titlesByName.addAll(pageHashMap.values()
                                       .stream()
                                       .map(Page::getTitle)
                                       .collect(Collectors.toSet()));
    }

    public Map<Long, Page> getPageHashMap() {
        return pageHashMap;
    }

    public Map<Long, Revision> getRevisionHashMap() {
        return revisionHashMap;
    }

    public Map<Long, Contributor> getContributorHashMap() {
        return contributorHashMap;
    }

    public long getPagesRead() {
        return pagesRead;
    }

    public SortedSet<Contributor> getContributorsByContributions() {
        return contributorsByContributions;
    }

    public SortedSet<Page> getPageByWords() {
        return pageByWords;
    }

    public SortedSet<Page> getPageByBytes() {
        return pageByBytes;
    }

    public SortedSet<String> getTitlesByName() {
        return titlesByName;
    }
}
