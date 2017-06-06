package engine;

import java.io.File;
import java.util.List;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

public class Parser {
    public static void parse(List<String> filenames, Result result){
        Handler handler = new Handler(result);
        for(String filename: filenames) {
            try {
                File inputFile = new File(filename);
                SAXParserFactory factory = SAXParserFactory.newInstance();
                SAXParser saxParser = factory.newSAXParser();
                saxParser.parse(inputFile, handler);

            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}

enum ParserState {
    PAGE, PAGE_ID, PAGE_TITLE, PAGE_TEXT,
    REVISION, REVISION_ID, REVISION_TIMESTAMP,
    CONTRIBUTOR_ID, CONTRIBUTOR_USERNAME;
}

class Handler extends DefaultHandler {

    private StringBuilder characters;
    private ParserState state;
    private Result result;

    private Long page_id;
    private String page_title;
    private Long revision_id;
    private String revision_timestamp;
    private Long contributor_id;
    private String contributor_username;

    private long nBytes, nWords;
    private boolean inWord;

    public Handler(Result r){
        characters = new StringBuilder();
        result = r;
        inWord = false;
    }

    @Override
    public void startElement(String uri, String ln, String elemName, Attributes attr) throws SAXException {
        switch (elemName){
            case "id":
                switch (state){
                    case PAGE_TITLE:
                        state = ParserState.PAGE_ID;
                        break;
                    case PAGE_ID:
                        state = ParserState.REVISION_ID;
                        break;
                    case CONTRIBUTOR_USERNAME:
                        state = ParserState.CONTRIBUTOR_ID;
                        break;
                }
                break;
            case "username":
                state = ParserState.CONTRIBUTOR_USERNAME;
                break;
            case "title":
                state = ParserState.PAGE_TITLE;
                break;
            case "timestamp":
                state = ParserState.REVISION_TIMESTAMP;
                break;
            case "text":
                state = ParserState.PAGE_TEXT;
                break;
        }
    }

    @Override
    public void endElement(String uri, String ln, String elemName) throws SAXException {
        final String content = characters.toString();
        switch (elemName){
            case "id":
                switch (state){
                    case PAGE_TITLE:
                        page_id = Long.parseLong(content);
                        break;
                    case PAGE_ID:
                        revision_id = Long.parseLong(content.trim());
                        break;
                    case CONTRIBUTOR_USERNAME:
                        contributor_id = Long.parseLong(content);
                        break;
                }
                break;
            case "title":
                page_title = content;
            case "timestamp":
                revision_timestamp = content;
            case "username":
                contributor_username = content;
            case "page":
                result.addPage(page_id, page_title, nBytes, nWords);
                nBytes = 0;
                nWords = 0;
                break;
            case "revision":
                result.addRevision(revision_id, revision_timestamp);
                break;
            case "contributor":
                result.addContributor(contributor_id, revision_id, contributor_username);
                break;
        }
        characters.setLength(0);
    }

    boolean space(char c){
        return (c == ' ' || c == '\n' || c == '\t');
    }

    @Override
    public void characters(char ch[], int start, int length) throws SAXException {
        if (state == ParserState.PAGE_TEXT) {
            nBytes += length;
            for (int i = 0; i < length; i++) {
                if (!inWord && !space(ch[start + i])) {
                    inWord = true;
                    nWords += 1;
                }
                if (inWord && space(ch[start + i])) {
                    inWord = false;
                }
            }
        } else {
            String str = new String(ch, start, length);
            characters.append(str);
        }
    }

    public Result getResult() {
        return result;
    }
}
