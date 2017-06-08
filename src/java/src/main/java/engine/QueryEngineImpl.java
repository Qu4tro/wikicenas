package engine;

import li3.Interface;

import java.util.ArrayList;
import java.util.SortedSet;
import java.util.stream.Collectors;

public class QueryEngineImpl implements Interface {

    Result result;

    public void init() {
        result = new Result();
    }

    public void load(int nsnaps, ArrayList<String> snaps_paths) {
        assert snaps_paths.size() == nsnaps : "Lied on number of backups";
        Parser.parse(snaps_paths, result);
        result.postProcess();
    }

    public long all_articles() {
        return result.getPagesRead();
    }

    public long unique_articles() {
        return (long) result.getPageHashMap().size();
    }

    public long all_revisions() {
        return (long) result.getRevisionHashMap().size();
    }

    public ArrayList<Long> top_10_contributors() {
        return result.getContributorsByContributions().stream()
                                                      .limit(10)
                                                      .map(c -> c.getId())
                                                      .collect(Collectors.toCollection(ArrayList::new));
    }

    public String contributor_name(long contributor_id) {
        Long id = new Long(contributor_id);
        return result.getContributorHashMap().get(id).getUsername();
    }

    public ArrayList<Long> top_20_largest_articles() {
        return result.getPageByBytes().stream()
                .limit(20)
                .map(p -> p.getId())
                .collect(Collectors.toCollection(ArrayList::new));
    }

    public String article_title(long article_id) {
        Long id = new Long(article_id);
        return result.getPageHashMap().get(id).getTitle();
    }

    public ArrayList<Long> top_N_articles_with_more_words(int n) {
        return result.getPageByWords().stream()
                .limit(n)
                .map(Page::getId)
                .collect(Collectors.toCollection(ArrayList::new));
    }

    public ArrayList<String> titles_with_prefix(String prefix) {
        SortedSet<String> titles = result.getTitlesByName();
        SortedSet<String> fromFirstPrefix = titles.tailSet(prefix);
        String end = fromFirstPrefix.stream()
                                    .filter(c -> !c.startsWith(prefix))
                                    .findFirst()
                                    .orElse(titles.last());

        return new ArrayList<>(fromFirstPrefix.headSet(end));
    }

    public String article_timestamp(long article_id, long revision_id) {
        Long id = revision_id;
        return result.getRevisionHashMap().get(id).getTimestamp();
    }

    public void clean() {
        result = new Result();
    }
}
